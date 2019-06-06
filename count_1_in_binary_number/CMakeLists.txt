cmake_minimum_required(VERSION 3.5)
project(cpp_demo)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost REQUIRED COMPONENTS
    system
)



if(NOT Boost_FOUND)
    message("Not found Boost")
endif()


include_directories(${Boost_INCLUDE_DIRS})

# message(${Boost_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(${PROJECT_NAME}
    # Boost::system
    pthread
)
