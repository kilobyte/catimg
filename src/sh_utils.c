#include "sh_utils.h"

#ifdef WINDOWS
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#endif

uint32_t terminal_columns()
{
#ifdef WINDOWS
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int ret;
        ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
        return ret?csbi.dwSize.X:0;
#else
        struct winsize win;
        const char *colenv;

        if (isatty(0)) {
                ioctl(0, TIOCGWINSZ, &win);
                if (win.ws_col > 0)
                        return win.ws_col;
        }

        if (colenv = getenv("COLUMNS")) {
                int c = atoi(colenv);
                if (c > 0)
                        return c;
        }

        return 80;
#endif
}

