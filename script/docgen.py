#!/usr/bin/env python3

import	os
import	subprocess

build_configs	= [ "Debug", "Release" ]

dox_file_name	= "Doxyfile"
dox_folder_name	= "r01lib_docs"
dox_folder_path	= "docs/" + dox_folder_name

base_dir	= os.getcwd() + "/"

prjs_path	= [ i.path for i in os.scandir( base_dir )  if "/." not in i.path ]
prjs_path	= [ i for i in prjs_path if "/." not in i ]
prjs_path	= [ i for i in prjs_path if "RTOS_TAD_logs" not in i ]
prjs_path.sort()

doxy_path	= []

###
### scan workspace and find directories/files
###

for prj in prjs_path:
	for rootdir, dirs, files in os.walk( prj ):
		for f in files:
			if ( dox_file_name == f ):
				doxy_path	+= [ rootdir ]

###
### show found directories/files
###

print( "======= process started for .. =======" )
print( "Doxyfile path:\n  " + "\n  ".join( doxy_path ) )
print( "Generated docs will be in\n  " + dox_folder_path )
print( "" )

###
### clear directory on the dox_folder_path
###

print( "####### clearing \"" + dox_folder_path + "\" folder" )
subprocess.run( "rm -rf " + dox_folder_path, shell = True )

###
### choose one of "Doxyfile" and generate docments in dox_folder_path
###

try:
	os.chdir( doxy_path[ 0 ] )
except:
	pass
else:
	print( "####### generating documents: " + doxy_path[ 0 ] )
	subprocess.run( "doxygen", shell = True )
	subprocess.run( "mv ../" + dox_folder_name + " " + base_dir + dox_folder_path, shell = True )

###
### show result
###

print( "" )
print( "======= process completed =======" )
print( "Doxyfile(s) are found in:\n  " + "\n  ".join( doxy_path ) )
print( "And the documents generated from:\n  " + doxy_path[ 0 ] + "/" + dox_file_name )
print( "Generated docs are in:\n  " + dox_folder_path )
print( "" )

print( "Note: For update of \"r01lib\" source code to latest one, use next command and run this script again:\n" )
