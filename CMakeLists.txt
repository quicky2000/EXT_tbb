cmake_minimum_required(VERSION 3.8)
project(EXT_tbb)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
find_package(TBB REQUIRED COMPONENTS tbb)

#------------------------------
#- Generic part
#------------------------------
get_target_property(INTERFACE_INCLUDE_DIRECTORIES TBB::tbb INTERFACE_INCLUDE_DIRECTORIES)
#Prepare targets
message("Declare library ${PROJECT_NAME}")
add_library(${PROJECT_NAME} SHARED IMPORTED GLOBAL)
get_target_property(IMPORTED_LOCATION TBB::tbb IMPORTED_LOCATION)
get_target_property(INTERFACE_COMPILE_OPTIONS TBB::tbb INTERFACE_COMPILE_OPTIONS)
set_target_properties(${PROJECT_NAME} PROPERTIES
                      IMPORTED_LOCATION ${IMPORTED_LOCATION}
                      INTERFACE_COMPILE_OPTIONS "${INTERFACE_COMPILE_OPTIONS}"
                      INTERFACE_INCLUDE_DIRECTORIES ${INTERFACE_INCLUDE_DIRECTORIES})

get_directory_property(HAS_PARENT PARENT_DIRECTORY)
if(NOT IS_DIRECTORY ${HAS_PARENT})
    #set(CMAKE_VERBOSE_MAKEFILE ON)
    set(CMAKE_CXX_STANDARD 17)
    add_executable(test_${PROJECT_NAME} ${MY_SOURCE_FILES} ${DEPENDANCY_OBJECTS} src/main_${PROJECT_NAME}.cpp)
    target_compile_definitions(test_${PROJECT_NAME} PRIVATE -D$<UPPER_CASE:${PROJECT_NAME}>_SELF_TEST)
    target_compile_options(test_${PROJECT_NAME} PUBLIC -Wall -ansi -pedantic -g -O3)
    target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})
endif()


#Force use of -std=c++11 instead of -std=gnu++11
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

#EOF
