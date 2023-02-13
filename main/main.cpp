#include <stdio.h>
#include <esp_nn.h>

#include "shared.h"

#include "basic_math_test.h"

extern "C" void app_main(void) {
  esp_nn_add_elementwise_s8_test();
}

