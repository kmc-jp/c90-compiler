void print_num(int);
void print(const char *);

int main(void) {
  int a;
  a = 1 + 5 * 8 + 1;
  print_num(a);
  print("\n");
  a = 100 / 200 * 200;
  print_num(a);
  print("\n");
  a = 1 - 20 / 10 * 4 + 10;
  print_num(a);
  print("\n");
  a = 1 - 10 - 100;
  print_num(a);
  print("\n");
  a = 1024 / 512 / 2;
  print_num(a);
  print("\n");
  return 0;
}
