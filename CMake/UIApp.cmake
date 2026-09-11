find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(UIApp Main/main.cpp Main/MainUI.ui)
target_compile_features(UIApp PRIVATE cxx_std_20)
target_link_libraries(UIApp PRIVATE Qt6::Widgets)
