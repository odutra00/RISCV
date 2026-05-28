#ifndef DENSE_H
#define DENSE_H

void dense_forward(const float* input, float* output, int input_size, int output_size, const float* weights, const float* biases, int activation_type);

void save_dense_output_to_file(const char* filename, const float* output, int size);

#endif
