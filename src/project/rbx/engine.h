#ifndef uuid_guard_7f2d6c37_0dab35e7_455b47f4_a8436531
#define uuid_guard_7f2d6c37_0dab35e7_455b47f4_a8436531

#include "cube.h"

namespace tul{
namespace project{
namespace rbx{

Dir_t rotate_dir(Dir_t axis, Dir_t dir);

void rotate_F(Cube& cube, int times);
void rotate_B(Cube& cube, int times);
void rotate_L(Cube& cube, int times);
void rotate_R(Cube& cube, int times);
void rotate_U(Cube& cube, int times);
void rotate_D(Cube& cube, int times);

}
}
}

#endif // uuid_guard_7f2d6c37_0dab35e7_455b47f4_a8436531
