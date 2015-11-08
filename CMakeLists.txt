# ================================================================================
# 
# This file is part of the VRBase project.
# 
# File: CMakeLists.txt
# 
# Original Author(s) of this File:
# 	Dan Orban, 2015, University of Minnesota
# 
# Author(s) of Significant Updates/Modifications to the File:
# 	...
# 
# -----------------------------------------------------------------------------------
# Copyright (c) 2015 Regents of the University of Minnesota
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice, this
#   list of conditions and the following disclaimer in the documentation and/or
#   other materials provided with the distribution.
# 
# * The name of the University of Minnesota, nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ================================================================================ 
 


# CMakeLists files in this project can refer to the root source directory of the 
cmake_minimum_required (VERSION 2.8.2) 
project (VRBase)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${${PROJECT_NAME}_SOURCE_DIR}/build/install" CACHE PATH "default install path" FORCE )
endif()

# Use the root of the MinVR tree as an include dir, then include headers like this:

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

############################################################
#Start of library detection
#Any libraries outside of your source should have a corresponding
#find module in the $G/src/cmake/Modules directory and the 
#find_package method should be used here.
############################################################

set(MinVR_DIR $ENV{MinVR_DIR})
find_package(MinVR COMPONENTS MVRCore AppKit_GLFW REQUIRED)
include_directories(${MinVR_INCLUDE_DIRS})

include(ExternalProject)

message(${${PROJECT_NAME}_INSTALL_PREFIX} ${PROJECT_NAME})
set(plugin_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/PluginFW")
set(plugin_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${plugin_INSTALL_DIR}")

ExternalProject_add(PluginFW
		PREFIX "${CMAKE_SOURCE_DIR}/dependencies/PluginFW"
		GIT_REPOSITORY https://github.com/ivlab/PluginFramework.git
		GIT_TAG master
		INSTALL_DIR "${plugin_INSTALL_DIR}"
		CMAKE_ARGS "${plugin_CMAKE_ARGS}"
		PATCH_COMMAND ""
		UPDATE_COMMAND ""
)

############################################################
#End external library searching
############################################################

############################################################
#OS Specific flags should go here
############################################################

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    find_library(COCOA_LIB Cocoa)
    find_library(IOKIT_LIB IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    set(LIBS_ALL ${LIBS_ALL} ${COCOA_LIB} ${IOKIT_LIB} ${CORE_FOUNDATION_FRAMEWORK} ${CORE_VIDEO_FRAMEWORK})
    message(STATUS "${CORE_VIDEO_FRAMEWORK}")

endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # Linux specific code
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
	set(Lib_Config "none")
	set(MinVR_LIBS)
	FOREACH (LIB ${MinVR_LIBRARIES})
	  if("${LIB}" STREQUAL "debug" OR "${LIB}" STREQUAL "optimized")
	    set(Lib_Config ${LIB})
	  else()
	    list(APPEND MinVR_LIBS ${LIB})
	    if("${Lib_Config}" STREQUAL "debug" OR "${Lib_Config}" STREQUAL "optimized")
	      list(APPEND MinVR_LIBS ${Lib_Config})
	    endif()
	    set(Lib_Config none)
	  endif()
	ENDFOREACH(LIB)
	LIST(REVERSE MinVR_LIBS)

	set(MinVR_LIBRARIES)

	FOREACH (LIB ${MinVR_LIBS})
	  list(APPEND MinVR_LIBRARIES ${LIB})
	ENDFOREACH(LIB)	

	find_package(Threads)
	find_package(X11)
	set(LIBS_ALL ${LIBS_ALL} ${CMAKE_THREAD_LIBS_INIT} rt Xrandr Xxf86vm Xi m dl ${X11_LIBRARIES})
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  # Windows specific code

endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if (MSVC)
	# Windows specific code
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")

endif (MSVC)

############################################################
# Add POSTFIX info
############################################################

# Let's follow the convention of putting all of the libs in "build/lib" and all
# of the exes in "build/bin".  To distingusih between debugging, release, and
# other builds, we'll add a postfix to the name of the lib or exe that we generate.

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_RELEASE_POSTFIX "")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
set(CMAKE_MINSIZEREL_POSTFIX "s")

if (CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "MinSizeRel")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
else()
  set(CMAKE_BUILD_POSTFIX "")
endif()

make_directory(${CMAKE_BINARY_DIR}/lib)
make_directory(${CMAKE_BINARY_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
foreach (CONF ${CMAKE_CONFIGURATION_TYPES})
  string (TOUPPER ${CONF} CONF)
  set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/bin)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/lib)
  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/lib)
endforeach(CONF CMAKE_CONFIGURATION_TYPES)


# Recurse into the following subdirs to build the core MinVR set of libraries:
# (Uncomment the lines below as we add .cpp files to those directories.)

add_subdirectory (vrbase)


# Now, build some programs, such as tests, that depend upon the MinVR libraries:

#add_subdirectory (tests/app)
