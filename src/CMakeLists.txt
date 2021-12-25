find_path(OSPRAY_INCLUDE_DIR ospray/ospray.h DOC "Path to the include directory of OSPRay.")
find_path(RKCOMMON_INCLUDE_DIR rkcommon/common.h DOC "Path to the include directory of rkcommon.")

include_directories(../include ${OSPRAY_INCLUDE_DIR} ${RKCOMMON_INCLUDE_DIR})

add_library(${PROJECT_NAME}
    GCD.cpp
    TransferFunction.cpp

    # only to make sure that headers are shown in IDEs as part of the project
    ../include/ospray_util/GCD.hpp
    ../include/ospray_util/PiecewiseLinearFunction.hpp
    ../include/ospray_util/TransferFunction.hpp
)
