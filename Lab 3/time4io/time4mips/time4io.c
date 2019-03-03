#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
  int switch1 = (PORTD >> 8) & 0x000F;
  return switch1;
}

int getbtns(void){
  int buttons = (PORTD >> 5) & 0x0007;
  return buttons;
}
