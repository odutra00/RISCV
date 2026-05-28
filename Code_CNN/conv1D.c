#include <stdio.h>

void conv1D(const float* input,       // input array: shape (input_time * in_channels)
            const float* weights,     // weights: shape (kernel_size * in_channels * out_channels)
            const float* biases,      // biases: shape (out_channels)
            float* output,            // output array: shape (output_time * out_channels)
            int input_time,
            int in_channels,
            int out_channels,
            int kernel_size)
{
    int output_time = input_time - kernel_size + 1;

    for (int t = 0; t < output_time; t++) { //iterate through input timesteps
        for (int f = 0; f < out_channels; f++) { //iterate through filters
            float sum = biases[f];
            for (int k = 0; k < kernel_size; k++) { //iterate through filter timesteps
                for (int c = 0; c < in_channels; c++) { //iterate through features
                    float x = input[(t + k) * in_channels + c];
                    float w = weights[k * in_channels * out_channels + c * out_channels + f];
                    sum += x * w;
                }
            }
            // ReLU activation
            output[t * out_channels + f] = (sum > 0) ? sum : 0;
        }
    }
}


void save_output_to_file(const char* filename, const float* output, int output_size) {
    for (int i = 0; i < output_size; i++) {
        printf("%.6f\n", output[i]);
    }   
}

