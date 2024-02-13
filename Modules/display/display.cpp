#include "mbed.h"
#include "arm_book_lib.h"

#include "display.h"
#include "windshield_wiper_selection.h"

#define TIME_INCREMENT_MS 10

#define DISPLAY_REFRESH_TIME_MS 1000

#define DISPLAY_IR_CLEAR_DISPLAY   0b00000001
#define DISPLAY_IR_ENTRY_MODE_SET  0b00000100
#define DISPLAY_IR_DISPLAY_CONTROL 0b00001000
#define DISPLAY_IR_FUNCTION_SET    0b00100000
#define DISPLAY_IR_SET_DDRAM_ADDR  0b10000000

#define DISPLAY_IR_ENTRY_MODE_SET_INCREMENT 0b00000010
#define DISPLAY_IR_ENTRY_MODE_SET_DECREMENT 0b00000000
#define DISPLAY_IR_ENTRY_MODE_SET_SHIFT     0b00000001
#define DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT  0b00000000

#define DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON  0b00000100
#define DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF 0b00000000
#define DISPLAY_IR_DISPLAY_CONTROL_CURSOR_ON   0b00000010
#define DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF  0b00000000
#define DISPLAY_IR_DISPLAY_CONTROL_BLINK_ON    0b00000001
#define DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF   0b00000000

#define DISPLAY_IR_FUNCTION_SET_8BITS    0b00010000
#define DISPLAY_IR_FUNCTION_SET_4BITS    0b00000000
#define DISPLAY_IR_FUNCTION_SET_2LINES   0b00001000
#define DISPLAY_IR_FUNCTION_SET_1LINE    0b00000000
#define DISPLAY_IR_FUNCTION_SET_5x10DOTS 0b00000100
#define DISPLAY_IR_FUNCTION_SET_5x8DOTS  0b00000000

#define DISPLAY_20x4_LINE1_FIRST_CHARACTER_ADDRESS 0
#define DISPLAY_20x4_LINE2_FIRST_CHARACTER_ADDRESS 64
#define DISPLAY_20x4_LINE3_FIRST_CHARACTER_ADDRESS 20
#define DISPLAY_20x4_LINE4_FIRST_CHARACTER_ADDRESS 84

#define DISPLAY_RS_INSTRUCTION 0
#define DISPLAY_RS_DATA        1

#define DISPLAY_RW_WRITE 0
#define DISPLAY_RW_READ  1

#define DISPLAY_PIN_RS  4
#define DISPLAY_PIN_RW  5
#define DISPLAY_PIN_EN  6
#define DISPLAY_PIN_D0  7  
#define DISPLAY_PIN_D1  8  
#define DISPLAY_PIN_D2  9  
#define DISPLAY_PIN_D3 10
#define DISPLAY_PIN_D4 11
#define DISPLAY_PIN_D5 12 
#define DISPLAY_PIN_D6 13 
#define DISPLAY_PIN_D7 14 


DigitalOut displayD0( D0 );
DigitalOut displayD1( D1 );
DigitalOut displayD2( D2 );
DigitalOut displayD3( D3 );
DigitalOut displayD4( D4 );
DigitalOut displayD5( D5 );
DigitalOut displayD6( D6 );
DigitalOut displayD7( D7 );
DigitalOut displayRs( D8 );
DigitalOut displayEn( D9 );

int accumulatedDisplayTime = 0;

void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );
void displayPinWrite( uint8_t pinName, int value );
void displayDataBusWrite( uint8_t dataByte );
void displayCodeWrite( bool type, uint8_t dataBus );
void displayStringWrite( const char * str );

void displayUpdate() {
    if (accumulatedDisplayTime >= DISPLAY_REFRESH_TIME_MS) {
        accumulatedDisplayTime = 0;
        windshieldMode_t modeSelected = modeSelectedUpdate();
        displayCharPositionWrite(6,0);
        switch (modeSelected) {
        
        case HI:
            displayStringWrite("HI ");
            break;

        case LO:
            displayStringWrite("LO ");
            break; 

        case INT:
            displayStringWrite("INT");
            break; 

        case OF: 
            displayStringWrite("OFF");
            break; 
        }

        displayCharPositionWrite(7,1);
        if (modeSelected == INT) {
            windshieldDelay_t delaySelected = delaySelectedUpdate();
            switch (delaySelected) {
            
            case SHORT: 
                displayStringWrite("SHORT ");
                break; 
            
            case MEDIUM:
                displayStringWrite("MEDIUM");
                break;

            case LONG: 
                displayStringWrite("LONG  ");
                break;
            }
        }
        else {
            displayStringWrite("none  ");
        }
    }
    else {
        accumulatedDisplayTime = accumulatedDisplayTime + TIME_INCREMENT_MS;
    }
}

