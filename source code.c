/*
 * Author: Mehmet KAHRAMAN
 * LCD Calculator Project
 */

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

// CONFIG
#pragma config FOSC = XT        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF     
#pragma config BOREN = ON       
#pragma config LVP = ON         
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF      

// LCD config
#define RS RA2
#define RW RA1
#define E RA0

// KEYPAD config
#define satir_1 RB0
#define satir_2 RB1
#define satir_3 RB2
#define satir_4 RB3
#define sutun_1 RB4
#define sutun_2 RB5
#define sutun_3 RB6
#define sutun_4 RB7

// Functions
void Lcd_komut(unsigned char k);
void Lcd_putch(char veri);
void Lcd_puts(char *veri);
void Lcd_init(void);
void Lcd_clear(void);
char Keypad_oku(void);
int get_num(char ch);
void Memory_reset(void);
float power(int b);

// Variables
float num_high=0;
float num_low=0;
float deger1=0;
float deger2=0;
float result=0;
float diffValue=0;
int count_1=0;
int count_2=0;
int result1=0;
int result2=0;
char point_pass=0;
char point_key=0;
char operator_key=0;
char operator='0';
char str[8];

void main(void) {
    
    signed char tus;
    
    TRISA=0x00;
    TRISB=0xF0;
    TRISC=0x00;
    ADCON1=0x06;
    OPTION_REG=0x80;
    __delay_ms(500);
    
    // ACILIS 
    Lcd_init();
    Lcd_puts("Hesap Makinesi");
    Lcd_komut(0xC0);
    Lcd_puts("Mehmet Kahraman");
    __delay_ms(2000);
    Lcd_clear();

    while(1){
        tus = Keypad_oku();

        if(tus!='!'){
            if(tus=='c'){
                Lcd_clear();
                Memory_reset();
                deger1=0;
                deger2=0;
                operator='0';
                operator_key=0;
            }
            else{
            
                if(tus=='+' || tus=='-' || tus=='*' || tus=='/'){
                    if(operator_key==0){
                        if(tus=='+'){
                            operator='+';
                        }
                        if(tus=='-'){
                            operator='-';
                        }
                        if(tus=='*'){
                            operator='*';
                        }
                        if(tus=='/'){
                            operator='/';
                        }
                       
                        Lcd_putch(tus);
                        operator_key=1;

                        if(count_2==0){
                            deger1 = num_high;   
                        }
                        else{
                            deger1 = num_high + num_low/power(count_2);
                        }

                        Memory_reset();
                    }
                    

                }
                else if(tus=='.' && point_key==0){
                    Lcd_putch(tus);
                    point_pass=1;
                    point_key=1;

                }
                else if(tus=='='){
                    Lcd_putch(tus);
                    if(operator=='0'){
                        Lcd_clear();
                        Memory_reset();
                        Lcd_puts("Hatali giris!");
                    }
                    else{
                        if(count_2==0){
                            deger2 = num_high;   
                        }
                        else{
                            deger2 = num_high + num_low/power(count_2);
                        }
                    }
                    if(operator=='+'){
                        result = deger1 + deger2;
                    }
                    if(operator=='-'){
                        result = deger1 - deger2;
                    }
                    if(operator=='*'){
                        result = deger1 * deger2;
                    }
                    if(operator=='/'){
                        result = deger1 / deger2;
                    }
                    
                    result1 = (int)result;
                    diffValue = result - (float)result1;
                    result2 = (int)(diffValue * 100.0);

                    Lcd_komut(0xC0);
                    sprintf(str,"%d",result1);
                    Lcd_puts(str);
                    Lcd_putch('.');
                    sprintf(str,"%d",result2);
                    Lcd_puts(str);

                }
                else{  // rakam
                    if(count_1<7 && count_2<4){
                        Lcd_putch(tus);
                        if(point_pass==0){
                            count_1=count_1+1;
                            if(count_1==1){
                                num_high = get_num(tus);
                            }
                            else{
                                num_high = num_high*10 + get_num(tus);
                            }
                        }
                        
                        else{
                            count_2=count_2+1;
                            if(count_2==1){
                                num_low = get_num(tus);
                            }
                            else{
                                num_low = num_low*10 + get_num(tus);
                            }
                        }
                    }
                }
            }
        }
    } 
}

