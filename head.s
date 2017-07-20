.extern     main
.text 
.global _start 
_start:
	ldr sp, =1024*1024*2
	bl	disable_watch_dog  
	bl  clock_init
	bl	memsetup
	bl  Lcd_Port_Init
	bl  Lcd_PowerEnable

	ldr sp, =0x34000000
	ldr lr, =halt_loop
	ldr pc, =main
halt_loop:
	b halt_loop
	
	

