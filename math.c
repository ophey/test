#include <stdio.h>
char* OP = NULL;

typedef double (function)(double[]);

double stack[4];
int top = 0;

void push(double val) {
  stack[top++] = val;
}

double pop(double args[]) {
  return args ? args[0] : 1.0;
}

void drop() {
  top -= 1;
}


double apply(function f) {
  int arity = f(NULL);
  top -= arity;
  return f(&stack[top]);
}


double add(double args[]) {
  OP = "+";
  return args ? args[0] + args[1] :  2.0;
}

double subtract(double args[]) {
  OP = "-";
  return args ? args[0] - args[1] :  2.0;
}

double multiply(double args[]) {
  OP = "*";
  return args ? args[0] * args[1] :  2.0;
}

double divide(double args[]) {
  OP = "/";
  return args ? args[0] / args[1] :  2.0;
}

double square(double args[]) {
  OP = "^2";
  return args ? args[0] * args[0] : 1.0;
}


double pwr(double x, double y) {
  push(1.0);
  int times = y;
  function *f;
  if(y) {
    f = (times > 0 ? &multiply : &divide);
    times = times > 0 ? times : times * -1;
    for(int i = 0; i < times; i++) {
      push(x);
      push(apply(f));
    }
    return apply(&pop);
  } else {
    return 1.0;
  }
  
}

double power(double args[]) {
  double result = args ? pwr(args[0], args[1]) : 2.0;
  OP = "^";
  return result;
}


void show() {
  printf("-------------- %s\n", OP ? OP : "");
  OP = NULL;
  for(int i = 0; i < top; i++) {
    printf("%d : %f\n", i, stack[i]);
  }
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
  push(apply(&square));
  show();
  push(1.0);
  show();
  push(apply(&subtract));
  show();
  push(3.0);
  show();
  push(apply(&power));
  show();
  return(0);
}
