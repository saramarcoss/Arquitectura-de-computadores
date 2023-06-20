#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <assert.h> 
#include <cuda.h> 
#include <cuda_runtime.h> 
#define N 10000000 // tamaño del vector
#define MAX_ERR 1e-6

global void vector_add(float *out, float *a, float *b, int n) { // realiza la suma de vectores en el dispositivo con el kernel vector_add 
int index = threadIdx.x; int stride = blockDim.x;
for(int i = index; i < n; i += stride){ 
    out[i] = a[i] + b[i];
    }
}

int main(){
float *a, *b, *out; // declaracion de punteros para los vectores a, b y out en el host
float *d_a, *d_b, *d_out; // declaracion de punteros para los vectores a, b y out en el dispositivo

// Allocate host memory
a = (float*)malloc(sizeof(float) * N); // reserva memoria en el host para el vector a. 
b = (float*)malloc(sizeof(float) * N); // reserva memoria en el host para el vector b
out = (float*)malloc(sizeof(float) * N); // reserva memoria en el host para el vector out

// Initialize host arrays
for(int i = 0; i < N; i++){
     a[i] = 1.0f; 
     b[i] = 2.0f; 
}

// Allocate device memory 
cudaMalloc((void**)&d_a, sizeof(float) * N);  // reserva memoria en el dispositivo para el vector a. cuda
cudaMalloc((void**)&d_b, sizeof(float) * N);  // reserva memoria en el dispositivo para el vector b
cudaMalloc((void**)&d_out, sizeof(float) * N); // reserva memoria en el dispositivo para el vector out

// Transfer data from host to device memory
cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);  // copia el vector a al dispositivo. cudaMemcpyHostToDevice: copia de host a dispositivo
cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice); // copia el vector b al dispositivo


blockDim.x = 256;// con blockDim.x = 256, se ejecutará el kernel vector_add con 256 hilos por bloque
gridDim.x = (2*N + blockDim.x - 1) / blockDim.x; 

// Executing kernel 
vector_add<<< gridDim.x, blockDim.x >>>(d_out, d_a, d_b, N); // ejecuta el kernel vector_add en el dispositivo con el número de bloques y el número de hilos por bloque

// Transfer data back to host memory 
cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost); // copia el vector out del dispositivo al host  cudaMemcpyDeviceToHost: copia de dispositivo a host

// Verification
for(int i = 0; i < N; i++){ // comprueba que el resultado es correcto 
assert(fabs(out[i] - a[i] - b[i]) < MAX_ERR); // fabs: devuelve el valor absoluto de un número. assert: comprueba que la condición es verdadera. Si no lo es, se produce un error y se muestra un mensaje de error
} // out - a - b = 0
printf("PASSED\n");

// Deallocate device memory 
cudaFree(d_a);  // libera la memoria del vector a en el dispositivo
cudaFree(d_b);  // libera la memoria del vector b en el dispositivo
cudaFree(d_out); // libera la memoria del vector out en el dispositivo

// Deallocate host memory 
free(a); // libera la memoria del vector a en el host
free(b);  // libera la memoria del vector b en el host
free(out); // libera la memoria del vector out en el host
}