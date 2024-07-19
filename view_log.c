
#include <xc.h>
#include "Common.h"

void view_log() {
    unsigned char add;
    clcd_print("#  _view_log_   ", LINE1(0));

    if (event_count != 0) {
        if (view_index == 0) {
            add = 0x00;
        } else if (view_index == 1) {
            add = 0x0A;
        } else if (view_index == 2) {
            add = 0x14;
        } else if (view_index == 3) {
            add = 0x1E;
        } else if (view_index == 4) {
            add = 0x28;
        } else if (view_index == 5) {
            add = 0x32;
        } else if (view_index == 6) {
            add = 0x3C;
        } else if (view_index == 7) {
            add = 0x46;
        } else if (view_index == 8) {
            add = 0x50;
        } else if (view_index == 9) {
            add = 0x5A;
        }
        clcd_putch('0' + view_index, LINE2(0));
        clcd_print("  ", LINE2(1));

        clcd_putch(read_external_eeprom(add), LINE2(2));
        clcd_putch(read_external_eeprom(++add), LINE2(3));
        clcd_putch(':', LINE2(4));
        clcd_putch(read_external_eeprom(++add), LINE2(5));
        clcd_putch(read_external_eeprom(++add), LINE2(6));
        clcd_putch(':', LINE2(7));
        clcd_putch(read_external_eeprom(++add), LINE2(8));
        clcd_putch(read_external_eeprom(++add), LINE2(9));
        clcd_print(" ", LINE2(10));
        clcd_putch(read_external_eeprom(++add), LINE2(11));
        clcd_putch(read_external_eeprom(++add), LINE2(12));
        clcd_print(" ", LINE2(13));
        clcd_putch(read_external_eeprom(++add), LINE2(14));
        clcd_putch(read_external_eeprom(++add), LINE2(15));
    } else {
        clcd_print("No events stored", LINE2(0));
    }
    
}

