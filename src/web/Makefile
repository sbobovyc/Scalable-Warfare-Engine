CONTENT_DIR = content

convert:
	bash geojson-conversion.sh
	python ../utils/geonames2geojson.py
    
download:
	wget -nc http://thematicmapping.org/downloads/TM_WORLD_BORDERS_SIMPL-0.3.zip
	# roads
	wget -nc http://biogeo.ucdavis.edu/data/diva/rds/SYR_rds.zip
	# inland water
	wget -nc http://biogeo.ucdavis.edu/data/diva/wat/SYR_wat.zip
	# land cover
	wget -nc http://biogeo.ucdavis.edu/data/diva/cov/SYR_cov.zip
	# administrative borders
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/SYR_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/TUR_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/LBN_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/IRQ_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/JOR_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/ISR_adm_shp.zip
	wget -nc http://biogeo.ucdavis.edu/data/gadm2.8/shp/PSE_adm_shp.zip
	# city names
	wget -nc http://download.geonames.org/export/dump/SY.zip
	# markers
	wget -nc http://dev.openlayers.org/img/marker.png 
	mv marker.png ${CONTENT_DIR}
	# country flags
	wget -nc http://www.famfamfam.com/lab/icons/flags/famfamfam_flag_icons.zip
	unzip -n famfamfam_flag_icons.zip -d ${CONTENT_DIR}
	# openstreetmap data
	wget -nc http://download.geofabrik.de/asia/syria-latest.shp.zip
    


