CONTENT_DIR = content

convert:
	#ogr2ogr -skipfailures -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/110m_land.geojson /usr/share/magics/110m/110m_land.shp
	#ogr2ogr -skipfailures -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/TM_WORLD_BORDERS_SIMPL-0.3.geojson ${CONTENT_DIR}/TM_WORLD_BORDERS_SIMPL-0.3.shp
	## admin borders
	#ogr2ogr -skipfailures -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/SYR_adm0.geojson ${CONTENT_DIR}/SYR_adm0.shp
	#ogr2ogr -skipfailures -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/SYR_adm1.geojson ${CONTENT_DIR}/SYR_adm1.shp
	#ogr2ogr -skipfailures -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/SYR_adm2.geojson ${CONTENT_DIR}/SYR_adm2.shp
	ogr2ogr -skipfailures -f GeoJSON -t_srs crs:84 ${CONTENT_DIR}/TUR_adm0.geojson ${CONTENT_DIR}/TUR_adm0.shp

download:
	wget -nc http://thematicmapping.org/downloads/TM_WORLD_BORDERS_SIMPL-0.3.zip
	unzip -n TM_WORLD_BORDERS_SIMPL-0.3.zip -d ${CONTENT_DIR}
	# administrative borders
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/SYR_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/TUR_adm_shp.zip
	unzip -n SYR_adm_shp.zip -d ${CONTENT_DIR}
	unzip -n TUR_adm_shp.zip -d ${CONTENT_DIR}


