

#include <xc.h>
#include "Common.h"
#include <string.h>
extern char org_password[5];
unsigned char password_cursor = 1; // password cursor position 
unsigned char password_clear_flag = 1;
static unsigned char key, attempt = 3;
unsigned int wait1 = 0,wait1_i = 1;
//extern char clear_screen;
void password_screen()
{
    
    
    switch(password_screen_flag)
    {
        case ENTER_PASS:
            
            /*if(password_clear_flag == 1)
            {
                CLEAR_DISP_SCREEN;
                password_clear_flag = 0;
            }*/

            clcd_print("ENTER PASSWORD  ", LINE1(0));
            
            if(pass_count == 1)
            {
                clcd_putch('*', LINE2(0));
            }else if(pass_count == 2)
            {
                clcd_print("**", LINE2(0));
            }else if(pass_count == 3)
            {
                clcd_print("***", LINE2(0));
            }else if(pass_count == 4)
            {
                clcd_print("****", LINE2(0));
            }else{
                clcd_print("                ", LINE2(0));
            }
            break;
        case MATCH_PASS:
            clcd_print("Password match  ", LINE1(0));
            clcd_print("Enter into menu ", LINE2(0));
            clear_screen = 1;
            if(wait1_i)
            {
                wait1_i = 0;
                wait1 = 1;
            }
            
            /* after sum amount of time going to a menu screen*/
            break;
        case WRONG_PASS:
            password_clear_flag = 1;
            clcd_print("Entered wrg pass", LINE1(0));
            clcd_print("attempt left  ", LINE2(0));
           
            clcd_putch('0'+attempt, LINE2(14));
            //password_screen_flag = ENTER_PASS;
            if(wait1_i){
                wait1_i = 0;
                wait1 = 1;
            }
            
            break;
        case USER_BLOCK:
            clcd_print("User is blocked ", LINE1(0));
            clcd_print("Screen wait.. ", LINE2(0));
            clcd_putch('0'+(screen_wait_flag / 10), LINE2(14));
            clcd_putch('0'+(screen_wait_flag % 10), LINE2(15));
            if(screen_wait_flag == 0)
            {
                screen_wait_flag = 60;
                password_screen_flag = ENTER_PASS;
                screen_flag = DASHBOARD;
                attempt = 3;
                
                
            }
            break;
            
    }
    if(pass_count == 4) /*password comparison*/
    {
        user_password[4] = '\0';
        if(!strcmp(org_password, user_password))
        {
            password_screen_flag = MATCH_PASS;
            pass_count = 0;
        }
        else{
            attempt--;
            pass_count = 0;
            password_screen_flag = WRONG_PASS;
            
        }
    }
    if(attempt == 0)// user block message in clcd
    {
        password_screen_flag = USER_BLOCK;
        pass_count = 0;
    }    
    
    
    if(timeout_flag >= 5) /* this for after 5s time it will go dashboard screen*/
    {
        screen_flag = DASHBOARD;
        pass_count = 0;
    }
    else  if(password_screen_flag == ENTER_PASS){
        if(password_cursor  == 1)
        {
            clcd_putch('_', LINE2(pass_count));
        }
        else{
            
            clcd_putch(' ', LINE2(pass_count));
        }
    }
}