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

int prime = 1234567;
int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  timeoutcount++;

  if(timeoutcount == 10){
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
    tick(&mytime);
    timeoutcount = 0;
  }
  IFSCLR(0) = 0x100;  //Resetting flag


  if ((IFS(0) & 0x800) | (IFS(0) & 0x900) ){
    mytime = mytime + 0x3;
  }
  IFSCLR(0) = 0x800;

  return;
}


/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trise = (volatile int*) 0xbf886100; //volatile pointer, pekar på TRISE
  *trise = *trise & 0xFF00; // sätter bits 0 till 7 = 0 (output)...1111111100000000

  volatile int * porte = (volatile int*) 0xbf886110; //skapar pekaren for output
  *porte = 0x0; //sätter värdet till 0

  *porte = *porte + 0x1; //adderar porte med 1

  //volatile int * portd = (volatile int*) 0x860D0; behöver inte göra för vi använder pic32mx definition
  TRISD = TRISD | 0x0FE0; // sätter bits 5 till 11 = 1 (input)...0000111111100000

  T2CON = 0x0;                    //Stoppar timer och clearar control register
  T2CONSET =  0x70;               //Sätter prescale till 1:256
  PR2 = 0x7A12;                   //(80 000 000 / 256) / 10 Perioden till 10ggr per sekund, från föreläsningslide
  TMR2 = 0x0;                     //Resettar timern
  T2CONSET = 0x8000;              //Sätter på timern

  IEC(0) = 0x900;  //1001 0000 0000 //Ändrar bit 8 till 1, enligt referensmanualerna
  IPC(2) = 0x1F00001F;                  //0001 1111

//  IEC(0) = 0x800;  1000 0000 0000

  enable_interrupt();             // kallar på interruptfunktionen


  return;
}


/* This function is called repetitively from the main program */// 64 32 16 8 4 2 1 0
void labwork( void )
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();



/*
  int switch1;
  int buttons;


    buttons = getbtns();
    switch1 = getsw();

    if(buttons == 7 | buttons == 6 | buttons == 5 | buttons == 4){ //button 4, 100
      mytime = mytime & 0x0FFF;
      mytime = mytime | (switch1 << 12);
    }
    if(buttons == 7 | buttons == 6 | buttons == 3 | buttons == 2){ // button 3, 010
      mytime = mytime & 0xF0FF;
      mytime = mytime | (switch1 << 8);
    }
    if(buttons == 7 | buttons == 5 | buttons == 3 | buttons == 1){ // button 2, 001
      mytime = mytime & 0xFF0F;
      mytime = mytime | (switch1 << 4);
    }
    //delay( 1000 );

    if (IFS(0) & 0x100) { // kollar flaggan

      timeoutcount++; // ökar countern
      IFSCLR(0) = 0x100;  //Resetting flag
    }

    if(timeoutcount == 10){
      timeoutcount = 0;

      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      display_image(96, icon);

    }*/

}
