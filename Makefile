CC = gcc
AR = ar

CUSTOM_CFLAGS = 

DX11_LIBS = -ldxgi -ld3d11 -luuid -ld3dcompiler
LIBS :=-lgdi32 -lm -lopengl32 -lwinmm -ggdb 
EXT = .exe
STATIC =

WARNINGS = -Wall -Werror -Wstrict-prototypes -Wextra

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc i686-w64-mingw32-gcc))
	STATIC = --static
    detected_OS := Windows
else
	ifeq '$(findstring ;,$(PATH))' ';'
		detected_OS := Windows
	else
		detected_OS := $(shell uname 2>/dev/null || echo Unknown)
		detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
		detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
		detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
	endif
endif

ifeq ($(detected_OS),Windows)
	LIBS := -ggdb -ldwmapi -lshell32 -lwinmm -lgdi32 -lopengl32 $(STATIC)
	EXT = .exe
endif
ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Foundation -framework AppKit -framework OpenGL -framework CoreVideo$(STATIC)
	EXT = 
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm -lGL -ldl -lpthread $(STATIC)
	EXT =
endif

all: source/main.c include/*.h
	$(CC) source/main.c $(LIBS) -I./include $(WARNINGS) -o lonic

clean:
	rm -f lonic lonic.exe

debug: source/main.c include/*.h
	make clean

	$(CC) source/main.c $(LIBS) -I./include $(WARNINGS) -D RGFW_DEBUG -o lonic
	./lonic$(EXT)