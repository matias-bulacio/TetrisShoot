#pragma once

#include <escape.h>
#include <lista_enemigos.h>
#include <lista_escondites.h>
#include <stdbool.h>
#include <stdio.h>
bool InitShooterConfig(FILE *ini);

ListaEnemigos *GetListaEnemigos();
ListaEscapes *GetListaEscapes();
ListaEscondites *GetListaEscondites();
int *GetCollisionMargin();
