#pragma once

#include "common.h"
#include "exefs.h"

// start sector of the essential backup in NAND
// careful with this, essential backup should never reach sector 0x96
#define ESSENTIAL_SECTOR 0x1

// magic number for essential backup
#define ESSENTIAL_MAGIC 'n', 'a', 'n', 'd', '_', 'h', 'd', 'r', 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00

// /rw/sys/LocalFriendCodeSeed_B (/_A) file
// see: http://3dbrew.org/wiki/Nandrw/sys/LocalFriendCodeSeed_B
typedef struct {
    u8 signature[0x100];
    u8 unknown[0x8]; // normally zero
    u8 codeseed[0x8]; // the actual data
} __attribute__((packed)) LocalFriendCodeSeed;

// /private/movable.sed file
// see: http://3dbrew.org/wiki/Nand/private/movable.sed
typedef struct {
    u8 magic[0x4]; // "SEED"
    u8 indicator[0x4]; // uninitialized all zero, otherwise u8[1] nonzero  
    LocalFriendCodeSeed codeseed_data;
    u8 keyy_high[8];
    u8 unknown[0x10];
    u8 cmac[0x10];
} __attribute__((packed)) MovableSed;

// /rw/sys/Secure_A (/_B) file
// see: http://3dbrew.org/wiki/Nandrw/sys/SecureInfo_A
typedef struct {
    u8 signature[0x100];
    u8 region;
    u8 unknown;
    char serial[0xF];
} __attribute__((packed)) SecureInfo;

// includes all essential system files
// (this is of our own making)
typedef struct {
    ExeFsHeader header;
    u8 nand_hdr[0x200];
    SecureInfo secinfo;
    u8 padding_secinfo[0x200 - sizeof(SecureInfo)];
    MovableSed movable;
    u8 padding_movable[0x200 - sizeof(MovableSed)];
    LocalFriendCodeSeed frndseed;
    u8 padding_frndseed[0x200 - sizeof(LocalFriendCodeSeed)];
} __attribute__((packed)) EssentialBackup;
