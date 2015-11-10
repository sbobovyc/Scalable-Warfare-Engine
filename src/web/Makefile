CONTENT_DIR = content

all:
	ogr2ogr -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/110m_land.geojson /usr/share/magics/110m/110m_land.shp
	wget -nc http://thematicmapping.org/downloads/TM_WORLD_BORDERS_SIMPL-0.3.zip
	unzip TM_WORLD_BORDERS_SIMPL-0.3.zip -d ${CONTENT_DIR}
	ogr2ogr -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/TM_WORLD_BORDERS_SIMPL-0.3.geojson ${CONTENT_DIR}/TM_WORLD_BORDERS_SIMPL-0.3.shp
