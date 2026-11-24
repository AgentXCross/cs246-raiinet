# Target executable
TARGET = raiinet

# Source files
SRC = main.cc \
      src/core/controller.cc src/core/controller-impl.cc \
      src/core/game.cc src/core/game-impl.cc \
      src/core/board.cc src/core/board-impl.cc \
      src/core/player.cc src/core/player-impl.cc \
      src/links/link.cc src/links/link-impl.cc \
      src/links/linkdecorator.cc src/links/linkdecorator-impl.cc \
      src/abilities/ability.cc src/abilities/ability-impl.cc \
      src/display/display.cc src/display/display-impl.cc \
      src/display/textdisplay.cc src/display/textdisplay-impl.cc \
      src/display/graphicsdisplay.cc src/display/graphicsdisplay-impl.cc

# Dependencies
MODULES = vector sstream string iostream memory array fstream

ARGS =