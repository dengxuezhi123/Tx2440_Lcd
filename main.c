#include "picture.h"

void show_picture(unsigned short *img)
{	
	int i=0;	
	unsigned short *frame_buf = ( unsigned short *)0x30400000;
	for(i = 0; i < (480*272); i++)
	{		
		*frame_buf = *img;		
		frame_buf++;		
		img++;	
	}
}

int main(void)
{
	show_picture((unsigned short *)pic);
	return 0;
}
