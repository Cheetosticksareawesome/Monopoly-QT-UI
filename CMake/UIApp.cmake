find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Keep automatic discovery limited to application files under GAME.
file(GLOB_RECURSE UIAPP_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/GAME/*.cpp"
    "${PROJECT_SOURCE_DIR}/GAME/*.h"
    "${PROJECT_SOURCE_DIR}/GAME/*.hpp"
    "${PROJECT_SOURCE_DIR}/GAME/*.ui"
    "${PROJECT_SOURCE_DIR}/GAME/*.qrc"
)

add_executable(UIApp ${UIAPP_FILES})
set_target_properties(UIApp PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    CXX_EXTENSIONS OFF
)
target_compile_features(UIApp PRIVATE cxx_std_20)
target_link_libraries(UIApp PRIVATE Qt6::Widgets)

# Make component headers and Designer forms available across GAME folders.
set(UIAPP_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/GAME")
set(UIAPP_FORM_DIRS "")
foreach(UIAPP_FILE IN LISTS UIAPP_FILES)
    get_filename_component(UIAPP_DIRECTORY "${UIAPP_FILE}" DIRECTORY)
    list(APPEND UIAPP_INCLUDE_DIRS "${UIAPP_DIRECTORY}")
    if(UIAPP_FILE MATCHES "\\.ui$")
        list(APPEND UIAPP_FORM_DIRS "${UIAPP_DIRECTORY}")
    endif()
endforeach()
list(REMOVE_DUPLICATES UIAPP_INCLUDE_DIRS)
list(REMOVE_DUPLICATES UIAPP_FORM_DIRS)
target_include_directories(UIApp PRIVATE ${UIAPP_INCLUDE_DIRS})
set_property(TARGET UIApp PROPERTY AUTOUIC_SEARCH_PATHS "${UIAPP_FORM_DIRS}")

