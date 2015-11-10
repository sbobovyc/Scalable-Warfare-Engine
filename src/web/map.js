// http://christopherjennison.com/openlayers3-quickstart-tutorial/
// http://openlayers.org/en/v3.6.0/examples/vector-layer.html
console.log('SWE: starting render');
console.time('render')
var start = +new Date();  // log start timestamp
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
      style: new ol.style.Style({
                stroke: new ol.style.Stroke({
                color: '#ccb',
                width: 2})
                })
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
    })
  ],
  view: new ol.View({
    //projection: 'EPGS:4326', //WGS84
    center: ol.proj.fromLonLat([37.41, 8.82]),
    zoom: 4
  })
});
console.timeEnd('render');
var end =  +new Date();  // log end timestamp
var diff = end - start;
