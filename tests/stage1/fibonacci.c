void print_num(int);
void print(const char *);

int fib(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fib(n-1) + fib(n-2);
}

int main() {
  print_num(fib(5));
  print("\n");
  return 0;
}
