//Nome: Pierre Willian Graciano 
//Projeto Final - ECOP04 - #Jogo da Velha#

#include "bits.h"
#include "lcd.h"
#include "pwm.h"
#include "delay.h"
#include "keypad.h"
#include "io.h"
#include "lcd_Position.h"
#include "ssd.h"
#include <pic18f4520.h>

#define L1  0x80
#define L2  0xC0
#define L3  0x90
#define L4  0xD0
#define ON  0x0F

//===============IMPRESSAO DA IMAGEM===============
void simbolo(void) {

    unsigned char i;
    unsigned char velha[48] = {
        0x00, 0x00, 0x07, 0x0E, 0x1E, 0x1E, 0x1E, 0x19,
        0x07, 0x0E, 0x1F, 0x00, 0x0A, 0x00, 0x11, 0x0E,
        0x00, 0x00, 0x1C, 0x0E, 0x0F, 0x0F, 0x0F, 0x13,
        0x01, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00,
        0x1F, 0x04, 0x0C, 0x14, 0x1F, 0x04, 0x0A, 0x11,
        0x10, 0x00, 0x03, 0x04, 0x1F, 0x04, 0x03, 0x00
    };

    lcdInit();
    lcdCommand(0x40);

    for (i = 0; i < 48; i++) {
        lcdData(velha[i]);
    }

    lcdCommand(L1 + 13); //a imagem começa do final do LCD
    lcdData(0);
    lcdData(1);
    lcdData(2);
    lcdCommand(L2 + 13);
    lcdData(3);
    lcdData(4);
    lcdData(5);

    for (i = 0; i < 1; i++) {

        for (i = 0; i < 20; i++) {
            atraso_ms(150);
            lcdCommand(0x18); //move para esquerda
        }
    }
}
//=================================================

//====================INSTRUCOES===================
void instrucoes(void) {

    unsigned char a[16] = {">>INSTRUCOES:   "};
    unsigned char b[16] = {"Use os botoes de"};
    unsigned char c[16] = {"1 a 9 para posi-"};
    unsigned char d[16] = {"cionar X ou O   "};
    unsigned char i;

    lcdInit();

    for (i = 0; i < 17; i++) {
        lcdData(a[i]);
    }

    lcdCommand(L2);
    for (i = 0; i < 17; i++) {
        lcdData(b[i]);
    }

    lcdCommand(L3);
    for (i = 0; i < 17; i++) {
        lcdData(c[i]);
    }

    lcdCommand(L4);
    for (i = 0; i < 17; i++) {
        lcdData(d[i]);
    }

    atraso_ms(1000);
    atraso_ms(1000);
    atraso_ms(1000);
}
//=================================================

//===================MENU INICIAL==================
void menu_inicial(void) {

    unsigned char a[16] = {"# TIC-TAC-TOE # "};
    unsigned char b[16] = {"Seja Bem-Vindo  "};
    unsigned char c[16] = {"Dev: Pierre     "};
    unsigned char d[16] = {"[#]-> Instrucoes"};
    unsigned char i;

    lcdInit();

    for (i = 0; i < 17; i++) {
        lcdData(a[i]);
    }

    lcdCommand(L2);
    for (i = 0; i < 17; i++) {
        lcdData(b[i]);
    }

    lcdCommand(L3);
    for (i = 0; i < 17; i++) {
        lcdData(c[i]);
    }

    lcdCommand(L4);
    for (i = 0; i < 17; i++) {
        lcdData(d[i]);
    }
}
//=================================================

//======================COOLER=====================
void cooler(int v) {

    if (v == 1)
        TRISCbits.RC2 = 1;

    else
        TRISCbits.RC2 = 0;

    atraso_ms(2000);
}
//=================================================

//===================FIM DE JOGO===================
void fim_de_jogo() {

    char saida = 0xAA;
    char led = 0;
    
    unsigned char i, j;
    
    unsigned char x[16] = {"FIM DE JOGO     "};
    unsigned char y[16] = {"                "};
    unsigned char z[16] = {"Pressione o bo- "};
    unsigned char k[16] = {"tao RESET       "};
    
    ssdInit();
    lcdInit();
    
    cooler(1);

    for (i = 0; i < 17; i++) {
        lcdData(x[i]);
    }

    lcdCommand(L2);
    for (i = 0; i < 17; i++) {
        lcdData(y[i]);
    }

    lcdCommand(L3);
    for (i = 0; i < 17; i++) {
        lcdData(z[i]);
    }

    lcdCommand(L4);
    for (i = 0; i < 17; i++) {
        lcdData(k[i]);
    }
    
    TRISEbits.TRISE0 = 0; //RELE 1
    for (i = 0; i < 10; i++) {
        PORTEbits.RE0 ^= 1;
        atraso_ms(100);
        atraso_ms(100);
    }
    PORTEbits.RE0 = 0;
    
    TRISCbits.TRISC0 = 0; //RELE 2
    for (i = 0; i < 10; i++) {
        PORTCbits.RC0 ^= 1;
        atraso_ms(100);
        atraso_ms(100);
    }
    PORTCbits.RC0 = 0;
   
    atraso_ms(10000);
}
//=================================================

