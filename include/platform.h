#ifndef _PLATFORM_H__
#define _PLATFORM_H__

#define PLATFORM "virt"
#define ARCH "RISC-V"

#define CPU_NUM 2

#define SPIE (1<<5)			//control s-mode previous interrupt enable

#define ADDR(addr) *((uint32_t *)addr)

/*VIRT_TEST*/
#define SYS_CTL_ADDR 0x100000
#define SYS_FAIL 0
#define SYS_PASS 1
#define SYS_RESET 2
#define SYS_CTL(n) (0x3333 + n * 0x2222)

/*IRQ*/
#define UART0_IRQ 10
#define VIRTIO0_IRQ 1

/*UART*/
#define UART0 0x10000000L


/*PLIC*/
#define PLIC_BASE 0X0C000000L	
#define PLIC_PRIORITY(id) (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id) (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_SENABLE(hart) (PLIC_BASE  + 0x2000 + 0x80 + (hart) * 0x80)
#define PLIC_STHRESHOLD(hart) (PLIC_BASE  + 0x200000 + 0x1000 + (hart) * 0x1000)
#define PLIC_SCLAIM(hart) (PLIC_BASE  + 0x200004 + 0x1000 + (hart) * 0x1000)
#define PLIC_SCOMPLETE(hart) (PLIC_BASE  + 0x200004 + 0x1000 + (hart) * 0x1000)


/*CLIENT*/
#define CLIENT_BASE 0X2000000L	
#define CLIENT_MTIMER (CLIENT_BASE + 0XBFF8)
#define CLIENT_MTIMERCMP(hart) (CLIENT_BASE + 0x4000 + 8 * (hart))


/*VIRTIO*/
#define VIRTIO_BASE 0x10001000L	
#define MAGIC_VALUE           (VIRTIO_BASE + 0x000) //A LITTLE ENDIAN EQUIVALENT OF THE “VIRT” STRING
#define DEVICE_VERSION        (VIRTIO_BASE + 0x004) //VALUE OF 0X2
#define DEVICE_ID             (VIRTIO_BASE + 0x008) //VALUE ZERO (0X0) IS USED TO DE-FINE A SYSTEM MEMORY MAP WITH PLACEHOLDER DEVICES AT STATIC, WELL KNOWNADDRESSES, ASSIGNING FUNCTIONS TO THEM DEPENDING ON USER’S NEEDS.
#define VENDOR_ID             (VIRTIO_BASE + 0x00c) //0x554d4551

#define DEVICE_FEATURES       (VIRTIO_BASE + 0x010) //FLAGS REPRESENTING FEATURES THE DEVICE SUPPORTS
#define DEVICE_FEATURES_SEL   (VIRTIO_BASE + 0x014) //DEVICE (HOST) FEATURES WORD SELECTION.
#define DRIVER_FEATURES       (VIRTIO_BASE + 0x020) //FLAGS REPRESENTING DEVICE FEATURES UNDERSTOOD AND ACTIVATED BY THE DRIVER
#define DRIVER_FEATURES_SEL   (VIRTIO_BASE + 0x024) //ACTIVATED (GUEST) FEATURES WORD SELECTION

#define QUEUE_SEL             (VIRTIO_BASE + 0x030) //VIRTUAL QUEUE INDEX    
#define QUEUE_NUM_MAX         (VIRTIO_BASE + 0x034) //MAXIMUM VIRTUAL QUEUE SIZE
#define QUEUE_NUM             (VIRTIO_BASE + 0x038) //VIRTUAL QUEUE SIZE
#define QUEUE_READY           (VIRTIO_BASE + 0x044) //VIRTUAL QUEUE READY BIT
#define QUEUE_NOTIFY          (VIRTIO_BASE + 0x050) //QUEUE NOTIFIER

#define INTERRUPT_STATUS      (VIRTIO_BASE + 0x060) //INTERRUPT STATUS
#define INTERRUPT_ACK         (VIRTIO_BASE + 0x064) //INTERRUPT ACKNOWLEDGE
#define DEVICE_STATUS         (VIRTIO_BASE + 0x070)

#define QUEUE_DESC_LOW        (VIRTIO_BASE + 0x080) //VIRTUAL QUEUE’S DESCRIPTOR AREA 64 BIT LONG PHYSICAL ADDRESS
#define QUEUE_DESC_HIGH       (VIRTIO_BASE + 0x084)
#define QUEUE_DRIVER_LOW      (VIRTIO_BASE + 0x090) //VIRTUAL QUEUE’S DRIVER AREA 64 BIT LONG PHYSICAL ADDRESS
#define QUEUE_DRIVER_HIGH     (VIRTIO_BASE + 0x094)
#define QUEUE_DEVICE_LOW      (VIRTIO_BASE + 0x0A0) //VIRTUAL QUEUE’S DEVICE AREA 64 BIT LONG PHYSICAL ADDRESS
#define QUEUE_DEVICE_HIGH     (VIRTIO_BASE + 0x0A4)

#define CONFIG_GENERATION     (VIRTIO_BASE + 0x0FC) //CONFIGURATION ATOMICITY VALUE
#define CONFIG                (VIRTIO_BASE + 0x100) //CONFIGURATION SPACE



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
    [_VIRT_PCIE_VIRTIO]  = _VIRT_MEMMAP_ENTRY(0x40000000,   0x40000000),
    [_VIRT_DRAM]       = _VIRT_MEMMAP_ENTRY(0x80000000,   0x0)
};*/

#endif
