#include "engine.h"

#include <exception>
#include <map>

namespace tul{
namespace project{
namespace rbx{

Dir_t rotate_dir(Dir_t axis, Dir_t dir){
	static std::map<Dir_t, std::map<Dir_t, Dir_t>> ret = {
		{Dir_t::pos_x, {
			{Dir_t::pos_x, Dir_t::pos_x},
			{Dir_t::pos_y, Dir_t::pos_z},
			{Dir_t::pos_z, Dir_t::neg_y},
			{Dir_t::neg_y, Dir_t::neg_z},
			{Dir_t::neg_z, Dir_t::pos_y}
		}},
		{Dir_t::neg_x, {
			{Dir_t::neg_x, Dir_t::neg_x},
			{Dir_t::pos_y, Dir_t::neg_z},
			{Dir_t::neg_z, Dir_t::neg_y},
			{Dir_t::neg_y, Dir_t::pos_z},
			{Dir_t::pos_z, Dir_t::pos_y}
		}},
		{Dir_t::pos_y, {
			{Dir_t::pos_y, Dir_t::pos_y},
			{Dir_t::pos_x, Dir_t::neg_z},
			{Dir_t::neg_z, Dir_t::neg_x},
			{Dir_t::neg_x, Dir_t::pos_z},
			{Dir_t::pos_z, Dir_t::pos_x}
		}},
		{Dir_t::neg_y, {
			{Dir_t::neg_y, Dir_t::neg_y},
			{Dir_t::pos_x, Dir_t::pos_z},
			{Dir_t::pos_z, Dir_t::neg_x},
			{Dir_t::neg_x, Dir_t::neg_z},
			{Dir_t::neg_z, Dir_t::pos_x}
		}},
		{Dir_t::pos_z, {
			{Dir_t::pos_z, Dir_t::pos_z},
			{Dir_t::pos_x, Dir_t::pos_y},
			{Dir_t::pos_y, Dir_t::neg_x},
			{Dir_t::neg_x, Dir_t::neg_y},
			{Dir_t::neg_y, Dir_t::pos_x}
		}},
		{Dir_t::neg_z, {
			{Dir_t::neg_z, Dir_t::neg_z},
			{Dir_t::pos_x, Dir_t::neg_y},
			{Dir_t::neg_y, Dir_t::neg_x},
			{Dir_t::neg_x, Dir_t::pos_y},
			{Dir_t::pos_y, Dir_t::pos_x}
		}}
	};

	//only accept valid inputs
	if (!ret.count(axis) || !ret[axis].count(dir)){
		throw std::exception();
	}

	return ret[axis][dir];
}

void rotate(Cube& cube, Dir_t axis, int times){
	if (times < 0 || times > 3){
		throw std::exception();
	}

	Dir_t look_dir = negate_dir(axis);

	for (int i = 0; i < times; ++i){
		//swap corners
		auto corners = get_visible_corners(look_dir);
		auto temp_corner = cube.corners[corners[3]];
		cube.corners[corners[3]] = cube.corners[corners[2]];
		cube.corners[corners[2]] = cube.corners[corners[1]];
		cube.corners[corners[1]] = cube.corners[corners[0]];
		cube.corners[corners[0]] = temp_corner;

		//set corner orientations
		for (int i = 0; i < 4; ++i){
			cube.corners[corners[i]].dir_1 = rotate_dir(axis, cube.corners[corners[i]].dir_1);
			cube.corners[corners[i]].dir_2 = rotate_dir(axis, cube.corners[corners[i]].dir_2);
		}
		
		//swap edges
		auto edges = get_visible_edges(look_dir);
		auto temp_edge = cube.edges[edges[3]];
		cube.edges[edges[3]] = cube.edges[edges[2]];
		cube.edges[edges[2]] = cube.edges[edges[1]];
		cube.edges[edges[1]] = cube.edges[edges[0]];
		cube.edges[edges[0]] = temp_edge;

		//set edge orientations
		for (int i = 0; i < 4; ++i){
			cube.edges[edges[i]].dir = rotate_dir(axis, cube.edges[edges[i]].dir);
		}

		//TODO swap centers and set center orientations if we have an op that does that
	}
}

void rotate_F(Cube& cube, int times){
	rotate(cube, Dir_t::pos_z, times);
}

void rotate_B(Cube& cube, int times){
	rotate(cube, Dir_t::neg_z, times);
}

void rotate_L(Cube& cube, int times){
	rotate(cube, Dir_t::pos_x, times);
}

void rotate_R(Cube& cube, int times){
	rotate(cube, Dir_t::neg_x, times);
}

void rotate_U(Cube& cube, int times){
	rotate(cube, Dir_t::pos_y, times);
}

void rotate_D(Cube& cube, int times){
	rotate(cube, Dir_t::neg_y, times);
}

}
}
}
