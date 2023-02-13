//
// Created by bohm on 13/02/23.
//

#ifndef ESP_NN_TEST_FULLY_CONNECTED_TEST_H
#define ESP_NN_TEST_FULLY_CONNECTED_TEST_H

void esp_nn_fully_connected_s8_test()
{
  static uint16_t row_len = 3;
  static uint16_t out_channels = 4;
  int8_t input[3]{1, 2, 3};
  // this is the weights vector squashed to a single dimension and transposed (compared to ONNX weights)
  int8_t filter_data[3 * 4]{
          1, 2, 3,
          4, 5, 6,
          7, 8, 9,
          10, 11, 12
  };
  int8_t output_c[out_channels], output_opt[out_channels];
  static int32_t activation_min = -128;
  static int32_t activation_max = 127;
  static int32_t input_offset = 0;
  static int32_t filter_offset = 0;
  int32_t out_shift = 0;
  static int32_t out_offset = 0;
  int32_t out_mult = INT32_MAX;

  /* C function */
  esp_nn_fully_connected_s8_ansi(input, input_offset, row_len, filter_data, filter_offset,
                                 NULL, output_c, out_channels, out_offset, out_shift, out_mult,
                                 activation_min, activation_max);
  printf("Fully connected Results: %d, %d, %d, %d\n", output_c[0], output_c[1], output_c[2], output_c[3]);

  /* Optimized function */
  esp_nn_fully_connected_s8(input, input_offset, row_len, filter_data, filter_offset,
                            NULL, output_opt, out_channels, out_offset, out_shift, out_mult,
                            activation_min, activation_max);
  printf("Fully connected Opt Results: %d, %d, %d, %d\n", output_opt[0], output_opt[1], output_opt[2], output_opt[3]);

  printf(ANSI_COLOR_GREEN "%s[%d] passed\n" ANSI_COLOR_RESET, __FUNCTION__, 0);
}


#endif //ESP_NN_TEST_FULLY_CONNECTED_TEST_H
