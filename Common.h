#ifndef MAIN_H
#define MAIN_H

#define DASHBOARD               0
#define PASSWORD_SCREEN         1
#define MENU_SCREEN             2
#define DISPLAY_MENU            3
#define VIEW_LOG                4
#define DOWNLOAD_LOG            5
#define CLEAR_LOG               6
#define SET_TIME                7
#define CHANGE_PASSWORD         8
#define COLLISION               9



#define ENTER_PASS      0
#define MATCH_PASS      1
#define WRONG_PASS      2
#define USER_BLOCK      3


/* glabal varibles */

unsigned screen_flag = DASHBOARD;
unsigned menu_flag = DISPLAY_MENU;
unsigned password_screen_flag = ENTER_PASS;

char *gears[9] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4", "G5", "C_"}; // event signatures

unsigned char time_hrs = 0;
unsigned char time_min = 0;
unsigned char time_sec = 0;

unsigned char speed = 0;
unsigned char gear = 0;
unsigned short adc_speed;

unsigned char timeout_flag = 0;
unsigned char screen_wait_flag = 60;// if user block wait period flag

unsigned char collision_flag = 0;

char new_password[5];
unsigned char new_pass_count = 0;

char re_password[5];
unsigned char re_pass_count = 0;

char user_password[5];
unsigned char pass_count = 0;
char org_password[5];
//char org_password[5] = "1100";
//write_internal_eeprom(0x80, "1100");

int change_password_wait = 0; // for message printing of pass match or not

unsigned char address_eeprom = 0x00;

unsigned char event_count = 0;

unsigned char interept_flag = 0;

unsigned char clear_screen = 0;
void clear_scr(); // clear the clcd screen
unsigned char menu_index = 0; // index for enter into logs(view_log, download_log))
unsigned char view_index = 0;

void init_timer(void);
void init_adc();
unsigned short read_adc(unsigned char channel);
void gear_display();
void speed_display(unsigned short adc_speed);
void time();// for change hours and minutes and sec


void init_external_interrupt(void);

void display_dashboard();
void store_event(char *str);
void password_screen();
void menu_screen();
void view_log();
void download_log();
void clear_log();
void set_time();
void change_password();


/* Functions declarations and global variable declarations */

#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7


#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0
#define _XTAL_FREQ                  20000000
#define LINE1(x)									(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)
#define EIGHT_BIT_MODE   0x33
void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);


#define MAX_ROW				4
#define MAX_COL				3

#define STATE_CHANGE				1
#define LEVEL_CHANGE				0
#define MATRIX_KEYPAD_PORT			PORTB
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1

#define ON      0
#define GN      1
#define GR      2
#define G1      3
#define G2      4
#define G3      5
#define  G4     6
#define G5      7


#define MK_SW1					1
#define MK_SW2					2
#define MK_SW3					3
#define MK_SW4					4
#define MK_SW5					5
#define MK_SW6					6
#define MK_SW7					7
#define MK_SW8					8
#define MK_SW9					9
#define MK_SW10				10
#define MK_SW11				11
#define MK_SW12				12

#define ALL_RELEASED	0xFF

#define HI				1
#define LO				0

void init_matrix_keypad(void);
unsigned char scan_key(void);
unsigned char read_switches(unsigned char detection_type);
void check_matrix_keypad(void);

/*unsigned char read_internal_eeprom(unsigned char address);
void init_external_interrupt(void);
void write_internal_eeprom(unsigned char address, unsigned char data);*/

#define SLAVE_READ_E		0xA1
#define SLAVE_WRITE_E		0xA0


void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);


void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0


#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07


void write_ds1307(unsigned char address1,  unsigned char data);
unsigned char read_ds1307(unsigned char address1);
void init_ds1307(void);

void get_time(void);

void init_uart();
void putch(unsigned char data);
unsigned char getch();
void puts(unsigned char *data);





#endif