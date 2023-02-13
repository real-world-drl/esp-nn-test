#include <stdio.h>
#include <esp_nn.h>

#include "shared.h"

#include "basic_math_test.h"
#include "fully_connected_test.h"

extern "C" void app_main(void) {
  esp_nn_add_elementwise_s8_test();
  esp_nn_fully_connected_s8_test();
}

