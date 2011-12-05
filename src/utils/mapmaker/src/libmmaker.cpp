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
	//printf("row %i\n", row);
}

/**
 * @param seed
 * This function generates a thumbnail of a planet using a cylindrical projection. More accurately, this is a Mercator projection.
 */
void render_thumb(int seed) {
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
	int width = 16200;
	float resolution = EARTH_WIDTH/width;
	int height = 8100;
	heightMapBuilder.SetDestSize (width, height);
	heightMapBuilder.SetBounds (-180.0, 180.0, -2.0, 2.0);
	printf("Resolution %f km per pixel\n", EARTH_WIDTH/width);
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

void render_tile(module::Perlin & myModule, int i, int j, float tile_height, float tile_width) {

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderCylinder heightMapBuilder;
	heightMapBuilder.SetSourceModule (myModule);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetCallback(*callback);
	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap (heightMap);
	renderer.SetDestImage (image);
	int width = 512;
	int height = 460;
	heightMapBuilder.SetDestSize (width, height);
	heightMapBuilder.SetBounds (-90.0, 90.0, -1.0, 1.0);
	printf("Resolution %f km per pixel\n", EARTH_WIDTH/width);
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
	sprintf(name, "tile%i%i.bmp", i, j);
	writer.SetDestFilename (name);
	writer.WriteDestFile ();
}

void render_tiles(int seed, float tile_height, float tile_width, int x_tiles, int y_tiles) {

	module::Perlin myModule;
	myModule.SetSeed(seed);
	
	for(int i = 0; i < x_tiles; i++) {
		for(int j = 0; j < y_tiles; j++) {
			render_tile(myModule, i, j, tile_height, tile_width);
		}
	}

}

