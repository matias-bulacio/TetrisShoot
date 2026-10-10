#include <enemigos.h>
#include <escape.h>
#include <raymath.h>
#include <screen.h>

void Enemigo_Update(Enemigo *e, float now, float frame_time) {
    Vector2 obj, zona_escondida;
    switch (e->estado) {
    case ENEM_STATE_NULL:
        e->esperar_hasta = now + GetRandomValue(2000, 6000) / 1000.;
        e->coordenadas.y = -100;
        e->coordenadas.x = -100;
        e->velocidad = GetRandomValue(e->min_velocidad, e->max_velocidad);
        e->estado = ENEM_STATE_INACTIVO;
        break;
    case ENEM_STATE_INACTIVO:
        if (now > e->esperar_hasta) {
            e->esc = PrimerEsconditeLibre(e->le);
            if (e->esc) {
                zona_escondida = (Vector2){0, e->esc->distancia_de_escondite};
                e->objetivo = Vector2Add(zona_escondida, e->esc->coords);
                e->coordenadas.x = e->objetivo.x;
                e->esc->ocupado = true;
                e->estado = ENEM_STATE_CORRIENDO_Y;
                break;
            }
            Escape *exit =
                MejorEscape(e->lexits, GetRandomValue(0, SCREEN_SHOOTER_WIDTH));
            if (exit) {
                e->objetivo = (Vector2){
                    .x = exit->x,
                    .y = SCREEN_SHOOTER_HEIGHT + 200,
                };
                e->coordenadas.x = exit->x;
                e->estado = ENEM_STATE_CORRIENDO_Y;
                break;
            }
        }
        break;
    case ENEM_STATE_CORRIENDO_X:
        obj = e->objetivo;
        obj.y = e->coordenadas.y;

        e->coordenadas =
            Vector2MoveTowards(e->coordenadas, obj, e->velocidad * frame_time);

        if (Vector2Equals(e->coordenadas, obj))
            e->estado = ENEM_STATE_CORRIENDO_Y;

        break;
    case ENEM_STATE_CORRIENDO_Y:
        obj = e->objetivo;
        obj.x = e->coordenadas.x;

        e->coordenadas =
            Vector2MoveTowards(e->coordenadas, obj, e->velocidad * frame_time);

        if (Vector2Equals(e->coordenadas, obj)) {
            e->estado = ENEM_STATE_ESCONDIDO;
            e->esperar_hasta = now + GetRandomValue(250, 3500) / 1000.;
        }
        break;
    case ENEM_STATE_ESCONDIDO:
        if (now > e->esperar_hasta) {
            Escondite *esc = SiguienteEscondite(e->le, e->coordenadas);
            if (esc) {
                e->esc->ocupado = false;
                e->esc = esc;
                zona_escondida = (Vector2){0, e->esc->distancia_de_escondite};
                e->objetivo = Vector2Add(zona_escondida, e->esc->coords);
                e->esc->ocupado = true;
                e->estado = ENEM_STATE_CORRIENDO_X;
                break;
            }

            Escape *exit = MejorEscape(e->lexits, e->coordenadas.x);
            if (exit) {
                e->esc->ocupado = false;
                e->esc = NULL;
                e->objetivo = (Vector2){
                    .x = exit->x,
                    .y = SCREEN_SHOOTER_HEIGHT + 200,
                };
                e->estado = ENEM_STATE_CORRIENDO_X;
                break;
            }
        }
        break;
    case ENEM_STATE_OUT:
        break;
    }
}

void Enemigo_Reset(Enemigo *e) {
    e->estado = ENEM_STATE_INACTIVO;
    e->coordenadas.y = -100;
    if (e->esc)
        e->esc->ocupado = false;
    e->velocidad = GetRandomValue(195, 260);
}
