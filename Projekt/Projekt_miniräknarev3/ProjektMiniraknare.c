#include <stdio.h>
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


//char inputnbr[];

//Globala variabler
int x = 0;              // Input number
int v0 = 0;             // Resultat
int counter1 = 0;       // Counter för interruptions switch 4
int op=0;               // Vilken operation skall utföras
int buttons = 0;        // Sparar värdet för buttons 2-4
int button1 = 0;        // Sparar värdet för button 1
int y=0;                // Varibel för att spara x-värdet
int dw = 0;             // Sätts till 1 när interuption för switch4 sker
int dw2 = 0;            // Sätts till ett om interuptions för switch 4 sker i läget där operation väljs
char binaryNum[16] = {48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48};  // Används för att konvertera från dec till bin
int done = 0;
int counterhex;

void converttobin(){    // Konverterar resultatet till bin (Author: André)
    int k;
    for(k=0; k<16; k++){      // Rensar binaryNum
      binaryNum[k] = 48;
    }
      done=1;                 // Talet ska visas på displayen i binärt ellr hex
      int i = 15;
      int v;
      int j = 0;
      v = v0;
      //sätter binärt"två komp"
        while (v != 0) {
          if((v%2 == 1) || (v%2 == -1)){
            binaryNum[i] = 49;
          }
          else{
            binaryNum[i] = 48;
          }
          v = v / 2;
          i--;
        }
        //////////////////////////////////

        //sätter binärt negativt "två komp"
        if(v0<0){
          for(i = 0; i<16; i++){
            if(binaryNum[i] == 48){
              binaryNum[i] = 49;
            }
            else {
              binaryNum[i] = 48;
            }
          }
          j=15;
          while(j>=0){
            if(binaryNum[j] == 48){
              binaryNum[j] = 49;
              break;
            }
            binaryNum[j] = 48;
            j--;
          }
          //////////////////////////
          //rensar 1or negativt binärt
        /*
          j=0;
          while((binaryNum[j] == 49) && (j<16)){
            if (binaryNum[j] == 48){
              break;
            }
            binaryNum[j] = 32;
            j++;
          /////////////////////////
        }
        binaryNum[j-1] = 49;
        */
      }
        ///////////////////////////////////////////////////////////////

        //rensar vi 0or på positivt binärt
      /*
        j=0;
        if(v0>=0){
        while ((binaryNum[j] == 48) && (j<16)){
          if(binaryNum[j] == 49){
            break;
          }
          binaryNum[j] = 32;
          j++;
        }
        binaryNum[j-1] = 48;
      }
      */

      volatile int * porte = (volatile int*) 0xbf886110; //skapar pekaren for output
      *porte = v0; //sätter värdet till 0
}

void converttohex(){            // Konverterar resultatet till hex (Author: Adam)
  int i = 0;
  int j=15;
  int ha;
  int hb;
  int hc;
  int hd;
  for(i = 15; i>=0; i = i-4){  // Kollar 4 bitar åt gången
    ha = ((binaryNum[i] % 2) * 1);
    hb = ((binaryNum[i-1] % 2) * 2);
    hc = ((binaryNum[i-2] % 2) * 4);
    hd = ((binaryNum[i-3] % 2) * 8);
    binaryNum[j] = hexasc(ha+hb+hc+hd); // Lägger in 4 bitar per plats på 4 första arrayplatserna
    j--;
  }
  j=0;
  for(j=0; j<=11; j++){
    binaryNum[j] = 32;           // Lägger in mellanslag på platser som inte ska displayas
  }
}

void operations( void ){ //Gör operationerna (Author: André)
  if (op == 1){
    v0 = v0 + x;
  }
  if (op == 2){
    v0 = v0 - x;
  }
  if (op == 3){
    v0 = v0 * x;
  }
  if (op == 4){
    v0 = v0 / x;
  }
  if (op == 5){
    //Give Bin
    converttobin();
  }
  if (op == 6){
   //Give Hex
   converttobin();
   converttohex();
  }
  op = 0;
  return;
}

void setoper(void){ //Tilldelar vilken operation som ska göras (Author: Adam)
  if(buttons & 4){
    op = 1;
  }
  if(buttons & 2){
    op = 2;
  }
  if(buttons & 1){
    op = 3;
  }
  if(button1 & 1){
    op = 4;
  }
}

void setop2(void){ // Tilldelar vilken operations som ska göras (Author: Adam)
  if(buttons & 4){
    op = 5;
  }
  if(buttons & 2){
    op = 6;
  }
}

