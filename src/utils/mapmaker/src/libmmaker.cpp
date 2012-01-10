/**
 * @doc http://egsc.usgs.gov/isb/pubs/MapProjections/projections.html
 */
#include <stdio.h>
#include <noise.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "noiseutils.h"
#include "gdal_priv.h"
#include "ogr_spatialref.h"

using namespace noise;

#include "libmmaker.hpp"

void callback(int row) {
    //	printf("row %i\n", row);
}

/**
 */
inline double ppd(double pixels, double degrees) {
    return pixels/degrees;
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

void cyl2lat_long(float angle, float height, float & latitude, float & longitude) {
    latitude = angle;
    longitude = (height > 0.0) ? (height / HEIGHTMAP_BUILDER_Y_HIGH) * 90.0 : (height / HEIGHTMAP_BUILDER_Y_LOW) * -90.0;
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
    angle = ( (x_transformed - 0) / PIXELS_PER_DEGREE_X );
    height = ( ((y_transformed - 0) / THUMBNAIL_MAP_HEIGHT) * HEIGHTMAP_BUILDER_Y_HIGH * 2 );

}


void render_geotif(char * infile, char * outfile, double ulx, double uly, double lrx, double lry) {
    int i;
    GDALDatasetH    hDataset, hOutDS;
    GDALDriverH     hDriver;
    int             bStrict = FALSE;
    char                **papszCreateOptions = NULL;
    GDALProgressFunc    pfnProgress = GDALTermProgress;
    int         nRasterXSize, nRasterYSize;
    int         nBandCount;
    int         *panBandList = NULL;
    const char  *pszSource=infile, *pszDest=outfile, *pszFormat = "GTiff";
    char        *pszOutputSRS = NULL;
    double              adfULLR[4] = { ulx,uly,lrx,lry };
    int                 bGotBounds = TRUE;

    GDALAllRegister();
    OGRSpatialReference oOutputSRS;

    if( oOutputSRS.SetFromUserInput(OGR_PROJECTION) != OGRERR_NONE )
    {
        fprintf( stderr, "Failed to process SRS definition: %s\n", OGR_PROJECTION);
        GDALDestroyDriverManager();
        exit( 1 );
    }
    if ( strcmp(pszSource, pszDest) == 0)
    {
        fprintf(stderr, "Source and destination datasets must be different.\n");
        GDALDestroyDriverManager();
        exit( 1 );
    }

    oOutputSRS.exportToWkt( &pszOutputSRS );

    /* -------------------------------------------------------------------- */
    /*      Attempt to open source file.                                    */
    /* -------------------------------------------------------------------- */

    hDataset = GDALOpenShared( pszSource, GA_ReadOnly );

    if( hDataset == NULL )
    {
        fprintf( stderr,
                "GDALOpen failed - %d\n%s\n",
                CPLGetLastErrorNo(), CPLGetLastErrorMsg() );
        GDALDestroyDriverManager();
        exit( 1 );
    }
    /* -------------------------------------------------------------------- */
    /*      Collect some information from the source file.                  */
    /* -------------------------------------------------------------------- */
    nRasterXSize = GDALGetRasterXSize( hDataset );
    nRasterYSize = GDALGetRasterYSize( hDataset );

    /* -------------------------------------------------------------------- */
    /*  Build band list to translate                    */
    /* -------------------------------------------------------------------- */
    nBandCount = GDALGetRasterCount( hDataset );
    if( nBandCount == 0 )
    {
        fprintf( stderr, "Input file has no bands, and so cannot be translated.\n" );
        GDALDestroyDriverManager();
        exit(1 );
    }

    panBandList = (int *) CPLMalloc(sizeof(int)*nBandCount);
    for( i = 0; i < nBandCount; i++ )
        panBandList[i] = i+1;

//    /* -------------------------------------------------------------------- */
//    /*      Compute the source window from the projected source window      */
//    /*      if the projected coordinates were provided.  Note that the      */
//    /*      projected coordinates are in ulx, uly, lrx, lry format,         */
//    /*      while the anSrcWin is xoff, yoff, xsize, ysize with the         */
//    /*      xoff,yoff being the ulx, uly in pixel/line.                     */
//    /* -------------------------------------------------------------------- */
//    double  adfGeoTransform[6];
//
//    GDALGetGeoTransform( hDataset, adfGeoTransform );
//
//    if( adfGeoTransform[2] != 0.0 || adfGeoTransform[4] != 0.0 )
//    {
//        fprintf( stderr, 
//                "The -projwin option was used, but the geotransform is\n"
//                "rotated.  This configuration is not supported.\n" );
//        GDALClose( hDataset );
//        CPLFree( panBandList );
//        GDALDestroyDriverManager();
//        exit( 1 );
//    }
//
//    anSrcWin[0] = (int) 
//        ((dfULX - adfGeoTransform[0]) / adfGeoTransform[1] + 0.001);
//    anSrcWin[1] = (int) 
//        ((dfULY - adfGeoTransform[3]) / adfGeoTransform[5] + 0.001);
//
//    anSrcWin[2] = (int) ((dfLRX - dfULX) / adfGeoTransform[1] + 0.5);
//    anSrcWin[3] = (int) ((dfLRY - dfULY) / adfGeoTransform[5] + 0.5);
//
//    if( !bQuiet )
//        fprintf( stdout, 
//                "Computed -srcwin %d %d %d %d from projected window.\n",
//                anSrcWin[0], 
//                anSrcWin[1], 
//                anSrcWin[2], 
//                anSrcWin[3] );
//
//    if( anSrcWin[0] < 0 || anSrcWin[1] < 0 
//            || anSrcWin[0] + anSrcWin[2] > GDALGetRasterXSize(hDataset) 
//            || anSrcWin[1] + anSrcWin[3] > GDALGetRasterYSize(hDataset) )
//    {
//        fprintf( stderr, 
//                "Computed -srcwin falls outside raster size of %dx%d.\n",
//                GDALGetRasterXSize(hDataset), 
//                GDALGetRasterYSize(hDataset) );
//        exit( 1 );
//    }
//
//    /* -------------------------------------------------------------------- */
//    /*      Verify source window.                                           */
//    /* -------------------------------------------------------------------- */
//    if( anSrcWin[0] < 0 || anSrcWin[1] < 0 
//            || anSrcWin[2] <= 0 || anSrcWin[3] <= 0
//            || anSrcWin[0] + anSrcWin[2] > GDALGetRasterXSize(hDataset) 
//            || anSrcWin[1] + anSrcWin[3] > GDALGetRasterYSize(hDataset) )
//    {
//        fprintf( stderr, 
//                "-srcwin %d %d %d %d falls outside raster size of %dx%d\n"
//                "or is otherwise illegal.\n",
//                anSrcWin[0],
//                anSrcWin[1],
//                anSrcWin[2],
//                anSrcWin[3],
//                GDALGetRasterXSize(hDataset), 
//                GDALGetRasterYSize(hDataset) );
//        exit( 1 );
//    }
/* -------------------------------------------------------------------- */
/*      Find the output driver.                                         */
/* -------------------------------------------------------------------- */
    hDriver = GDALGetDriverByName( pszFormat );
    if( hDriver == NULL )
    {
        int iDr;
        
        printf( "Output driver `%s' not recognised.\n", pszFormat );
        printf( "The following format drivers are configured and support output:\n" );
        for( iDr = 0; iDr < GDALGetDriverCount(); iDr++ )
        {
            GDALDriverH hDriver = GDALGetDriver(iDr);

            if( GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATE, NULL ) != NULL
                || GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATECOPY,
                                        NULL ) != NULL )
            {
                printf( "  %s: %s\n",
                        GDALGetDriverShortName( hDriver  ),
                        GDALGetDriverLongName( hDriver ) );
            }
        }
        printf( "\n" );
        
        GDALClose( hDataset );
        CPLFree( panBandList );
        GDALDestroyDriverManager();
        exit( 1 );
    }
       hOutDS = GDALCreateCopy( hDriver, pszDest, hDataset, 
                                 bStrict, papszCreateOptions, 
                                 pfnProgress, NULL );

        if( hOutDS != NULL )
            GDALClose( hOutDS );
        
        GDALClose( hDataset );

        CPLFree( panBandList );

        CSLDestroy( papszCreateOptions );
}

