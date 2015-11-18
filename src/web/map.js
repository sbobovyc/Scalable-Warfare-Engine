// http://christopherjennison.com/openlayers3-quickstart-tutorial/
// http://openlayers.org/en/v3.6.0/examples/vector-layer.html
// http://openlayers.org/en/v3.9.0/examples/vector-labels.html
// http://openlayers.org/en/v3.11.1/examples/zoomslider.html
// http://openlayers.org/en/v3.11.1/examples/vector-layer.html?q=server
// https://openlayersbook.github.io/ch06-styling-vector-layers/example-08.html

console.log('SWE: starting render');
console.time('render')

var labelFont = 'Verdana';
var maxCityZoom = 310;
var maxProvinceTextZoom = 1200;
var minRoadZoom = 310;
var maxInlandWaterZoom = maxProvinceTextZoom;

var shadowStyle = new ol.style.Style({
  stroke: new ol.style.Stroke({
    color: [0, 0, 127, 0.15],
    width: 6
  }),
  zIndex: 1
});

var getCityStyle = function() {
    return function(feature, resolution) {
        var style = new ol.style.Style();
        var text = feature.get('asciiname');
        if (resolution < maxCityZoom && (text == "Damascus" || text == "Homs" || text == "Aleppo" || text == 'Dar\'a')) {
            var style = new ol.style.Style({
                    image: new ol.style.Icon({
                        src: './content/marker.png'
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

var provinceCache = {};
var getProvinceStyle = function() {
    return function(feature, resolution) {
        var text = '';
        if (resolution < maxProvinceTextZoom) {
            text = feature.get('NAME_1');
        }
        if (!provinceCache[text]) {
            provinceCache[text] = new ol.style.Style({
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
        }
        return [shadowStyle, provinceCache[text]];
    };
};

var neighborNameCache = {};
var getNeighborStyle = function() {
    return function(feature, resolution) {
        var countryName = feature.get('NAME_ENGLI');
        //var flag_icon = './content/png/'+feature.get('ISO2').toLowerCase()+'.png';
        //console.log(flag_icon);
        //console.log('getNeighborStyle, got ' + feature.get('NAME_ENGLI') + ', type ' + feature.getGeometry().getExtent() + ', resolution ' + resolution);
        if(!neighborNameCache[countryName]) {
            neighborNameCache[countryName] = new ol.style.Style({
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
        }
        return [neighborNameCache[countryName]];
    };
};

var openStreetMapRoads = false;

var getRoadStyle = function() {
    return function(feature, resolution) {
        var style = new ol.style.Style();
        if (resolution < minRoadZoom) {
            if(openStreetMapRoads) {
                if(feature.get('ref') == 'M5') {
                   style = new ol.style.Style({stroke: new ol.style.Stroke({color: 'black', width: 1.5})});
                } else {
                   //style = new ol.style.Style({stroke: new ol.style.Stroke({color: '#808000', width: 0.5})});
                } 

            } else {
                if(feature.get('RTT_DESCRI') == 'Primary Route' || feature.get('RTT_DESCRI') == 'Unknown') {
                   style = new ol.style.Style({stroke: new ol.style.Stroke({color: 'black', width: 1.5})});
                } else {
                   style = new ol.style.Style({stroke: new ol.style.Stroke({color: '#808000', width: 0.5})});
                } 
            }
        }
        
        return [style];
    };
};

var getInlandWaterStyle = function() {
    return function(feature, resolution) {
        var style = new ol.style.Style();
        if (resolution < maxInlandWaterZoom) {
            var style = new ol.style.Style({
                    stroke: new ol.style.Stroke({color: 'blue', width: 0.3}),
                    fill: new ol.style.Fill({color: 'rgba(0, 0, 255, 0.1)'})
            });
        }
        return [style];
    };
};

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
       style: getInlandWaterStyle()
    })
  ],
  view: new ol.View({
    center: ol.proj.fromLonLat([38, 35.145]),
    zoom: 7 
  })
});

// select interaction working on "click"
var selectClick = new ol.interaction.Select({
  condition: ol.events.condition.click,
  layers: function (layer) {
    return layer.get('title') == 'vector_layer_syria1';
  }
});


map.addInteraction(selectClick);

selectClick.on('select', function(e) {
    //console.log(e.target.getFeatures().getLength() +
    //  ' selected features (last operation selected ' + e.selected.length +
    //  ' and deselected ' + e.deselected.length + ' features)');
    if(e.selected.length != 0) {
        var feature = e.target.getFeatures().item(0);
        document.getElementById('test_description').innerHTML = feature.get('NAME_1');
        //console.log(feature);
    } else {
        document.getElementById('test_description').innerHTML = "Nothing selected";

    }
});

var highlightStyleCache = {};

var featureOverlay = new ol.layer.Vector({
  source: new ol.source.Vector(),
  map: map,
  style: function(feature, resolution) {
    var text = resolution < 5000 ? feature.get('NAME_1') : '';
    if (!highlightStyleCache[text]) {
      highlightStyleCache[text] = [new ol.style.Style({
        stroke: new ol.style.Stroke({
          color: '#f00',
          width: 1
        }),
        fill: new ol.style.Fill({
          color: 'rgba(255,0,0,0.1)'
        }),
        text: new ol.style.Text({
          font: '12px Calibri,sans-serif',
          text: text,
          fill: new ol.style.Fill({
            color: '#000'
          }),
          stroke: new ol.style.Stroke({
            color: '#f00',
            width: 3
          })
        })
      })];
    }
    return highlightStyleCache[text];
  }
});

var highlight;
var displayFeatureInfo = function(pixel) {

  var feature = map.forEachFeatureAtPixel(pixel, function(feature, layer) {
    return feature;
  });

  var info = document.getElementById('info');
  if (feature) {
    document.getElementById('test_description').innerHTML = feature.get('NAME_1');
  } else {
    document.getElementById('test_description').innerHTML = 'Ynbsp;';
  }

  if (feature !== highlight) {
    if (highlight) {
      featureOverlay.getSource().removeFeature(highlight);
    }
    if (feature) {
      featureOverlay.getSource().addFeature(feature);
    }
    highlight = feature;
  }

};


map.on('pointermove', function(evt) {
  if (evt.dragging) {
    return;
  }
  var pixel = map.getEventPixel(evt.originalEvent);
  displayFeatureInfo(pixel);
});

var zoomSlider = new ol.control.ZoomSlider();
map.addControl(zoomSlider);
map.addControl(new ol.control.MousePosition());
map.addControl(new ol.control.FullScreen());

// Create the graticule component
var graticule = new ol.Graticule({
  // the style to use for the lines, optional.
  strokeStyle: new ol.style.Stroke({
    color: 'rgba(255,120,0,0.9)',
    width: 2,
    lineDash: [0.5, 4]
  })
});
//graticule.setMap(map);


console.timeEnd('render');

