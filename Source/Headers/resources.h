#pragma once
#include <dibujo.h>
#include <raylib.h>
#include <stddef.h>

extern const char *ApplicationDirectory;

Image Resources_LoadImage(const char *path);
Dibujo Resources_LoadCenteredDibujo(const char *path, size_t width,
                                    size_t height);
