cmake_minimum_required(VERSION 3.16)

project(Tap_G VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tap_g
    src/main.cpp
    src/InputManager.cpp
    src/GestureDetector.cpp
    src/CommandDispatcher.cpp
    src/ConfigManager.cpp
    src/CommandExecutor.cpp
)

find_package(PkgConfig REQUIRED)
find_package(nlohmann_json REQUIRED)
pkg_check_modules(LIBINPUT REQUIRED libinput)
pkg_check_modules(LIBUDEV REQUIRED libudev)

target_include_directories(tap_g PRIVATE
    nlohmann_json::nlohmann_json
    include
    ${LIBINPUT_INCLUDE_DIRS}
    ${LIBUDEV_INCLUDE_DIRS}
)

target_link_libraries(tap_g PRIVATE
    nlohmann_json::nlohmann_json
    ${LIBINPUT_LIBRARIES}
    ${LIBUDEV_LIBRARIES}
)

install(FILES config/config.json
        DESTINATION share/tap_g)
install(TARGETS tap_g
        RUNTIME DESTINATION bin)