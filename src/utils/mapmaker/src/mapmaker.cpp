#include <stdio.h>

#include "libmmaker.hpp"

int main(int argc, char ** argv) {
	char name[] = "world_one_map";
	render_thumb(200, name);
	render_tiles(200, 1260, 280, 1, 1, 30, 30, 512, 256, name);
	//render_tiles(200, 1260, 280, 1, 1, 15, 15, 512, 256, name);
	//render_tiles(200, 1260, 280, 1, 1, 5, 5, 512, 256, name);
	return 0;
}
