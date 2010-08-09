SET(CMAKE_CONFIGURATION_TYPES Debug Release)

# set the default build type if needed
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "debug" CACHE STRING "Choose build type (Release or Debug)" FORCE)
	MESSAGE(STATUS "BUILD_TYPE is unset, defaulting to \"${CMAKE_BUILD_TYPE}\"")
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(BUILD_SHARED_LIBS TRUE)
