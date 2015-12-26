void print_num(int);
void print(const char *);

void put_num(int n) {
  print_num(n);
  print("\n");
}

int collatz() {
  int n = 27;
  
  while (n != 1) {
    put_num(n);
    
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = 3 * n + 1;
    }
    
    if (n > 1000) {
      return n;
    }
  }
  return -1;
}

int main(void) {
  int i;

  i = 0;
  for (;;) {
    put_num(i++);
    if (i > 5) { break; }
  }

  i = collatz();
  put_num(i);

  for (i = 0; i < 10; ++i) {
    if (i & 1) { continue; }
    put_num(i);
  }

  i = 1;
loop_head:
  put_num(i);
  i = i * 2;
  if (i > 1000) goto loop_tail;
  goto loop_head;
loop_tail:
  
  return 0;
}
