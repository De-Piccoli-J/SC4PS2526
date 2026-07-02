#include <stdint.h>
#include <stdio.h>

/*
 * Common LGC
 */
static inline uint32_t lcg32_next(uint32_t *state) {
    const uint32_t a = 1664525u;
    const uint32_t c = 1013904223u;
    *state = a * (*state) + c;
    return *state;
}

static inline double lcg32_next_double(uint32_t *state) {
    return lcg32_next(state) / 4294967296.0;
}

int main() {
    uint32_t state = 987654321u;
    const int n = 1000000;
    FILE *f = fopen("Ex3.csv", "w");
    fprintf(f, "y\n");

    for (int i = 0; i < n; ++i) {
        double u = lcg32_next_double(&state);
        double y = u * u;
        fprintf(f, "%.12f\n", y);
    }

    fclose(f);
    return 0;
}