add_library(xml_formatter_plugin SHARED
    plugin.cpp
)

target_include_directories(xml_formatter_plugin
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(xml_formatter_plugin
    PRIVATE
        imgui::imgui
        pugixml::pugixml
)

target_compile_definitions(xml_formatter_plugin PRIVATE PLUGIN_BUILD)

set_target_properties(xml_formatter_plugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins"
)
