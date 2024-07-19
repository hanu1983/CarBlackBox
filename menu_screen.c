

#include "Common.h"
//unsigned char clear_screen = 1;
//char *menu[] = {"View_log", "download_log", "Clear_log", "Set_time", "change_pwd"};
extern unsigned char line;
static char *menu[] = {"View_log     ", "download_log ", "Clear_log    ", "Set_time     ", "change_pwd   "};

void menu_screen()
{
    
    
    if(line == 1)
    {
        clcd_print("-->", LINE1(0));
        clcd_print("   ", LINE2(0));
        
    }else{
        clcd_print("   ", LINE1(0));
        clcd_print("-->", LINE2(0));
    }
    clcd_print(menu[menu_index], LINE1(3));
    clcd_print(menu[menu_index+1], LINE2(3));
    
}

