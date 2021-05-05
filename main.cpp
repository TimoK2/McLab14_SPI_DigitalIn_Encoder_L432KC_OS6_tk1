/*****************************************************************
*
*  Digital input extension using the 74HC165N with SPI
*
*****************************************************************
* 74HC165 is a parallel in seriel out shift register. Several of 
* these can be connected in parallel and the bits shifted with
* one SPI channel. In here the HC165N_L is for the lower bits
* and HC165N_H is for the higher bits
* 
* Connections 
* HC165N_H 9 -- 10 HC165N_L 
* HC165N_L 9 -- L432KC D12       Data out to SPI MISO
* L432KC D13 -- 2  HC165N_H -- 2  HC165N_L  SPI CLK
* L432KC  D5 -- 15 HC165N_H -- 15 HC165N_L  CLK_INH = SPI CS
* L432KC  D6 -- 1  HC165N_H -- 1  HC165N_L  LD
* 
* Timo Karppinen 11.9.2020
****************************************************************/

#include "mbed.h"


#define REPEAT_RATE  1000ms

// SPI class
SPI spi(D11, D12, D13); // mosi, miso, sck 
 
DigitalOut hc165LD(D6);     // Loading parallel values to shift register 
DigitalOut hc165INH(D5);    // Chip Select for sensor SPI communication

//unsigned short sw16 = 0; // short integer 16 bits for the switch states
                         // try what happens without the unsigned 
                         // and highest bit 1 ! example 11000011 11000000                        
char sw8 = 0;                                               
int   sw32 = 0; // integer 32 bits 
int position = 0;

int GrayToDecimal(int gray);

int main(){
    // the working mode settings for the 74HC165N
    //spi.format(16,3); //16:16bit frame, 0:POL=0 PHA=0(Rising Edge Sampled)
                      //16:16bit frame, 3:POL=1 PHA=0(Rising Edge Sampled)
    spi.format(8,3);                  
    spi.frequency(1000000); // 1 MHz, the 74HC165N should be reliable
                            // up to 10 MHz with operating voltage 3.3V
    
   hc165LD.write(1);   // LD high
   hc165INH.write(1);  // CLK Inhibit high
   
   while(1){
    // reading the 16 bit
    hc165LD.write(0);  // Loads parallel inputs to a register
    ThisThread::sleep_for(1ms);
    hc165LD.write(1);
    hc165INH.write(0);   // CS low
    ThisThread::sleep_for(1ms);
    
    //sw16 = spi.write(0xFFFF); 
    sw8 = spi.write(0xFF);
    
    ThisThread::sleep_for(1ms);
    
    hc165INH.write(1);   // CS high
   
    //sw32 = sw16;
    sw32 = sw8;
    printf(" 32 bit value without leading zeros %d\n", sw32);
    
    position = GrayToDecimal(sw32);
    
    printf(" Gray code converted to position %d\n", position);
    
    ThisThread::sleep_for(REPEAT_RATE);
    }
}

int GrayToDecimal(int gray){
    int pos;
    switch(gray){
        case 127: pos = 0;break;
        case 63: pos = 1;break;
        case 62: pos = 2;break;
        case 58: pos = 3;break;
        case 56: pos = 4;break;
        case 184: pos = 5;break;
        case 152: pos = 6;break;
        case 24: pos = 7;break;
        case 8: pos = 8;break;
        case 72: pos = 9;break;
        case 73: pos = 10;break;
        case 77: pos = 11;break;
        case 79: pos = 12;break;
        case 15: pos = 13;break;
        case 47: pos = 14;break;
        case 175: pos = 15;break;
        case 191: pos = 16;break;
        case 159: pos = 17;break;
        case 31: pos = 18;break;
        case 29: pos = 19;break;
        case 28: pos = 20;break;
        case 92: pos = 21;break;
        case 76: pos = 22;break;
        case 12: pos = 23;break;
        case 4: pos = 24;break;
        case 36: pos = 25;break;
        case 164: pos = 26;break;
        case 166: pos = 27;break;
        case 167: pos = 28;break;
        case 135: pos = 29;break;
        case 151: pos = 30;break;
        case 215: pos = 31;break;
        case 223: pos = 32;break;
        case 207: pos = 33;break;
        case 143: pos = 34;break;
        case 142: pos = 35;break;
        case 14: pos = 36;break;
        case 46: pos = 37;break;
        case 38: pos = 38;break;
        case 6: pos = 39;break;
        case 2: pos = 40;break;
        case 18: pos =41;break;
        case 82: pos = 42;break;
        case 83: pos = 43;break;
        case 211: pos = 44;break;
        case 195: pos = 45;break;
        case 203: pos = 46;break;
        case 235: pos = 47;break;
        case 239: pos = 48;break;
        case 231: pos = 49;break;
        case 199: pos = 50;break;
        case 71: pos = 51;break;
        case 7: pos = 52;break;
        case 23: pos = 53;break;
        case 19: pos = 54;break;
        case 3: pos = 55;break;
        case 1: pos = 56;break;
        case 9: pos = 57;break;
        case 41: pos = 58;break;
        case 169: pos = 59;break;
        case 233: pos = 60;break;
        case 225: pos = 61;break;
        case 229: pos = 62;break;
        case 245: pos = 63;break;
        case 247: pos = 64;break;
        case 243: pos = 65;break;
        case 227: pos = 66;break;
        case 163: pos = 67;break;
        case 131: pos = 68;break;
        case 139: pos = 69;break;
        case 137: pos = 70;break;
        case 129: pos = 71;break;
        case 128: pos = 72;break;
        case 132: pos = 73;break;
        case 148: pos = 74;break;
        case 212: pos = 75;break;
        case 244: pos = 76;break;
        case 240: pos = 77;break;
        case 242: pos = 78;break;
        case 250: pos = 79;break;
        case 251: pos = 80;break;
        case 249: pos = 81;break;
        case 241: pos = 82;break;
        case 209: pos = 83;break;
        case 193: pos = 84;break;
        case 197: pos = 85;break;
        case 196: pos = 86;break;
        case 192: pos = 87;break;
        case 64: pos = 88;break;
        case 66: pos = 89;break;
        case 74: pos = 90;break;
        case 106: pos = 91;break;
        case 122: pos = 92;break;
        case 120: pos = 93;break;
        case 121: pos = 94;break;
        case 125: pos = 95;break;
        case 253: pos = 96;break;
        case 252: pos = 97;break;
        case 248: pos = 98;break;
        case 232: pos = 99;break;
        case 224: pos = 100;break;
        case 226: pos = 101;break;
        case 98: pos = 102;break;
        case 96: pos = 103;break;
        case 32: pos = 104;break;
        case 33: pos = 105;break;
        case 37: pos = 106;break;
        case 53: pos = 107;break;
        case 61: pos = 108;break;
        case 60: pos = 109;break;
        case 188: pos = 110;break;
        case 190: pos = 111;break;
        case 254: pos = 112;break;
        case 126: pos = 113;break;
        case 124: pos = 114;break;
        case 116: pos = 115;break;
        case 112: pos = 116;break;
        case 113: pos = 117;break;
        case 49: pos = 118;break;
        case 48: pos = 119;break;
        case 16: pos = 120;break;
        case 144: pos = 121;break;
        case 146: pos = 122;break;
        case 154: pos = 123;break;
        case 158: pos = 124;break;
        case 30: pos = 125;break;
        case 94: pos = 126;break;
        case 95: pos = 127;break;
        default: pos = 200;
        }
        return pos;
        }