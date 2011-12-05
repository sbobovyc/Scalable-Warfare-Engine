export LD_LIBRARY_PATH=.
./mapmaker
gdal_translate -of GTiff -a_srs "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" -a_ullr -180 90 180 -90 tutorial.bmp tutorial.tif

