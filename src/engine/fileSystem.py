# A minimal SQLite shell for experiments

import os
import sys
import sqlite3

import mod

class FS():
    schema = "CREATE TABLE files (fullpath text, alias text, mod text, version text)"

    def __init__(self, resourcePath):
        self.initDB()   
        # 1. Find all mods
        # 2. Find main_game mod
        # 3. Add all main_game files to database

        # Step 1
        modList = self.findMods(resourcePath)
        print modList

        # Step 2
        fileList = []
        fileSize = 0
        folderCount = 0
        mainGamePath = os.path.join(resourcePath, "main_game")
        if os.path.exists(mainGamePath):
            print "Found main_game"
            files, size, count = self.recursiveWalk(mainGamePath)
            fileList += files
            fileSize += size
            folderCount += count
            self.addMod(files, mainGamePath)
        else:
            print "Error!"

        
        print("Total Size is %s bytes" % format(fileSize))
        print("Total Files ", len(fileList))
        print("Total Folders ", folderCount)

        buffer = ""
        
        print "Enter your SQL commands to execute in sqlite3."
        print "Enter a blank line to exit."

        #while True:
        #    line = raw_input()
        #    if line == "":
        #        break
        #    buffer += line
        #    if sqlite3.complete_statement(buffer):
        #        try:
        #            buffer = buffer.strip()
        #            cur.execute(buffer)
        #
        #            if buffer.lstrip().upper().startswith("SELECT"):
        #                print cur.fetchall()
        #        except sqlite3.Error, e:
        #            print "An error occurred:", e.args[0]
        #        buffer = ""

        self.con.close()

    def initDB(self):
        #con = sqlite3.connect(":memory:")
        self.con = sqlite3.connect("testfs.sqlite")
        self.con.isolation_level = None
        self.cur = self.con.cursor()

        # create the table
        self.cur.execute(FS.schema)
        # commit
        self.con.commit()

    def recursiveWalk(self, resourcePath):
        fileList = []
        fileSize = 0
        folderCount = 0
        
        for path, subFolders, files in os.walk(resourcePath):
            folderCount += len(subFolders)
            for file in files:
                f = os.path.join(path,file)
                fileSize += os.path.getsize(f)
                fileList.append(f)
    
        return fileList, fileSize, folderCount

    def findMods(self, resourcePath):
        print resourcePath
        fileList = []
        for each in os.listdir(resourcePath):
            fileList.append(os.path.abspath(os.path.join(resourcePath, each)))
        return filter(os.path.isdir, fileList)

    def addMod(self, fileList, modPath):
        m = mod.mod()
        m.open(os.path.join(modPath, mod.mod.MODCFG))

        for f in fileList:
            self.cur.execute("INSERT INTO files VALUES (?, ?, ?, ?)", (f, f, m.name, m.version))
        self.con.commit()
        
if __name__ == "__main__" :
    path = os.path.abspath("../../mods")
    print path
    fs = FS(path)
