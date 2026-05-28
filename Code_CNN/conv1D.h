#ifndef CONV1D_H
#define CONV1D_H

// Generic conv1D function declaration
void conv1D(const float* input, const float* weights, const float* biases,
            float* output, 
            int input_time, int in_channels,
            int out_channels, int kernel_size);

void save_output_to_file(const char* filename, const float* output, int out_channels);

#endif
