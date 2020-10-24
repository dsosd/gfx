#ifndef uuid_guard_4a7214d8_1b20a4fe_b2ce60e6_560da38d
#define uuid_guard_4a7214d8_1b20a4fe_b2ce60e6_560da38d

#include <array>

namespace tul{
namespace project{
namespace rbx{

enum Color_t{
	red,
	white,
	blue,
	orange,
	yellow,
	green
};

enum Dir_t{
	pos_x,
	neg_x,
	pos_y,
	neg_y,
	pos_z,
	neg_z
};

struct Edge{
	int id;
	Dir_t dir;
};

struct Corner{
	int id;
	Dir_t dir_1;
	Dir_t dir_2;
};

struct Center{
	int id;
};

struct Cube{
	std::array<Edge, 12> edges;
	std::array<Corner, 8> corners;
	std::array<Center, 6> centers;
};

Dir_t negate_dir(Dir_t dir);

Color_t get_corner_color(const Cube& cube, int corner_num, Dir_t look_dir);
Color_t get_edge_color(const Cube& cube, int edge_num, Dir_t look_dir);
Color_t get_center_color(const Cube& cube, int center_num, Dir_t look_dir);

Cube get_solved_cube();

std::array<int, 4> get_visible_corners(Dir_t look_dir);
std::array<int, 4> get_visible_edges(Dir_t look_dir);
std::array<int, 1> get_visible_centers(Dir_t look_dir);

}
}
}

#endif // uuid_guard_4a7214d8_1b20a4fe_b2ce60e6_560da38d