//==================INICIO DO JOGO=================
void inicio_do_jogo(void) {

    unsigned char tempo = 0, i;
    unsigned int tecla = 16;
    unsigned char coluna = 0, linha = 0;

    unsigned char x = 'X', o = 'O';

    unsigned char linha1[16] = {"################"};
    unsigned char linha2[16] = {"[ ]   [ ]   [ ]"};
    unsigned char linha3[16] = {"[ ]   [ ]   [ ]"};
    unsigned char linha4[16] = {"[ ]   [ ]   [ ]"};

    kpInit();
    lcdInit();
    lcdCommand(ON);
    kpDebounce();

    for (i = 0; i < 17; i++) {
        lcdData(linha1[i]);
    }

    lcdCommand(L2);
    for (i = 0; i < 17; i++) {
        lcdData(linha2[i]);
    }

    lcdCommand(L3);
    for (i = 0; i < 17; i++) {
        lcdData(linha3[i]);
    }

    lcdCommand(L4);
    for (i = 0; i < 17; i++) {
        lcdData(linha4[i]);
    }
}
//=================================================

//=====================MAIN========================
void main(void) {
    
    TRISD = 0x00;
    PORTD = 0x00;

    int tempo = 16, aux = 0, botao = 0, i, jogadas=0;
    unsigned int tecla = 0;

    char variavel[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    unsigned char x = 'X', o = 'O', coluna = 0, linha = 0;
    unsigned char a, num=0;
    
    kpInit();
    lcdInit();
    pwmInit();

    simbolo();
    menu_inicial();

    while (aux != 1) {
        kpDebounce();
        if (kpRead() != tempo) {
            tempo = kpRead();

            if (bitTst(tempo, 8)) {
                instrucoes();
                atraso_ms(5000);
                aux++;
            }
        }
    }
    inicio_do_jogo();
    
    num = 0x01;
    for (a = 0; a < 8; a++) {
        PORTD += num;
        num = num << 1;
        atraso_ms(300);
        }   

    for (;;) {

        while (aux != 15) {
            kpDebounce();

            if (kpRead() != tecla) {
                tecla = kpRead();

                //POSICIONAR X e O

                if (bitTst(tecla, 3)) { //BOTAO 1

                    linha = 1;
                    coluna = 1;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[0] = 'X';

                    if (bitTst(tecla, 3)&&(botao == 2)) { //BOTAO 1            
                        linha = 1;
                        coluna = 1;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[0] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 7)) { //BOTAO 2
                    linha = 1;
                    coluna = 7;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    variavel[1] = 'X';

                    if (bitTst(tecla, 7)&&(botao == 2)) { //BOTAO 2            
                        linha = 1;
                        coluna = 7;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[1] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 11)) { //BOTAO 3
                    linha = 1;
                    coluna = 13;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[2] = 'X';

                    if (bitTst(tecla, 11)&&(botao == 2)) { //BOTAO 3           
                        linha = 1;
                        coluna = 13;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[2] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 2)) { //BOTAO 4   
                    linha = 2;
                    coluna = 1;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[3] = 'X';

                    if (bitTst(tecla, 2)&&(botao == 2)) { //BOTAO 4              
                        linha = 2;
                        coluna = 1;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[3] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 6)) { //BOTAO 5  
                    linha = 2;
                    coluna = 7;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[4] = 'X';

                    if (bitTst(tecla, 6)&&(botao == 2)) { //BOTAO 5              
                        linha = 2;
                        coluna = 7;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[4] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 10)) { //BOTAO 6
                    linha = 2;
                    coluna = 13;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[5] = 'X';

                    if (bitTst(tecla, 10)&&(botao == 2)) { //BOTAO 6             
                        linha = 2;
                        coluna = 13;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[5] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 1)) { //BOTAO 7
                    linha = 3;
                    coluna = 1;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[6] = 'X';

                    if (bitTst(tecla, 1)&&(botao == 2)) { //BOTAO 7           
                        linha = 3;
                        coluna = 1;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[6] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 5)) { //BOTAO 8
                    linha = 3;
                    coluna = 7;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[7] = 'X';

                    if (bitTst(tecla, 5)&&(botao == 2)) { //BOTAO 8
                        linha = 3;
                        coluna = 7;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[7] = 'O';
                    }
                    aux++;
                }

                if (bitTst(tecla, 9)) { //BOTAO 9
                    linha = 3;
                    coluna = 13;
                    lcdPosition(linha, coluna);
                    lcdData(x);
                    botao++;
                    variavel[8] = 'X';

                    if (bitTst(tecla, 9)&&(botao == 2)) { //BOTAO 9
                        linha = 3;
                        coluna = 13;
                        lcdPosition(linha, coluna);
                        lcdData(o);
                        botao = 0;
                        variavel[8] = 'O';
                    }
                    aux++;
                }
            }
    
            if ((variavel[0] != ' ') && (variavel[1] != ' ') && (variavel[2] != ' ') && 
                    (variavel[3] != ' ') && (variavel[4] != ' ') && (variavel[5]!= ' ') && 
                    (variavel[6] != ' ') && (variavel[7] != ' ') && (variavel[8] != ' ')) {
                
                atraso_ms(2000);
                fim_de_jogo();
            
            }
        }                       
    }
}