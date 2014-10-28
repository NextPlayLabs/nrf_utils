/*
 * Copyright (c) 2014 Next Play Labs, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include "nrfunit_device.h"

int main(int argc, char **argv) {

    nrfunit_device_init();

    // Tell the user how it works.
    printf("Press Button 0 to run the tests.\n\r\n\r");

    // Main loop runs the tests.
    nrfunit_device_main_loop();

    return 0;
}
