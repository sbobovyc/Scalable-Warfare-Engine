# Bulk convert shapefiles to geojson using ogr2ogr
# Outputs as geojson with the crs:84 SRS (for use on GitHub or elsewhere)

CONTENT_DIR=./content
mkdir -p ${CONTENT_DIR}

function shp2geojson() {
    ogr2ogr -f GeoJSON -t_srs crs:84 "$1.geojson" "$1.shp"
}

#unzip all files in a directory
for var in *.zip; do unzip -n "$var" -d ${CONTENT_DIR} ; done

cd ${CONTENT_DIR}

#convert all shapefiles
for var in *.shp; do shp2geojson ${var%\.*}; done
