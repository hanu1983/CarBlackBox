

#include <xc.h>
#include "Common.h"

unsigned char download_flag = 1;
unsigned char download_wait_flag = 0;
void init_uart()
{
    TX9 = 0;
    TXEN = 1;
    SYNC = 0;
    SENDB = 1;
    BRGH = 1;
    
    SPEN = 1;
    RX9 = 0;
    CREN = 1;
    BRG16 = 0;
    SPBRG = 129;
    TXIF = 0;
    RCIF = 0;
}

void putch(unsigned char data)
{
    while(TXIF == 0);
    TXIF = 0;
    TXREG = data;
}
unsigned char getch()
{
    while(RCIF == 0);
    RCIF = 0;
    return RCREG;
}
void puts(unsigned char *data)
{
    while(*data)
    {
        putch(*data++);
    }
}
void download_log()
{
    unsigned char add = 0x00;
    unsigned char buffer[18];
    if (download_flag == 0) {

        for (int i = 0; i < event_count; i++) {
            buffer[0] = ' ';
            buffer[1] = (i+1)+48;
            buffer[2] = ' ';
            buffer[3] = read_external_eeprom(add);
            buffer[4] = read_external_eeprom(++add);
            buffer[5] = ':';
            buffer[6] = read_external_eeprom(++add);
            buffer[7] = read_external_eeprom(++add);
            buffer[8] = ':';
            buffer[9] = read_external_eeprom(++add);
            buffer[10] = read_external_eeprom(++add);
            buffer[11] = ' ';
            buffer[12] = read_external_eeprom(++add);
            buffer[13] = read_external_eeprom(++add);
            buffer[14] = ' ';
            buffer[15] = read_external_eeprom(++add);
            buffer[16] = read_external_eeprom(++add);
            buffer[17] = '\0';
            ++add;

            puts(buffer);
            puts("\n\r");
        }
        download_flag = 1;
        download_wait_flag = 0;
    }else{
        clcd_print("    Logs are     ", LINE1(0));
        clcd_print("download  Wait   ", LINE2(0));
        
        if(download_wait_flag == 20)
        {
            menu_flag = DISPLAY_MENU;
            download_flag = 0;
        }
    }
    
    
    
}