void displayInit() {
    delay( 50 );
    
    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS );
    delay( 5 );
            
    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS );
    delay( 1 ); 

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS );
    delay( 1 );  

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS | 
                      DISPLAY_IR_FUNCTION_SET_2LINES |
                      DISPLAY_IR_FUNCTION_SET_5x8DOTS );
    delay( 1 );         

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_DISPLAY_CONTROL |
                      DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF |      
                      DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF |       
                      DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF );       
    delay( 1 );          

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_CLEAR_DISPLAY );       
    delay( 1 ); 

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_ENTRY_MODE_SET |
                      DISPLAY_IR_ENTRY_MODE_SET_INCREMENT |       
                      DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT );                  
    delay( 1 );           

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_DISPLAY_CONTROL |
                      DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON |      
                      DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF |    
                      DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF );    
    delay( 1 );  

    displayCharPositionWrite (0,0);
    displayStringWrite("Mode: ");

    displayCharPositionWrite (0,1);
    displayStringWrite("Delay: ");
}

void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY ) {    
    switch( charPositionY ) {
        case 0:
            displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                              DISPLAY_IR_SET_DDRAM_ADDR |
                              ( DISPLAY_20x4_LINE1_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
       
        case 1:
            displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                              DISPLAY_IR_SET_DDRAM_ADDR |
                              ( DISPLAY_20x4_LINE2_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
    }
}

void displayStringWrite( const char * str ) {
    while (*str) {
        displayCodeWrite(DISPLAY_RS_DATA, *str++);
    }
}

void displayCodeWrite( bool type, uint8_t dataBus ) {
    if ( type == DISPLAY_RS_INSTRUCTION )
        displayPinWrite( DISPLAY_PIN_RS, DISPLAY_RS_INSTRUCTION);
        else
        displayPinWrite( DISPLAY_PIN_RS, DISPLAY_RS_DATA);
    displayPinWrite( DISPLAY_PIN_RW, DISPLAY_RW_WRITE );
    displayDataBusWrite( dataBus );
}

void displayPinWrite( uint8_t pinName, int value ) {
    switch( pinName ) {
        case DISPLAY_PIN_D0: displayD0 = value;   break;
        case DISPLAY_PIN_D1: displayD1 = value;   break;
        case DISPLAY_PIN_D2: displayD2 = value;   break;
        case DISPLAY_PIN_D3: displayD3 = value;   break;
        case DISPLAY_PIN_D4: displayD4 = value;   break;
        case DISPLAY_PIN_D5: displayD5 = value;   break;
        case DISPLAY_PIN_D6: displayD6 = value;   break;
        case DISPLAY_PIN_D7: displayD7 = value;   break;
        case DISPLAY_PIN_RS: displayRs = value;   break;
        case DISPLAY_PIN_EN: displayEn = value;   break;
        case DISPLAY_PIN_RW: break; 
        default: break;
    }
}

void displayDataBusWrite( uint8_t dataBus ) {
    displayPinWrite( DISPLAY_PIN_EN, OFF );
    displayPinWrite( DISPLAY_PIN_D7, dataBus & 0b10000000 );
    displayPinWrite( DISPLAY_PIN_D6, dataBus & 0b01000000 );
    displayPinWrite( DISPLAY_PIN_D5, dataBus & 0b00100000 );
    displayPinWrite( DISPLAY_PIN_D4, dataBus & 0b00010000 );
    displayPinWrite( DISPLAY_PIN_D3, dataBus & 0b00001000 );
    displayPinWrite( DISPLAY_PIN_D2, dataBus & 0b00000100 );  
    displayPinWrite( DISPLAY_PIN_D1, dataBus & 0b00000010 );      
    displayPinWrite( DISPLAY_PIN_D0, dataBus & 0b00000001 );
    displayPinWrite( DISPLAY_PIN_EN, ON );              
    delay( 1 );
    displayPinWrite( DISPLAY_PIN_EN, OFF );  
    delay( 1 );                   
}
