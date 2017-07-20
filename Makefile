objs := head.o init.o lcd.o main.o

lcd.bin : $(objs)	
	arm-linux-ld -Tlcd.lds	-o lcd_elf $^	
	arm-linux-objcopy -O binary -S lcd_elf $@	
	arm-linux-objdump -D -m arm  lcd_elf > lcd.dis
	
%.o:%.c	
	arm-linux-gcc -Wall -c -O2 -o $@ $<
	
%.o:%.s	
	arm-linux-gcc -Wall -c -O2 -o $@ $<
	
clean:	
	rm -f  lcd.dis lcd.bin lcd_elf *.o
