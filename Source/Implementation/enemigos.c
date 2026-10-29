#include <enemigos.h>
#include <escape.h>
#include <raymath.h>
#include <screen.h>

void Enemigo_Update(Enemigo *e, float now, float frame_time) {
    Vector2 obj, zona_escondida;
    switch (e->estado) {
    case ENEM_STATE_NULL:
        e->wait_until = now + GetRandomValue(2000, 6000) / 1000.;
        e->coord.y = -100;
        e->coord.x = -100;
        e->speed = GetRandomValue(e->min_speed, e->max_speed);
        e->estado = ENEM_STATE_INACTIVO;
        break;
    case ENEM_STATE_INACTIVO:
        if (now > e->wait_until) {
            e->esc = PrimerEsconditeLibre(e->lesc);
            if (e->esc) {
                zona_escondida = (Vector2){0, e->esc->standing_distance};
                e->goal = Vector2Add(zona_escondida, e->esc->coord);
                e->coord.x = e->goal.x;
                e->esc->occupied = true;
                e->estado = ENEM_STATE_CORRIENDO_Y;
                break;
            }
            Escape *exit =
                MejorEscape(e->lexit, GetRandomValue(0, SCREEN_SHOOTER_WIDTH));
            if (exit) {
                e->goal = (Vector2){
                    .x = exit->x,
                    .y = SCREEN_SHOOTER_HEIGHT + 200,
                };
                e->coord.x = exit->x;
                e->estado = ENEM_STATE_CORRIENDO_Y;
                break;
            }
        }
        break;
    case ENEM_STATE_CORRIENDO_X:
        obj = e->goal;
        obj.y = e->coord.y;

        e->coord = Vector2MoveTowards(e->coord, obj, e->speed * frame_time);

        if (Vector2Equals(e->coord, obj))
            e->estado = ENEM_STATE_CORRIENDO_Y;

        break;
    case ENEM_STATE_CORRIENDO_Y:
        obj = e->goal;
        obj.x = e->coord.x;

        e->coord = Vector2MoveTowards(e->coord, obj, e->speed * frame_time);

        if (Vector2Equals(e->coord, obj)) {
            e->estado = ENEM_STATE_ESCONDIDO;
            e->wait_until = now + GetRandomValue(250, 3500) / 1000.;
        }
        break;
    case ENEM_STATE_ESCONDIDO:
        if (now > e->wait_until) {
            Escondite *esc = SiguienteEscondite(e->lesc, e->coord);
            if (esc) {
                e->esc->occupied = false;
                e->esc = esc;
                zona_escondida = (Vector2){0, e->esc->standing_distance};
                e->goal = Vector2Add(zona_escondida, e->esc->coord);
                e->esc->occupied = true;
                e->estado = ENEM_STATE_CORRIENDO_X;
                break;
            }

            Escape *exit = MejorEscape(e->lexit, e->coord.x);
            if (exit) {
                e->esc->occupied = false;
                e->esc = NULL;
                e->goal = (Vector2){
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
    e->coord.y = -100;
    if (e->esc)
        e->esc->occupied = false;
    e->speed = GetRandomValue(195, 260);
}
