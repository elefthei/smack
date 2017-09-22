#include "smack.h"

// The assertion will fail without flag `--split-aggregate-values`.

// @flag --split-aggregate-values
// @expect verified

typedef struct {
  int x;
  int y;
  int z;
} S;

S foo() {
  S s;
  s.x = 1;
  s.y = 2;
  s.z = 3;
  return s;
}

int main() {
  S s = foo();
  assert(s.z == 3);
  return 0;
}
