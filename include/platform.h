#ifndef _PLATFORM_H__
#define _PLATFORM_H__

#define PLATFORM "virt"
#define ARCH "RISC-V"

#define CPU_NUM 2

#define MPIE (1<<7)			//control machine previous interrupt enable

#define PLIC_BASE 0X0C000000L
#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_MENABLE(hart) (PLIC_BASE + 0x2000 + (hart) * 0x80)
#define PLIC_MTHRESHOLD(hart) (PLIC_BASE + 0x200000 + (hart) * 0x1000)
#define PLIC_MCLAIM(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)
#define PLIC_MCOMPLETE(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)

#define CLIENT_BASE 0X2000000L
#define CLIENT_MTIMER (CLIENT_BASE + 0XBFF8)
#define CLIENT_MTIMERCMP(hart) (CLIENT_BASE + 0x4000 + 8 * (hart))

/*struct _Memmap_Entry _virt_memmap[] = 
{
    [_VIRT_DEBUG]      = _VIRT_MEMMAP_ENTRY(0x0,          0x100),
    [_VIRT_MROM]       = _VIRT_MEMMAP_ENTRY(0x1000,       0xf000),
    [_VIRT_TEST]       = _VIRT_MEMMAP_ENTRY(0x100000,     0x1000),
    [_VIRT_RTC]        = _VIRT_MEMMAP_ENTRY(0x101000,     0x1000),
    [_VIRT_CLINT]      = _VIRT_MEMMAP_ENTRY(0x2000000,    0x10000),
    [_VIRT_PCIE_PIO]   = _VIRT_MEMMAP_ENTRY(0x3000000,    0x10000),
    [_VIRT_PLIC]       = _VIRT_MEMMAP_ENTRY(0xc000000,    0x4000000),
    [_VIRT_UART0]      = _VIRT_MEMMAP_ENTRY(0x10000000,   0x100),
    [_VIRT_VIRTIO]     = _VIRT_MEMMAP_ENTRY(0x10001000,   0x1000),
    [_VIRT_FLASH]      = _VIRT_MEMMAP_ENTRY(0x20000000,   0x4000000),
    [_VIRT_PCIE_ECAM]  = _VIRT_MEMMAP_ENTRY(0x30000000,   0x10000000),
    [_VIRT_PCIE_MMIO]  = _VIRT_MEMMAP_ENTRY(0x40000000,   0x40000000),
    [_VIRT_DRAM]       = _VIRT_MEMMAP_ENTRY(0x80000000,   0x0)
};*/

#endif
