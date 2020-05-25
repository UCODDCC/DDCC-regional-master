cmake_minimum_required (VERSION 2.8.11)

project(DDCD-regional-master)

set(SOURCES
        app/src/requesters/resourceRequester.cpp
        app/src/utils.cpp
        app/src/handlers/resourceHandler.cpp
        )

set(TARGET app/src/app.cpp)

add_executable(${PROJECT_NAME} ${TARGET} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/app/include)

find_package(Threads REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

target_link_libraries(${PROJECT_NAME} lwcpps)

target_compile_definitions (${PROJECT_NAME} PRIVATE -DDEBUG)



