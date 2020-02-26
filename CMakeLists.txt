cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

project("yacs")

find_library(CUNIT cunit)
find_library(YAML yaml)

include_directories(
	${PROJECT_SOURCE_DIR}/include
)
	
link_directories(
    ${PROJECT_BINARY_DIR}
)	

ADD_LIBRARY(${PROJECT_NAME}-yml
    STATIC 
    include/config.h
    src/config.c
    src/config-yml.c
)

target_link_libraries(
    ${PROJECT_NAME}-yml PUBLIC ${YAML}    
)	
    
add_executable(test_core
    ${PROJECT_SOURCE_DIR}/include/config.h
    ${PROJECT_SOURCE_DIR}/src/config.c
    ${PROJECT_SOURCE_DIR}/tst/schema.h
 	${PROJECT_SOURCE_DIR}/tst/schema.c
 	${PROJECT_SOURCE_DIR}/tst/ut-conf.h
	${PROJECT_SOURCE_DIR}/tst/ut-conf.c
)

target_link_libraries(
    test_core PUBLIC ${CUNIT} -lgcov    
)	


