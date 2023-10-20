#include "pch.h"
#include "cleanup-windows.h"

int main() {
    internals::cleanup_windows::start_cleanup();

    return 0;
}
