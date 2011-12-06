/**
 * @doc http://egsc.usgs.gov/isb/pubs/MapProjections/projections.html
 */
#include <stdio.h>
#include <noise.h>
#include <math.h>
#include "noiseutils.h"

using namespace noise;

#include "libmmaker.hpp"

void callback(int row) {
	//	printf("row %i\n", row);
}

/**
 * Round to largest integer quantity.
 */
double round_li(double f) {
	if(f > 0.0 ) {
		return ceil(f);
	} else if(f < 0.0) {
		return -ceil(-f);
	} else {
		return 0.0;
	}
}

/**
 * @param x The x coordinate in image space.
 * @param y The y coordinate in image space.
 * @param angle The pointer to an angle in cylinder space.
 * @param height The the pointer a height in cylinder space.
 */
void xy2cyl(int x, int y, float & angle, float & height) {
	float center_x = THUMBNAIL_MAP_WIDTH / 2.0;
	float center_y = THUMBNAIL_MAP_HEIGHT / 2.0;
	float x_transformed = x - center_x;
	float y_transformed = -1.0 * (y - center_y);

	//printf("%i %i  %f %f \n", x, y, x_transformed, y_transformed);
	angle = ( (x_transformed - 0) / PIXELS_PER_DEGREE );
	height = ( ((y_transformed - 0) / THUMBNAIL_MAP_HEIGHT) * HEIGHTMAP_BUILDER_Y_HIGH * 2 );

}

void noises() {
	module::RidgedMulti mountainTerrain;
	//mountainTerrain.SetOctaveCount(1);
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule (mountainTerrain);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetDestSize (256, 256);
	heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
	heightMapBuilder.Build ();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);
	renderer.ClearGradient ();
	renderer.BuildGrayscaleGradient();
	renderer.EnableLight ();
	renderer.SetLightContrast (3.0);
	renderer.SetLightBrightness (2.0);
	renderer.Render ();

	utils::WriterBMP writer;
	writer.SetSourceImage (image);
	writer.SetDestFilename ("mountainTerrain.bmp");
	writer.WriteDestFile ();	

	module::Billow baseFlatTerrain;
	baseFlatTerrain.SetOctaveCount(1);
	baseFlatTerrain.SetFrequency (2.0);
	
	heightMapBuilder.SetSourceModule (baseFlatTerrain);
        heightMapBuilder.SetDestNoiseMap (heightMap);
        heightMapBuilder.SetDestSize (256, 256);
        heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
        heightMapBuilder.Build ();
	
	renderer.SetSourceNoiseMap (heightMap);
        renderer.SetDestImage (image);
        renderer.ClearGradient ();
        renderer.BuildGrayscaleGradient();
        renderer.EnableLight ();
        renderer.SetLightContrast (3.0);
        renderer.SetLightBrightness (2.0);
        renderer.Render ();

	writer.SetSourceImage (image);
	writer.SetDestFilename ("baseFlatTerrain.bmp");
	writer.WriteDestFile ();

	  module::ScaleBias flatTerrain;
  flatTerrain.SetSourceModule (0, baseFlatTerrain);
  flatTerrain.SetScale (0.125);
	
	heightMapBuilder.SetSourceModule (flatTerrain);
        heightMapBuilder.SetDestNoiseMap (heightMap);
        heightMapBuilder.SetDestSize (256, 256);
        heightMapBuilder.SetBounds (6.0, 10.0, 1.0, 5.0);
        heightMapBuilder.Build ();

        renderer.SetSourceNoiseMap (heightMap);
        renderer.SetDestImage (image);
        renderer.ClearGradient ();
        renderer.BuildGrayscaleGradient();
        renderer.EnableLight ();
        renderer.SetLightContrast (3.0);
        renderer.SetLightBrightness (2.0);
        renderer.Render ();

        writer.SetSourceImage (image);
        writer.SetDestFilename ("flatTerrain.bmp");
        writer.WriteDestFile ();	
}
/**
 * @param seed
 * This function generates a thumbnail of a planet using a cylindrical projection. More accurately, this is a Mercator projection.
 */
void render_thumb(int seed) {
	noises();
	module::Perlin myModule;
	myModule.SetSeed(seed);

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderCylinder heightMapBuilder;
	heightMapBuilder.SetSourceModule (myModule);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetCallback(*callback);
	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);
	int width = THUMBNAIL_MAP_WIDTH;
	int height = THUMBNAIL_MAP_HEIGHT;
	heightMapBuilder.SetDestSize (width, height);
	heightMapBuilder.SetBounds (-180.0, 180.0, HEIGHTMAP_BUILDER_Y_LOW, HEIGHTMAP_BUILDER_Y_HIGH);
	//float resolution = EARTH_WIDTH/width;
	//printf("Resolution %f km per pixel\n", EARTH_WIDTH/width);
	heightMapBuilder.Build ();
	renderer.ClearGradient ();
	renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
	renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
	renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
	renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
	renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
	renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
	renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
	renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
	renderer.EnableLight ();
	renderer.SetLightContrast (3.0);
	renderer.SetLightBrightness (2.0);
	renderer.Render ();

	utils::WriterBMP writer;
	writer.SetSourceImage (image);
	writer.SetDestFilename ("tutorial.bmp");
	writer.WriteDestFile ();
}

