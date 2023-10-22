// http://akira.ruc.dk/~keld/teaching/algoritmedesign_f03/Artikler/02/Atkinson86.pdf
#include <cmath>

#define LeftChild(i) i<<1
#define RightChild(i) i<<1 + 1
#define Parent(i) i>>1
#define GrandParent(i) i>>2
#define Level(i) int(std::log2(i))

