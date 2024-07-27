#include <windows.h>


#include <stdio.h>
#include <stdlib.h>

#include <nvdaController.h>

int main(void) {
    error_status_t res = nvdaController_testIfRunning();
    if (res == 0) {
        puts("NVDA is running");
    } else {
        puts("NVDA is not running");
    }
    return EXIT_SUCCESS;
}
