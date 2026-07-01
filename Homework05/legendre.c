#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Method 1: Direct forward recurrence
void compute_forward(double x, int l_max, double *p) {
    p[0] = 1.0;
    if (l_max >= 1) p[1] = x;

    for (int l = 1; l < l_max; l++) {
        p[l + 1] = ((2.0 * l + 1.0) / (l + 1.0)) * x * p[l] -
                    ((double)(l) / (double)(l + 1.0)) * p[l - 1];
    }
}

// Method 2: High-precision "reference" computation
void compute_reference(double x, int lmax, double *p) {
    long double xl = (long double)x;
    long double *pl = malloc((size_t)(lmax + 1) * sizeof(*pl));

    pl[0] = 1.0L;
    if (lmax >= 1) pl[1] = xl;
    for (int l = 1; l < lmax; ++l) {
        // FIXED: Added missing division by (l + 1.0) on the first term
        pl[l + 1] = (((long double)(2.0 * l + 1.0) / (long double)(l + 1.0)) * xl * pl[l] -
                      ((long double)(l) / (long double)(l + 1.0)) * pl[l - 1]);
    }
    for (int l = 0; l <= lmax; ++l) {
        p[l] = (double)pl[l];
    }
    free(pl);
}



// Method 3: Backward recurrence (Miller)
void compute_backward(double x, int l_max, int l_miller, double *p) {
    p[l_miller + 1] = 0.0;
    p[l_miller] = 1.0;

    for (int l = l_miller; l > 0; l--) {
        p[l - 1] = ((2.0 * l + 1.0) / l) * x * p[l] - ((double)(l + 1.0) / l) * p[l + 1];
    }
    // Rescale using P_0(x) = 1
    double c = 1.0 / p[0];
    for (int l = 0; l <= l_max; l++) {
        p[l] = p[l] * c;
    }

}



int main() {
    const int L_MAX = 50;
    const int L_MILLER = 80;
    double x_vals[] = {0.1, 0.5, 0.9, 0.99};
    int num_x = sizeof(x_vals) / sizeof(x_vals[0]);

    // Print CSV header
    FILE *f = fopen("legendre_errors.csv", "w");
    fprintf(f, "x,l,err_fwd_rel,err_bwd_rel,err_fwd_abs,err_bwd_abs\n");

    for (int i = 0; i < num_x; i++) {
        double x = x_vals[i];

        double ref[L_MAX + 1];
        double forw[L_MAX + 1];
        double bkwd[L_MILLER + 1];

        // Compute using all three methods
        compute_reference(x, L_MAX, ref);
        compute_forward(x, L_MAX, forw);
        compute_backward(x, L_MAX, L_MILLER, bkwd);

        // Calculate errors and print
        for (int l = 0; l <= L_MAX; l++) {
            double ref_val = (double)ref[l];

            // Add tiny epsilon to denominator to prevent division by zero at roots
            double denom = fabs(ref_val) > 1e-100 ? fabs(ref_val) : 1e-100;
            double err_fwd_abs = fabs(forw[l] - ref_val);
            double err_bwd_abs = fabs(bkwd[l] - ref_val);
            double err_fwd_rel = err_fwd_abs / denom;
            double err_bwd_rel = err_bwd_abs / denom;

            // Output row for CSV
            fprintf(f, "%.2f,%d,%.15e,%.15e,%.15e,%.15e\n", x, l, err_fwd_rel, err_bwd_rel, err_fwd_abs, err_bwd_abs);
        }
    }
    fclose(f);
    return 0;
}