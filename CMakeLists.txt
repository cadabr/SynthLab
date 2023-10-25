cmake_minimum_required(VERSION 3.15)

project(SynthLab VERSION 0.0.1)

set(LIB_JUCE_TAG "7.0.8")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Show all module sources in IDE projects" ON)

include(FetchContent)

set(FETCHCONTENT_BASE_DIR "${PROJECT_SOURCE_DIR}/Libs" CACHE PATH "External dependencies path." FORCE)

FetchContent_Declare(juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        ${LIB_JUCE_TAG}
    GIT_SHALLOW    TRUE
    GIT_CONFIG     advice.detachedHead=false    # Disable detached HEAD warning for fetching a specific tag
    SOURCE_DIR     "${FETCHCONTENT_BASE_DIR}/JUCE"
    SUBBUILD_DIR   "${FETCHCONTENT_BASE_DIR}/JUCE-Subbuild"
    BINARY_DIR     "${FETCHCONTENT_BASE_DIR}/JUCE-Build")

FetchContent_MakeAvailable(juce)

juce_add_gui_app("${PROJECT_NAME}"
    FORMATS Standalone
    PRODUCT_NAME "SynthLab"
    COMPANY_NAME FreqTech
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
)

target_compile_features("${PROJECT_NAME}" PUBLIC cxx_std_17)

# Disable compiler extensions for the project targets (e.g. use -std=c++17 instead of -std=gnu++17).
get_property(project_targets DIRECTORY "${PROJECT_SOURCE_DIR}" PROPERTY BUILDSYSTEM_TARGETS)

set_target_properties(${project_targets} PROPERTIES CXX_EXTENSIONS OFF)

add_subdirectory(Sources)

# `juce_generate_juce_header` will create a JuceHeader.h for a given target, which will be generated
# into your build tree. The include path for this header will be automatically added to the target.
# NOTE: JuceHeader.h is generated when the target is built.

juce_generate_juce_header("${PROJECT_NAME}")

# `target_compile_definitions` adds some preprocessor definitions to our target.
# JUCE modules also make use of compile definitions to switch certain features on/off,
# so if there's a particular feature you need that's not on by default, check the module header
# for the correct flag to set here.
# These definitions will be visible both to your code, and also the JUCE module code.

target_compile_definitions("${PROJECT_NAME}"
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        DONT_SET_USING_JUCE_NAMESPACE=1
)

# If your target needs extra binary assets, you can add them here.
# NOTE: Conversion to binary-data happens when the target is built.

# juce_add_binary_data(Assets       # Name of a static library target that will include all the binary resources
    # HEADER_NAME ...               # Name of the generated header. "BinaryData.h" is used by default
    # NAMESPACE ...                 # Namespace of the generated binary data class. "BinaryData" is used by default
#   SOURCES ...)                    # List of asset files of any kind that should be built into the static library

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically.

target_link_libraries("${PROJECT_NAME}"
    PRIVATE
        # Assets                # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)


### IDE Generator post-config ###

# IDEs:  Place source groups for project targets into a "Targets" folder (to reduce visual clutter).
# Xcode: Generate build schemes for project targets.
set_target_properties(${project_targets} PROPERTIES
    FOLDER "Targets"
    XCODE_GENERATE_SCHEME ON)

# IDEs:  Move the "shared code" source group (main target) out of the "Targets" folder
#        to the top level.
set_target_properties("${PROJECT_NAME}" PROPERTIES FOLDER "")

# IDEs:  Organise source file grouping.
get_target_property(project_sources "${PROJECT_NAME}" SOURCES)

#   If JuceHeader.h is generated, remove it from the source file list and handle it individually.
get_target_property(juce_library_code "${PROJECT_NAME}" JUCE_GENERATED_SOURCES_DIRECTORY)
set(juce_header "${juce_library_code}/JuceHeader.h")

list(REMOVE_ITEM project_sources "${juce_header}")

#   Place JuceHeader.h and the associated CMake Rule file into a "JUCE Library Code" folder.
source_group("JUCE Library Code" FILES "${juce_header}")
source_group("JUCE Library Code/CMake Rules" FILES "${juce_header}.rule")

#   Generate source groups that follow the organisation of source file directories.
source_group(TREE "${PROJECT_SOURCE_DIR}/Source" FILES ${project_sources})

#   Place Binary Data related source files into the root of their target folder.
if(TARGET Assets)
    get_target_property(project_assets Assets SOURCES)
    source_group("" FILES ${project_assets})
endif()

