void print_num(int);
void print(const char *);

typedef int INT;

INT f(INT n) {
  INT count 
    = 0;
  while (n != 1) {
    if (n & 1)
      n = 3 * n /* a comment */ + 1;
    else n >>= 1;
    count++;
  }
  return count;
}

INT main() {
  int i = 1;
  for (i = 1; i <= 20; ++i) {
    print_num(f(i));
    print("\n");
  }
  return 0;
}
