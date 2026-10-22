cmake_minimum_required(VERSION 3.16)

project(MotorThermalGuard LANGUAGES CXX)

# C++ dil standardi: 17 degeri proje tercihidir.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Uygulamaya ortak olan kodun kutuphanesi.
add_library(motor_protection
    src/motor_protection.cpp
)

target_include_directories(motor_protection
    PUBLIC include
)

# Gercek calistirabilir konsol programi.
add_executable(motor_monitor
    src/main.cpp
)

target_link_libraries(motor_monitor
    PRIVATE motor_protection
)

# Ayri test programi ve CTest tanimi.
enable_testing()

add_executable(motor_tests
    tests/test_motor_protection.cpp
)

target_link_libraries(motor_tests
    PRIVATE motor_protection
)

add_test(
    NAME MotorProtectionTests
    COMMAND motor_tests
)
