set(Math_sources
    src/Round.cpp
)

add_library(Math ${Math_sources})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)