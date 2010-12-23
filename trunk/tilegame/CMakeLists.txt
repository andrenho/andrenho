cmake_minimum_required (VERSION 2.6)
project (tilegame C)

add_definitions(`sdl-config --cflags`)
link_libraries(`sdl-config --libs` -lSDL_image)

add_library(tilegame tilegame.c debug.c)
add_executable(test test.c)
target_link_libraries(test tilegame)

#include(FindSDL)
#if(SDL_FOUND)
#  include_directories(${SDL_INCLUDE_DIR})
#  target_link_libraries(test SDL_main ${SDL_LIBRARY})
#else(SDL_FOUND)
#  message(FATAL_ERROR "SDL not found")
#endif(SDL_FOUND)

install(TARGETS tilegame DESTINATION bin)
install(FILES tilegame.h DESTINATION include)

