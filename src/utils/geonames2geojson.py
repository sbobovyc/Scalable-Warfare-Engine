import csv, codecs, cStringIO
import geojson
from geojson import Point, Feature, FeatureCollection

class UTF8Recoder:
    """
    Iterator that reads an encoded stream and reencodes the input to UTF-8
    """
    def __init__(self, f, encoding):
        self.reader = codecs.getreader(encoding)(f)

    def __iter__(self):
        return self

    def next(self):
        return self.reader.next().encode("utf-8")

class UnicodeReader:
    """
    A CSV reader which will iterate over lines in the CSV file "f",
    which is encoded in the given encoding.
    """

    def __init__(self, f, dialect=csv.excel, encoding="utf-8", **kwds):
        f = UTF8Recoder(f, encoding)
        self.reader = csv.reader(f, dialect=dialect, **kwds)

    def next(self):
        row = self.reader.next()
        return [unicode(s, "utf-8") for s in row]

    def __iter__(self):
        return self

if __name__ == "__main__":
    f = open("../web/content/SY.txt", "rb")
    ur = UnicodeReader(f, dialect='excel-tab')
    
    collection = []
    for row in ur:
        [geonameid, \
        name,\
        asciiname,\
        alternatenames,\
        latitude,\
        longitude,\
        fclass,  \
        fcode,   \
        country, \
        cc2, \
        admin1,\
        admin2, \
        admin3,  \
        admin4,  \
        population,\
        elevation,  \
        gtopo30,     \
        timezone,\
        moddate]  = row
        collection.append(Feature(geometry=Point((float(longitude), float(latitude))), properties={"geonameid": geonameid, "country" : country, "asciiname" : asciiname}))
    
    feature_collection = FeatureCollection(collection)
    dump = geojson.dumps(feature_collection)
    
    f.close()
    
    with open("../web/content/SYR_cities.geojson", "wb") as f:
        f.write(dump)

