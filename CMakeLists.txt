cmake_minimum_required(VERSION 3.16)
project(algorithmic_trading_backtester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(trading_engine
    src/main.cpp
    src/DataLoader.cpp
    src/Portfolio.cpp
    src/BuyAndHoldStrategy.cpp
    src/Backtester.cpp
)

target_include_directories(trading_engine PRIVATE include)

if (MSVC)
    target_compile_options(trading_engine PRIVATE /W4)
else()
    target_compile_options(trading_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
