"""
Created on December 12, 2011

@author: sbobovyc
"""
"""
Copyright (C) 2011 Stanislav Bobovych

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
"""

import ctypes
import os

try:
    import mapnik2 
except:
    print '\n\nThe mapnik library and python bindings must have been compiled and \
installed successfully before running this script.\n\n'
    sys.exit(1)

def print_mapnik_plugins():
    from mapnik2 import DatasourceCache as c; print ','.join(c.plugin_names())

def create_testmap():
    map_out = "map.png"
    m = mapnik.Map(1024, 768)

    style = mapnik.Style()
    rule = mapnik.Rule()
    rs = mapnik.RasterSymbolizer()
    rule.symbols.append(rs)
    style.rules.append(rule)
    m.append_style('raster',style)
    lyr = mapnik.Layer('raster')
    lyr.datasource = mapnik.Gdal(base='..', file="world_one_mapCLIPPED.tif")
    lyr.styles.append('raster') 
    m.layers.append(lyr)


    symbolizer = mapnik.PolygonSymbolizer(mapnik.Color(255, 0, 0))
    symbolizer.fill_opacity = 0.5
    symbolizer.gamma = 0.0
    rule.symbols.append(symbolizer)
    style2 = mapnik.Style()
    style2.rules.append(rule)
    layer2 = mapnik.Layer("mapLayer")
    layer2.datasource = mapnik.Shapefile(file="../border.shp")
    layer2.styles.append("mapStyle")
    m.background = mapnik.Color("steelblue")
    m.append_style("mapStyle", style2)
    m.layers.append(layer2)

    m.zoom_all()   
    mapnik.render_to_file(m, map_out, 'png')

def create_testmap_db():
    map_out = "map_from_db.png"
    m = mapnik2.Map(1024, 768)

    style = mapnik2.Style()
    rule = mapnik2.Rule()
    rs = mapnik2.RasterSymbolizer()
    rule.symbols.append(rs)
    style.rules.append(rule)
    m.append_style('raster',style)
    lyr = mapnik2.Layer('raster')
    lyr.datasource = mapnik2.Gdal(base='..', file="world_one_mapCLIPPED.tif")
    lyr.styles.append('raster') 
    m.layers.append(lyr)


    symbolizer = mapnik2.PolygonSymbolizer(mapnik2.Color(255, 0, 0))
    symbolizer.fill_opacity = 0.5
    symbolizer.gamma = 0.0
    rule.symbols.append(symbolizer)
    style2 = mapnik2.Style()
    style2.rules.append(rule)
    layer2 = mapnik2.Layer("mapLayer")
    layer2.datasource = mapnik2.SQLite(file="../border.sqlite", table='border', key_field='OGC_FID', geometry_field='GEOMETRY', wkb_format='spatialite', extent='-64.5721,31.0319,-4.50204,61.8924')
    layer2.styles.append("mapStyle")
    m.background = mapnik2.Color("steelblue")
    m.append_style("mapStyle", style2)
    m.layers.append(layer2)

    m.zoom_all()   
    mapnik2.render_to_file(m, map_out, 'png')

def create_testmap_region_filter():
    map_out = "map_from_db.png"
    m = mapnik2.Map(1024, 768)

    style = mapnik2.Style()
    rule = mapnik2.Rule()
    rs = mapnik2.RasterSymbolizer()
    rule.symbols.append(rs)
    style.rules.append(rule)
    lyr = mapnik2.Layer('raster')
    lyr.datasource = mapnik2.Gdal(base='..', file="world_one_mapCLIPPED.tif")
    lyr.styles.append('raster') 
    m.append_style('raster',style)
    m.layers.append(lyr)


    symbolizer = mapnik2.PolygonSymbolizer(mapnik2.Color(255, 0, 0))
    symbolizer.fill_opacity = 0.5
    symbolizer.gamma = 0.0
    rule.symbols.append(symbolizer)
    style2 = mapnik2.Style()
    style2.rules.append(rule)
    layer2 = mapnik2.Layer("notSelected")
    layer2.datasource = mapnik2.SQLite(file="../border.sqlite", table='(SELECT * from border WHERE Name IS NOT "Pi") as notSelected', key_field='OGC_FID', geometry_field='GEOMETRY', wkb_format='spatialite', extent='-64.5721,31.0319,-4.50204,61.8924')
    layer2.styles.append("unselectedStyle")

    symbolizer2 = mapnik2.PolygonSymbolizer(mapnik2.Color(0, 125, 125))
    symbolizer2.fill_opacity = 0.5
    symbolizer2.gamma = 0.0
    rule.symbols.append(symbolizer2)
    style3 = mapnik2.Style()
    style3.rules.append(rule)
    layer3 = mapnik2.Layer("selected")
    layer3.datasource = mapnik2.SQLite(file="../border.sqlite", table='(SELECT * from border WHERE Name IS "Pi") as notSelected', key_field='OGC_FID', geometry_field='GEOMETRY', wkb_format='spatialite', extent='-64.5721,31.0319,-4.50204,61.8924')
    layer3.styles.append("selectedStyle")

    m.background = mapnik2.Color("steelblue")
    m.append_style("unselectedStyle", style2)
    m.append_style("selectedStyle", style3)
    m.layers.append(layer2)
    m.layers.append(layer3)

    m.zoom_all()   
    mapnik2.render_to_file(m, map_out, 'png')

def create_testmap_db_point():
    map_out = "map_pi.png"
    m = mapnik2.Map(1024, 768)

    #style = mapnik2.Style()
    rule = mapnik2.Rule()
    #rs = mapnik2.RasterSymbolizer()
    #rule.symbols.append(rs)
    #style.rules.append(rule)
    #m.append_style('raster',style)
    #lyr = mapnik2.Layer('raster')
    #lyr.datasource = mapnik2.Gdal(base='..', file="world_one_mapCLIPPED.tif")
    #lyr.styles.append('raster') 
    #m.layers.append(lyr)


    symbolizer = mapnik2.PointSymbolizer(mapnik2.PathExpression("draw_circle.png"))
    symbolizer.allow_overlap = True
    symbolizer.fill_opacity = 0.5
    symbolizer.gamma = 0.0
    rule.symbols.append(symbolizer)
    style2 = mapnik2.Style()
    style2.rules.append(rule)
    layer2 = mapnik2.Layer("mapLayer")
    layer2.datasource = mapnik2.SQLite(file="../test-2.3.sqlite", table='(SELECT * FROM Towns WHERE Peoples < 500) as data', key_field='PK_UID', geometry_field='GEOMETRY', wkb_format='spatialite', extent="319224,3934670,1308590,5214370")
    print layer2.datasource.describe()
    layer2.styles.append("mapStyle")
    m.background = mapnik2.Color("red")
    m.append_style("mapStyle", style2)
    m.layers.append(layer2)

    m.zoom_all()   
    mapnik2.render_to_file(m, map_out, 'png')

if __name__ == '__main__':
    print_mapnik_plugins()
    #create_testmap_db()
    #create_testmap_db_region()
    create_testmap_region_filter()
