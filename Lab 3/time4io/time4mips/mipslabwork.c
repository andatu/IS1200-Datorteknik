/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trise = (volatile int*) 0xbf886100; //volatile pointer, pekar på TRISE
  *trise = *trise & 0xFF00; // sätter bits 0 till 7 = 0 (output)...1111111100000000

  //volatile int * portd = (volatile int*) 0x860D0; behöver inte göra för vi använder pic32mx definition
  TRISD = TRISD | 0xFE0; // sätter bits 5 till 11 = 1 (input)...0000111111100000 0x0FE0
  return;
}

/* This function is called repetitively from the main program */// 64 32 16 8 4 2 1 0
void labwork( void )
{
  volatile int * porte = (volatile int*) 0xbf886110; //skapar pekaren for output
  *porte = 0x0; //sätter värdet till 0

  int switch1;
  int buttons;

  while(1){
    //delay( 1000 );
    buttons = getbtns();
    switch1 = getsw();

    if(buttons & 4){
    //if(buttons == 7 | buttons == 6 | buttons == 5 | buttons == 4){ //button 4, 111, 110  buttons
      mytime = mytime & 0x0FFF;
      mytime = mytime | (switch1 << 12);
    }
    if(buttons & 2){
    //if(buttons == 7 | buttons == 6 | buttons == 3 | buttons == 2){ // button 3, 010
      mytime = mytime & 0xF0FF;
      mytime = mytime | (switch1 << 8);
    }
    if(buttons & 1){
    //if(buttons == 7 | buttons == 5 | buttons == 3 | buttons == 1){ // button 2, 001
      mytime = mytime & 0xFF0F;
      mytime = mytime | (switch1 << 4);
    }
    delay( 1000 );


    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    display_image(96, icon);
    *porte = *porte + 0x1; //adderar porte med 1
  }
}
