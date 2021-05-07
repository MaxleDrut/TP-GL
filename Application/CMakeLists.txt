cmake_minimum_required(VERSION 3.16)
project(Application)

set(CMAKE_CXX_STANDARD 11)
include_directories(include/main)


add_executable(Application_main
        include/main/sensors/Attribute.h
        include/main/sensors/Measurement.h
        include/main/sensors/Sensor.h
        include/main/user/Cleaner.h
        include/main/user/GovernmentUser.h
        include/main/user/IndividualUser.h
        include/main/user/ProviderUser.h
        include/main/user/User.h
        include/main/utils/utils.h
        include/main/Terminal.h
        include/main/services/CleanerService.h
        include/main/services/SensorService.h
        include/main/services/UserService.h

        src/main/main.cpp
        src/main/Terminal.cpp

        )

add_executable(Application_tests

        include/main/sensors/Attribute.h
        include/main/sensors/Measurement.h
        include/main/sensors/Sensor.h
        include/main/user/Cleaner.h
        include/main/user/GovernmentUser.h
        include/main/user/IndividualUser.h
        include/main/user/ProviderUser.h
        include/main/user/User.h
        include/main/utils/utils.h
        include/main/Terminal.h
        include/main/services/CleanerService.h
        include/main/services/SensorService.h
        include/main/services/UserService.h

        src/main/Terminal.cpp

        src/tests/main_tests.cpp
        )

target_include_directories(Application_tests PUBLIC include/tests include/main)

target_compile_options(Application_main PUBLIC "-D MAP")
target_compile_options(Application_tests PUBLIC "-D MAP -D DEBUG")

add_link_options(-ansi -pedantic -Wall -Werr)

# target_link_options(TP2_main PUBLIC )
# target_link_options(TP2_tests PUBLIC "--ansi --pedantic -Wall")