#include <windows.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include <nvdaController.h>

wchar_t *get_error_message(error_status_t code) {
    wchar_t *message = NULL;
    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            code,
            0,
            (LPWSTR)&message,
            0,
            NULL
            );
    return message;
}

wchar_t *wasprintf(wchar_t *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int size = vswprintf(NULL, 0, fmt, ap);
    va_end(ap);
    wchar_t *str = malloc(sizeof(wchar_t) * (size + 1));
    if (!str) {
        return NULL;
    }
    va_start(ap, fmt);
    vswprintf(str, size, fmt, ap);
    va_end(ap);
    return str;
}

#define NVDA_NOT_RUNNING_ERROR_MESSAGE L"NVDA is not running, or we couldn't communicate with it"

void ensure_nvda_is_running(void) {
    while (TRUE) {
        error_status_t res = nvdaController_testIfRunning();
        if (res == 0) {
            break; // NVDA is running
        }

        // Construct the error message
        wchar_t *errmsg = get_error_message(res);
        wchar_t *message;
        if (errmsg) {
            message = wasprintf(NVDA_NOT_RUNNING_ERROR_MESSAGE L":\n%ls", errmsg);
        LocalFree(errmsg);
        } else {
            // FormatMessage failed, use generic message only
            message = NVDA_NOT_RUNNING_ERROR_MESSAGE;
        }

        // Notify the user that NVDA isn't running and give them the chance to retry
        int btn = MessageBox(NULL,
             message,
                L"NVDA Emacspeak Server",
                MB_RETRYCANCEL | MB_ICONERROR | MB_DEFBUTTON2);

        // Clean up message
        if (errmsg) {
            // errmsg *was* a valid pointer, so we definitely allocated message with malloc()
            free(message);
        }

        if (btn == IDCANCEL) {
            // User requested to cancel
            exit(EXIT_FAILURE);
        }
    }
}

int main(void) {
    ensure_nvda_is_running();
    return EXIT_SUCCESS;
}
