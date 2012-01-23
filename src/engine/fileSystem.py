# A minimal SQLite shell for experiments

import os
import sys
import sqlite3

class FS():
    def __init__(self, resourcePath):
        #con = sqlite3.connect(":memory:")
        con = sqlite3.connect("testfs.sqlite")
        con.isolation_level = None
        cur = con.cursor()


        fileList = []
        fileSize = 0
        folderCount = 0
        
        for path, subFolders, files in os.walk(resourcePath):
            folderCount += len(subFolders)
            for file in files:
                f = os.path.join(path,file)
                fileSize += os.path.getsize(f)
                fileList.append(f)
        
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

        con.close()

if __name__ == "__main__" :
    path = os.path.abspath("../../mods")
    print path
    fs = FS(path)
