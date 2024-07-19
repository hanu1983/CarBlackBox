/*
 * File:   change_password.c
 * Author: DELL
 *
 * Created on 29 March, 2024, 11:28 AM
 */

#include <xc.h>
#include "Common.h"
unsigned char flag = 0;
extern char org_password[5];
void change_password() {

    if(flag == 1 || flag == 2)
    {
        if(change_password_wait == 0)
        {
            change_password_wait = 1;
        }
    }
    
    
    if (flag == 1) {
        //change_password_wait = 1;

        clcd_print("Pwd is match    ", LINE1(0));
        clcd_print("    Success     ", LINE2(0));
    } else if (flag == 2) {
        //change_password_wait = 1;
        clcd_print("Pwd is not match", LINE1(0));
        clcd_print("    Failure     ", LINE2(0));
    } else {
        if (new_pass_count < 4) {
            clcd_print("Enter new_pwd   ", LINE1(0));

        }
        else if (new_pass_count == 4 && re_pass_count != 4) {

            clcd_print("Re_enter pwd    ", LINE1(0));

        } else if (!strcmp(new_password, re_password)) {

            new_pass_count = 0;
            re_pass_count = 0;

            flag = 1;
            
            store_event("CP");
            write_external_eeprom(0x90, re_password[0]);
            write_external_eeprom(0x91, re_password[1]);
            write_external_eeprom(0x92, re_password[2]);
            write_external_eeprom(0x93, re_password[3]);

        } else {
            new_pass_count = 0;
            re_pass_count = 0;
            flag = 2;
        }
    }
    if (new_pass_count == 1 || re_pass_count == 1) {
        clcd_print("*                ", LINE2(0));
    } else if (new_pass_count == 2 || re_pass_count == 2) {
        clcd_print("**              ", LINE2(0));
    } else if (new_pass_count == 3 || re_pass_count == 3) {
        clcd_print("***             ", LINE2(0));
    }/* else if (new_pass_count == 4 || re_pass_count == 4) {
        clcd_print("****            ", LINE2(0));
    } else {
        clcd_print("                ", LINE2(0));
    }*/
    if(new_pass_count == 4 && re_pass_count == 0)
    {
        clcd_print("                  ", LINE2(0));
    }
    
    if(flag == 0 && new_pass_count == 0)
    {
        clcd_print("               ", LINE2(0));
    }else if(flag == 0 && new_pass_count == 4 && re_pass_count == 0)
    {
        clcd_print("               ", LINE2(0));
    }
    

}