#include <ini.h>
#include <resources.h>
#include <shooter_config.h>
#include <stdio.h>
#include <string.h>

ini_handler handler;

ListaEnemigos lenems_cfg = {0};
ListaEscapes lexits_cfg = {0};
ListaEscondites lescs_cfg = {0};
int collision_margin_cfg, standing_distance_cfg;

Dibujo dib_tigre_cfg;

// Compare if two strings are the same
// Returns true if so
bool str_eq(const char *a, const char *b) { return strcmp(a, b) == 0; }

bool str2int_or_log_err(const char *s, const char *n, const char *v, int *out) {
    int r = sscanf(v, "%d", out);
    if (r != 1) {
        TraceLog(LOG_ERROR, "Bad config on %s/%s = %s", s, n, v);
        return false;
    }
    return true;
}

int handler_func_enemigos(const char *n, const char *v) {
    const char *s = "enemigos";
    if (!str_eq("tiger_count", n))
        return false;

    int num;
    if (!str2int_or_log_err(s, n, v, &num))
        return false;
    lenems_cfg = NewListaEnemigos(num);
    return true;
}

int handler_func_escondites(const char *n, const char *v) {
    const char *s = "escondites";
    if (str_eq(n, "count")) {
        int num;
        if (!str2int_or_log_err(s, n, v, &num))
            return false;
        lescs_cfg = NewListaEscondites(num);
        return true;
    }
    if (str_eq(n, "collisionMargin")) {
        return str2int_or_log_err(s, n, v, &collision_margin_cfg);
    }
    if (str_eq(n, "standingDistance")) {
        if (!str2int_or_log_err(s, n, v, &standing_distance_cfg)) {
            return false;
        }
        standing_distance_cfg = -standing_distance_cfg;
        return true;
    }

#define PREFIX_LENGTH 6
    // 6 is the size of the string "list."
    //
    char prefix[PREFIX_LENGTH];
    strncpy(prefix, n, PREFIX_LENGTH)[PREFIX_LENGTH - 1] = '\0';
    if (str_eq(prefix, "list.")) {
        size_t idx;
        int r = sscanf(n, "list.%zu", &idx);
        if (r != 1) {
            TraceLog(LOG_WARNING,
                     "Config. sscanf for idx returned %d instead of 1", r);
            goto bad_config_list;
        }

        Vector2 vec;
        r = sscanf(v, "%f,%f", &vec.x, &vec.y);
        if (r != 2) {
            TraceLog(LOG_WARNING,
                     "Config. sscanf for vec returned %d instead of 2", r);
            goto bad_config_list;
        }
        if (lescs_cfg.arr == NULL) {
            TraceLog(LOG_ERROR,
                     "Bad config. You should specify the count before adding "
                     "elements to the escondites list.");
            return false;
        }
        if (idx >= lescs_cfg.cantidad) {
            TraceLog(LOG_ERROR, "Bad config. Impossible index due to item "
                                "count on escondites list.");
            return false;
        }
        lescs_cfg.arr[idx].coords = vec;
        lescs_cfg.arr[idx].distancia_de_escondite = standing_distance_cfg;
        return true;
    bad_config_list:
        TraceLog(LOG_ERROR, "Bad config on %s/%s = %s", s, n, v);
        return false;
    }
    return false;
}

