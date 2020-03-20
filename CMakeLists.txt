cmake_minimum_required (VERSION 2.8.11)

project (DDCD-regional-master)

set(SOURCES
    app/src/kernel/Server.cpp
)

set(TARGET app/src/app.cpp)

add_executable(server ${TARGET} ${SOURCES})

target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/app/include)

find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(server Threads::Threads)