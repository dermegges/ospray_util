find_path(OSPRAY_INCLUDE_DIR ospray/ospray.h DOC "Path to the include directory of OSPRay.")

include_directories(../include ${OSPRAY_INCLUDE_DIR})

add_library(${PROJECT_NAME}
    GCD.cpp

    # only to make sure that headers are shown in IDEs as part of the project
    ../include/GCD.hpp
    ../include/PiecewiseLinearFunction.hpp
)
