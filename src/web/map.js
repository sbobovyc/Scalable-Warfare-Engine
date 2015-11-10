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
    new ol.layer.Vector({
      title: 'vector layer',
      source: new ol.source.Vector({
              projection: 'EPGS:4326',
              url: './110m_land.geojson', 
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
