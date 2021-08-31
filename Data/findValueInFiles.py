'''
Created on 22 dic. 2017

@author: Ivan
'''

import os, struct
from os.path import isfile
path = "./"

def getFiles():
    files =  [archivos for archivos in os.listdir(path) if isfile(path+archivos)]
    return files

def convertHex(number):
    if(isinstance(number, float)):
        return struct.pack('f', number).encode("hex")
    else:
        return struct.pack('I', number).encode("hex")

def findValue(lista, value):
    inFile = []
    
    for item in lista:
        test = open(path+item, "rb")
        fileHex = test.read().encode("hex")
        test.close()
        
        if convertHex(value) in fileHex:
            inFile.append(item)
            
    return inFile

def showList(lista):
    print ""
    for item in lista:
        print item
    
    print ""

files = getFiles()
print "Total Files:", len(files)

value = input("Insert number to search: ")

search = findValue(files, value)

print "Coincidences:", len(search)

showList(search)

raw_input("Press enter to finish...")