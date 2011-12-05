#ifndef LIBMMAKER_H
#define LIBMMAKER_H

#define EARTH_WIDTH 40075.017 /// in km
#define EARTH_HEIGTH 12713.6  /// in km

extern "C" void render_thumb(int);
void render_tiles(int seed, float tile_height, float tile_width, int x_tiles, int y_tiles);
#endif /* LIBMMAKER_H */
