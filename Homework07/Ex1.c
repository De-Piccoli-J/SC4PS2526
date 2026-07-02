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
    uint32_t seed = 123456789u;
    const int N = 100000;
    int heads = 0;

    FILE *f = fopen("Ex1.csv", "w");
    fprintf(f, "n,heads\n");
    for (int i = 1; i < N; i++) {
        double u = lcg32_next_double(&seed);
    
        heads += (int)((u < 0.5) ? 1 : 0);

        fprintf(f, "%d,%d\n", i, heads);
        printf("n toss:%d n heads:%d fraction:%.10f\n", i, heads, (double)heads / i);
    }

    fprintf(stderr, "Final fraction of heads = %.10f\n", (double)heads / N);
    fclose(f);
    return 0;
}