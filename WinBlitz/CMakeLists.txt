cmake_minimum_required(VERSION 3.5)

project(WinBlitz VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    Main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(WinBlitz
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        WriteText.h WriteText.cpp WriteText.ui
        NotClosable.h NotClosable.cpp
        CookieClicker.h CookieClicker.cpp CookieClicker.ui
        Calculation.h Calculation.cpp Calculation.ui
        WaitTimer.h WaitTimer.cpp WaitTimer.ui
        RememberNumber.h RememberNumber.cpp RememberNumber.ui
        SlideTo.h SlideTo.cpp SlideTo.ui
        ClickDate.h ClickDate.cpp ClickDate.ui
        CheckBox.h CheckBox.cpp CheckBox.ui
        ScrollEnd.h ScrollEnd.cpp ScrollEnd.ui
        FindLabel.h FindLabel.cpp FindLabel.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET WinBlitz APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(WinBlitz SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(WinBlitz
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(WinBlitz PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WinBlitz)
endif()
set_target_properties(WinBlitz PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS WinBlitz
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WinBlitz)
endif()
