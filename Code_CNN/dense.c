#include <math.h>
#include <stdio.h>
#include "dense.h"

#define RELU 1 // must be equal to the one defined in main.c
#define SIGMOID 2

static float activate(float x, int type) {
    if (type == RELU)
        return x > 0 ? x : 0;
    else if (type == SIGMOID)
        return 1.0f / (1.0f + expf(-x)); //maybe we don't have math.h
    else
        return x;  // No activation fallback
}

void dense_forward(const float* input, float* output, int input_size, int output_size, const float* weights, const float* biases, int activation_type) {
    for (int i = 0; i < output_size; i++) {
        float sum = biases[i];
        for (int j = 0; j < input_size; j++) {
            sum += input[j] * weights[j * output_size + i];
        }
        output[i] = activate(sum, activation_type);
    }
}

void save_dense_output_to_file(const char* filename, const float* output, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.6f\n", output[i]);
    }
}





