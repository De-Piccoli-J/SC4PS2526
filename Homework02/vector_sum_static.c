#include <stdio.h>

int main() {
    int n;
    float a,x_value,y_value,d_value;
    // ask for the parameters

    printf("Enter the number of elements in the vectors: ");
    scanf("%d", &n);

    printf("Enter the value of the elements of x: ");
    scanf("%f", &x_value);
    printf("Enter the value of the elements of y: ");
    scanf("%f", &y_value);

    printf("Enter the value of the scalar a: ");
    scanf("%f", &a);

    printf("Enter the expected value of the sum: ");
    scanf("%f", &d_value);

    // Create the vectors and initialize them with the input values
    float x[n], y[n], d[n];
    for (int i = 0; i < n; i++) {
        x[i] = x_value;
        y[i] = y_value;
    }

    // Perform the vector sum

    for (int i = 0; i < n; i++) {
        d[i] = a * x[i] + y[i];
    }

    // test the result against the expected value
    int success = 1; // flag to indicate success
    for (int i = 0; i < n; i++) {
        if (d[i] != d_value) {
            success = 0; // set flag to 0 if any element does not match
            printf("Test failed at index %d: expected %f but got %f\n", i, d_value, d[i]);
            break; // exit loop early if a mismatch is found    
        }
    }

    return 0;
}