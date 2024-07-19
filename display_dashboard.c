

#include <xc.h>
#include "Common.h"
extern unsigned char time1[9];
void display_dashboard()
{
    clcd_print("TIME     ", LINE1(0));
    clcd_print("EV   ", LINE1(9));
    clcd_print("SP ", LINE1(12));
    
    /*clcd_putch('0'+(time_hrs / 10), LINE2(0));
    clcd_putch('0'+(time_hrs % 10), LINE2(1));
    clcd_putch(':', LINE2(2));
    clcd_putch('0'+(time_min / 10), LINE2(3));
    clcd_putch('0'+(time_min % 10), LINE2(4));
    clcd_putch(':', LINE2(5));
    clcd_putch('0'+(time_sec / 10), LINE2(6));
    clcd_putch('0'+(time_sec % 10), LINE2(7));
    */
    get_time();
    clcd_print(time1, LINE2(0));
    //clcd_print("00:00:00 ", LINE2(0));

    //clcd_print("ON", LINE2(9));
    //gear_display();
    if(collision_flag == 1)
    {
        clcd_print("C_", LINE2(9));
    }else{
        clcd_print(gears[gear], LINE2(9));
    }
    clcd_putch(' ', LINE2(8));
    adc_speed = (read_adc(4) / 10.23);
    
    speed_display(adc_speed);
    
    
    
    
}

void speed_display(unsigned short adc_speed)
{
    clcd_putch(' ', LINE2(11));
    clcd_putch('0' + (speed / 10), LINE2(12));
    clcd_putch('0' + (speed % 10), LINE2(13));
    clcd_print("  ", LINE2(14));
    speed = adc_speed;
    switch(gear){
        case ON:
            if(adc_speed > 0)
            {
                speed = 0;
            }
            break;
        case GN:
            if(adc_speed > 0)
            {
                speed = 0;
            }
            break;
        case GR:
            if(adc_speed > 25)
            {
                speed = 25;
            }
            break;
        case G1:
            if(adc_speed > 25)
            {
                speed = 25;
            }
            break;
        case G2:
            if(adc_speed > 35)
            {
                speed = 35;
                
            }
            break;
        case G3:
            if(adc_speed > 50)
            {
                speed = 50;
            }
            break;
        case G4:
            if(adc_speed > 70)
            {
                speed = 70;
            }
            break;
        case G5:
            if(adc_speed > 99)
            {
                speed = 99;
            }
            break;
        
    }
}

void clear_scr()
{
    //if(clear_screen == 1)
    //{
        CLEAR_DISP_SCREEN;
      //  clear_screen = 0;
    //}
}
