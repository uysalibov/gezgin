set(Processing_sources
    src/Round.cpp
    src/Graph.cpp
    src/Dijkstra.cpp
)

add_library(Processing ${Processing_sources})

add_dependencies(Processing raylib FileParser nlohmann_json::nlohmann_json)
target_link_libraries(Processing PRIVATE raylib FileParser nlohmann_json::nlohmann_json)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Processing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)