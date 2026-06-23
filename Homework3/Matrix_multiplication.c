#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Error: Missing arguments.\n");
        printf("Usage: %s <a> <b> <N> <fileout>\n", argv[0]);
        return 1;
    }

    float a = atof(argv[1]); 
    float b = atof(argv[2]);  
    int N = atoi(argv[3]);    
    char *fileout = argv[4];  


    // Prepare Matrix
    float A[N][N], B[N][N], C[N][N];

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=(i==j)?a:0.0f;
            B[i][j]=(i==j)?b:0.0f;
        }
    }



    //Prepare Timing:
    struct timespec start,end;

    //Naive Multiply
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j]=0.0f; 
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_naive = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    //Cache Optimized Multiply
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i=0; i<N; i++)
    {
        for(int j=0;j<N;j++)
        {
            C[i][j]=0.0f;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) { 
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_optimized = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;


    printf("Naive time: %f  Optimized time: %f \n",time_naive,time_optimized);





    // check C Naive (only diagonal elements?):
    clock_gettime(CLOCK_MONOTONIC, &start);
    int success=0;
    for(int i=0;i<N;i++)
    {
        if(C[i][i]!=a*b){
            success=1;
            printf("Test failed\n");
            break; // exit loop early if a mismatch is found    
        }
        
    }
    if(success==0){
    	printf("Test succeded\n");
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_check1 = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // check C optimized:
    clock_gettime(CLOCK_MONOTONIC, &start);
    int sum=N*a*b;
    for(int i=0;i<N;i++)
    {
        sum-=C[i][i];
    }
    if(sum==0)
    	printf("Test succeded\n");
    else
        printf("Test failed\n");

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_check2 = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Naive check: %f  Optimized check: %f \n",time_check1,time_check2);




    // save matrix C to a fileout
    FILE *f = fopen(fileout, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(f, "%f ", C[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    return 0;

}


