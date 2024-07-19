#include <xc.h>
#include "Common.h"
//extern unsigned char clear_screen;
static char menu[] = {VIEW_LOG, DOWNLOAD_LOG, CLEAR_LOG, SET_TIME, CHANGE_PASSWORD};
extern unsigned int wait1, wait1_i;
unsigned char sw5_first = 1, sw6_first = 1, line = 1;
unsigned char flag = 0;
extern unsigned char sec_field, minute_field, hour_field, set_time_field, set_time_sec, set_time_min, set_time_hrs, set_time_flag,set_time_wait;
void init_matrix_keypad(void) {
    /* Config PORTB as digital */
    ADCON1 = 0x0F;

    /* Set Rows (RB7 - RB5) as Outputs and Columns (RB4 - RB1) as Inputs */
    TRISB = 0x1F;

    /* Set PORTB input as pull up for columns */
    RBPU = 0;

    MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0xE0; 
}

void check_matrix_keypad(void) {


    static unsigned int delay = 0;
    static unsigned char key;
    static unsigned char key2;
    

    key2 = read_switches(LEVEL_CHANGE);

    if(key2 == MK_SW5 || key2 == MK_SW6 || key2 == MK_SW3 || key2 == MK_SW2 || key2 == MK_SW1) {
        key = key2;
        delay++;
        if(delay > 300 && key2 == MK_SW6 &&(menu_flag == VIEW_LOG || menu_flag == CHANGE_PASSWORD))
        {
            menu_flag = DISPLAY_MENU;
            delay = 0;
            menu_index = 0;
            re_pass_count = 0;
            new_pass_count = 0;
            
             //clcd_print("hello", LINE1(0));
             //while(1);
            
        }
        if (delay > 300 && key2 == MK_SW5 && menu_flag == DISPLAY_MENU && screen_flag == MENU_SCREEN) {
            if (line == 1) {
                menu_flag = menu[menu_index];
                
            } else {
                menu_flag = menu[menu_index + 1];
            }
            delay = 0;
            //clear_screen = 1;
        }
        if(delay > 300 && key2 == MK_SW5 && menu_flag == SET_TIME)
        {
            write_ds1307(0x00, ((read_ds1307(SEC_ADDR) & 0x80) | set_time_sec));
            write_ds1307(0x01, ((read_ds1307(MIN_ADDR) & 0x80) | set_time_min));
            write_ds1307(0x02, ((read_ds1307(HOUR_ADDR) & 0xC0) | set_time_hrs));
            //time_sec = set_time_sec;
            //time_min = set_time_min;
            //time_hrs = set_time_hrs;
            
            set_time_sec = set_time_hrs = set_time_min = 0;
            
            set_time_field = 1;
            set_time_flag = 1;
            
            set_time_wait = 0;
            delay = 0;
        }else if(delay > 300 && key2 == MK_SW6 && menu_flag == SET_TIME)
        {
            set_time_sec = set_time_hrs = set_time_min = 0;
            set_time_field = 1;
            set_time_flag = 2;
            set_time_wait = 0;
            delay = 0;
            
            
        }
        if (delay > 300 && key2 == MK_SW6){
            delay = 0;
            if(menu_flag == DISPLAY_MENU && screen_flag == MENU_SCREEN) {
                
                screen_flag = DASHBOARD;
            }else if(menu_flag == VIEW_LOG){
                screen_flag = DISPLAY_MENU;
            }
            
        }
              
    }
    else if (delay < 300 && delay != 0) {
        //clcd_print("hello", LINE1(0));
        delay = 0;
        if(key == MK_SW5 && menu_flag == VIEW_LOG)
        {
           // clcd_print("hello", LINE1(0));
            //clcd_putch('0'+event_count, LINE1(0));
            //while(1);
            if(view_index > 0 && event_count != 0)
            {
                view_index--;
            }else{
                view_index = event_count-1;
            }
        }else if(key == MK_SW6 && menu_flag == VIEW_LOG)
        {
            //clcd_print("hello", LINE1(0));
            //while(1);
            if(view_index < event_count)
            {
                view_index++;
                if(view_index == event_count)
                {
                    view_index = 0;
                }
            }
        }
        if (key == MK_SW6 && menu_flag == DISPLAY_MENU && screen_flag == MENU_SCREEN) {
            //clear_screen = 1;
            if (sw6_first != 1 && menu_index < 3) {
                menu_index++;

                sw5_first = 1;
                line = 2;
            }
            else {
                sw6_first = 0;
                sw5_first = 1;
                line = 2;
            }
        } else if (key == MK_SW5 && menu_flag == DISPLAY_MENU && screen_flag == MENU_SCREEN) {
            //clear_screen = 1;
            if (sw5_first != 1 && menu_index > 0) {
                menu_index--;
                sw6_first = 1;
                line = 1;

            } else {
                sw5_first = 0;
                sw6_first = 1;
                line = 1;
            }
        }
        if(key == MK_SW5 && menu_flag == SET_TIME)
        {
            if(sec_field == set_time_field)
            {
                if(set_time_sec > 58)
                {
                    set_time_sec = 0;
                }else{
                    set_time_sec++;
                }
                
            }else if(minute_field == set_time_field)
            {
                if(set_time_min > 58)
                {
                    set_time_min = 0;
                }else{
                    set_time_min++;
                }
                
            }else if(hour_field == set_time_field)
            {
                if(set_time_hrs > 22)
                {
                    set_time_hrs = 0;
                }else
                {
                    set_time_hrs++;
                    
                }
                
            }
        }else if(key == MK_SW6 && menu_flag == SET_TIME)
        {
            set_time_field++;
            if(set_time_field > 3)
            {
                set_time_field = 1;
            }
        }
        if(key == MK_SW5 && (screen_flag == PASSWORD_SCREEN || menu_flag == CHANGE_PASSWORD)) {
            if(screen_flag == PASSWORD_SCREEN){
                user_password[pass_count++] = '1';
            }else if(menu_flag == CHANGE_PASSWORD && new_pass_count != 4){
                new_password[new_pass_count++] = '1';
            }else if(menu_flag == CHANGE_PASSWORD){
                re_password[re_pass_count++] = '1';
            }        
        } else if (key == MK_SW6 && (screen_flag == PASSWORD_SCREEN || menu_flag == CHANGE_PASSWORD)) {
            if(screen_flag == PASSWORD_SCREEN){
                user_password[pass_count++] = '0';
            }else if(menu_flag == CHANGE_PASSWORD && new_pass_count != 4){
                new_password[new_pass_count++] = '0';
            }else if(menu_flag == CHANGE_PASSWORD){
                re_password[re_pass_count++] = '0';
            }
            
        }else if(key == MK_SW5 && screen_flag == DASHBOARD) {
            screen_flag = PASSWORD_SCREEN;
            timeout_flag = 0;
        }
        if(key == MK_SW2 && screen_flag == DASHBOARD) {
            if (gear < 7) {
                gear++;
                
            }
            store_event(gears[gear]);
            collision_flag = 0;

        } else if (key == MK_SW3 && screen_flag == DASHBOARD) {
            if (gear > 1) {
                gear--;
                
            }
            store_event(gears[gear]);
            collision_flag = 0;

        } else if (key == MK_SW1 && screen_flag == DASHBOARD) {
            //screen_flag = COLLISION;
            collision_flag = 1;
           store_event(gears[8]);

        }
        
    }
    

    if (wait1 == 3000 && password_screen_flag == WRONG_PASS) {
        password_screen_flag = ENTER_PASS;
        wait1 = 0;
        wait1_i = 1;
    } else if (wait1 == 3000 && password_screen_flag == MATCH_PASS) {
        password_screen_flag = ENTER_PASS;
        screen_flag = MENU_SCREEN;
        menu_flag = DISPLAY_MENU;
        wait1_i = 1;
        wait1 = 0;
    } else if (password_screen_flag == WRONG_PASS || password_screen_flag == MATCH_PASS) {
        wait1++;
    }
    
    
    if(flag == 1 || flag == 2){
        //clcd_print("hi", LINE2(14));
        if(change_password_wait++ == 3000){
            flag = 0;
            change_password_wait = 0;
            menu_flag = DISPLAY_MENU;
        }
    }else{
       // clcd_print("hhi", LINE2(13));
        change_password_wait = 0;
    }

}

