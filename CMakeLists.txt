cmake_minimum_required(VERSION 3.15)
project(mbedtls_test C)


#set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_C_FLAGS_DEBUG "-g -O0")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


# C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)




# 头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 库文件路径
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 生成可执行文件
add_executable(main 
main.c 
app_sdl2.c
app_mbedtls.c
)


target_link_libraries(
    main
    mbedcrypto
    mbedtls
    mbedx509
    pthread
    SDL2
    SDL2_ttf
)