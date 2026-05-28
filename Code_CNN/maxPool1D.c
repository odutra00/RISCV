#include <stdio.h>
#include "maxPool1D.h"

void max_pool1D(const float* input, float* output, int channels, int pool_size, int output_time) {

    for (int t = 0; t < output_time; t++) {
        for (int c = 0; c < channels; c++) {
            float max_val = input[(t * pool_size) * channels + c];
            for (int i = 1; i < pool_size; i++) {
                float val = input[(t * pool_size + i) * channels + c];
                if (val > max_val) {
                    max_val = val;
                }
            }
            output[t * channels + c] = max_val;
        }
    }
}

void save_pool_output_to_file(const char* filename, const float* output, int output_size) {
    for (int i = 0; i < output_size; i++) {
        printf("%.6f\n", output[i]);
    }
}


