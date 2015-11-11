// http://christopherjennison.com/openlayers3-quickstart-tutorial/
// http://openlayers.org/en/v3.6.0/examples/vector-layer.html
console.log('SWE: starting render');
console.time('render')

var neighbor_border_style = new ol.style.Style({stroke: new ol.style.Stroke({color: '#ccb', width: 2})});

var road_style = new ol.style.Style({stroke: new ol.style.Stroke({color: '#808000', width: 0.5})});

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
      style: neighbor_border_style
    }),
    new ol.layer.Vector({
      title: 'vector_layer_lebanon0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/LBN_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: neighbor_border_style
    }),
    new ol.layer.Vector({
      title: 'vector_layer_israel0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/ISR_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: neighbor_border_style
    }),
    new ol.layer.Vector({
      title: 'vector_layer_jordan0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/JOR_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: neighbor_border_style
    }),
    new ol.layer.Vector({
      title: 'vector_layer_iraq0',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/IRQ_adm0.geojson', 
              format: new ol.format.GeoJSON()
            }),
      style: neighbor_border_style
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
              format: new ol.format.GeoJSON()})
    }),
    new ol.layer.Vector({
      title: 'vector_layer_syria2',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_adm2.geojson', 
              format: new ol.format.GeoJSON()})
    }),
    new ol.layer.Vector({
      title: 'vector_layer_syria_roads',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './content/SYR_roads.geojson', 
              format: new ol.format.GeoJSON()}),
       style: road_style
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
    center: ol.proj.fromLonLat([40.41, 35.82]),
    zoom: 6 
  })
});
console.timeEnd('render');
