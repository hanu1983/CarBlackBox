

#include <xc.h>
#include "Common.h"
unsigned char set_time_sec = 0;
unsigned char set_time_min = 0;
unsigned char set_time_hrs = 0;

unsigned char sec_field = 1;
unsigned char minute_field = 2;
unsigned char hour_field = 3;

unsigned char set_time_field = 1;

unsigned char set_time_flag = 0; // for what happened (time is updated or not updated))
unsigned char set_time_wait = 0;

unsigned char set_t_f_blink = 1; // blinking timing fields

unsigned char clock_reg[3];

unsigned char time1[9];

void get_time(void)
{
   // write_ds1307(0x00, (read_ds1307(SEC_ADDR) | 4));
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time1[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time1[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time1[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time1[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time1[2] = ':';
	time1[3] = '0' + ((clock_reg[1] >> 4) & 0x07);
	time1[4] = '0' + (clock_reg[1] & 0x0F);
	time1[5] = ':';
	time1[6] = '0' + ((clock_reg[2] >> 4) & 0x07);
	time1[7] = '0' + (clock_reg[2] & 0x0F);
	time1[8] = '\0';
}

void set_time() 
{
    if (set_time_flag == 0) {

        clcd_print("S_time HH MM SS ", LINE1(0));
        clcd_print("       ", LINE2(0));
        clcd_putch(' ', LINE2(9));
        clcd_putch(' ', LINE2(12));
    }

    if (sec_field == set_time_field && set_time_flag == 0) 
    {
        clcd_putch('0' + (set_time_hrs / 10), LINE2(7));
        clcd_putch('0' + (set_time_hrs % 10), LINE2(8));
        clcd_putch('0'+(set_time_min / 10), LINE2(10));
        clcd_putch('0'+(set_time_min % 10), LINE2(11));
        if (set_t_f_blink == 1) 
        {
            clcd_putch('0' + (set_time_sec / 10), LINE2(13));
            clcd_putch('0' + (set_time_sec % 10), LINE2(14));
        } else 
        {
            clcd_print("  ", LINE2(13));
        }

    } else if (minute_field == set_time_field && set_time_flag == 0)
    {
        clcd_putch('0' + (set_time_hrs / 10), LINE2(7));
        clcd_putch('0' + (set_time_hrs % 10), LINE2(8));
        clcd_putch('0' + (set_time_sec / 10), LINE2(13));
        clcd_putch('0' + (set_time_sec % 10), LINE2(14));
        if(set_t_f_blink == 1)
        {
            clcd_putch('0'+(set_time_min / 10), LINE2(10));
            clcd_putch('0'+(set_time_min % 10), LINE2(11));            
        }else
        {
            clcd_print("  ", LINE2(10));
        }

    } else if (hour_field == set_time_field && set_time_flag == 0)
    {
        clcd_putch('0' + (set_time_sec / 10), LINE2(13));
        clcd_putch('0' + (set_time_sec % 10), LINE2(14));
        clcd_putch('0'+(set_time_min / 10), LINE2(10));
        clcd_putch('0'+(set_time_min % 10), LINE2(11));
       
        if (set_t_f_blink == 1) 
        {
            clcd_putch('0' + (set_time_hrs / 10), LINE2(7));
            clcd_putch('0' + (set_time_hrs % 10), LINE2(8));
        }else
        {
            clcd_print("  ", LINE2(7));
        }

    }
    
    if(set_time_flag == 1)
    {
        clcd_print("Time is updated  ", LINE1(0));
        clcd_print("  Successfully   ", LINE2(0));
        if(set_time_wait == 15)
        {
            menu_flag = DISPLAY_MENU;
            set_time_flag = 0;
        }
        
    }
    if(set_time_flag == 2)
    {
        clcd_print("Time  is  not  ", LINE1(0));
        clcd_print("   Updated       ", LINE2(0));
        //while(1);
        if(set_time_wait == 15)
        {
            menu_flag = DISPLAY_MENU;
            set_time_flag = 0;
            
        }
    }

}


