void print_num(int);
void print(const char *);

void print_chars(void) {
  char array[3];
  array[1] = '\n';
  array[2] = '\0';
  
  array[0] = L'a';
  print(array);
  array[0] = '\41';
  print(array);

  array[0] = '\x4f';
  print(array);

  array[0] = '\0';
  print(array);

  array[0] = '\43';
  print(array);

  array[0] = '\100';
  print(array);
 
  array[0] = L'\043';
  print(array);

  array[0] = 'ab';    /* implementation defined */
  array[0] = 'a\n\\'; /* implementation defined */
}

int main() {
  print("abfnrtvABFNRTV\n");
  print("\"WHAT \nDO\r YOU GET IF\tYOU MULTIPLY\vSIX BY\\ NINE\?\'\n");
  print("\x0068\x65\154\154o\n");
  print_chars();
  return 0;
}
