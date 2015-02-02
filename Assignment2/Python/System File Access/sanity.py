#!/usr/bin/python

import os,sys
import zipfile
import filecmp

#list of files expected to be in the zipfile
fileList=['Makefile', 'FacebookVertex.cpp', 'FacebookVertex.h', 'Graph.cpp', 'Graph.h', 'Main.cpp']
#exec name after make
execName='a.out'

outDir='/tmp/Assignment6/'

OKGREEN = '\033[92m'
FAIL    = '\033[91m'
ENDC    = '\033[0m'

def main():
    if unzipFiles() and makeSrc() and runTests():
        print OKGREEN + 'zipfile looks good for submission' + ENDC 

def unzipFiles():
    isOK = True
    fname = sys.argv[1]
    print 'Performing Sanity on ' + fname
    zfile = zipfile.ZipFile(fname)
    for name in zfile.namelist():   
        try:
            (dirname, filename) = os.path.split(name)
            if filename in fileList:
                fileList.remove(filename)
            print "Decompressing " + name + ' to ' + outDir
            if not os.path.exists(outDir):
              os.makedirs(outDir)
            zfile.extract(name, outDir)
            os.system('cd ' + outDir + ';mv ' + name + ' ' + outDir)
        except:
            isOK = False
            print FAIL + 'Some issue while unzipping the given zipfile' + ENDC 
    
    if len(fileList) == 0:  #all expected files found
        print OKGREEN + 'All expected file found in the zipfile' + ENDC 
    else:
        isOK = False
        print FAIL + 'Following files not found in the zipfile: ' + ENDC, fileList 

    return isOK

def makeSrc():
    isOK = True
    os.system('cd ' + outDir + '; make');
    if not os.path.exists(outDir + execName):
        isOK = False
        print FAIL + 'make failed or the executable name is not ' + execName + ENDC 
    return isOK

def runTests():
    isOK = True
    os.system('cp ' + outDir + execName + ' .');
    os.system('./' + execName + " facebook-graph.txt < test.txt > run.log")
    if not filecmp.cmp('expected_output_test.txt', 'run.log'):
        isOK = False
        print FAIL + 'Expected ouput did not match' + ENDC 

    return isOK

if __name__ == '__main__':
    main()