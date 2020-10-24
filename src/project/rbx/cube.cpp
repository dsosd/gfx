#include "cube.h"

#include <exception>

namespace tul{
namespace project{
namespace rbx{

Dir_t negate_dir(Dir_t dir){
	switch (dir){
	case Dir_t::pos_x:
		return Dir_t::neg_x;
	case Dir_t::neg_x:
		return Dir_t::pos_x;
	case Dir_t::pos_y:
		return Dir_t::neg_y;
	case Dir_t::neg_y:
		return Dir_t::pos_y;
	case Dir_t::pos_z:
		return Dir_t::neg_z;
	case Dir_t::neg_z:
		return Dir_t::pos_z;
	default:
		throw std::exception();
	}
}

Color_t get_corner_color(const Cube& cube, int corner_num, Dir_t look_dir){
	if (corner_num < 0 || corner_num > 7){
		throw std::exception();
	}

	static Color_t colors[8 * 3] = {
		Color_t::red, Color_t::white, Color_t::blue,
		Color_t::red, Color_t::white, Color_t::green,
		Color_t::red, Color_t::blue, Color_t::yellow,
		Color_t::red, Color_t::yellow, Color_t::green,
		Color_t::white, Color_t::blue, Color_t::orange,
		Color_t::white, Color_t::orange, Color_t::green,
		Color_t::blue, Color_t::orange, Color_t::yellow,
		Color_t::orange, Color_t::yellow, Color_t::green
	};

	//match using if-else with corner dir_1/dir_2
	Dir_t request_dir = negate_dir(look_dir);

	if (request_dir == cube.corners[corner_num].dir_1){
		return colors[3 * cube.corners[corner_num].id];
	}
	else if (request_dir == cube.corners[corner_num].dir_2){
		return colors[3 * cube.corners[corner_num].id + 1];
	}
	else{
		return colors[3 * cube.corners[corner_num].id + 2];
	}
}

Color_t get_edge_color(const Cube& cube, int edge_num, Dir_t look_dir){
	if (edge_num < 0 || edge_num > 11){
		throw std::exception();
	}

	static Color_t colors[12 * 2] = {
		Color_t::red, Color_t::white,
		Color_t::red, Color_t::blue,
		Color_t::red, Color_t::yellow,
		Color_t::red, Color_t::green,
		Color_t::white, Color_t::blue,
		Color_t::white, Color_t::orange,
		Color_t::white, Color_t::green,
		Color_t::blue, Color_t::orange,
		Color_t::blue, Color_t::yellow,
		Color_t::orange, Color_t::yellow,
		Color_t::orange, Color_t::green,
		Color_t::yellow, Color_t::green
	};

	//match using if-else with edge dir
	Dir_t request_dir = negate_dir(look_dir);

	if (request_dir == cube.edges[edge_num].dir){
		return colors[2 * cube.edges[edge_num].id];
	}
	else{
		return colors[2 * cube.edges[edge_num].id + 1];
	}
}

Color_t get_center_color(const Cube& cube, int center_num, Dir_t look_dir){
	if (center_num < 0 || center_num > 5){
		throw std::exception();
	}

	static Color_t colors[6 * 1] = {
		Color_t::red,
		Color_t::white,
		Color_t::blue,
		Color_t::orange,
		Color_t::yellow,
		Color_t::green
	};

	return colors[1 * cube.centers[center_num].id];
}

Cube get_solved_cube(){
	Cube ret;

	ret.centers = {{
		{0},
		{1},
		{2},
		{3},
		{4},
		{5}
	}};

	ret.edges = {{
		{0, Dir_t::pos_y},
		{1, Dir_t::pos_y},
		{2, Dir_t::pos_y},
		{3, Dir_t::pos_y},
		{4, Dir_t::pos_z},
		{5, Dir_t::pos_z},
		{6, Dir_t::pos_z},
		{7, Dir_t::pos_x},
		{8, Dir_t::pos_x},
		{9, Dir_t::neg_y},
		{10, Dir_t::neg_y},
		{11, Dir_t::neg_z}
	}};

	ret.corners = {{
		{0, Dir_t::pos_y, Dir_t::pos_z},
		{1, Dir_t::pos_y, Dir_t::pos_z},
		{2, Dir_t::pos_y, Dir_t::pos_x},
		{3, Dir_t::pos_y, Dir_t::neg_z},
		{4, Dir_t::pos_z, Dir_t::pos_x},
		{5, Dir_t::pos_z, Dir_t::neg_y},
		{6, Dir_t::pos_x, Dir_t::neg_y},
		{7, Dir_t::neg_y, Dir_t::neg_z}
	}};

	return ret;
}

std::array<int, 4> get_visible_corners(Dir_t look_dir){
	switch (look_dir){
	case Dir_t::neg_x:
		return {0, 4, 6, 2};
	case Dir_t::pos_x:
		return {1, 3, 7, 5};
	case Dir_t::neg_y:
		return {0, 2, 3, 1};
	case Dir_t::pos_y:
		return {4, 5, 7, 6};
	case Dir_t::neg_z:
		return {0, 1, 5, 4};
	case Dir_t::pos_z:
		return {2, 6, 7, 3};
	default:
		throw std::exception();
	}
}

std::array<int, 4> get_visible_edges(Dir_t look_dir){
	switch (look_dir){
	case Dir_t::neg_x:
		return {1, 4, 7, 8};
	case Dir_t::pos_x:
		return {3, 11, 10, 6};
	case Dir_t::neg_y:
		return {0, 1, 2, 3};
	case Dir_t::pos_y:
		return {5, 10, 9, 7};
	case Dir_t::neg_z:
		return {0, 6, 5, 4};
	case Dir_t::pos_z:
		return {2, 8, 9, 11};
	default:
		throw std::exception();
	}
}

std::array<int, 1> get_visible_centers(Dir_t look_dir){
	switch (look_dir){
	case Dir_t::neg_x:
		return {2};
	case Dir_t::pos_x:
		return {5};
	case Dir_t::neg_y:
		return {0};
	case Dir_t::pos_y:
		return {3};
	case Dir_t::neg_z:
		return {1};
	case Dir_t::pos_z:
		return {4};
	default:
		throw std::exception();
	}
}

}
}
}
