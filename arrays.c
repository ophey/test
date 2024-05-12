#include <stdlib.h>
#include <stdio.h>

double data[3][3] = {
  { 1, 2, 3 },
  { 4, 5, 6 },
  { 7, 8, 9 }
};

void cls() {
  printf("\033[H\033[J");
}
      
void at(int x, int y) {
  printf("\033[%d;%dH", y, x);
}

//ESC[7m ESC[27m set inverse/reverse mode
void inverse() {
  printf("\033[7m");
}

void reverse() {
  printf("\033[27m");
}
	  
void key() {
  printf("\nPress key ...");
  getchar();
}

int main() {
  int row, col;
  int x=0, y=0;
  cls();
  at(10,10);
  printf("1234567890");
  at(10,11);
  printf("%10f",12.0);
  key();
  cls();
  for(row = 0; row < 3; row++) {
    for(col = 0; col < 3; col++) {
      at(10*col, row+1);
      if(row == x && col == y) {
	inverse();
      }
      printf("%10f",data[row][col]);      
      if(row == x && col == y) {
	reverse();
      }
    }
  }
  key();
  cls();
  return 0;
}


  
