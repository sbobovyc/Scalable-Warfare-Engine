import ConfigParser
import os

class mod():
    MODCFG = "mod.ini"

    def __init__(self, name="modname", author="", version="", description=""):
        self.name = name
        self.version = version
        self.author = author
        self.description = description

    def open(self, path):
        config = ConfigParser.ConfigParser()
        config.read(path)
        self.name = config.get("Mod Init", "Name")
        self.version = config.get("Mod Init", "Version")
        self.author = config.get("Mod Init", "Author")
        self.description = config.get("Mod Init", "Description")

    def write(self, path):
        config = ConfigParser.RawConfigParser()
        config.add_section("Mod Init")
        config.set("Mod Init", "Name", self.name)
        config.set("Mod Init", "Version", self.version)
        config.set("Mod Init", "Author", self.author)
        config.set("Mod Init", "Description", self.description)
        with open(os.path.join(path,"mod.ini"), 'wb') as configfile:
            config.write(configfile)

    
    def __str__(self):
        return "Name: %s \nVersion: %s\nAuthor: %s\nDescription: %s" % (self.name, self.version, self.author, self.description)

if __name__ == '__main__':
    mod = mod("Main game", "Stan Bobovych", "0.1a", "SWE")
    print mod
    mod.write("./")
    mod.open("mod.ini")
    print mod
