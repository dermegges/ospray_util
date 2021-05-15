find_package(ospray 2.2.0 REQUIRED)

include_directories(../include)

add_library(${PROJECT_NAME}
    GCD.cpp

    # only to make sure that headers are shown in IDEs as part of the project
    ../include/GCD.hpp
    ../include/PiecewiseLinearFunction.hpp
)

target_link_libraries(${PROJECT_NAME} ospray::ospray)