void render_tile(module::Perlin & terrain, int octaves, float tile_ul_x, float tile_ul_y, float tile_size_x, float tile_size_y, int output_width, int output_height, char * name) {
    module::Const water;
    water.SetConstValue(-1.0);

    module::Billow waterBillow;
    waterBillow.SetOctaveCount(octaves);
    waterBillow.SetFrequency (0.5);

    module::RidgedMulti mountainTerrain;
    mountainTerrain.SetOctaveCount(octaves);
    mountainTerrain.SetFrequency(0.5);

    module::Billow baseFlatTerrain;
    baseFlatTerrain.SetOctaveCount(octaves);
    baseFlatTerrain.SetFrequency (2.0);

    module::ScaleBias flatTerrain;
    flatTerrain.SetSourceModule (0, baseFlatTerrain);
    flatTerrain.SetScale (0.175);
    flatTerrain.SetBias (0.05);

    module::Select terrainSelector;
    terrainSelector.SetSourceModule (0, flatTerrain);
    terrainSelector.SetSourceModule (1, mountainTerrain);
    terrainSelector.SetControlModule (terrain);
    terrainSelector.SetBounds (0.0, 1000.0);
    terrainSelector.SetEdgeFalloff (0.25);

    module::Select waterSelector;
    waterSelector.SetSourceModule(0, terrainSelector);
    waterSelector.SetSourceModule(1, water);
    waterSelector.SetControlModule(waterBillow);
    waterSelector.SetBounds (0.0, 1000.0);
    waterSelector.SetEdgeFalloff (0.5);

    module::Turbulence finalTerrain;
    finalTerrain.SetSourceModule(0, waterSelector);
    finalTerrain.SetFrequency(8.0);
    finalTerrain.SetPower(0.001);

    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderCylinder heightMapBuilder;
    heightMapBuilder.SetSourceModule (finalTerrain);
    heightMapBuilder.SetDestNoiseMap (heightMap);
    heightMapBuilder.SetCallback(*callback);
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);

    heightMapBuilder.SetDestSize (output_width, output_height);
    float upper_x = 0.0;
    float upper_y = 0.0;
    float lower_x = 0.0;
    float lower_y = 0.0;
    float tile_lr_x = tile_ul_x + tile_size_x * PIXELS_PER_DEGREE_X;
    float tile_lr_y = tile_ul_y + tile_size_y * PIXELS_PER_DEGREE_Y;

    printf("Tile coordinates in image space: (ulx, uly)=(%f,%f) (lrx, lry)=(%f,%f) \n", tile_ul_x, tile_ul_y, tile_lr_x, tile_lr_y);
    xy2cyl(tile_ul_x, tile_ul_y, lower_x, upper_y);
    xy2cyl(tile_lr_x, tile_lr_y, upper_x, lower_y);
    printf("Tile coordinates in cylinder space: (lx, ly)=(%f,%f) (ux, uy)=(%f,%f) \n", lower_x, lower_y, upper_x, upper_y);
    float ul_latitude;
    float ul_longitude;
    float lr_latitude;
    float lr_longitude;
    cyl2lat_long(lower_x, upper_y, ul_latitude, ul_longitude);
    cyl2lat_long(upper_x, lower_y, lr_latitude, lr_longitude);
    printf("Tile coordinates in lat/long: (ulx, uly)=(%f,%f) (lrx, lry)=(%f,%f) \n", ul_latitude, ul_longitude, lr_latitude, lr_longitude);
    heightMapBuilder.SetBounds (lower_x, upper_x, lower_y, upper_y);
    double horizontal_resolution = METERS_PER_DEGREE_X / ppd(output_width, tile_size_x);
    double vertical_resolution = METERS_PER_DEGREE_Y / ppd(output_height, tile_size_y);
    printf("Tile horizontal resolution %f km per pixel\n", horizontal_resolution);
    printf("Tile vertical resolution %f km per pixel\n", vertical_resolution);
    printf("Tile horizontal pixels per degree %f \n", ppd(output_width, tile_size_x));
    printf("Tile vertical pixels per degree %f \n", ppd(output_height, tile_size_y));
    heightMapBuilder.Build ();
    renderer.ClearGradient ();
    renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
    renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
    renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
    renderer.AddGradientPoint ( 0.0125, utils::Color (240, 240,  64, 255)); // sand
    renderer.AddGradientPoint ( 0.0250, utils::Color ( 32, 160,   0, 255)); // grass
    renderer.AddGradientPoint ( 0.3750, utils::Color (139, 169,  19, 255)); // dirt
    renderer.AddGradientPoint ( 0.7500, utils::Color ( 92,  51,  23, 255)); // rock
    renderer.AddGradientPoint ( 0.9000, utils::Color (125, 125, 125, 255)); // mixed rock and snow
    renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
    renderer.EnableLight ();
    renderer.SetLightContrast (3.0);
    renderer.SetLightBrightness (2.0);
    renderer.Render ();

    utils::Color color = image.GetValue(0,0);
    printf("R:%i G:%i B:%i A:%i \n", color.red, color.green, color.blue, color.alpha);
    utils::WriterBMP writer;
    writer.SetSourceImage (image);
    char final_name[100];
    sprintf(final_name, "%s_%f_%f_%f_%f.bmp", name, tile_ul_x, tile_ul_y, tile_lr_x, tile_lr_y);
    printf("%s \n", final_name);
    writer.SetDestFilename (final_name);
    writer.WriteDestFile ();

    //render_geotif(final_name, "out.tif", ul_latitude, ul_longitude, lr_latitude, lr_longitude);
}

