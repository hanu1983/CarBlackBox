/*
 * File:   clear_log.c
 * Author: DELL
 *
 * Created on 6 April, 2024, 4:09 PM
 */


#include <xc.h>
#include "Common.h"

void clear_log()
{
    static int delay = 0;
    event_count = 0;
    address_eeprom = 0x00;
    
    clcd_print("Clearing all logs", LINE1(0));
    clcd_print("                 ", LINE2(0));
    
    delay++;
    if(delay == 2000)
    {
        store_event("CL");
        menu_flag = DISPLAY_MENU;
    }
    
}
