#include <stdio.h>


int main(void) {
  char c1[6] = "Hello";
  char* c2;
  c2 = c1;
  printf("%p\n", c2);
  printf("%p\n", c2+1);
  printf("%c\n", (*c2));
  printf("%c\n", *(c2+1));
  printf("%c\n", *(c2+2));
  printf("%p\n", c2+1);
}


// Created by Luka Zorin on 2/25/26.
//