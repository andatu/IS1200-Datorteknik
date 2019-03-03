// Authored by Adam Gustavsson

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int TIMES=0;  //Global för att vi vill inte att den ska resettas för varje anrop
void print_number(int x){
  printf("%10d", x);
  TIMES++;
    if (TIMES%COLUMNS==0) {
      printf("\n");
      TIMES=0;
    }
}

void print_sieves (int max){
int x = 2;
int y = 0;
  char *primes = (char *) malloc(max);  //Allokerar plats på heapen med max bytes

  for (int i = 0; i <= max; i++) {
    *(primes+i)=1;                      //Fyller arrayen med 1:or
  }
  for (int i = 2; i <= max; i++) {      //Kollar om i är en faktor och talet därmed inte är ett primtal
    for (int j=2; i*j<=max; j++) {      //Går igenom alla tal
      *(primes+(i*j))=0;                //Nollar alla tal där i är en faktor
    }
  }

  for (int i = 2; i < max; i++) {
    if(*(primes+i)==1){                 //Kollar om det ligger ett primtal på index if
      print_number(i);                  //Skriver ut i om det ligger ett primtal på det indexet
      if ((i-x)==8){
        y++;
      }
      x=i;
    }
  }
  printf("\nAntal differenser av 8: %d\n", y);
  free(primes);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