int handler_func_escapes(const char *n, const char *v) {
    const char *s = "escapes";
    if (str_eq(n, "count")) {
        int cnt;
        if (!str2int_or_log_err(s, n, v, &cnt)) {
            return false;
        }
        FreeListaEscapes(&lexits_cfg);
        lexits_cfg = NewListaEscapes(cnt);
    }
#define PREFIX_LENGTH 6
    // 6 is the size of the string "list."
    //
    char prefix[PREFIX_LENGTH];
    strncpy(prefix, n, PREFIX_LENGTH)[PREFIX_LENGTH - 1] = '\0';
    if (str_eq(prefix, "list.")) {
        size_t idx;
        int r = sscanf(n, "list.%zu", &idx);
        if (r != 1) {
            goto bad_config_list;
        }

        float coord;
        r = sscanf(v, "%f", &coord);
        if (r != 1) {
            goto bad_config_list;
        }
        if (lexits_cfg.arr == NULL) {
            TraceLog(LOG_ERROR,
                     "Bad config. You should specify the count before adding "
                     "elements to the escapes list.");
            return false;
        }
        if (idx >= lexits_cfg.n) {
            TraceLog(LOG_ERROR, "Bad config. Impossible index due to item "
                                "count on escapes list.");
            return false;
        }
        lexits_cfg.arr[idx].x = coord;
        return true;
    bad_config_list:
        TraceLog(LOG_ERROR, "Bad config on %s/%s = %s", s, n, v);
        return false;
    }
    return false;
}

int handler_func_tigre(const char *n, const char *v) {
    const char *s = "tigre";
    if (lenems_cfg.arr == NULL) {
        TraceLog(
            LOG_ERROR,
            "Bad config. [enemigos] section should be present before [tigre].");
        return false;
    }
    if (str_eq(n, "size")) {
        Vector2 size;
        int r = sscanf(v, "%f,%f", &size.x, &size.y);
        if (r != 2) {
            TraceLog(LOG_ERROR, "Bad config. Couldn't parse line %s/%s = %s", s,
                     n, v);
            return false;
        }

        ResetDibujo(&dib_tigre_cfg);
        dib_tigre_cfg = Resources_LoadCenteredDibujo(
            "Resources/Animals/tiger.png", size.x, size.y);
        for (size_t i = 0; i < lenems_cfg.n; i++) {
            Enemigo *e = &lenems_cfg.arr[i];
            e->dib = &dib_tigre_cfg;
        }
        return true;
    }
    if (str_eq(n, "collisionBox")) {
        CollisionBox cb;
        int r = sscanf(v, "%f,%f,%f,%f", &cb.left, &cb.up, &cb.right, &cb.down);
        if (r != 4) {
            TraceLog(LOG_ERROR,
                     "Bad config. collisionBox property on section tiger "
                     "expects the format '<left>,<up>,<right>,<down>'.");
            return false;
        }

        for (size_t i = 0; i < lenems_cfg.n; i++) {
            lenems_cfg.arr[i].colisiones = cb;
        }
        return true;
    }
    if (str_eq(n, "speed")) {
        int n, m;
        int r = sscanf(v, "%d-%d", &n, &m);
        if (r != 2) {
            TraceLog(LOG_ERROR,
                     "Bad config. %s/%s = %s expected a range of velocities. "
                     "As in <min>-<max>.",
                     s, n, v);
            return false;
        }
        for (size_t i = 0; i < lenems_cfg.n; i++) {
            lenems_cfg.arr[i].min_velocidad = n;
            lenems_cfg.arr[i].max_velocidad = m;
        }
        return true;
    }
    return false;
}

int handler_func(void *_, const char *s, const char *n, const char *v) {
    TraceLog(LOG_INFO, "Processing %s/%s = %s", s, n, v);
    if (str_eq(s, "enemigos"))
        return handler_func_enemigos(n, v);
    if (str_eq(s, "escondites"))
        return handler_func_escondites(n, v);
    if (str_eq(s, "escapes"))
        return handler_func_escapes(n, v);
    if (str_eq(s, "tigre"))
        return handler_func_tigre(n, v);
    return true;
}

ListaEnemigos *GetListaEnemigos() { return &lenems_cfg; }
ListaEscondites *GetListaEscondites() { return &lescs_cfg; }
ListaEscapes *GetListaEscapes() { return &lexits_cfg; }
int *GetCollisionMargin() { return &collision_margin_cfg; }

bool InitShooterConfig(FILE *ini) {
    TraceLog(LOG_INFO, "Reading configuration...");
    handler = handler_func;
    return ini_parse_file(ini, handler, NULL);
}
