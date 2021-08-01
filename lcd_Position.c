#define L1  0x80
#define L2  0xC0
#define L3  0x90
#define L4  0xD0

#include "lcd.h"


void lcdPosition(unsigned char line, unsigned char column){

    unsigned char lin=0;
    
    if (line==0){
        lin = L1 + column;
       lcdCommand(lin);
    }
    
    if (line==1){
        lin = L2 + column;
        lcdCommand(lin);
    }
    
    if (line==2){
        lin = L3 + column;
        lcdCommand(lin);
    }
    
    if (line==3){
        lin = L4 + column;
        lcdCommand(lin);
    }
}
