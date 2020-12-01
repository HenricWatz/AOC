cmake_minimum_required (VERSION 2.9)

# Maps to a solution file (Tutorial.sln). The solution will 
# have all targets (exe, lib, dll) as projects (.vcproj)
project (AdventOfCode_2020)

# function for adding problems to the solution
function(add_problem name path)

	# Set Properties->General->Configuration Type to Application(.exe)
	# Creates app.exe with the listed sources (main.cxx)
	# Adds sources to the Solution Explorer
	add_executable (${name} ${path})
	
	# Creates a folder "problems" and adds target 
	# project (name.vcproj) under it
	set_property(TARGET ${name} PROPERTY FOLDER "problems")
	
	# Properties->General->Output Directory
	set_target_properties(${name} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
					
	# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
	install (TARGETS ${name}
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)
	
endfunction()

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# Sub-directories where more CMakeLists.txt exist
add_subdirectory(src)
#add_subdirectory(library)
