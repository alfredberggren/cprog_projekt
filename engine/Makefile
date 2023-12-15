# Mac, g++(Apple Clang) alt. g++-13(GCC) och sdl2 genom homebrew
# Windows, g++(GCC) och sdl2 genom MSYS2 mingw-w64

# DIN KÄLLKOD-var dina egna .cpp-filer finns
SRC_DIR = src
# FILNAMNET för ditt program som skall byggas, och VAR
OBJ_NAME = play
BUILD_DIR = build/debug

# KOMPILATOR, g++/g++-13/c++/c++-13 beroende på installation
# Mac GCC COMPILER(231010, obs. problem efter uppdatering av Xcode, använd 'g++'(Apple Clang) eller 'g++-13'(GCC) med länk-flaggan '-ld_classic')
#CC = g++-13
#CC = g++-13 -ld_classic
#CC = g++

# Windows GCC COMPILER
CC = g++

# Valbara kompileringsflaggor(options)
COMPILER_FLAGS = -std=c++17 -Wall -O0 -g

# ALLA filer med filändelsen .cpp i foldern SRC_DIR
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# INKLUDERINGSFILER–var dina header-filer finns
# Mac INTEL INCLUDE_PATHS!
#INCLUDE_PATHS = -Iinclude -I/usr/local/include
# Mac ARM INCLUDE_PATHS!
#INCLUDE_PATHS = -Iinclude -I/opt/homebrew/include
# Windows INCLUDE_PATHS!
INCLUDE_PATHS = -Iinclude -IC:/msys64/ucrt64/include

# BIBLIOTEKSFILER–kompilerad objektkod
# Mac INTEL LIBRARY_PATHS!
#LIBRARY_PATHS = -Llib -L/usr/local/lib
# Mac ARM LIBRARY_PATHS!
#LIBRARY_PATHS = -Llib -L/opt/homebrew/lib
# Windows LIBRARY_PATHS
LIBRARY_PATHS = -Llib -LC:/msys64/ucrt64/lib

# LÄNKNING - objekfiler som används vid länkning. Enklare program utan SDL behöver normalt inte några speciella länk-flaggor
LINKER_FLAGS = 
# Om SDL2 används, Mac LINKER_FLAGS!
#LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
# Om SDL2 används, Windows LINKER_FLAGS!
#LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf


all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)
