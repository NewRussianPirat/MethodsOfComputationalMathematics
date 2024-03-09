add_library(MethodsOfComputationalMathematics_lib
        Double.cpp
        Rational.cpp
)

add_executable(main main.cpp)

target_link_libraries(main MethodsOfComputationalMathematics_lib)