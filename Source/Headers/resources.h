#pragma once
#include <dibujo.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

extern const char *ApplicationDirectory;

FILE *Resources_OpenFile(const char *path, const char *mode);
Image Resources_LoadImage(const char *path);
Dibujo Resources_LoadCenteredDibujo(const char *path, size_t width,
                                    size_t height);
