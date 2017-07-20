#define WTCON    (*(volatile unsigned long *)0x53000000)
#define CLKDIVN  (*(volatile unsigned long *)0x4C000014)
#define MPLLCON  (*(volatile unsigned long *)0x4C000004)


//关看门狗
void disable_watch_dog(void)
{
	WTCON = 0;
}

//初始化时钟
void clock_init(void)
{
	MPLLCON = (0x5c<<12) | (1<<4) | 2;
	CLKDIVN = 0x3;

	 /* 如果HDIVN非0，CPU的总线模式应该从“fast bus mode”变为“asynchronous bus mode” */
__asm__(
    "mrc    p15, 0, r1, c1, c0, 0\n"        /* 读出控制寄存器 */ 
    "orr    r1, r1, #0xc0000000\n"          /* 设置为“asynchronous bus mode” */
    "mcr    p15, 0, r1, c1, c0, 0\n"        /* 写入控制寄存器 */
    );
	
}

typedef struct {
	unsigned long BWSCON;	
	unsigned long BANKCON0;	
	unsigned long BANKCON1;
	unsigned long BANKCON2;	
	unsigned long BANKCON3;	
	unsigned long BANKCON4;	
	unsigned long BANKCON5;
	unsigned long BANKCON6;
	unsigned long BANKCON7;	
	unsigned long REFRESH;	
	unsigned long BANKSIZE;	
	unsigned long MRSRB6;	
	unsigned long MRSRB7;
}MemoryReg;

static MemoryReg *memreg = (MemoryReg *)0x48000000;
void memsetup(void)
{
	memreg->BWSCON    = 0x22011110;     //BWSCON
    memreg->BANKCON0  = 0x00000700;     //BANKCON0
    memreg->BANKCON1  = 0x00000700;     //BANKCON1
    memreg->BANKCON2  = 0x00000700;     //BANKCON2
    memreg->BANKCON3  = 0x00000700;     //BANKCON3  
    memreg->BANKCON4  = 0x00000700;     //BANKCON4
    memreg->BANKCON5  = 0x00000700;     //BANKCON5
    memreg->BANKCON6  = 0x00018005;     //BANKCON6
    memreg->BANKCON7  = 0x00018005;     //BANKCON7                       
    memreg->REFRESH   = 0x008C04F4;	     //REFRESH,
    memreg->BANKSIZE  = 0x000000B1;     //BANKSIZE
    memreg->MRSRB6    = 0x00000030;     //MRSRB6
    memreg->MRSRB7    = 0x00000030;     //MRSRB7
}
