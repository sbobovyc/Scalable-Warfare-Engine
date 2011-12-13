export LD_LIBRARY_PATH=.
./mapmaker
convert world_one_map.bmp -edge 1 -colorspace Gray world_one_map_mask.png
convert world_one_map_mask.png -blur 0x2.0 world_one_map_mask_blur.png
convert world_one_map_mask_blur.png -threshold 10% world_one_map_thresh.pgm

gdal_translate -of GTiff -a_srs "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" -a_ullr -180 90 180 -90 world_one_map.bmp world_one_map.tif
gdal_translate -of GTiff -a_srs "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" -a_ullr -180 90 180 -90 world_one_map_thresh.pgm world_one_map_thresh.tif
