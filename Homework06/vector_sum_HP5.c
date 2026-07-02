#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <hdf5.h>


void parse_config(const char *filename, int *n, int *chunk_size, double *a, double *x, double *y) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error: Could not open config file");
        exit(EXIT_FAILURE);
    }
    
    char var[64];
    char eq;
    double val;
    
    // Reads format: Variable = Value
    while (fscanf(file, "%63s %c %lf", var, &eq, &val) == 3) {
        if (strcmp(var, "n") == 0 || strcmp(var, "N") == 0) {
            *n = (int)val;
        } else if (strcmp(var, "chunk_size") == 0 || strcmp(var, "CHUNK_SIZE") == 0) {
            *chunk_size = (int)val;
        } else if (strcmp(var, "a") == 0 || strcmp(var, "A") == 0) {
            *a = val;
        }
         else if (strcmp(var, "x") == 0 || strcmp(var, "X") == 0) {
            *x = val;
        } else if (strcmp(var, "y") == 0 || strcmp(var, "Y") == 0) {
            *y = val;
        }
    }
    fclose(file);
}

int main() {
    int n = 0, chunk_size = 0;
    double a = 0.0, x_val = 0.0, y_val = 0.0;

    // Load inputs
    parse_config("config.txt", &n, &chunk_size, &a, &x_val, &y_val);
    printf("Loaded Config -> n: %d, chunk_size: %d, a: %.2f, x_val: %.2f, y_val: %.2f\n", n, chunk_size, a, x_val, y_val);

    if (n <= 0 || chunk_size <= 0) {
        fprintf(stderr, "Error: Invalid vector size or chunk size.\n");
        return 1;
    }

    // Allocate memory for vectors
    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));
    double *d = (double *)malloc(n * sizeof(double));
    double *d_orig = (double *)malloc(n * sizeof(double)); // For validation

    // Initialize vectors x and y
    for (int i = 0; i < n; i++) {
        x[i] = i * 1.0;
        y[i] = i * 2.0;
    }

    // Chunked Vector Sum

    
    // Calculate the number of chunks
    int n_chunks = (n + chunk_size - 1) / chunk_size; // This ensures we round up to account for any remaining elements in the last chunk
    double *partial_chunk_sum = (double *)malloc(n_chunks * sizeof(double));

    // Iterates through chunks
    for (int chunk_idx = 0; chunk_idx < n_chunks; chunk_idx++) {
        // Calculate start and end indices for C (0-based indexing)
        int current_start = chunk_idx * chunk_size;
        int current_end = current_start + chunk_size;
        
        // Adjust for the last chunk
        if (current_end > n) {
            current_end = n;
        }

        double current_chunk_sum = 0.0;

        // Inner loop: actual logic
        for (int i = current_start; i < current_end; i++) {
            d[i] = a * x[i] + y[i];
            current_chunk_sum += d[i]; 
        }
        
        // Save the sum for this chunk
        partial_chunk_sum[chunk_idx] = current_chunk_sum;
    }
    double total_partial_sum = 0.0;
    for (int i = 0; i < n_chunks; i++) {
        total_partial_sum += partial_chunk_sum[i];
    }

    // Validation

    // Calculate baseline for comparison
    double total_sum_d_orig = 0.0;
    for (int i = 0; i < n; i++) {
        d_orig[i] = a * x[i] + y[i];
        total_sum_d_orig += d_orig[i];
    }

    // Element by element
    int vectors_match = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(d[i] - d_orig[i]) > 1e-9) {
            vectors_match = 1;
            break;
        }
    }
    if (vectors_match == 0) {
        printf("Element by element comparison: PASSED\n");
    } else {
        printf("Element by element comparison: FAILED\n");
    }

    // Sum of partial chunks
    
    if (fabs(total_sum_d_orig - total_partial_sum) < 1e-9) {
        printf("Sum of partial chunks equals total sum: PASSED\n");
    } else {
        printf("Sum of partial chunks equals total sum: FAILED\n");
    }

    // Save results in HDF5

    hid_t file_id, space_d, space_p, dataset_d, dataset_p;
    hsize_t dims_d[1] = {n};
    hsize_t dims_p[1] = {n_chunks};

    file_id = H5Fcreate("results.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    
    // Write full vector 'd'
    space_d = H5Screate_simple(1, dims_d, NULL);
    dataset_d = H5Dcreate(file_id, "d_vector", H5T_NATIVE_DOUBLE, space_d, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dataset_d, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, d);
    
    // Write 'partial_chunk_sum'
    space_p = H5Screate_simple(1, dims_p, NULL);
    dataset_p = H5Dcreate(file_id, "partial_sums", H5T_NATIVE_DOUBLE, space_p, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dataset_p, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, partial_chunk_sum);
    
    H5Dclose(dataset_d); H5Sclose(space_d);
    H5Dclose(dataset_p); H5Sclose(space_p);
    H5Fclose(file_id);
    
    // Clean up memory
    free(x); free(y); free(d); free(d_orig); free(partial_chunk_sum);
    
    return 0;
}