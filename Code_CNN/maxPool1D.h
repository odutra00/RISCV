#ifndef MAXPOOL1D_H
#define MAXPOOL1D_H

void max_pool1D(const float* input,   // input array: shape (input_time * channels)
                float* output,        // output array: shape (output_time * channels)
                int channels,
                int pool_size,
                int output_time);

void save_pool_output_to_file(const char* filename, const float* output, int output_size);

#endif
