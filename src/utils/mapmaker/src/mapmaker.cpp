#include <stdio.h>

#include "libmmaker.hpp"

int main(int argc, char ** argv) {
	//render_thumb(200);
	//render_tiles(200, 50, 50, 1, 1);
	render_tiles(200, 0, 0, 2, 2, TILE_SIZE);
	return 0;
}