unsigned char scan_key(void) {
    ROW1 = LO;
    ROW2 = HI;
    ROW3 = HI;

    if (COL1 == LO) {
        return 1;
    } else if (COL2 == LO) {
        return 4;
    } else if (COL3 == LO) {
        return 7;
    } else if (COL4 == LO) {
        return 10;
    }

    ROW1 = HI;
    ROW2 = LO;
    ROW3 = HI;

    if (COL1 == LO) {
        return 2;
    } else if (COL2 == LO) {
        return 5;
    } else if (COL3 == LO) {
        return 8;
    } else if (COL4 == LO) {
        return 11;
    }

    ROW1 = HI;
    ROW2 = HI;
    ROW3 = LO;
    /* TODO: Why more than 2 times? */
    ROW3 = LO;

    if (COL1 == LO) {
        return 3;
    } else if (COL2 == LO) {
        return 6;
    } else if (COL3 == LO) {
        return 9;
    } else if (COL4 == LO) {
        return 12;
    }

    return 0xFF;
}

unsigned char read_switches(unsigned char detection_type) {
    static unsigned char once = 1, key;

    if (detection_type == STATE_CHANGE) {
        key = scan_key();
        if (key != 0xFF && once) {
            once = 0;
            return key;
        } else if (key == 0xFF) {
            once = 1;
        }
    } else if (detection_type == LEVEL_CHANGE) {
        return scan_key();
    }

    return 0xFF;

}
