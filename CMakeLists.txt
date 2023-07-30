cmake_minimum_required(VERSION 3.25)
project(flappy-mind)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include and configure GoogleTest
include(FetchContent)
FETCHCONTENT_DECLARE(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FETCHCONTENT_MAKEAVAILABLE(googletest)

enable_testing()

# macro to find subdirectories
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB_RECURSE children LIST_DIRECTORIES true CONFIGURE_DEPENDS ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

# find all cpp files in src
FILE(GLOB src_sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# find subdirectories in src that contain code for classes
SUBDIRLIST(SOURCE_DIRECTORIES src)

# in each subdirectory, find cpp files and add them to the source list
set(SOURCES ${src_sources})
set(TEST_SOURCES "")
FOREACH(subdir ${SOURCE_DIRECTORIES})
    FILE(GLOB sources CONFIGURE_DEPENDS ${subdir}/*.cpp)
    FILE(GLOB test_sources CONFIGURE_DEPENDS ${subdir}/test*.cpp)

    LIST(APPEND SOURCES ${sources})
    IF(test_sources)
        LIST(REMOVE_ITEM SOURCES ${test_sources})
    ENDIF()

    LIST(APPEND TEST_SOURCES ${test_sources})
ENDFOREACH()

# include the source directories
include_directories(${SOURCE_DIRECTORIES})

# create a build target for the main project file
add_executable(main src/main.cpp ${SOURCES})

# create a build target for the testing file
add_executable(tests ${TEST_SOURCES} ${SOURCES})
target_link_libraries(tests PUBLIC gtest_main)

# initialize GoogleTest
include(GoogleTest)
gtest_discover_tests(tests)

#################################################################################################
#                                     CONFIGURE SFML                                            #
#################################################################################################

# Add directory containing FindSFML.cmake to module path
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

# Find SFML
# Note: SFML_STATIC_LIBRARIES determines which libraries are found by find_package()
set(SFML_ROOT C:/Program\ Files/SFML)
find_package(SFML 2 COMPONENTS audio graphics window system network)

# If found, include and link; otherwise output error message
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Link SFML. For versions < 2.2, SFML_DEPENDENCIES is not defined, and we do not need to link dependencies
if(SFML_VERSION_MINOR LESS 2)
    set(SFML_DEPENDENCIES "")
endif()
target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
