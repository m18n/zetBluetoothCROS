cmake_minimum_required(VERSION 2.6)
project(ZETPROGRAM)
file(GLOB CPPS "*.cpp")
include_directories("include")
link_directories("${PROJECT_SOURCE_DIR}/lib")
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#add_library(${PROJECT_NAME} SHARED ${CPPS})
add_executable(${PROJECT_NAME} ${CPPS})
if (UNIX)
target_include_directories(${PROJECT_NAME} PUBLIC bluetooth)
target_link_libraries(${PROJECT_NAME} bluetooth)
endif (UNIX)
target_link_libraries(${PROJECT_NAME} UltralightCore AppCore Ultralight WebCore)
if (APPLE)
  # Enable High-DPI on macOS through our custom Info.plist template
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in) 
endif()

if (MSVC)
  # Tell MSVC to use main instead of WinMain for Windows subsystem executables
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()
set(dirbuild ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${dirbuild}/assets DESTINATION ${PROJECT_SOURCE_DIR} )
# Copy all binaries to target directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
