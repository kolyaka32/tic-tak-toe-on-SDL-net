cmake_minimum_required(VERSION 3.10)

project(tic-tac-toe)  # Main game project

# Set source files
add_executable( ${CMAKE_PROJECT_NAME}
    # Base includes and defines
    src/include.hpp
    src/define.hpp
    src/dataTypes.hpp
    src/values.hpp

    # Function of initialasing all data
    src/init.hpp
    src/init.cpp

    # Functions of loading all in-game data
    src/dataLoader.hpp
    src/dataLoader.cpp

    # Base interface
    src/baseGUI.hpp
    src/baseGUI.cpp

    # Interface of game pausing
    src/pause.hpp
    src/pause.cpp

    # System of initialasing file loading and unloading
    src/initFile.hpp
    src/initFile.cpp

    # In game classes
    src/entity.hpp
    src/entity.cpp

    # Singleplayer game cycles
    src/gameSingle.hpp
    src/gameSingle.cpp

    # Server game cycle
    src/gameServer.hpp
    src/gameServer.cpp

    # Client game cycle
    src/gameClient.hpp
    src/gameClient.cpp

    # Main function
    src/main.cpp
    
    # Adding game icone
    src/set.rc
)


set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")

#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

find_package(PkgConfig QUIET)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/sdl2/")
set(BIN_DIR ${SDL_cmake_template_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)

# Including libzip
#set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/share")
find_package(libzip REQUIRED)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Including external included directories
include_directories(${CMAKE_PROJECT_NAME})
include_directories(${LIBZIP_INCLUDE_DIRS})

# Including linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer SDL2::Net)
target_link_libraries(${CMAKE_PROJECT_NAME} ${libzip_LIBRARIES} libzip::zip)