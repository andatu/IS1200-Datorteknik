#include <stdio.h>

void CalculateFaculty(int a)
{
  int result = a;
  int factor1;
  int factor2 = a;
    for(int i=1; i<a-1; i++)
    {
      factor1 = result;
      for(int i=1; i<factor2-1; i++)
      {
        result += factor1;
      }
      factor2--;
    }
  printf("%d\n", result);

}



int main(int argc, char const *argv[]) {
  CalculateFaculty(6);
  return 0;
}
