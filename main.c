

#include <xc.h>
#include "Common.h"
//char org_password[5] = read_internal_eeprom(0x80);
extern unsigned char line;
void init_config() {

    /*Initial configurations function call */
    init_clcd();
    init_matrix_keypad();
    init_timer();
    init_adc();
    init_i2c();
    init_ds1307();
    
    init_uart();
    GIE = 1;
    PEIE = 1;
}

void main(void) {

       
  
    init_config();
    /*write_external_eeprom(0x90, '1');
    write_external_eeprom(0x91, '1');
    write_external_eeprom(0x92, '0');
    write_external_eeprom(0x93, '0');*/
    char add = 0x90;
    int i;
    for (i = 0; i < 4; i++)
    {
        org_password[i] = read_external_eeprom(add++);
    }
    org_password[i] = '\0';
    //clcd_print(org_password, LINE2(0));
    //while(1);
    
  
    
    //unsigned char clear_flag = 1, pass_clear_flag = 1;;

    while (1) {
    
    
        
        check_matrix_keypad();
                
        switch (screen_flag) {
            case DASHBOARD:
                
                menu_index = 0;
                line = 1;
                
                display_dashboard();
                break;
            case PASSWORD_SCREEN:
                /*call password_screen function */
                /*if(pass_clear_flag)
                {
                    CLEAR_DISP_SCREEN;
                    pass_clear_flag = 0;
                    clear_flag = 1;
                }*/
                password_screen();
                
                break;            
            case MENU_SCREEN:
            {
                switch (menu_flag) {
                    case VIEW_LOG:
                        /*call view_log function */
                        view_log();
                        //clcd_print("hello", LINE1(0));
                        break;
                    case DOWNLOAD_LOG:
                        /*call download log function */
                        //clcd_print("hello1", LINE1(0));
                        download_log();
                        break;
                    case CLEAR_LOG:
                        /*call clear_log function */
                        clear_log();
                        //clcd_print("hello2", LINE1(0));
                        break;
                    case SET_TIME:
                        /*call set_time function */
                        //clcd_print("hello3", LINE1(0));
                        set_time();
                        break;
                    case CHANGE_PASSWORD:
                        /*call change_password function */
                        change_password();
                        //clcd_print("hello4", LINE1(0));
                        break;
                    case DISPLAY_MENU:
                        /*call menu_screen function */
                        //clear_flag = 1;
                        menu_screen();
                        break;
                }
                break;
            }
                /*call menu_screen function */

        }

    }

}