void render_tile(module::Perlin & terrain, int tile_ul_x, int tile_ul_y, float tile_size) {
	//module::RidgedMulti mountainTerrain;

	//module::Billow baseFlatTerrain;
	//baseFlatTerrain.SetFrequency (2.0);

	//module::ScaleBias flatTerrain;
	//flatTerrain.SetSourceModule (0, baseFlatTerrain);
	//flatTerrain.SetScale (0.125);
	//flatTerrain.SetBias (-0.25);

	//module::Select terrainSelector;
	//terrainSelector.SetSourceModule(0, flatTerrain);
	//terrainSelector.SetSourceModule(1, mountainTerrain);
	//terrainSelector.SetControlModule (terrain);
	//terrainSelector.SetBounds (0.0, 1000.0);
	//terrainSelector.SetEdgeFalloff (0.125);

	//module::Turbulence myModule;
	//myModule.SetFrequency(4.0);
	//myModule.SetSourceModule (0, terrainSelector);

	//module::Turbulence myModule;
	//myModule.SetFrequency(1.0);
	//myModule.SetPower(0.25);
	//myModule.SetSourceModule (0, terrain);

	//module::Add finalTerrain;
	//finalTerrain.SetSourceModule(0, terrain);
	//finalTerrain.SetSourceModule(1, flatTerrain);

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderCylinder heightMapBuilder;
	heightMapBuilder.SetSourceModule (terrain);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetCallback(*callback);
	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);
	int width = 512;
	int height = 512;
	heightMapBuilder.SetDestSize (width, height);
	float upper_x = 0.0;
	float upper_y = 0.0;
	float lower_x = 0.0;
	float lower_y = 0.0;
	int tile_lr_x = tile_ul_x + tile_size * PIXELS_PER_DEGREE;
	int tile_lr_y = tile_ul_y + tile_size * PIXELS_PER_DEGREE;
	printf("%i %i    %i %i \n", tile_ul_x, tile_ul_y, tile_lr_x, tile_lr_y);
	xy2cyl(tile_ul_x, tile_ul_y, lower_x, upper_y);
	xy2cyl(tile_lr_x, tile_lr_y, upper_x, lower_y);
	printf("%f %f    %f %f \n", lower_x, lower_y, upper_x, upper_y);
	heightMapBuilder.SetBounds (lower_x, upper_x, lower_y, upper_y);
	//printf("Resolution %f km per pixel\n", EARTH_WIDTH/width);
	heightMapBuilder.Build ();
	renderer.ClearGradient ();
	renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
	renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
	renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
	renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
	renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
	renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
	renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
	renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
	renderer.EnableLight ();
	renderer.SetLightContrast (3.0);
	renderer.SetLightBrightness (2.0);
	renderer.Render ();

	utils::WriterBMP writer;
	writer.SetSourceImage (image);
	char name[100];
	sprintf(name, "tile_%i_%i.bmp", tile_ul_x, tile_ul_y);
	writer.SetDestFilename (name);
	writer.WriteDestFile ();
}

/**
 * 30*e^(-x/5) + 10
 */
int get_octaves(double tile_size) {
	return ceil( 30 * exp( -tile_size / 5.0 ) + 10 );
}

/**
 * @param x The upper left x coordinate in image space.
 * @param y The upper left y coordinate in image space.
 * @param x_count Number of horizontal tiles. 
 * @param y_count Number of vertical tiles. 
 * @param tile_size Size of each tile in degrees.
 */
void render_tiles(int seed, int x, int y, int x_count, int y_count, float tile_size) {

	module::Perlin myModule;
	myModule.SetSeed(seed);
	int octaves = get_octaves(tile_size);
	myModule.SetOctaveCount(octaves);
	printf("Octave count %i \n", octaves);

	for(int i = 0; i < x_count; i++) {
		for(int j = 0; j < y_count; j++) {
			int tile_ul_x = x + i * tile_size * PIXELS_PER_DEGREE;
			int tile_ul_y = y + j * tile_size * PIXELS_PER_DEGREE;
			render_tile(myModule, tile_ul_x, tile_ul_y, tile_size);
		}
	}
}

