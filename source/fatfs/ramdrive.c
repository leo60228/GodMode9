#include "ramdrive.h"
#include "unittype.h"

static u8* ramdrv_buffer = NULL;
static u32 ramdrv_size = 0;

int ReadRamDriveSectors(u8* buffer, u32 sector, u32 count) {
    u64 offset = sector * 0x200;
    u64 btr = count * 0x200;
    if (!ramdrv_buffer) return -1;
    if ((offset + btr) > ramdrv_size) return -1;
    memcpy(buffer, ramdrv_buffer + offset, btr);
    return 0;
}
int WriteRamDriveSectors(const u8* buffer, u32 sector, u32 count) {
    u64 offset = sector * 0x200;
    u64 btw = count * 0x200;
    if (!ramdrv_buffer) return -1;
    if ((offset + btw) > ramdrv_size) return -1;
    memcpy(ramdrv_buffer + offset, buffer, btw);
    return 0;
}

u64 GetRamDriveSize(void) {
    return ramdrv_size;
}

void InitRamDrive(void) {
    if (IS_O3DS) {
        ramdrv_buffer = RAMDRV_BUFFER_O3DS;
        ramdrv_size = RAMDRV_SIZE_O3DS;
    } else {
        ramdrv_buffer = RAMDRV_BUFFER_N3DS;
        ramdrv_size = RAMDRV_SIZE_N3DS;
    }
}