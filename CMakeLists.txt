cmake_minimum_required(VERSION 3.15)
project(mbedtls_test C)

# C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 手动指定 SDL2 路径（你只需要改这里）
set(SDL2_PATH "D:/etec/hive/SDL2-devel-2.32.8-mingw/SDL2-2.32.8/x86_64-w64-mingw32")


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/main.map")


# 手动添加头文件路径
include_directories(${SDL2_PATH}/include)

# 手动添加库路径
link_directories(${SDL2_PATH}/lib)




# 头文件路径
include_directories(${CMAKE_SOURCE_DIR}/include)

# 库文件路径
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 生成可执行文件
add_executable(main main.c)

# 链接 MbedTLS + Windows 系统库
target_link_libraries(
    main
    mbedtls
    mbedx509
    mbedcrypto
    bcrypt
    ws2_32
    pthread
    mingw32       
    SDL2main      
    SDL2
    SDL2_ttf
)