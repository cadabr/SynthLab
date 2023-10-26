#target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>")

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${FETCHCONTENT_BASE_DIR}/JUCE/modules/
)

add_subdirectory(Core)

target_sources("${PROJECT_NAME}"
    PRIVATE
        AudioApp.h
        AudioApp.cpp
        MainComponent.h
        MainComponent.cpp
        MainWindow.h
        MainWindow.cpp
        SynthLab.h
        SynthLab.cpp
)

add_subdirectory(CUDA)
