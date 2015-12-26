void print_num(int);
void print(const char *);

void f(int n) {
  int a = n & 2, b = n & 1;
  if (a)
    if (b)
      print("42");
    else
      print("54");

  if (a)
    if (b)
      print("42");
  else
    print("54");
}

int main(void) {
  int i;
  for (i = 0; i < 4; ++i) f(i);
  print("\n");
  return 0;
}
