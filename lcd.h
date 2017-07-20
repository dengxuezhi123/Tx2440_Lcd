#ifndef _LCD_H_
#define  _LCD_H_

#define GPBCON  (*(volatile unsigned long *)0x56000010)
#define GPBDAT  (*(volatile unsigned long *)0x56000014)
#define GPCUP   (*(volatile unsigned long *)0x56000028)
#define GPCCON  (*(volatile unsigned long *)0x56000020)
#define GPDUP   (*(volatile unsigned long *)0x56000038)
#define GPDCON  (*(volatile unsigned long *)0x56000030)
#define GPGUP   (*(volatile unsigned long *)0x56000068)
#define GPGCON  (*(volatile unsigned long *)0x56000060)

typedef struct{	
unsigned long LCDCON1;	
unsigned long LCDCON2;	
unsigned long LCDCON3;	
unsigned long LCDCON4;	
unsigned long LCDCON5;	
unsigned long LCDSADDR1;	
unsigned long LCDSADDR2;	
unsigned long LCDSADDR3;	
unsigned long REDLUT;	
unsigned long GREENLUT;	
unsigned long BLUELUT;	
unsigned long DITHMODE;	
unsigned long TPAL;
unsigned long LCDINTPND;	
unsigned long LCDSRCPND;	
unsigned long LCDINTMSK;
} Lcd;

#endif
