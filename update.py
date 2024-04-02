#!/usr/bin/env python3

import	os
import	subprocess

base_dir	= os.getcwd() + "/"

prjs_path	= [ i.path for i in os.scandir( base_dir )  if "/." not in i.path ]
prjs_path	= [ i for i in prjs_path if "/." not in i ]
prjs_path	= [ i for i in prjs_path if "RTOS_TAD_logs" not in i ]
prjs_path.sort()

print( "======= process started for .. =======" )
print( "projects:\n  " + "\n  ".join( [ os.path.basename( i ) for i in prjs_path ] ) )
print( "" )

for target in prjs_path:
	try:
		os.chdir( target )
	except:
		pass
	else:
		print( "####### updating: " + target )
		subprocess.run( "git submodule update --remote", shell = True )
		print( "" )

print( "done" )
