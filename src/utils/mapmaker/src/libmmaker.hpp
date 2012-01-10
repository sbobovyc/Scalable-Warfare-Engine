#ifndef LIBMMAKER_H
#define LIBMMAKER_H

#define THUMBNAIL_MAP_WIDTH 1620			/// in pixels
#define THUMBNAIL_MAP_HEIGHT (THUMBNAIL_MAP_WIDTH / 2) 	/// in pixels
#define EARTH_WIDTH 40075.017 /// in km
#define EARTH_HEIGTH 12713.6  /// in km
#define PIXELS_PER_DEGREE_X (THUMBNAIL_MAP_WIDTH / 360.0)
#define PIXELS_PER_DEGREE_Y (THUMBNAIL_MAP_HEIGHT / 180.0)
#define METERS_PER_DEGREE_X EARTH_WIDTH / 360.0
#define METERS_PER_DEGREE_Y EARTH_HEIGTH / 180.0
#define TILE_SIZE 6					/// in degrees
#define CELL_SIZE 52                /// in pixels
#define HEIGHTMAP_BUILDER_Y_LOW -2.0
#define HEIGHTMAP_BUILDER_Y_HIGH 2.0
#define OGR_PROJECTION "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs"

extern "C" double round_li(double f);
extern "C" void xy2cyl(int x, int y, float & angle, float & height);
extern "C" void render_thumb(int seed, char * name);
extern "C" void render_tiles(int seed, int x, int y, int x_count, int y_count, float tile_size_x, float tile_size_y, int output_width, int output_height, char * name);
#endif /* LIBMMAKER_H */
