cmake_minimum_required( VERSION 2.4 )
project(ViZDoomC++Examples)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

add_library(vizdoom SHARED IMPORTED GLOBAL)
set_property(TARGET vizdoom PROPERTY IMPORTED_LOCATION ../../bin/libvizdoom.so)

find_package(Boost COMPONENTS filesystem thread system date_time chrono regex iostreams REQUIRED)
find_package(Threads REQUIRED)

set( VIZDOOM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../vizdoom_api_src )
include_directories( ${VIZDOOM_INCLUDE_DIR} ${Boost_INCLUDE_DIR} )

set( VIZDOOM_EXAMPLES_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/examples )

set( VIZDOOM_LIBS vizdoom
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

if( UNIX )
    set( VIZDOOM_LIBS ${VIZDOOM_LIBS} rt)

endif()	
	
add_executable( basic Basic.cpp )
target_link_libraries (basic ${VIZDOOM_LIBS})

add_executable( cig CIG.cpp )
target_link_libraries (cig ${VIZDOOM_LIBS})

add_executable( cigbots CIGBots.cpp )
target_link_libraries (cigbots ${VIZDOOM_LIBS})

add_executable( cighost CIGHost.cpp )
target_link_libraries (cighost ${VIZDOOM_LIBS})

add_executable( deltabuttons DeltaButtons.cpp )
target_link_libraries (deltabuttons ${VIZDOOM_LIBS})

add_executable( multiplayer Multiplayer.cpp )
target_link_libraries (multiplayer ${VIZDOOM_LIBS})

add_executable( multiplayerhost MultiplayerHost.cpp )
target_link_libraries (multiplayerhost ${VIZDOOM_LIBS})

add_executable( seed Seed.cpp )
target_link_libraries (seed ${VIZDOOM_LIBS})

add_executable( shaping Shaping.cpp )
target_link_libraries (shaping ${VIZDOOM_LIBS})

add_executable( spectator Spectator.cpp )
target_link_libraries (spectator ${VIZDOOM_LIBS})

set_target_properties( basic cig cigbots cighost deltabuttons multiplayer multiplayerhost seed shaping spectator
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${VIZDOOM_EXAMPLES_OUTPUT_DIR}
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${VIZDOOM_EXAMPLES_OUTPUT_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${VIZDOOM_EXAMPLES_OUTPUT_DIR}
)
