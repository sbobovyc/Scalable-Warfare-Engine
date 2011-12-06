#ifndef LIBMMAKER_H
#define LIBMMAKER_H

#define THUMBNAIL_MAP_WIDTH 1620			/// in pixels
#define THUMBNAIL_MAP_HEIGHT (THUMBNAIL_MAP_WIDTH / 2) 	/// in pixels
#define EARTH_WIDTH 40075.017 /// in km
#define EARTH_HEIGTH 12713.6  /// in km
#define PIXELS_PER_DEGREE (THUMBNAIL_MAP_WIDTH / 360.0)
#define TILE_SIZE 6					/// in degrees
#define HEIGHTMAP_BUILDER_Y_LOW -2.0
#define HEIGHTMAP_BUILDER_Y_HIGH 2.0

extern "C" double round_li(double f);
extern "C" void xy2cyl(int x, int y, float & angle, float & height);
extern "C" void render_thumb(int);
extern "C" void render_tiles(int seed, int x, int y, int x_count, int y_count, float tile_size);
#endif /* LIBMMAKER_H */
