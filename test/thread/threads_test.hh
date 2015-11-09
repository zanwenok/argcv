/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Yu Jing <yu@argcv.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/
#ifndef ARGCV_TEST_THREAD_TH_LACUS_TEST_HH
#define ARGCV_TEST_THREAD_TH_LACUS_TEST_HH
#include "test/argcv_test.h"

#include "argcv/thread/threads.hh"

using namespace argcv::thread;

void test_case_th_lacus_data_printer(int* v) {
    printf("[start] : %d \n", *v);
    // usleep(1000000);
    printf("[ end ] : %d \n", *v);
}

static int test_case_threads(int argc, char* argv[]) {
    threads<int> thlacus(test_case_th_lacus_data_printer, 3, 100, 300000);
    int vals[10];
    for (int v = 0; v < 10; v++) {
        vals[v] = v;
        thlacus.enqueue(&vals[v]);
    }
    thlacus.join();
    return 0;
}

#endif  // ARGCV_TEST_THREAD_TH_LACUS_TEST_HH