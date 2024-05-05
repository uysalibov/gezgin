set(FileParser_sources
    src/OSMJson.cpp
    src/AdjList.cpp
)

add_library(FileParser ${FileParser_sources})

add_dependencies(FileParser Processing raylib nlohmann_json::nlohmann_json)
target_link_libraries(FileParser PRIVATE  Processing raylib nlohmann_json::nlohmann_json)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(FileParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)