/**
 * 30*e^(-x/5) + 10
 */
int get_octaves(double tile_size) {
    int octave = ceil( 30 * exp( -tile_size / 5.0 ) + 10 );

    if(octave > noise::module::PERLIN_MAX_OCTAVE)
        octave = noise::module::PERLIN_MAX_OCTAVE;
    return octave;
}

/**
 * @param x The upper left x coordinate in image space.
 * @param y The upper left y coordinate in image space.
 * @param x_count Number of horizontal tiles. 
 * @param y_count Number of vertical tiles. 
 * @param tile_size Size of each tile in degrees.
 */
void render_tiles(int seed, int x, int y, int x_count, int y_count, float tile_size_x, float tile_size_y, int output_width, int output_height, char * name) {
    module::Perlin terrain;
    terrain.SetSeed(seed);

    int octaves = get_octaves( (tile_size_x + tile_size_y / 2.0) );
    terrain.SetOctaveCount(octaves);

    printf("Octave count %i \n", octaves);

    for(int i = 0; i < x_count; i++) {
        for(int j = 0; j < y_count; j++) {
            float tile_ul_x = x + i * tile_size_x * PIXELS_PER_DEGREE_X;
            float tile_ul_y = y + j * tile_size_y * PIXELS_PER_DEGREE_Y;
            render_tile(terrain, octaves, tile_ul_x, tile_ul_y, tile_size_x, tile_size_y, output_width, output_height, name);
        }
    }
}

/**
 * @param seed
 * This function generates a thumbnail of a planet using a cylindrical projection. More accurately, this is a Mercator projection.
 */
void render_thumb(int seed, char * name) {
    module::Perlin terrain;
    terrain.SetSeed(seed);
    render_tile(terrain, 10, 0, 0, 360, 180, THUMBNAIL_MAP_WIDTH, THUMBNAIL_MAP_HEIGHT, name);
}
