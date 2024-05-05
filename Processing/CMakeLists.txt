set(Processing_sources
    src/Round.cpp
)

add_library(Processing ${Processing_sources})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Processing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)