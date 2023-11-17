cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(BankApp VERSION 1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 20)

# Link QT6
find_package(Qt6 COMPONENTS Core Quick Widgets Core5Compat REQUIRED)

set(ProjectName BankApp)
qt_standard_project_setup()

qt_add_executable(${ProjectName}
        main.cpp
        core/Login.cpp
        core/Login.hpp
        core/User.hpp
        core/Signup.cpp
        core/Signup.hpp
        core/Cards.cpp
        core/Cards.hpp
        core/Bills.cpp
        core/Bills.hpp
)

qt_add_qml_module(${ProjectName}
        URI main
        VERSION 1.0
        QML_FILES
            "frontend/LoginPage.qml"
            "frontend/LoginPageCode.qml"
            "frontend/Main.qml"
            "frontend/PopUpWarning.qml"
            "frontend/SignupPage.qml"
            "frontend/PopUpInfo.qml"
            "frontend/MainPage.qml"
            "frontend/Card.qml"
            "frontend/GetString.qml"
            "frontend/History.qml"
            "frontend/CardsView.qml"
            "frontend/BillsView.qml"
            "frontend/Bill.qml"
            "frontend/KreditsView.qml"
            "frontend/DocumentsView.qml"
        RESOURCES
            "frontend/images/card_background.png"
        RESOURCE_PREFIX /
        RESOURCES resources.qrc
)

set_target_properties(${ProjectName} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
)

target_link_libraries(${ProjectName} PRIVATE Qt6::Core Qt6::Quick Qt6::Widgets Qt6::Core5Compat)
