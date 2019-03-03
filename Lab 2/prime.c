/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/
// Authored by Adam Gustavsson


#include <stdio.h>

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

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
