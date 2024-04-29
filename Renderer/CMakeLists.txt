set(renderer_sources
    src/Renderer.cpp
    src/Inputs.cpp
)

add_library(Renderer ${renderer_sources})

add_dependencies(Renderer raylib FileParser nlohmann_json::nlohmann_json)
target_link_libraries(Renderer PRIVATE raylib FileParser nlohmann_json::nlohmann_json)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)