cmake_minimum_required(VERSION 3.20)
project(Project_Calculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем библиотеку с логикой (КЛАССЫ)
# Сюда входят все .cpp файлы, КРОМЕ main.cpp и тестов
add_library(CoreLib STATIC
        src/Complex.cpp
        src/Expression.cpp
        src/Operations.cpp
        src/Logger.cpp
)

# Указываем, где лежат заголовочные файлы (.h)
target_include_directories(CoreLib PUBLIC include)

# 2. Основная программа (Executable)
# Только main.cpp, логика берется из CoreLib
add_executable(Project_Calculator main.cpp)
target_link_libraries(Project_Calculator PRIVATE CoreLib)

# 3. Подключаем Google Test (FetchContent)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. Настраиваем тесты
enable_testing()

add_executable(Project_Tests tests/test_main.cpp)
target_link_libraries(Project_Tests PRIVATE
        CoreLib          # Ваша логика
        GTest::gtest_main # Библиотека тестов
)

include(GoogleTest)
gtest_discover_tests(Project_Tests)
