#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void legendre_forward(double x, int lmax, double *P)
{
    P[0] = 1.0;
    if (lmax == 0) {
        return;
    }

    P[1] = x;
    for (int l = 1; l < lmax; ++l) {
        P[l + 1] = ((2.0 * l + 1.0) * x * P[l]
                    - (double)l * P[l - 1]) / (double)(l + 1);
    }
}

void legendre_reference(double x, int lmax, double *Pref)
{
    long double xl = (long double)x;
    long double *P = malloc((size_t)(lmax + 1) * sizeof(*P));
    if (P == NULL) {
        fprintf(stderr, "allocation failed in legendre_reference\n");
        exit(EXIT_FAILURE);
    }

    P[0] = 1.0L;
    if (lmax >= 1) {
        P[1] = xl;
    }

    for (int l = 1; l < lmax; ++l) {
        P[l + 1] = (((long double)(2 * l + 1)) * xl * P[l]
                    - (long double)l * P[l - 1]) / (long double)(l + 1);
    }

    for (int l = 0; l <= lmax; ++l) {
        Pref[l] = (double)P[l];
    }

    free(P);
}

void legendre_backward_experiment(double x, int lmax, int L, double *P)
{
    if (L <= lmax) {
        fprintf(stderr, "need L > lmax in legendre_backward_experiment\n");
        exit(EXIT_FAILURE);
    }

    double *Q = calloc((size_t)(L + 2), sizeof(*Q));
    if (Q == NULL) {
        fprintf(stderr, "allocation failed in legendre_backward_experiment\n");
        exit(EXIT_FAILURE);
    }

    Q[L + 1] = 0.0;
    Q[L] = 1.0;

    for (int l = L; l >= 1; --l) {
        Q[l - 1] = ((2.0 * l + 1.0) * x * Q[l]
                    - (double)(l + 1) * Q[l + 1]) / (double)l;
    }

    double scale = 1.0 / Q[0];
    for (int l = 0; l <= lmax; ++l) {
        P[l] = scale * Q[l];
    }

    free(Q);
}

static double relative_error(double value, double reference)
{
    double abs_err = fabs(value - reference);
    if (fabs(reference) > DBL_MIN) {
        return abs_err / fabs(reference);
    }
    return abs_err;
}

int main(void)
{
    const int lmax = 50;
    const int L = 80;
    const double xs[] = {0.1, 0.5, 0.9, 0.99};
    const int nx = (int)(sizeof(xs) / sizeof(xs[0]));

    double Pf[51];
    double Pb[51];
    double Pref[51];

    printf("x,l,err_fwd_rel,err_bwd_rel,err_fwd_abs,err_bwd_abs\n");

    for (int ix = 0; ix < nx; ++ix) {
        double x = xs[ix];

        legendre_reference(x, lmax, Pref);
        legendre_forward(x, lmax, Pf);
        legendre_backward_experiment(x, lmax, L, Pb);

        for (int l = 0; l <= lmax; ++l) {
            double abs_err_f = fabs(Pf[l] - Pref[l]);
            double abs_err_b = fabs(Pb[l] - Pref[l]);
            double rel_err_f = relative_error(Pf[l], Pref[l]);
            double rel_err_b = relative_error(Pb[l], Pref[l]);

            printf("%.2f,%d,%.15e,%.15e,%.15e,%.15e\n", x, l, rel_err_f, rel_err_b, abs_err_f, abs_err_b);

        }

        printf("\n");
    }

    return 0;
}