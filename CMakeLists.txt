cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(
  game
  src/main.cpp
  src/ally/Ally.cpp
  src/ally/Ally.hpp
  src/animal/Animal.cpp
  src/animal/Animal.hpp
  src/enemy/Enemy.cpp
  src/enemy/Enemy.hpp
  src/game/Game.cpp
  src/game/Game.hpp
  src/game/GameOver.cpp
  src/game/GameOver.hpp
  src/game/Paused.hpp
  src/game/Paused.cpp
  src/health_bar/HealthBar.cpp
  src/health_bar/HealthBar.hpp
  src/logger/Logger.cpp
  src/logger/Logger.hpp
  src/map/Map.cpp
  src/map/Map.hpp
  src/menu/Menu.cpp
  src/menu/Menu.hpp
  src/npc/NPC.cpp
  src/npc/NPC.hpp
  src/player/Player.cpp
  src/player/Player.hpp
  src/game/Victory.cpp
  src/game/Victory.hpp
  src/leaderboard/Leaderboard.hpp
  src/leaderboard/Leaderboard.cpp
  src/utils/Utils.hpp
  src/utils/Utils.cpp
  src/replay/Replay.hpp
  src/replay/Replay.cpp
)

include_directories(
  game
  ${SDL2_INCLUDE_DIR}
  ${SDL2_MIXER_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(
  game
  ${SDL2_LIBRARY}
  ${SDL2_MIXER_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
)