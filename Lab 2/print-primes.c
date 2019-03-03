/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/
// Authored by André Aturai

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

int is_prime(int n){
  int x = 0;
  int delbart = 0;
  for (int i = 1; i < n; i++) {
    if(n%i==0){
      delbart++;
    }
  }
  if(delbart>1){
    x=0;
  }
  else{
    x=1;
  }
  return x;
}


void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
  for (int i = 2; i <= n; i++) {
    if(is_prime(i)==1){
      print_number(i);
    }
  }
}



// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
