cmake_minimum_required(VERSION 3.10.0)

project(easypg
    VERSION 0.1.6
    LANGUAGES C
    DESCRIPTION "EasyPG (Easy Password Generator)"
    HOMEPAGE_URL "https://github.com/movhex/easypg"
)

add_executable(${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PRIVATE include)

target_sources(${PROJECT_NAME}
PRIVATE
    src/main.c
    src/generator.c
    src/memory.c
    src/random.c
)

target_compile_options(${PROJECT_NAME}
PRIVATE
    -Wall
    -Wextra
    -Wuninitialized
)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_99)

if (NOT CMAKE_BUILD_TYPE)
    set (build_type release)
else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
endif()

if (build_type STREQUAL debug)
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O0 -ggdb3)
elseif (build_type STREQUAL release)
    target_compile_options(${PROJECT_NAME} PRIVATE -g0 -O3)
endif()

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_REQUIRED_LIBRARIES}
    ${ALL_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ssl crypto)

string(TOLOWER ${CMAKE_SYSTEM_NAME} system_name)
if (system_name STREQUAL windows)
    target_link_libraries(${PROJECT_NAME} ws2_32)
else()
    target_link_libraries(${PROJECT_NAME} pthread)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
endif()
