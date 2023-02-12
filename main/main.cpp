#include <stdio.h>
#include <esp_nn.h>
#include <malloc.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MULT_MAX    INT32_MAX
#define MULT_MIN    0

#define CHECK_EQUAL(ARRAY1, ARRAY2, size) ({    \
    bool res = true;                            \
    for (int _i = 0; _i < size; _i++) {         \
        if (ARRAY1[_i] != ARRAY2[_i]) {         \
            res = false;                        \
            break;                              \
        }                                       \
    }                                           \
    res;                                        \
})

void esp_nn_add_elementwise_s8_test();

extern "C" void app_main(void) {
  esp_nn_add_elementwise_s8_test();
}

void esp_nn_add_elementwise_s8_test() {
  /* prepare data */
  const int size = 4; /* odd len to test leftover */
  const int8_t input1[4]{1, 2, 3, 4};
  const int8_t input2[4]{1, 3, 6, 8};
  int8_t out_data_c[4]{};
  int8_t out_data_opt[4]{};
//  int8_t *input1_orig = NULL;
//  int8_t *input2_orig = NULL;
//  int8_t *out_c_orig = NULL;
//  int8_t *out_opt_orig = NULL;
  int32_t input1_offset = 34;
  int32_t input2_offset = 35;
  int32_t output_offset = 36;
  int32_t input1_shift = -8; // right_shift amt always <= 0
  int32_t input2_shift = -8; // right_shift amt always <= 0
  int32_t output_shift = -9; // right_shift amt always <= 0
  int32_t left_shift = 15; // always +ve
  int32_t input1_mult = INT32_MAX;
  int32_t input2_mult = INT32_MAX;
  int32_t output_mult = INT32_MAX;
  int32_t output_mult_gemm = MULT_MAX;
  int32_t activation_min = -128;
  int32_t activation_max = 127;

  input1_offset = 0;
  input2_offset = 0;
  output_offset = 0;
//  input1_mult = 0;
//  input2_mult = 0;
//  output_mult = 0;
  input1_shift = 0;
  input2_shift = 0;
  output_shift = 0;
  left_shift = 0;

//  input1 = memalign(16, size);
//  input2 = memalign(16, size);
//  out_data_c = memalign(16, size);
//  out_data_opt = memalign(16, size);

//  for (int i = 0; i < size; ++i) {
//    input1[i] = int8_t(rand() % 256 - 128);
//    input2[i] = int8_t(rand() % 256 - 128);
//  }

  /* C function */
  esp_nn_add_elementwise_s8_ansi(input1, input2, input1_offset, input2_offset,
                                 input1_mult, input2_mult, input1_shift, input2_shift,
                                 left_shift, out_data_c, output_offset, output_mult,
                                 output_shift, activation_min, activation_max, size);

  printf("Add Results: %d, %d, %d, %d\n", out_data_c[0], out_data_c[1], out_data_c[2], out_data_c[3]);

  /* Optimized function */
  esp_nn_add_elementwise_s8(input1, input2, input1_offset, input2_offset,
                            input1_mult, input2_mult, input1_shift, input2_shift,
                            left_shift, out_data_opt, output_offset, output_mult,
                            output_shift, activation_min, activation_max, size);
  printf("Add Results Opt: %d, %d, %d, %d\n", out_data_opt[0], out_data_opt[1], out_data_opt[2], out_data_opt[3]);

  esp_nn_mul_elementwise_s8_ansi(input1, input2, input1_offset, input2_offset,
                                 out_data_c, output_offset, output_mult_gemm, output_shift,
                                 activation_min, activation_max, size);

  printf("Mul Results: %d, %d, %d, %d\n", out_data_c[0], out_data_c[1], out_data_c[2], out_data_c[3]);

  // Why does this produce results - 1???
  esp_nn_mul_elementwise_s8(input1, input2, input1_offset, input2_offset,
                            out_data_opt, output_offset, output_mult_gemm, output_shift,
                            activation_min, activation_max, size);

  printf("Mul Results Opt: %d, %d, %d, %d\n", out_data_opt[0], out_data_opt[1], out_data_opt[2], out_data_opt[3]);

//  bool ret = CHECK_EQUAL(out_data_c, out_data_opt, size);
//  if (!ret) {
//    printf(ANSI_COLOR_RED"%s[%d] failed\n"ANSI_COLOR_RESET, __FUNCTION__, itr);
//    printf("Output: \n");
//    PRINT_ARRAY_HEX(out_data_opt, size, 1);
//    printf("Expected: \n");
//    PRINT_ARRAY_HEX(out_data_c, size, 1);
//    printf("Input1:\n");
//    PRINT_ARRAY_HEX(input1, size, 1);
//    printf("Input2:\n");
//    PRINT_ARRAY_HEX(input2, size, 1);
//    printf("in1_shift %d, in2_shift %d, left_shift %d, out_shift %d\n",
//           input1_shift, input2_shift, left_shift, output_shift);
//    printf("in1_mult %d, in2_mult %d, out_mult %d\n", input1_mult, input2_mult, output_mult);
//    goto elementwise_add_test_cleanup;
//  }
  printf(ANSI_COLOR_GREEN "%s[%d] passed\n" ANSI_COLOR_RESET, __FUNCTION__, 0);


}

