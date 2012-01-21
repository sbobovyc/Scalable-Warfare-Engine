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
    import mapnik
except:
    print '\n\nThe mapnik library and python bindings must have been compiled and \
installed successfully before running this script.\n\n'
    sys.exit(1)

#def render_thumb(seed, name):
#    path = os.path.dirname(os.path.realpath(__file__))
#    lib = "libmmaker.so"
#    lib_path = os.path.join(path, lib)
#    libmmaker = ctypes.CDLL(lib_path, mode=ctypes.RTLD_GLOBAL)

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
    layer2.datasource = mapnik.SQLite(file="../border.sqlite", table='border', key_field='OGC_FID', geometry_field='GEOMETRY', wkb_format='spatialite', extent='-64.5721,31.0319,-4.50204,61.8924')
    layer2.styles.append("mapStyle")
    m.background = mapnik.Color("steelblue")
    m.append_style("mapStyle", style2)
    m.layers.append(layer2)

    m.zoom_all()   
    mapnik.render_to_file(m, map_out, 'png')

if __name__ == '__main__':
    create_testmap_db()
