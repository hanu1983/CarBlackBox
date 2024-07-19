
#include <xc.h>
#include "Common.h"
extern unsigned char password_cursor, set_t_f_blink, set_time_wait;

extern unsigned char download_wait_flag;

void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
            //clear_scr();
			count = 0;
			time_sec++;
            
            password_cursor = !password_cursor; // password crsor position;
            set_t_f_blink = !set_t_f_blink; // blinking fields
            
            set_time_wait++; // wait for print messege time updated or not
            
            download_wait_flag++;
            
            time();
		}
		TMR0IF = 0;
	}
    
}

void init_timer(void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */

/*Setting 8 bit timer register*/
	T08BIT = 1;

/* Selecting internal clock source */
	T0CS = 0;

/* Enabling timer0*/
	TMR0ON = 1;

/* disabling prescaler*/
	PSA = 1;

	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}


void time()
{
    if(password_screen_flag == USER_BLOCK)
    {
        screen_wait_flag--;
    }
    
    if(time_sec > 59)
    {
        if(pass_count > 0)
        {
            timeout_flag++;
        }
        
        time_min++;
        time_sec = 0;
    }
    if(time_min > 59)
    {
        time_hrs++;
        time_min = 0;
    }
    if(time_hrs > 23)
    {
        time_hrs = 0;
        time_min = 0;
        time_sec = 0;
    }   
    
    
}

