LINUX_CC=gcc
WINDOWS_CC=x86_64-w64-mingw32-gcc
WEB_CC=/usr/lib/emscripten/emcc
CFLAGS=-O2 -Wall -Wextra -MMD -MP
CFLAGS_LINUX= -DPLATFORM_LINUX
CFLAGS_WINDOWS= -DPLATFORM_WINDOWS
CFLAGS_WEB= -DPLATFORM_WEB --memory-init-file 0 -s USE_GLFW=3 --shell-file=Libraries/Static/Web/minshell.html -s MAX_WEBGL_VERSION=2

SOURCES=$(wildcard Source/*.c Source/Implementation/*.c)
OBJECTS_LINUX=$(patsubst %.c,Build/Linux/%.o,$(SOURCES))
OBJECTS_WINDOWS=$(patsubst %.c,Build/Windows/%.o,$(SOURCES))
OBJECTS_WEB=$(patsubst %.c,Build/Web/%.o,$(SOURCES))
DEPENDENCIES_LINUX=$(OBJECTS_LINUX:.o=.d)
DEPENDENCIES_WINDOWS=$(OBJECTS_WINDOWS:.o=.d)
DEPENDENCIES_WEB=$(OBJECTS_WEB:.o=.d)

COMMON_INCLUDE=-ISource/Headers/

LINUX_INCLUDE=-ILibraries/Include/Linux/
WINDOWS_INCLUDE=-ILibraries/Include/Windows/
WEB_INCLUDE=-ILibraries/Include/Web/

STATIC_LINUX_LIBS = -lraylib
DYNAMIC_LINUX_LIBS= -lm -lGL -lpthread -ldl -lrt -lX11
LINUX_LIBS        = -LLibraries/Static/Linux/ -Wl,-Bstatic $(STATIC_LINUX_LIBS) -Wl,-Bdynamic $(DYNAMIC_LINUX_LIBS)

STATIC_WINDOWS_LIBS = -lraylib
DYNAMIC_WINDOWS_LIBS= -lgdi32 -lwinmm
WINDOWS_LIBS= -LLibraries/Static/Windows/ -Wl,-Bstatic $(STATIC_WINDOWS_LIBS) -Wl,-Bdynamic $(DYNAMIC_WINDOWS_LIBS)

WEB_LIBS= -LLibraries/Static/Web/ -lraylib -lGL

linux: Binaries/Linux/game
windows: Binaries/Windows/game.exe
web: Binaries/Web/game.html

Binaries/Linux/game: $(OBJECTS_LINUX) | Binaries/Linux
	$(LINUX_CC) -o $@ $^ $(LINUX_LIBS)
	rm -rf $(dir $@)/Resources
	cp -r Resources $(dir $@)

Build/Linux/%.o: %.c | Build/Linux
	mkdir -p $(dir $@)
	$(LINUX_CC) $(CFLAGS) $(CFLAGS_LINUX) $(COMMON_INCLUDE) $(LINUX_INCLUDE) -c -o $@ $< -MF $(@:.o=.d)

Binaries/Windows/game.exe: $(OBJECTS_WINDOWS) | Binaries/Windows
	$(WINDOWS_CC) -o $@ $^ $(WINDOWS_LIBS)
	rm -rf $(dir $@)/Resources
	cp -r Resources $(dir $@)

Build/Windows/%.o: %.c | Build/Windows
	mkdir -p $(dir $@)
	$(WINDOWS_CC) $(CFLAGS) $(CFLAGS_WINDOWS) $(COMMON_INCLUDE) $(WINDOWS_INCLUDE) -c -o $@ $< -MF $(@:.o=.d)

Binaries/Web/game.html: $(OBJECTS_WEB) | Binaries/Web
	$(WEB_CC) -o $@ $^ $(WEB_LIBS)
	rm -rf $(dir $@)/Resources
	cp -r Resources $(dir $@)

Build/Web/%.o: %.c | Build/Web
	mkdir -p $(dir $@)
	$(WEB_CC) $(CFLAGS) $(CFLAGS_WEB) $(COMMON_INCLUDE) $(WEB_INCLUDE) -c -o $@ $< -MF $(@:.o=.d)

Build/Linux Build/Windows Build/Web Binaries/Linux Binaries/Windows Binaries/Web:
	mkdir -p $@

-include $(DEPENDENCIES_LINUX) $(DEPENDENCIES_WINDOWS) $(DEPENDENCIES_WEB)

all: linux

.PHONY: all linux windows

clean:
	rm -rf Build Binaries
	mkdir -p Build/Linux Build/Web Build/Windows
	mkdir -p Binaries/Linux Binaries/Web Binaries/Windows
	touch Build/.gitkeep Binaries/.gitkeep
