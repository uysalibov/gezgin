set(renderer_sources
    src/Renderer.cpp
)

add_library(Renderer ${renderer_sources})

add_dependencies(Renderer raylib)
target_link_libraries(Renderer PRIVATE raylib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)