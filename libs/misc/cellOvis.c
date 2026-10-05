/*
 * ps3recomp - cellOvis HLE implementation
 *
 * Stub. Init/term work, overlay creation succeeds as no-op.
 */

#include "cellOvis.h"
#include <stdio.h>
#include "../../runtime/ppu/ppu_memory.h"   /* vm_write*: guest EA -> host, byte-swapped */

/* Internal state */

static int s_initialized = 0;
static u32 s_next_handle = 1;

/* API */

s32 cellOvisInit(void)
{
    printf("[cellOvis] Init()\n");
    if (s_initialized)
        return (s32)CELL_OVIS_ERROR_ALREADY_INITIALIZED;
    s_initialized = 1;
    s_next_handle = 1;
    return CELL_OK;
}

s32 cellOvisTerm(void)
{
    printf("[cellOvis] Term()\n");
    s_initialized = 0;
    return CELL_OK;
}

/* Firmware signature: s32 cellOvisGetOverlayTableSize(const char* elf) -- the
 * table size IS the return value; there is no out-param and no Init call in
 * front of it (cellOvisInit is not a firmware export). The old version wanted
 * a second pointer and an Init, so titles got CELL_OVIS_ERROR_NOT_INITIALIZED
 * (0x80410785) back as the "size": Drakengard 3 malloc'd 2 GB off it and died
 * in FMallocPS3DL OOM. We load no PPU overlays, so the table is empty. */
s32 cellOvisGetOverlayTableSize(const char* elf)
{
    (void)elf;
    printf("[cellOvis] GetOverlayTableSize() -> 0\n");
    return 0;
}

s32 cellOvisInitializeOverlayTable(void* ea_ovly_table, const char* elf)
{
    (void)ea_ovly_table; (void)elf;
    printf("[cellOvis] InitializeOverlayTable()\n");
    return CELL_OK;
}

s32 cellOvisCreateOverlay(const void* table, u32 tableSize, CellOvisHandle* handle)
{
    (void)table; (void)tableSize;
    if (!s_initialized) return (s32)CELL_OVIS_ERROR_NOT_INITIALIZED;
    if (!handle) return (s32)CELL_OVIS_ERROR_INVALID_ARGUMENT;
    vm_write32((u32)(uintptr_t)handle, (u32)s_next_handle++);
    return CELL_OK;
}

s32 cellOvisDestroyOverlay(CellOvisHandle handle)
{
    (void)handle;
    if (!s_initialized) return (s32)CELL_OVIS_ERROR_NOT_INITIALIZED;
    return CELL_OK;
}

s32 cellOvisInvalidateOverlay(CellOvisHandle handle)
{
    (void)handle;
    if (!s_initialized) return (s32)CELL_OVIS_ERROR_NOT_INITIALIZED;
    return CELL_OK;
}
