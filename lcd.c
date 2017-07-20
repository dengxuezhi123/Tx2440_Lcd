#include "lcd.h"

#define LCD_FRAMEBUFFER 0x30400000
#define LCD_WIDTH  480
#define LCD_HEIGHT 272
#define LCD_LINEVAL  (LCD_HEIGHT - 1)
#define LCD_HOZVAL (LCD_WIDTH - 1)

#define CLKVAL_TFT 	(4)
#define MVAL		    (13)
#define MVAL_USED 	    (0)	
#define BSWP		(0)
#define HWSWP		    (1)			
#define PNRMODE		    (3)			
#define BPPMODE		    (12)	

#define VBPD 		(2)	   //垂直同步信号的后肩
#define VFPD 		(4)	  //垂直同步信号的前肩
#define VSPW 		(8)	  //垂直同步信号的脉宽
#define HBPD 		(10)  //水平同步信号的后肩
#define HFPD 		(19)  //水平同步信号的前肩
#define HSPW 		(30)  //水平同步信号的脉宽

Lcd *lcd = (Lcd *)0x4d000000;

void Lcd_Port_Init(void)
{
    GPCUP   = 0x00000000;   // 禁止内部上拉   
    GPCCON  = 0xaaaa02a9;   // GPIO管脚用于VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
    GPDUP   = 0x00000000;   // 禁止内部上拉
    GPDCON  = 0xaaaaaaaa;   // GPIO管脚用于VD[23:8]
  		
	lcd->LCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;    	// TFT LCD panel,12bpp TFT,ENVID=off	
	lcd->LCDCON2=(VBPD<<24)|(LCD_LINEVAL<<14)|(VFPD<<6)|(VSPW);	
	lcd->LCDCON3=(HBPD<<19)|(LCD_HOZVAL<<8)|(HFPD);
	lcd->LCDCON4=(MVAL<<8)|(HSPW);
	lcd->LCDCON5 = (1<<11) | (0<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6) | (1<<3)  |(BSWP<<1) | (HWSWP);	
	
	lcd->LCDSADDR1=(LCD_FRAMEBUFFER>>22)<<21 | ((LCD_FRAMEBUFFER>>1) & 0x1fffff);	
	lcd->LCDSADDR2=((LCD_FRAMEBUFFER + LCD_WIDTH * LCD_HEIGHT*2)>>1) & 0x1fffff;
	lcd->LCDSADDR3= LCD_WIDTH ;	
	lcd->LCDINTMSK|=(3); 
	lcd->TPAL = 0;
}

void Lcd_PowerEnable(void)
{
    //GPG4 is setted as LCD_PWREN    
    GPGUP  = GPGUP  | (1<<4);     
	GPGCON = GPGCON | (3<<8);    
	//Enable LCD POWER ENABLE Function   
	lcd->LCDCON1 |= 1;
	lcd->LCDCON5 &=(~(1<<3))|(1<<3);   // PWREN  
	lcd->LCDCON5 &=(~(1<<5))|(0<<5);   // INVPWREN
}    

void Lcd_EnvidOnOff(void)
{
  	lcd->LCDCON1 |= 0 ;
} 

