find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(UIApp
    GAME/Main/main.cpp
    "GAME/QT UI/MainUI.ui"
)
set_property(TARGET UIApp PROPERTY AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/GAME/QT UI")
target_compile_features(UIApp PRIVATE cxx_std_20)
target_link_libraries(UIApp PRIVATE Qt6::Widgets)
