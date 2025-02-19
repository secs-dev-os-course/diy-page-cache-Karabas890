cmake_minimum_required(VERSION 3.12)
project(app
        VERSION 0.0.0
        DESCRIPTION "Application module"
        LANGUAGES C CXX
)

cmake_policy(SET CMP0076 NEW) # avoid warning of relative paths translation

# Создание библиотеки из cache.cpp
add_library(cache SHARED cache.cpp) 

# Основной исполнимый файл
add_executable(app app.cpp)

# Исполнимые файлы для io-thpt-writeApp.cpp и io-thpt-writeModApp.cpp
add_executable(io-thpt-writeApp io-thpt-writeApp.cpp io-thpt-write.cpp)
add_executable(io-thpt-writeModApp io-thpt-writeModApp.cpp  io-thpt-writeMod.cpp)

# Указываем директорию с заголовочными файлами
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(io-thpt-writeApp PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(io-thpt-writeModApp PRIVATE ${CMAKE_SOURCE_DIR})


# Связь библиотеки с основным приложением и другими исполнимыми файлами
target_link_libraries(app PRIVATE cache)
target_link_libraries(io-thpt-writeApp PRIVATE cache)
target_link_libraries(io-thpt-writeModApp PRIVATE cache)

