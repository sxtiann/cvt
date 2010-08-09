# (C) 2010, Sebastian Klose, <kloses@in.tum.de>

#	this automatically generates a target executable, using all 
#	.cpp, .c, .hpp and .h files of the current directory
#	The name of the target will be either the one passed as argument,
#	or (if none is passed) the name of the folder
#
#	Dependencies we search for and link against:
#	- Boost (filesystem, system, program_options)
#	- OpenCV (2.1)
#	- Eigen2

MACRO (MACRO_TEST_APPLICATION)

FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(Eigen2 REQUIRED)

SET(DATA_FOLDER
	"${CMAKE_SOURCE_DIR}/data"
)
ADD_DEFINITIONS(-DDATA_FOLDER="${DATA_FOLDER}")

IF(${ARGC} GREATER 0)
	SET(APP_NAME "${ARGV0}")
ELSE(${ARGC} GREATER 0)
	GET_FILENAME_COMPONENT(folderName ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	SET(APP_NAME "${folderName}")
ENDIF(${ARGC} GREATER 0)

MESSAGE(STATUS "Configuring: ${APP_NAME}") 

# get all headers and cpp files in the folder:
FILE(GLOB SRCS_${APP_NAME} "*.cpp" "*.h" "*.hpp")
                           
ADD_EXECUTABLE(${APP_NAME} ${SRCS_${APP_NAME}})

INCLUDE_DIRECTORIES(
    BEFORE
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${OpenCV_INCLUDE_DIRS}"
	"${Eigen2_INCLUDE_DIR}"

)

TARGET_LINK_LIBRARIES(
	${APP_NAME}
	${OpenCV_LIBS}
	Tools
)

SET_TARGET_PROPERTIES("${APP_NAME}" PROPERTIES DEBUG_POSTFIX "_d")

# -> TOOD: this should not be done under linux (or mac with makefiles -> so inly when using Xcode or MVSC)
SET_TARGET_PROPERTIES("${APP_NAME}" PROPERTIES PREFIX "../")

INSTALL(TARGETS "${APP_NAME}"
	RUNTIME DESTINATION bin
	COMPONENT Tests
)

ENDMACRO (MACRO_TEST_APPLICATION)
