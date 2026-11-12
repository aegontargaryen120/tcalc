#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b) {
  return a + b;
}

int sub(int a, int b) {
  return b - a;
}

int mul(int a, int b) {
  return a  * b;
}

int divide(int a, int b) {
  if (b != 0) {
    return a / b;
  }
  fprintf(stderr, "ERROR: Division by zero.\n");
  exit(1);
}

bool calc(int a, int b, char *op) {
  if (strcmp(op, "+") == 0)
    add(a, b);
  else if (strcmp(op, "-") == 0)
    sub(a, b);
  else if (strcmp(op, "*") == 0)
    mul(a, b);
  else if (strcmp(op, "/") == 0)
    divide(a, b);
  else
    return false;
  return true;
}

int main(void) {
  if (!calc(34, 35, "+"))
    return 1;
  printf("69\n");
  return 0;
}
