

	project "wxWidgetsTreeCtrlTest"
		
	kind "WindowedApp"
	flags { "WinMain" }
	targetdir "../../bin"
	
	includedirs 
	{
		"../wxWidgets-2.9.0/include/setup",
		"../wxWidgets-2.9.0/include",
		"../../rendering/GlutGlewWindows",
		"../../rendering/BulletMath"
	}
	libdirs {"../../rendering/GlutGlewWindows"}

	configuration {"vs2008", "release"}
	libdirs {"../wxWidgets-2.9.0/lib/vs2008release"}

	configuration {"vs2008", "debug"}
	libdirs {"../wxWidgets-2.9.0/lib/vs2008debug"}

	configuration {}
	
	

	links {
		"wxAll",
		"Comctl32",
		"Rpcrt4"
	}
	
	
	files {
			"treetest.cpp",
			"treetest.h"
	}