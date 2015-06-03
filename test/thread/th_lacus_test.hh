#ifndef ARGCV_TEST_THREAD_TH_LACUS_TEST_HH
#define ARGCV_TEST_THREAD_TH_LACUS_TEST_HH
#include "test/argcv_test.h"

#include "argcv/thread/th_lacus.hh"

using namespace argcv::thread;

void test_case_th_lacus_data_printer(int* v) {
    printf("[start] : %d \n", *v);
    // usleep(1000000);
    printf("[ end ] : %d \n", *v);
}

static int test_case_th_lacus(int argc, char* argv[]) {
    thread_lacus<int> thlacus(test_case_th_lacus_data_printer,3,100,300000);
    int vals[10];
    for (int v = 0; v < 10; v++) {
        vals[v] = v;
        thlacus.enqueue(&vals[v]);
    }
    thlacus.join();
    return 0;
}

#endif  // ARGCV_TEST_THREAD_TH_LACUS_TEST_HH