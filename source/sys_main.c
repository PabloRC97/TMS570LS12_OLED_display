/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#define i2c_ i2cREG1
#define command_reg_data 0x80

#define SCREEN_ADDRESS 0x3D
#define SCREEN_ADDRESS_1 0x3C


#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define div_ration 0x80
#define SSD1306_SETMULTIPLEX 0xA8
#define Multiplex_val 0x3F

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define no_offset 0x00
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_CHARGEPUMP 0x8D
#define chargepump_config 0x14

#define SSD1306_MEMORYMODE 0x20
#define Horizontal_add_mode 0x00
#define SSD1306_SEGREMAP 0xA0
#define SEGREMAP_conf 0x01
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SETCOMPINS 0xDA
#define comPins 0x12
#define SSD1306_SETCONTRAST 0x81
#define contrast_config 0xCF

#define SSD1306_SETPRECHARGE 0xD9
#define SETPRECHARGE_config 0xF1

#define SSD1306_SETVCOMDETECT 0xDB
#define SETVCOMDETECT_config  0x40
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY  0xA6
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_DISPLAYON 0xAF


#define SSD1306_PAGEADDR 0x22
#define SSD1306_COLUMNADDR 0x21

#define data_count 10
#define data_count2 12

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "i2c.h"
#include "string.h"
#include "font_5x7.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */


uint8 buffer[17];

void SSD1306_configuration (void);
void ssd1306_clearDisplay(void);
void SSD1306_clear( uint32, uint8 * );
void clear_ssd1306(void);
void ssd1306_command(uint8, uint8);
void ssd1306_setPosition(uint8, uint8);

void ssd1306_printText(uint8 , uint8 , char *);

void Acknowledge_byte_receive();
int delay=0;
int val=0;
uint32 i2cRxError_variable=100;
i2c_config_reg_t *i2c_configR;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    i2cInit();
//    i2cEnableNotification(i2c_, I2C_AL_INT);
//    i2cEnableNotification(i2c_, I2C_NACK_INT );
//    i2cEnableNotification(i2c_, I2C_RX_INT);
    SSD1306_configuration ();
    ssd1306_clearDisplay();

    while(1){
        ssd1306_printText(0, 1, "Line 1");
        ssd1306_clearDisplay();
        val=1;
    }

/* USER CODE END */

    return 0;
}

/* USER CODE BEGIN (4) */
void SSD1306_configuration (){

    ssd1306_command(2,SSD1306_DISPLAYOFF);                                // 0xAE

    //i2cGetConfigValue(i2c_configR, CurrentValue);
    //Acknowledge_byte_receive();
    ssd1306_command(2,SSD1306_SETDISPLAYCLOCKDIV);                        // 0xD5
//    Acknowledge_byte_receive();
    ssd1306_command(2,div_ration);                                              // the suggested ratio 0x80
//    Acknowledge_byte_receive();
    ssd1306_command(2,SSD1306_SETMULTIPLEX);                              // 0xA8
//    Acknowledge_byte_receive();
    ssd1306_command(2,Multiplex_val);                                     //63 --> 0x3F
//    Acknowledge_byte_receive();
//
    ssd1306_command(2, SSD1306_SETDISPLAYOFFSET);                          // 0xD3
//    Acknowledge_byte_receive();
    ssd1306_command(2, no_offset);                                               // no offset
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_SETSTARTLINE | 0x0);                        // line #0
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_CHARGEPUMP);                                // 0x8D
//    Acknowledge_byte_receive();
    ssd1306_command(2, chargepump_config);                                 // generate high voltage from 3.3v line internally
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_MEMORYMODE);                                // 0x20
//    Acknowledge_byte_receive();
    ssd1306_command(2, Horizontal_add_mode);                               // 0x0 act like ks0108
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_SEGREMAP | 0x01);
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_COMSCANDEC);
//    Acknowledge_byte_receive();
//
    ssd1306_command(2, SSD1306_SETCOMPINS);                                // 0xDA
//    Acknowledge_byte_receive();
    ssd1306_command(2, comPins);
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_SETCONTRAST);                               // 0x81
//    Acknowledge_byte_receive();
    ssd1306_command(2, contrast_config);
//    Acknowledge_byte_receive();
//
    ssd1306_command(2, SSD1306_SETPRECHARGE);                              // 0xd9
//    Acknowledge_byte_receive();
    ssd1306_command(2, SETPRECHARGE_config);
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_SETVCOMDETECT);                             // 0xDB
//    Acknowledge_byte_receive();
    ssd1306_command(2, SETVCOMDETECT_config);
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_DISPLAYALLON_RESUME);                       // 0xA4
//    Acknowledge_byte_receive();
    ssd1306_command(2, SSD1306_NORMALDISPLAY);                             // 0xA6
//    Acknowledge_byte_receive();
//
    ssd1306_command(2, SSD1306_DEACTIVATE_SCROLL);
//    Acknowledge_byte_receive();
//
    ssd1306_command(2, SSD1306_DISPLAYON);                                 //--turn on oled panel
//    Acknowledge_byte_receive();
}

