cmake_minimum_required(VERSION 3.26)

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(BankApp VERSION 1.0.0)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

# Link QT6
find_package(Qt6 COMPONENTS Core Quick Widgets Network Core5Compat REQUIRED)
find_package(GTest CONFIG REQUIRED)

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
        core/History.hpp
        backend/Api.cpp
        backend/Api.hpp
        core/User.cpp
        core/Credits.cpp
        core/Credits.hpp
        core/Documents.cpp
        core/Documents.hpp
        core/utils.cpp
        core/utils.hpp
        core/Bonus.cpp
        core/Bonus.hpp
)

qt_add_executable(test_app
        test.cpp
        core/Bills.cpp
        core/Bills.hpp
        core/History.hpp
        backend/Api.cpp
        backend/Api.hpp
        core/User.hpp
        core/User.cpp
        test_api.hpp
        core/Cards.cpp
        core/Cards.hpp
        core/utils.cpp
        core/utils.hpp
)

qt_add_qml_module(${ProjectName}
        URI main
        VERSION 1.0
        QML_FILES
        "frontend/CreditsView.qml"
        "frontend/LoginPageCode.qml"
        "frontend/Card.qml"
        "frontend/PopUpWarning.qml"
        "frontend/LoginPage.qml"
        "frontend/DocumentsView.qml"
        "frontend/Main.qml"
        "frontend/SignupPage.qml"
        "frontend/SignupPageCode.qml"
        "frontend/Bill.qml"
        "frontend/PopUpInfo.qml"
        "frontend/History.qml"
        "frontend/MainPage.qml"
        "frontend/CardsView.qml"
        "frontend/BillsView.qml"
        "frontend/GetString.qml"
        "frontend/GetCredentials.qml"
        "frontend/Details.qml"
        "frontend/Credit.qml"
        "frontend/Document.qml"
        "frontend/NewCard.qml"
        "frontend/BonusView.qml"
        "frontend/Bonus.qml"
        RESOURCES
        "frontend/images/card_background.png"
        "frontend/images/card_background1.png"
        "frontend/images/account_background.jpeg"
        "frontend/fonts/sfpro.otf"
        "frontend/fonts/Markdown.ttf"
        "frontend/images/logo.jpeg"
        RESOURCE_PREFIX /
        RESOURCES resources.qrc
)

set_target_properties(${ProjectName} PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
)

target_link_libraries(${ProjectName} PRIVATE Qt6::Core Qt6::Quick Qt6::Widgets Qt6::Core5Compat Qt6::Network)

target_link_libraries(${ProjectName} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

target_link_libraries(test_app PRIVATE Qt6::Core Qt6::Quick Qt6::Widgets Qt6::Core5Compat Qt6::Network)

target_link_libraries(test_app PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

include_directories(./)
