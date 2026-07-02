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

static double estimate_pi(int n, uint32_t seed_x, uint32_t seed_y) {

    int hit = 0;

    for (int i = 0; i < n; ++i) {
        double x = lcg32_next_double(&seed_x);
        double y = lcg32_next_double(&seed_y);

        if (x * x + y * y <= 1.0) {
            hit++;
        }
    }

    return 4.0 * hit / n;
}

int main(void) {
    int samples[] = {100, 1000, 10000, 100000, 1000000, 1000000, 10000000, 100000000};
    int n_samp = (int)(sizeof(samples) / sizeof(samples[0]));
    FILE *f = fopen("Ex2.csv", "w");
    fprintf(f, "n,pi_estimate\n");
    for (int i = 0; i < n_samp; ++i) {
        double pi_est = estimate_pi(samples[i], 13579u, 24680u);
        printf("%d %.10f\n", samples[i], pi_est);
        fprintf(f, "%d,%.10f\n", samples[i], pi_est);
    }
    fclose(f);

    return 0;
}