# Makefile

# Define the compiler to use.
COMPILER = g++

# Define compiler flags.
COMPILER_FLAGS = \
	-D_THREAD_SAFE \
	-Wall \
	-Wno-multichar \
	-Wno-tautological-constant-out-of-range-compare \
	-g \
	-std=c++11 \
	-stdlib=libc++ \
	-static

# Define the archiver to use.
ARCHIVER = ar

# Define archiver flags.
ARCHIVER_FLAGS = rcs

# Define directories containing headers to include.
INCLUDE_PATHS = \
	-I/usr/local/include \
	-Iinclude

# Define source files.
SOURCE_FILES = \
	$(wildcard src/*.cpp)

# Define object files.
OBJECT_FILES = \
	$(patsubst src/%.cpp, obj/%.o, $(SOURCE_FILES))

# Define library file.
STATIC_LIBRARY = lib/libSAGE.a

all: $(STATIC_LIBRARY)

$(STATIC_LIBRARY): $(OBJECT_FILES)
	$(ARCHIVER) $(ARCHIVER_FLAGS) $(STATIC_LIBRARY) $(OBJECT_FILES)

$(OBJECT_FILES): obj/%.o : src/%.cpp
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@ $(INCLUDE_PATHS)

clean:
	$(RM) $(wildcard lib/*.a)
	$(RM) $(wildcard obj/*.o)