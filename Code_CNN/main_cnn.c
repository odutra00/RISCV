#include "libs/sys/timer/timer.h"
#include "libs/util/delay.h"
#include "libs/sys/gpio/gpio.h"
#include "libs/sys/serial/serial.h"
#include "libs/util/print.h"
#include "libs/lcd/LCD.h"
#include "libs/dht11/dht.h"
#include <stdlib.h>
//#include <stdio.h>

#include "conv1D.h" 
#include "conv1_biases.h"
#include "conv1_weights.h"

#include "maxPool1D.h"

#include "conv2_weights.h"
#include "conv2_biases.h"

#include "dense.h"
#include "dense1_weights.h"
#include "dense1_biases.h"

#include "output_weights.h"
#include "output_biases.h"

#include "input_sample.h"

extern __attribute__((section (".reset"), naked))
void _reset(){
    // setup the stack
    // must needed for both stdlib and newlib versions
    // since newlib assumes that stack has already been setup
    __asm(".option push\n"
          ".option norelax\n"
          "la gp, __global_pointer$\n"
          ".option pop");
    __asm("la sp, __stack_top");
    __asm("add s0, sp, zero");

}


// -------------------------------------------- FIRST CONV LAYER -----------------------------------



#define CONV1_INPUT_TIME 28 //number of timesteps
#define CONV1_IN_CHANNELS 28 //number of features
#define CONV1_KERNEL_SIZE 3 
#define CONV1_OUT_CHANNELS 32 //number of filters
#define CONV1_OUTPUT_TIME (CONV1_INPUT_TIME - CONV1_KERNEL_SIZE + 1)

float conv1D_output[CONV1_OUTPUT_TIME * CONV1_OUT_CHANNELS];

// -------------------------------------------------------------------------------------------------

// -------------------------------------------- FIRST POOLING LAYER -----------------------------------



#define POOL1_CHANNELS CONV1_OUT_CHANNELS //number of filters (or features in this case)
#define POOL1_SIZE 2 // stride
#define POOL1_OUTPUT_TIME (CONV1_OUTPUT_TIME / POOL1_SIZE) // pooling layer timesteps

float pool_output[POOL1_OUTPUT_TIME * POOL1_CHANNELS];

// -------------------------------------------------------------------------------------------------

// -------------------------------------------- SECOND CONV LAYER -----------------------------------



#define CONV2_INPUT_TIME 13
#define CONV2_IN_CHANNELS 32
#define CONV2_KERNEL_SIZE 3
#define CONV2_OUT_CHANNELS 16
#define CONV2_OUTPUT_TIME (CONV2_INPUT_TIME - CONV2_KERNEL_SIZE + 1)

float conv2_output[CONV2_OUTPUT_TIME * CONV2_OUT_CHANNELS];

// -------------------------------------------------------------------------------------------------

// -------------------------------------------- SECOND POOLING LAYER -----------------------------------

#define POOL2_CHANNELS CONV2_OUT_CHANNELS //number of filters (or features in this case)
#define POOL2_SIZE 2 // stride
#define POOL2_OUTPUT_TIME ((CONV2_OUTPUT_TIME) / 2)  // Since CONV2_OUTPUT_TIME is odd, we'll drop the last value, which is what tensorflow does by default

float pool2_output[POOL2_OUTPUT_TIME * POOL2_CHANNELS];

// -------------------------------------------------------------------------------------------------

// ----------------------------- FIRST DENSE LAYER -----------------------------



#define DENSE1_INPUT_SIZE (POOL2_OUTPUT_TIME * POOL2_CHANNELS) 
#define DENSE1_OUTPUT_SIZE 64
#define RELU 1
#define SIGMOID 2
#define DENSE1_ACTIVATION RELU

float dense1_output[DENSE1_OUTPUT_SIZE];

// -------------------------------------------------------------------------------------------------

// ----------------------------- SECOND DENSE LAYER -----------------------------



#define DENSE2_INPUT_SIZE (DENSE1_OUTPUT_SIZE) 
#define DENSE2_OUTPUT_SIZE 1
#define RELU 1
#define SIGMOID 2
#define DENSE2_ACTIVATION SIGMOID

float dense2_output[DENSE2_OUTPUT_SIZE];

// -------------------------------------------------------------------------------------------------

 // input array

// To compile this file, gcc src/main.c src/conv1D.c src/maxPool1D.c src/dense.c -Iheaders/sample0 -Iheaders/layers -o build/main -lm at the root directory

int main() {
	printf("Rodando codigo CNN...\n");
    conv1D(input_sample, conv1_weights, conv1_biases, conv1D_output,
           CONV1_INPUT_TIME, CONV1_IN_CHANNELS, CONV1_OUT_CHANNELS, CONV1_KERNEL_SIZE);

    save_output_to_file("C_outputs/conv1_output.txt", conv1D_output, CONV1_OUTPUT_TIME * CONV1_OUT_CHANNELS);

    max_pool1D(conv1D_output, pool_output, POOL1_CHANNELS, POOL1_SIZE, POOL1_OUTPUT_TIME);

    save_pool_output_to_file("C_outputs/pool1_output.txt", pool_output, POOL1_OUTPUT_TIME * POOL1_CHANNELS);

    conv1D(pool_output, conv2_weights, conv2_biases, conv2_output,
            CONV2_INPUT_TIME, CONV2_IN_CHANNELS, CONV2_OUT_CHANNELS, CONV2_KERNEL_SIZE);

    save_output_to_file("C_outputs/conv2_output.txt", conv2_output, CONV2_OUTPUT_TIME * CONV2_OUT_CHANNELS);

    max_pool1D(conv2_output, pool2_output, POOL2_CHANNELS, POOL2_SIZE, POOL2_OUTPUT_TIME);
        
    save_pool_output_to_file("C_outputs/pool2_output.txt", pool2_output, POOL2_OUTPUT_TIME * POOL2_CHANNELS);

    dense_forward(pool2_output, dense1_output, DENSE1_INPUT_SIZE, DENSE1_OUTPUT_SIZE, dense1_weights, dense1_biases, DENSE1_ACTIVATION);

    save_dense_output_to_file("C_outputs/dense1_output.txt", dense1_output, DENSE1_OUTPUT_SIZE);

    dense_forward(dense1_output, dense2_output, DENSE2_INPUT_SIZE, DENSE2_OUTPUT_SIZE, output_weights, output_biases, DENSE2_ACTIVATION);

    save_dense_output_to_file("C_outputs/output_output.txt", dense2_output, DENSE2_OUTPUT_SIZE);

    return 0;
}


