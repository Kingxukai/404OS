#ifndef _PLATFORM_H__
#define _PLATFORM_H__

#define PLATFORM "virt"
#define ARCH "RISC-V"

#define CPU_NUM 2

#define MPIE (1<<7)			//control machine previous interrupt enable


/*UART*/
#define UART0 0x10000000L


/*PLIC*/
#define PLIC_BASE 0X0C000000L	
#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_MENABLE(hart) (PLIC_BASE + 0x2000 + (hart) * 0x80)
#define PLIC_MTHRESHOLD(hart) (PLIC_BASE + 0x200000 + (hart) * 0x1000)
#define PLIC_MCLAIM(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)
#define PLIC_MCOMPLETE(hart) (PLIC_BASE + 0x200004 + (hart) * 0x1000)


/*CLIENT*/
#define CLIENT_BASE 0X2000000L	
#define CLIENT_MTIMER (CLIENT_BASE + 0XBFF8)
#define CLIENT_MTIMERCMP(hart) (CLIENT_BASE + 0x4000 + 8 * (hart))


/*MMIO*/
#define MMIO_BASE 40000000L	
#define MAGIC_VALUE MMIO_BASE + 0x000	//a Little Endian equivalent of the “virt” string
#define DEVICE_VESION MMIO_BASE + 0x004	//value of 0x2
#define DEVICE_ID MMIO_BASE + 0x008	//Value zero (0x0) is used to de-fine a system memory map with placeholder devices at static, well knownaddresses, assigning functions to them depending on user’s needs.
#define Device_Features MMIO_BASE + 0x010	//Flags representing features the device supports
#define Device_Features_Sel	MMIO_BASE + 0x014	//Device (host) features word selection.
#define Driver_Features	MMIO_BASE + 0X020	//Flags representing device features understood and activated by the driver
#define Driver_Features_Sel	MMIO_BASE + 0x024	//Activated (guest) features word selection

#define Queue_Sel MMIO_BASE + 0x030	//Virtual queue index	
#define Queue_Num_Max	MMIO_BASE + 0x034	//Maximum virtual queue size
#define Queue_Num	MMIO_BASE + 0x038	//Virtual queue size
#define Queue_Ready MMIO_BASE + 0x044	//Virtual queue ready bit
#define Queue_Notify MMIO_BASE + 0x050	//Queue notifier

#define Interrupt_Status MMIO_BASE + 0x060	//Interrupt status
#define Interrupt_ACK	MMIO_BASE + 0X064	//Interrupt acknowledge
#define Device_status	MMIO_BASE + 0X070

#define Queue_Desc_Low MMIO_BASE + 0x080	//Virtual queue’s Descriptor Area 64 bit long physical address
#define Queue_Desc_Hign MMIO_BASE + 0x084
#define Queue_Driver_Low MMIO_BASE + 0x090	//Virtual queue’s Driver Area 64 bit long physical address
#define Queue_Driver_High MMIO_BASE +0x094
#define Queue_Device_Low MMIO_BASE + 0x0a0	//Virtual queue’s Device Area 64 bit long physical address
#define Queue_Device_Hign MMIO_BASE + 0x0a4

#define Config_Generation MMIO_BASE + 0X0fc	//Configuration atomicity value
#define Config MMIO_BASE + 0X100	//Configuration space


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
