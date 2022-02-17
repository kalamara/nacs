
## Not Another Configuration System
## Copyright (C) 2020-2021, Antonis Kalamaras (kalamara AT ceid DOT upatras DOT gr)

## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.2)

set(CMAKE_BUILD_TYPE Debug)

project("nacs")

find_library(CUNIT cunit)
find_library(YAML yaml)

include_directories(
	${PROJECT_SOURCE_DIR}/include
)
	
link_directories(
    ${PROJECT_BINARY_DIR}
)	

ADD_LIBRARY(${PROJECT_NAME}-yml
    SHARED 
    include/config.h
    src/config.c
    src/config-yml.c
)

target_link_libraries(
    ${PROJECT_NAME}-yml PUBLIC ${YAML}    
)	
if(CUNIT)    
add_executable(test_core
    ${PROJECT_SOURCE_DIR}/include/config.h
    ${PROJECT_SOURCE_DIR}/src/config.c
    ${PROJECT_SOURCE_DIR}/tst/schema.h
 	${PROJECT_SOURCE_DIR}/tst/schema.c
 	${PROJECT_SOURCE_DIR}/tst/ut-conf.h
	${PROJECT_SOURCE_DIR}/tst/ut-conf.c
)


message("building tests...")
target_link_libraries(
    test_core PUBLIC ${CUNIT} -lgcov    
)	

add_executable(test_yml
    ${PROJECT_SOURCE_DIR}/include/config.h
    ${PROJECT_SOURCE_DIR}/tst/schema.h
 	${PROJECT_SOURCE_DIR}/tst/schema.c
 	${PROJECT_SOURCE_DIR}/tst/ut-yml.h
	${PROJECT_SOURCE_DIR}/tst/ut-yml.c
)

add_dependencies(test_yml ${PROJECT_NAME}-yml)

target_link_libraries(
    test_yml PUBLIC ${CUNIT} ${YAML} -l${PROJECT_NAME}-yml -lgcov 
   
)
endif(CUNIT)