// FUNCTIONS -------------------------------------------------------------------

float power(int b){
    float sonuc=1;
    for(int i=1;i<=b;i++){
        sonuc = sonuc*10;
    }
    return sonuc;
}

void Memory_reset(void){
    num_high=0;
    num_low=0;
    point_key=0;
    point_pass=0;
    count_1=0;
    count_2=0;
    result=0;
    diffValue=0;
    result1=0;
    result2=0;
}

char Keypad_oku(void){
    signed char tus='!';
    signed int sayac = 0;
    PORTB=0;
    
    satir_1=1;
    if(sutun_1==1){
        tus='1';
        while(sutun_1==1);
        __delay_ms(20);
    }
    if(sutun_2==1){
        tus='2';
        while(sutun_2==1);
        __delay_ms(20);
    }
    if(sutun_3==1){
        tus='3';
        while(sutun_3==1);
        __delay_ms(20);
    }
    if(sutun_4==1){
        tus='+';
        while(sutun_4==1);
        __delay_ms(20);
    }
    satir_1=0;
    
    satir_2=1;
    if(sutun_1==1){
        tus='4';
        while(sutun_1==1);
        __delay_ms(20);
    }
    if(sutun_2==1){
        tus='5';
        while(sutun_2==1);
        __delay_ms(20);
    }
    if(sutun_3==1){
        tus='6';
        while(sutun_3==1);
        __delay_ms(20);
    }
    if(sutun_4==1){
        tus='-';
        while(sutun_4==1);
        __delay_ms(20);
    }
    satir_2=0;
    
    satir_3=1;
    if(sutun_1==1){
        tus='7';
        while(sutun_1==1);
        __delay_ms(20);
    }
    if(sutun_2==1){
        tus='8';
        while(sutun_2==1);
        __delay_ms(20);
    }
    if(sutun_3==1){
        tus='9';
        while(sutun_3==1);
        __delay_ms(20);
    }
    if(sutun_4==1){
        tus='*';
        while(sutun_4==1);
        __delay_ms(20);
    }
    satir_3=0;
    
    satir_4=1;
    if(sutun_1==1){
        tus='.';
        while(sutun_1==1);
        __delay_ms(20);
    }
    if(sutun_2==1){
        tus='0';
        while(sutun_2==1);
        __delay_ms(20);
    }
    if(sutun_3==1){
        tus='=';
        while(sutun_3==1){
            sayac=sayac+1;
            if(sayac==320){
                tus='c';
                sayac=0;
                Lcd_clear();
            }
            __delay_ms(5);
        }
        __delay_ms(20);
    }
    if(sutun_4==1){
        tus='/';
        while(sutun_4==1);
        __delay_ms(20);
    }
    satir_4=0;
    
    return tus;
}

void Lcd_komut(unsigned char k){
    PORTC=k;
    RS=0;
    RW=0;
    E=1;
    __delay_ms(1);
    E=0;
}

void Lcd_putch(char veri){
    PORTC=veri;
    RS=1;
    RW=0;
    E=1;
    __delay_ms(1);
    E=0;
}

void Lcd_puts(char *veri){
    int i;
	for(i=0;veri[i]!='\0';i++){
        Lcd_putch(veri[i]);
    }
}

void Lcd_init(void){
    Lcd_komut(0x38); //2 satir 5*7 matrix
    __delay_ms(250);
    Lcd_komut(0x0E); //display ve kursor acik
    __delay_ms(15);
    Lcd_komut(0x01); //Ekrani temizle
    __delay_ms(15);
}

void Lcd_clear(void){
    Lcd_komut(0x00);
    Lcd_komut(0x01);
    Lcd_komut(0x80);
}

int get_num(char ch){
    switch(ch){
        case '0': return 0; break;
        case '1': return 1; break;
        case '2': return 2; break;
        case '3': return 3; break;
        case '4': return 4; break;
        case '5': return 5; break;
        case '6': return 6; break;
        case '7': return 7; break;
        case '8': return 8; break;
        case '9': return 9; break;
    }
    return 0;
}