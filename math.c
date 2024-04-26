#include <stdio.h>

typedef double (function)(double[]);

double add(double args[]) {
  return args ? args[0] + args[1] :  2.0;
}

double subtract(double args[]) {
  return args ? args[0] - args[1] :  2.0;
}

double multiply(double args[]) {
  return args ? args[0] * args[1] :  2.0;
}

double divide(double args[]) {
  return args ? args[0] / args[1] :  2.0;
}

double stack[4];
int top = 0;

void push(double val) {
  stack[top++] = val;
}


double apply(function f) {
  int arity = f(NULL);
  top -= arity;
  return f(&stack[top]);
}

void show() {
  for(int i = 0; i < top; i++) {
    printf("%d : %f\n", i, stack[i]);
  }
  printf("--------------\n");
}

int main(int argc, char **argv) {
  push(2.0);
  push(3.0);
  push(4.0);
  show();
  push(apply(&multiply));
  show();
  push(apply(&add));
  show();
  push(7.0);
  show();
  push(apply(&divide));
  show();
  push(1.0);
  show();
  push(apply(&subtract));
  show();
  return(0);
}