void ssd1306_command(uint8 datac,uint8  command) {
        buffer[0] = command_reg_data;
        buffer[1] = command;
        /* Configure address of Slave to talk to */
        i2cSetSlaveAdd(i2c_, SCREEN_ADDRESS_1);

        /* Set direction to Transmitter */
        /* Note: Optional - It is done in Init */
        i2cSetDirection(i2c_, I2C_TRANSMITTER);

        i2cSetCount(i2c_ ,  datac);

        /* Set mode as Master */
        i2cSetMode(i2c_ , I2C_MASTER);

        /* Set Stop after programmed Count */
        i2cSetStop(i2c_);

        /* Transmit Start Condition */
        i2cSetStart(i2c_);

        /* Transmit DATA_COUNT number of data in Polling mode */
        i2cSend(i2c_, (uint32) datac ,  buffer );

        /* Wait until Bus Busy is cleared */
        while(i2cIsBusBusy(i2c_) == true);

        /* Wait until Stop is detected */
        while(i2cIsStopDetected(i2c_) == 0);

        /* Clear the Stop condition */
        i2cClearSCD(i2c_);

        for(delay=0;delay<10000;delay++);

        //i2c_write(SSD1306_I2C_ADDRESS, buffer, 2);
}
void ssd1306_clearDisplay(void) {

    ssd1306_setPosition(0, 0);
    uint8_t i;
    for (i = 64; i > 0; i--) {                                          // count down for loops when possible for ULP
        uint8_t x;
        for(x = 16; x > 0; x--) {
            if (x == 1) {
                buffer[x-1] = 0x40;
            } else {
                buffer[x-1] = 0x0;
            }
        }
        SSD1306_clear( 17, buffer);

    }
    //SSD1306_clear( 17, buffer);
}

void ssd1306_setPosition(uint8 column, uint8 page) {
    if (column > 128) {
        column = 0;                                                     // constrain column to upper limit
    }

    if (page > 8) {
        page = 0;                                                       // constrain page to upper limit
    }

    ssd1306_command(2,SSD1306_COLUMNADDR);
    ssd1306_command(2,column);                                            // Column start address (0 = reset)
    ssd1306_command(2, 0x3F);                                // Column end address (127 = reset)

    ssd1306_command(2,SSD1306_PAGEADDR);
    ssd1306_command(2,page);                                              // Page start address (0 = reset)
    ssd1306_command(2,7);                                                 // Page end address
}

void SSD1306_clear( uint32 count, uint8 *comm ){

    /* Configure address of Slave to talk to */
        i2cSetSlaveAdd(i2c_, SCREEN_ADDRESS_1);

        /* Set direction to Transmitter */
        /* Note: Optional - It is done in Init */
        i2cSetDirection(i2c_, I2C_TRANSMITTER);

        i2cSetCount(i2c_ ,  count);

        /* Set mode as Master */
       i2cSetMode(i2c_ , I2C_MASTER);

       /* Set Stop after programmed Count */
       i2cSetStop(i2c_);

       /* Transmit Start Condition */
       i2cSetStart(i2c_);
       //i2cSendByte(i2c_ , (uint8) 0x40 );
       /* Transmit DATA_COUNT number of data in Polling mode */
       i2cSend(i2c_, count , comm  );

       /* Wait until Bus Busy is cleared */
       while(i2cIsBusBusy(i2c_) == true);

       /* Wait until Stop is detected */
       while(i2cIsStopDetected(i2c_) == 0);

       /* Clear the Stop condition */
       i2cClearSCD(i2c_);

       for(delay=0;delay<10000;delay++);
}


//void clear_ssd1306(void){
//    uint16 row=0;
//    uint16 col=0;
//    for ( row=0 ; row < 8; row++){
//        for( col=0 ; col < 16; col++ ){
//            OLED_YX(row, col);
//            OLED_PutChar(' ');
//        }
//    }
//}

//void OLED_YX(uint8 Row , uint8 Column){
//    ssd1306_command(2, 0xB0 + Row);
//    ssd1306_command(2, 0x00 + (8*Column & 0x0F) );
//    ssd1306_command(2, 0x10 + ((8*Column>>4) & 0x0F) );
//}
//
//void OLED_PutChar(char ch){
//    if ( (ch < 32 ) || (ch > 27 ) ){
//        ch= ' ';
//    }
//    const uint8 *base = &OledFont[ch-32][0];
//    uint8 bytes[9];
//    memmove (bytes + 1 , base , 8);
//    SSD1306_clear( 9, bytes);
//}


void ssd1306_printText(uint8 x, uint8 y, char *ptString) {
    ssd1306_setPosition(x, y);

    while (*ptString != '\0') {
        buffer[0] = 0x40;

        if ((x + 5) >= 127) {                                           // char will run off screen
            x = 0;                                                      // set column to 0
            y++;                                                        // jump to next page
            ssd1306_setPosition(x, y);                                  // send position change to oled
        }

        uint8 i;
        for(i = 0; i< 5; i++) {
            buffer[i+1] = font_5x7[*ptString - ' '][i];
        }

        buffer[6] = 0x0;
        SSD1306_clear( 7 , buffer );
        ptString++;
        x+=6;
    }
} // end ssd1306_printText


void Acknowledge_byte_receive(){
        i2cSetSlaveAdd(i2c_, SCREEN_ADDRESS);

        /* Set direction to receiver */
        i2cSetDirection(i2c_, I2C_RECEIVER);

        i2cSetCount(i2c_, 1);

        /* Set mode as Master */
        i2cSetMode(i2c_, I2C_MASTER);

        /* Set Stop after programmed Count */
        i2cSetStop(i2c_);

        /* Transmit Start Condition */
        i2cSetStart(i2c_);
        i2cRxError_variable=i2cRxError(i2c_);
        i2cReceiveByte(i2c_);

        /* Wait until Bus Busy is cleared */
        while(i2cIsBusBusy(i2cREG1) == true);

        /* Wait until Stop is detected */
        while(i2cIsStopDetected(i2cREG1) == 0);

        /* Clear the Stop condition */
        i2cClearSCD(i2cREG1);

        for(delay=0;delay<10000;delay++);


}

/* USER CODE END */
