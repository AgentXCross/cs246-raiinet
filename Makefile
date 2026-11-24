# Target executable
TARGET = raiinet

# Source files
SRC = 

# Dependencies
MODULES = vector sstream string iostream memory array fstream

ARGS =

# ====================================================================== #

COMP = g++-15.2.0
COMPFLAGS = -fno-elide-constructors -Wall -std=c++20 -fmodules-ts -Werror=vla
MODULEDIR = gcm.cache

all: $(TARGET)

$(TARGET): $(SRC) $(MODULEDIR)
	@$(COMP) $(COMPFLAGS) -g $(SRC) -o $@ -lX11

$(MODULEDIR):
	@$(COMP) $(COMPFLAGS) -c -x c++-system-header $(MODULES)

run: $(TARGET)
	@./$(TARGET) $(ARGS)

clean:
	@rm -rf $(TARGET) $(MODULEDIR)

.PHONY: all run clean