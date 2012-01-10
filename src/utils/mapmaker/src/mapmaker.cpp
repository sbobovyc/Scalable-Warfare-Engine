#include <stdio.h>

#include "libmmaker.hpp"

int main(int argc, char ** argv) {
	char name[] = "world_one_map";
	render_thumb(200, name);
    int cell_height = 2; //km
    int cell_width = 2;
    float size_x = 80 * cell_height / METERS_PER_DEGREE_X; //degree
    float size_y = 80 * cell_width / METERS_PER_DEGREE_Y;
    int width = 80 * CELL_SIZE;
    int height = 80 * CELL_SIZE;

	//render_tiles(200, 1260, 280, 1, 1, size_x, size_y, width, height, name);
	render_tiles(200, 1260, 280, 1, 1, 15, 30, 512, 512, name);
	//render_tiles(200, 1260, 280, 1, 1, 15, 15, 512, 256, name);
	//render_tiles(200, 1260, 280, 1, 1, 5, 5, 512, 256, name);
	return 0;
}
