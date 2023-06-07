#include "../include/mm/pg.h"
#include "../include/type.h"
#include "../include/mm/mm.h"
#include "../include/usr/lib.h"

extern uint32_t USER_START;
extern uint32_t USER_END;

uint32_t page_num = 0;

PageTable_t kernel_page_table;

PTE_t* kalloc() 
{
	return &kernel_page_table[page_num++];
}

void Init_vm() 
{
		printk("Initial virtual mm\n");
		page_num = 0;
    
    asm volatile("li t1,8");
    asm volatile("slli t1, t1, 60");
    asm volatile("mv t0,%0"::"r"(kernel_page_table));
    asm volatile("srli t0, t0, 12");
    asm volatile("or t0,t0,t1");
    asm volatile("csrw satp, t0");
    asm volatile("sfence.vma zero, zero");
}

void Init_page_table()
{
	printk("Initial page table\n");
	kernel_page_table = (PageTable_t)malloc(sizeof(PAGE_SIZE));//分配一个页来作页表，存储页表项
	memset(kernel_page_table,0,PAGE_SIZE);//清空页表
	map(kernel_page_table,0,USER_START,PAGE_SIZE * 512, PTE_X | PTE_R | PTE_W);//映射虚拟地址0->USER_START,共512项（512 * 8B = 4096B）
}

static uint32_t get_pagenum(uint64_t va) 
{
    int mask = 0x1ff;
    return ((va >> PAGE_OFF) & mask);
}

static uint64_t get_addr(uint32_t num,uint64_t base_addr)
{
	return base_addr + (num * PAGE_SIZE);
}

static PTE_t* virt_to_phys(PageTable_t table, uint64_t va) 
{
    int level;
    PTE_t* pte;
    pte = &table[get_pagenum(va)];//页表项 = 页表号 + 在页表上的偏移地址
    if (*pte & PTE_V) 
    {
      if (*pte & PTE_R || *pte & PTE_X) 
       {		// valid
       	return pte;  
       }
       else// leaf
       {
       	return NULL;
       }
    }
    else
    {
    	pte = kalloc();
    }
    return pte;
}

void map(PageTable_t table, uint64_t va, uint64_t pa, uint64_t size, uint64_t mode) 
{
    uint64_t pgstart = PAGE_ALIGN(va);
    uint64_t pglast = PAGE_ALIGN(va + size-1);
    for(; pgstart <= pglast; pgstart += PAGE_SIZE, pa += PAGE_SIZE) 
    {
        PTE_t *p = virt_to_phys(table, pgstart);
        *p = ((pa >> PAGE_OFF) << 10) | PTE_V | PTE_X | mode;
    }
    return;
}
