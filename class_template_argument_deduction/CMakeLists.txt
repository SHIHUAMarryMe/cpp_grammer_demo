cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-lstdc++fs -std=c++17")

project(class_template_argument_deduction)


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
#    ${Boost_LIBRARIES}
    # Boost::system
    # pthread
    stdc++fs #this is necessery in gcc 8.30
)