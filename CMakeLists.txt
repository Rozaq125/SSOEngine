cmake_minimum_required(VERSION 3.16)
project(SSOEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agar sistem tahu letak file .h
include_directories(include)

# Agar sistem tahu letak file .a
link_directories(lib)

# Tambahkan file utama
add_executable(${PROJECT_NAME} 01_Core/main.cpp)

# Proses linking ke library lokal dan library sistem Windows
# Urutan penting: raylib dulu, baru library Windows
target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    opengl32 
    gdi32 
    winmm
)

# Output .exe ke folder bin agar rapi
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)