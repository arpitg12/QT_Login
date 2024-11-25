cmake_minimum_required(VERSION 3.14)
project(QtSampleProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt path - adjust this to match your Qt installation path
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64/lib/cmake/Qt6")

# Find required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Source files
set(SOURCES
    src/main.cpp
    src/mainWindow.cpp
    src/dashboardwindow.cpp
)

# Header files
set(HEADERS
    include/mainwindow.h
    include/dashboardwindow.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Automatically copy Qt DLLs and plugins to output directory
if(WIN32)
    # Deploy Qt binaries using windeployqt
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
        --verbose 0
        --no-compiler-runtime
        --no-opengl-sw
        \"$<TARGET_FILE:${PROJECT_NAME}>\"
    COMMENT "Deploying Qt dependencies..."
)


    # Copy Visual C++ runtime DLLs
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
    include(InstallRequiredSystemLibraries)
    if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMENT "Copying MSVC runtime libraries..."
        )
    endif()
endif()

# Set output directories
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)