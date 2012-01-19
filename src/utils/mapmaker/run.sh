export LD_LIBRARY_PATH=.
./mapmaker
#Method 1
#convert world_one_map.bmp -negate -morphology EdgeOut Diamond -colorspace Gray world_one_edge.png
#convert world_one_edge.png -blur 0x2.0 world_one_edge_blur.png
#convert world_one_edge_blur.png -threshold 5% world_one_thresh.png
#convert world_one_thresh.png -negate -morphology Edge Diamond -colorspace Gray world_one_borders.png

#Method 2
convert world_one_map.bmp -negate -morphology EdgeOut Diamond -colorspace Gray world_one_edge.png
convert world_one_edge.png -threshold 10% world_one_thresh.png
convert world_one_thresh.png -morphology Close Disk:2 world_one_close.png
convert world_one_close.png -morphology EdgeIn Plus world_one_borders.png

#gdal_translate -of GTiff -a_srs "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" -a_ullr -180 90 180 -90 world_one_map.bmp world_one_map.tif
#gdal_translate -of GTiff -a_srs "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" -a_ullr -180 90 180 -90 world_one_borders.png world_one_borders.tif
#gdal_polygonize.py world_one_borders.tif -f "ESRI Shapefile" world_one_borders.shp
#ogr2ogr -f SQLite world_one_borders.sqlite world_one_borders.shp -dsco spatialite=yes
#
