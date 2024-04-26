#include <stdio.h>
#include <float.h>

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

double stack[4] = { 0.0, 0.0, 0.0, 0.0 };
int top = 0;

void push(double val) {
  stack[top++] = val;
}

double pop() {
  return stack[top--];
}

double apply(function f) {
  int arity = f(NULL);
  top -= arity;
  return f(&stack[top]);
}

int main(int argc, char **argv) {
  push(2.0);
  push(3.0);
  push(4.0);
  push(apply(&multiply));
  push(apply(&add));
  push(7.0);
  push(apply(&divide));
  push(1.0);
  push(apply(&subtract));
  
  printf("%d : %f", top, stack[top - 1]);
  return(0);
}
