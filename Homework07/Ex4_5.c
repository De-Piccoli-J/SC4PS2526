#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
    const int n = 50000;
    const double lambda = 1.5;
    double *y = malloc((size_t)n * sizeof(double));
    double *cdf = malloc((size_t)n * sizeof(double));
    FILE *f = fopen("Ex4_5.csv", "w");
    fprintf(f, "y,CDF_x,CDF_y\n");
    
    for (int i = 0; i < n; ++i) {
        double u = lcg32_next_double(&state);
        y[i] = -1*log(1.0 - u) / lambda;
        cdf[i] = y[i];
    }
    // Bubblesort (slow, for larger n need to use qsort or other sorting algorithms)
    for (int i = 0; i < n; ++i) {
        for(int j = 0; j < n - 1 - i; ++j) {
            if (cdf[j] > cdf[j + 1]) {
                double temp = cdf[j];
                cdf[j] = cdf[j + 1];
                cdf[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        fprintf(f, "%lf,%lf,%lf\n", y[i], cdf[i], (double)(i + 1) / n);
    }
    fclose(f);
    free(y);
    free(cdf);
    return 0;
}