void dowhat ( void ){//Skärm med olika val för operationer (Author: André)
  if (dw == 1){      //Kollar om interuptions har skett på sw1
    dw = 0;
    dw2 = 0;
    if (counter1 == 0){  //Första fallet där vi sätter in x till v0.
      counter1 ++;
      v0 = v0 + x;
      x=0;
      display_string(0, itoaconv(v0));//skärm 1.1
      display_string(1,"\0");
      display_string(2,"Button for op");
      display_string(3,"+ - * /");
      display_update();
      buttons = getbtns();
      button1 = getbtn1();
        while((buttons==0) && (button1==0)){
          if (dw2 == 1){
            display_string(0, itoaconv(v0));//skärm 1.2
            display_string(1,"\0");
            display_string(2,"Show base");
            display_string(3,"2 16");
            display_update();
            buttons = getbtns();
            setop2();
            }
          else{
            buttons = getbtns();
            button1 = getbtn1();
            setoper();
         }
        }
        dw2 = 0;  //resettar våra variabler
        buttons = 0;
        button1 = 0;
    }

    else { // alla andra fall
      operations(); //utför operationer
      display_string(0, itoaconv(v0)); //uppdaterar skärmen 2.1
      display_string(1,"\0");
      display_string(2,"Button for op");
      display_string(3,"+ - * /");
      display_update();
      buttons = getbtns();
      button1 = getbtn1();
      while((buttons==0) && (button1==0)){
        if (dw2 == 1){
          display_string(0, itoaconv(v0));// skärm 2.2
          display_string(1,"\0");
          display_string(2,"Show base");
          display_string(3,"2 16");
          display_update();
          buttons = getbtns();
          setop2();
        }
        else{
          buttons = getbtns();
          button1 = getbtn1();
          setoper();
        }
      }
      dw2 = 0; //resettar våra variabler
      buttons = 0;
      button1 = 0;
      y = x;
      x = 0;
    }
  }

  else {
    return;
  }
}



void user_isr( void ){     //(Author: Adam)
  if(IFS(0) & 0x80000){  //Kollar om switch 4 är aktiverad

    if (x > -10){
    x++;
    }
    else{
      x--;
      if (x%10 == 0){
        x = x+10;
      }
    }
    if((x>10) && (x%10==0) && (x!=0)){
    x = x - 10;
    }

    if((x%10 == 0) && (x > 0) && (x <= 10)){
      x = x - 19;
    }
  IFSCLR(0)=0x80000;
  }

  if(IFS(0) & 0x8000){  //Kollar om switch 3 är aktiverad
    x = x/10;
  IFSCLR(0)=0x8000;
  }

  if(IFS(0) & 0x800){  //Kollar om switch 2 är aktiverad
    x = x*10;
  IFSCLR(0)=0x800;
  }

  if(IFS(0) & 0x80){  //Kollar om switch 1 är aktiverad
    dw = 1; //variabler som sätts för att uföra olika funktioner
    dw2 = 1;
    done = 0;
    volatile int * porte = (volatile int*) 0xbf886110; //skapar pekaren for output
    *porte = 0;
    IFSCLR(0) = 0x80;
 }
 IFSCLR(0) = 0x88880;
}


void labinit( void ){ //(Author: Adam)

  volatile int * trise = (volatile int*) 0xbf886100; //volatile pointer, pekar på TRISE
  *trise = *trise & 0xFF00; // sätter bits 0 till 7 = 0 (output)...1111111100000000

  TRISFSET = 2;
  buttons = getbtns();
  button1 = getbtn1();
  TRISD = TRISD | 0xF0;
  delay(100000);
  //Clearar allt utom "Calculator"
  display_string(1,"\0");
  display_string(2,"\0");
  display_string(3,"\0");
  display_update();

  //Enable interupt för switcharna
  IEC(0) = 0x88880;
  IPC(1) = 0x1f000000;
  IPC(2) = 0x1f000000;
  IPC(3) = 0x1f000000;
  IPC(4) = 0x1f000000;
  enable_interrupt();

}

void labwork( void ){ //(Author: André)

    if(done == 1){
      display_string(0, binaryNum);
      display_string(1, "\0");
      display_string(2, "\0");
      display_string(3, itoaconv(x));
      display_update();
    }
    else if(dw==1){
      dowhat();
    }
    else{
    display_string(0, itoaconv(v0));
    display_string(1, "\0");
    display_string(2, "\0");
    display_string(3, itoaconv(x));
    display_update();
    }


}
