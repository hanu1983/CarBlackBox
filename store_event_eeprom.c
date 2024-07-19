
#include <xc.h>
#include "Common.h"

//char key_interrupt;
/*void init_external_interrupt(void)
{       //selecting the edge
	INTEDG0 = 1;
	//clear interrut flag
	INT0F = 0;
	//enable external interrut
	INT0E = 1;
}


void write_internal_eeprom(unsigned char address, unsigned char data) 
{
	//Write the address
	EEADR = address;

	//Write the data
	EEDATA = data;

	//Point to data memory
	EECON1bits.EEPGD = 0;

	//Access data EEPROM memory
	EECON1bits.CFGS = 0;

	//Data write enable bit
	EECON1bits.WREN = 1;

	//Global interrupt disable 
	GIE = 0;

	//Write protection sequence
	EECON2 = 0x55;
	EECON2 = 0xAA;

	//Initiate write
	EECON1bits.WR = 1;

	//Global interrupt enable
	GIE = 1;

	//Wait till write is complete
	while (!PIR2bits.EEIF);

	//Disable the flag
	PIR2bits.EEIF = 0;
}

unsigned char read_internal_eeprom(unsigned char address)
{
	//Write the address, from where data has to be read
	EEADR = address;

	//Inhibits write cycles to Flash program/data EEPROM
	EECON1bits.WREN = 0;

	//Point to data memory
	EECON1bits.EEPGD = 0;

	//Access data EEPROM memory
	EECON1bits.CFGS = 0;
	
	//Initiate read
	EECON1bits.RD = 1;

	//Data available in EEDATA register
	return EEDATA;
}*/
extern unsigned char time1[9];
void write_external_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
	for(unsigned int i = 3000;i--;);
}

unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE_E);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ_E);
	data = i2c_read();
	i2c_stop();

	return data;
}
void store_event(char *str)
{
    adc_speed = (read_adc(4) / 10.23);
    
    speed_display(adc_speed);
    event_count++;
    if(event_count > 10)
    {
        event_count--;
        address_eeprom = 0x00;
        unsigned char address = 0x0A;
        
        for(int i = 1; i < 10; i++)
        {
            write_external_eeprom(address_eeprom, read_external_eeprom(address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            write_external_eeprom(++address_eeprom, read_external_eeprom(++address));
            ++address_eeprom, ++address;
            
            
        }
        
        //address_eeprom = 0x5A;
    }
   
    get_time();
    
    write_external_eeprom(address_eeprom, time1[0]);
    write_external_eeprom(++address_eeprom, time1[1]);
    write_external_eeprom(++address_eeprom, time1[3]);
    write_external_eeprom(++address_eeprom, time1[4]);
    
    write_external_eeprom(++address_eeprom, time1[6]);
    write_external_eeprom(++address_eeprom, time1[7]);
    
    /*write_external_eeprom(address_eeprom, '0');
    write_external_eeprom(++address_eeprom, '0');
    write_external_eeprom(++address_eeprom, '0');
    write_external_eeprom(++address_eeprom, '0');
    
    write_external_eeprom(++address_eeprom, '0');
    write_external_eeprom(++address_eeprom, '0');*/
    
   
    write_external_eeprom(++address_eeprom, str[0]);
    write_external_eeprom(++address_eeprom, str[1]);
    
    write_external_eeprom(++address_eeprom, ((speed / 10) + '0'));
    write_external_eeprom(++address_eeprom, ((speed % 10) + '0'));
    address_eeprom++;
}