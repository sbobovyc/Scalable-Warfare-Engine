// http://christopherjennison.com/openlayers3-quickstart-tutorial/
// http://openlayers.org/en/v3.6.0/examples/vector-layer.html
// http://openlayers.org/en/v3.9.0/examples/vector-labels.html 

console.log('SWE: starting render');
console.time('render')

var labelFont = 'Verdana';
var maxCityZoom = 310;
var maxProvinceTextZoom = 1200;
var minRoadZoom = 310;

var getCityStyle = function() {
    return function(feature, resolution) {
        var style = new ol.style.Style();
        var text = feature.get('asciiname');
        if (resolution < maxCityZoom && (text == "Damascus" || text == "Homs" || text == "Aleppo")) {
            var style = new ol.style.Style({
                    image: new ol.style.Icon({
                        src: 'http://dev.openlayers.org/img/marker.png'
                    }),
                    text: new ol.style.Text({
                                font: '10px ' + labelFont,
                                text: text,
                                textAlign: 'center',
                                textBaseline: 'middle',
                                fill: new ol.style.Fill({color: 'black'}),
                                offsetX: 0,
                                offsetY: -20,
                                rotation: 0
                    })                                            
            });
        }
        return [style];
    };
};

var getProvinceStyle = function() {
    return function(feature, resolution) {
        var text = '';
        if (resolution < maxProvinceTextZoom) {
            text = feature.get('NAME_1');
        }

        var style = new ol.style.Style({
                stroke: new ol.style.Stroke({color: 'blue'}),
                text: new ol.style.Text({
                            font: '12px ' + labelFont,
                            text: text,
                            textAlign: 'center',
                            textBaseline: 'middle',
                            fill: new ol.style.Fill({color: 'black'}),
                            offsetX: 0,
                            offsetY: 0,
                            rotation: 0
                })                                            
        });
        return [style];
    };
};

var getNeighborStyle = function() {
    return function(feature, resolution) {
        console.log('getNeighborStyle, got ' + feature.get('NAME_ENGLI') + ', type ' + feature.getGeometry().getExtent() + ', resolution ' + resolution);
        var style = new ol.style.Style({
                stroke: new ol.style.Stroke({color: 'LightGray', width: 2}),
                text: new ol.style.Text({
                            font: '22px ' + labelFont,
                            text: feature.get('NAME_ENGLI'),
                            textAlign: 'center',
                            textBaseline: 'middle',
                            fill: new ol.style.Fill({color: 'black'}),
                            offsetX: 0,
                            offsetY: 0,
                            rotation: 0
                })                                            
        });
        return [style];
    };
};

var getRoadStyle = function() {
    return function(feature, resolution) {
        var style = new ol.style.Style();
        if (resolution < minRoadZoom) {
            if(feature.get('RTT_DESCRI') == 'Primary Route' || feature.get('RTT_DESCRI') == 'Unknown') {
               style = new ol.style.Style({stroke: new ol.style.Stroke({color: 'black', width: 1.5})});
            } else {
               style = new ol.style.Style({stroke: new ol.style.Stroke({color: '#808000', width: 0.5})});
            } 
        }
        
        return [style];
    };
};

var inland_water_style = new ol.style.Style({
            stroke: new ol.style.Stroke({color: 'blue', width: 0.3}),
            fill: new ol.style.Fill({color: 'rgba(0, 0, 255, 0.1)'})
});

var map = new ol.Map({
  target: 'map',
  render: 'canvas',
  layers: [
    //new ol.layer.Tile({
    //  source: new ol.source.MapQuest({layer: 'sat'})
    //}),
    //new ol.layer.Vector({
    //  title: 'vector layer',
    //  source: new ol.source.Vector({
    //          projection: 'EPGS:4326',
    //          url: './content/110m_land.geojson', 
    //          format: new ol.format.GeoJSON()})
    //}),
    //new ol.layer.Vector({
    //  title: 'vector_layer_borders',
    //  source: new ol.source.Vector({
    //          projection: 'EPGS:4326',
    //          url: './content/TM_WORLD_BORDERS_SIMPL-0.3.geojson', 
    //          format: new ol.format.GeoJSON()})
    //}),
    new ol.layer.Vector({
      title: 'vector_layer_turkey0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/TUR_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: getNeighborStyle()
    }),
    new ol.layer.Vector({
      title: 'vector_layer_lebanon0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/LBN_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: getNeighborStyle()
    }),
    new ol.layer.Vector({
      title: 'vector_layer_israel0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/ISR_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: getNeighborStyle()
    }),
    new ol.layer.Vector({
      title: 'vector_layer_jordan0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/JOR_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: getNeighborStyle()
    }),
    new ol.layer.Vector({
      title: 'vector_layer_iraq0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/IRQ_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: getNeighborStyle() 
    }),
    new ol.layer.Vector({
      title: 'vector_layer_syria0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_adm0.geojson', 
              format: new ol.format.GeoJSON()})
    }),
    new ol.layer.Vector({
      title: 'vector_layer_syria1',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_adm1.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: getProvinceStyle() 
    }),
    //new ol.layer.Vector({
    //  title: 'vector_layer_syria2',
    //  source: new ol.source.Vector({
    //          projection: 'EPGS:4326',
    //          url: './content/SYR_adm2.geojson', 
    //          format: new ol.format.GeoJSON()})
    //}),
    new ol.layer.Vector({
      title: 'vector_layer_syria_cities',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_cities.geojson', 
              format: new ol.format.GeoJSON()}),
       style: getCityStyle()
    }),
    new ol.layer.Vector({
      title: 'vector_layer_syria_roads',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_roads.geojson', 
              format: new ol.format.GeoJSON()}),
       style: getRoadStyle()
    }),
    new ol.layer.Vector({
      title: 'vector_layer_syria_water',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_water_areas_dcw.geojson', 
              format: new ol.format.GeoJSON()}),
       style: inland_water_style
    })
  ],
  view: new ol.View({
    center: ol.proj.fromLonLat([38, 35.145]),
    zoom: 7 
  })
});
console.timeEnd('render');
