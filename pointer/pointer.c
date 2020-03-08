int main(void) {
  int *p, *q;
  int **r;
  int i, j, k;

  i = 5;
  p = &i;
  q = p;
  j = *q;
  r = &q;
  k = **r;

  return 0;
}