cmake_minimum_required(VERSION 3.13)
project(FuseGame)


set(STATIC_BUILD FALSE)
set(ENV_ROOT "D:/Programs/ProgrammingEnvironment")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Executable/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -pedantic -Wall -Wextra")

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(STATIC_BUILD TRUE)
endif ()

if(STATIC_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
endif()


# Magic for add ico to exe
if(MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> <DEFINES> -o <OBJECT> <SOURCE>")
endif(MINGW)

add_executable(${PROJECT_NAME}
        config.rc # Add ico to exe
        Resources/ImageSources/Icon/FuseGameIcon.hpp # Images for OpenGL window
        Resources/ImageSources/Icon/FuseGameIcon.cpp

        SRC/main.cpp

        SRC/Enemy/Enemy.cpp
        SRC/Enemy/Enemy.hpp

        SRC/EnemyStorage/EnemyStorage.cpp
        SRC/EnemyStorage/EnemyStorage.hpp

        SRC/Player/Player.cpp
        SRC/Player/Player.hpp


        SRC/Utility/Updateable.hpp

        SRC/Utility/GameObject.hpp
        SRC/Utility/ProgramEvents/ProgramEvents.hpp
        SRC/Utility/Time/Timer.hpp
        SRC/Utility/Time/Stopwatch.hpp

        SRC/Utility/Math/Math.hpp

        SRC/Animations/Rotation/Rotation.cpp
        SRC/Animations/Rotation/Rotation.hpp


        SRC/Game/Game.cpp
        SRC/Game/Game.hpp

        SRC/Stats/StatsData.hpp
        SRC/Stats/Stats.cpp
        SRC/Stats/Stats.hpp

        SRC/AudioPlayer/AudioPlayer.hpp
        SRC/AudioPlayer/AudioPlayer.cpp

        SRC/AudioPlayer/MusicPlayer/MusicPlayer.hpp
        SRC/AudioPlayer/MusicPlayer/MusicPlayer.cpp

        SRC/AudioPlayer/SoundPlayer/SoundPlayer.hpp
        SRC/AudioPlayer/SoundPlayer/SoundPlayer.cpp


        SRC/Lasers/LasersController/LasersController.cpp
        SRC/Lasers/LasersController/LasersController.hpp

        SRC/Animations/FrameByFrame/FrameByFrame.cpp
        SRC/Animations/FrameByFrame/FrameByFrame.hpp


        SRC/Lasers/MassiveLaser/GenerateBeam.cpp
        SRC/Lasers/MassiveLaser/GenerateBeam.hpp

        SRC/Lasers/MassiveLaser/FlyingMassiveBeam.cpp
        SRC/Lasers/MassiveLaser/FlyingMassiveBeam.hpp


        SRC/Utility/IndexDataFile/IndexDataFile.cpp
        SRC/Utility/IndexDataFile/IndexDataFile.hpp

        SRC/Utility/MemoryTextureStorage/MemoryTextureStorage.cpp
        SRC/Utility/MemoryTextureStorage/MemoryTextureStorage.hpp

        SRC/Utility/WindowForTests/WindowForTests.cpp
        SRC/Utility/WindowForTests/WindowForTests.hpp

        SRC/Lasers/SimpleLaser/FlyingSimpleBeam.cpp
        SRC/Lasers/SimpleLaser/FlyingSimpleBeam.hpp

        SRC/Animations/Explosion/Explosion.cpp
        SRC/Animations/Explosion/Explosion.hpp

        SRC/Animations/HitpointsDecrease/HitpointsDecrease.cpp
        SRC/Animations/HitpointsDecrease/HitpointsDecrease.hpp

        SRC/Utility/Math/Line/Line.hpp
        SRC/Utility/Math/Line/Line.cpp
        SRC/Utility/Math/Circle/Circle.hpp
        SRC/Utility/Math/Circle/Circle.cpp
        SRC/Utility/Math/Vectors/Vectors.hpp
        SRC/Utility/Math/Vectors/Vectors.cpp

        SRC/Utility/Math/Random/Random.cpp
        SRC/Utility/Math/Random/Random.hpp

        SRC/Utility/MovementBorders.hpp

        SRC/Animations/LinearDeath/LinearDeath.cpp
        SRC/Animations/LinearDeath/LinearDeath.hpp

        SRC/Utility/Math/Parabola/Parabola.cpp
        SRC/Utility/Math/Parabola/Parabola.hpp

        SRC/Utility/Resources/Resources.cpp
        SRC/Utility/Resources/Resources.hpp

        SRC/Utility/ProgramEvents/ProgramEvents.cpp SRC/March8/March8.cpp SRC/March8/March8.hpp)





set(SFML_ROOT "${ENV_ROOT}/Librares/SFML-2.5.1")
set(SFML_STATIC_LIBRARIES ${STATIC_BUILD})
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system sfml-network)



set(SFML_STATIC_LIBRARIES ${STATIC_BUILD})
set(BOOST_ROOT "${ENV_ROOT}/Librares/boost_1_67_0/Build")
if(STATIC_BUILD)
    set(Boost_USE_STATIC_LIBS ON)
else()
    set(Boost_USE_STATIC_LIBS OFF)
endif()
find_package(Boost 1.67.0 REQUIRED filesystem system)
if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()




set(CONFIG_LOCATION "${ENV_ROOT}/Utility/PVS-Studio/PVS-Studio.cfg")
if(EXISTS ${CONFIG_LOCATION})
    file(READ "${CONFIG_LOCATION}" config_content)
endif()
if(config_content STREQUAL "")
    file(WRITE
            "${ENV_ROOT}/Utility/PVS-Studio/PVS-Studio.cfg"
            "exclude-path = ${ENV_ROOT}/Compilers \nexclude-path = ${ENV_ROOT}/Librares"
            )
endif()


include(${ENV_ROOT}/Utility/PVS-Studio/PVS-Studio.cmake)
pvs_studio_add_target(
        CONFIG ${ENV_ROOT}/Utility/PVS-Studio/PVS-Studio.cfg
        TARGET ${PROJECT_NAME}.analyze ALL
        OUTPUT FORMAT errorfile
        ANALYZE ${PROJECT_NAME}
        MODE GA 64 OP
        LOG target.err)