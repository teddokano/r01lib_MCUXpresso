#!/usr/bin/env python3

import	os
import	subprocess

build_configs	= [ "Debug", "Release" ]

dox_file_name	= "Doxyfile"
dox_folder_name	= "r01lib_docs"

base_dir	= os.getcwd() + "/"

prjs_path	= [ i.path for i in os.scandir( base_dir )  if "/." not in i.path ]
prjs_path	= [ i for i in prjs_path if "/." not in i ]
prjs_path	= [ i for i in prjs_path if "RTOS_TAD_logs" not in i ]
prjs_path.sort()

doxy_path	= []
dox_folders	= []

for prj in prjs_path:
	for rootdir, dirs, files in os.walk( prj ):
		for d in dirs:
			if ( dox_folder_name == d ):
					dox_folders	+= [ rootdir + "/" + d ]
		for f in files:
			if ( dox_file_name == f ):
				doxy_path	+= [ rootdir ]


print( "======= process started for .. =======" )
print( "projects:\n  " + "\n  ".join( [ os.path.basename( i ) for i in prjs_path ] ) )
print( "Doxyfile path:\n  " + "\n  ".join( doxy_path ) )
print( dox_folder_name + " are in ..\n  " + "\n  ".join( dox_folders ) )
print( "" )

for target in dox_folders:
	try:
		os.chdir( target )
	except:
		pass
	else:
		print( "####### clearing \"" + dox_folder_name + "\" folders" )
		subprocess.run( "rm -rf " + target, shell = True )

for target in doxy_path:
	try:
		os.chdir( target )
	except:
		pass
	else:
		print( "####### generating documents: " + target )
		subprocess.run( "doxygen", shell = True )

for target in prjs_path:
	print( "####### cleaning: " + target )			
	try:
		os.chdir( target + "/Debug/" )
	except:
		pass
	else:
		print( "####### cleaning: " + target )
		subprocess.run( "make -r -j9 clean", shell = True )
	
	try:
		os.chdir( target )
	except:
		pass
	else:
		for cnfg in build_configs:
			subprocess.run( "mkdir " + cnfg + "-ld", shell = True )
			subprocess.run( "cp " + cnfg + "/*.ld " + cnfg + "-ld/", shell = True )
			subprocess.run( "rm -rf " + cnfg + "/", shell = True )
			subprocess.run( "mv " + cnfg + "-ld/ " + cnfg + "/", shell = True )
	
		subprocess.run( "rm *.launch *.mex", shell = True )

print( "" )
print( "======= process completed for .. =======" )
print( "projects:\n  " + "\n  ".join( [ os.path.basename( i ) for i in prjs_path ] ) )
print( "Doxyfile path:\n  " + "\n  ".join( doxy_path ) )
print( dox_folder_name + " are in ..\n  " + "\n  ".join( dox_folders ) )

print( "done" )
