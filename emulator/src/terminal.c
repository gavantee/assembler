#include "terminal.h"

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

#include "emulator.h"

static int            terminal_descriptor = -1;
static struct termios terminal_original;
static struct termios terminal_settings;

static void terminal_signal(int signum)
{
    if (terminal_descriptor != -1)
        tcsetattr(terminal_descriptor, TCSANOW, &terminal_original);

    /* exit() is not async-signal safe, but _exit() is.
     * Use the common idiom of 128 + signal number for signal exits.
     * Alternative approach is to reset the signal to default handler,
     * and immediately raise() it. */
    _exit(128 + signum);
}

static void terminal_done(void)
{
    if (terminal_descriptor != -1)
        tcsetattr(terminal_descriptor, TCSANOW, &terminal_original);
}

int terminal_init() {
				struct sigaction act;

    /* Already initialized? */
    if (terminal_descriptor != -1)
        return errno = 0;

    /* Which standard stream is connected to our TTY? */
    if (isatty(STDERR_FILENO))
        terminal_descriptor = STDERR_FILENO;
    else
    if (isatty(STDIN_FILENO))
        terminal_descriptor = STDIN_FILENO;
    else
    if (isatty(STDOUT_FILENO))
        terminal_descriptor = STDOUT_FILENO;
    else
        return errno = ENOTTY;

    /* Obtain terminal settings. */
    if (tcgetattr(terminal_descriptor, &terminal_original) ||
        tcgetattr(terminal_descriptor, &terminal_settings))
        return errno = ENOTSUP;

    /* Disable buffering for terminal streams. */
    if (isatty(STDIN_FILENO))
        setvbuf(stdin, NULL, _IONBF, 0);
    if (isatty(STDOUT_FILENO))
        setvbuf(stdout, NULL, _IONBF, 0);
    if (isatty(STDERR_FILENO))
        setvbuf(stderr, NULL, _IONBF, 0);

    /* At exit() or return from main(),
     * restore the original settings. */
    if (atexit(terminal_done))
        return errno = ENOTSUP;

    /* Set new "default" handlers for typical signals,
     * so that if this process is killed by a signal,
     * the terminal settings will still be restored first. */
    sigemptyset(&act.sa_mask);
    act.sa_handler = terminal_signal;
    act.sa_flags = 0;
    if (sigaction(SIGHUP,  &act, NULL) ||
        sigaction(SIGINT,  &act, NULL) ||
        sigaction(SIGQUIT, &act, NULL) ||
        sigaction(SIGTERM, &act, NULL) ||
#ifdef SIGXCPU
        sigaction(SIGXCPU, &act, NULL) ||
#endif
#ifdef SIGXFSZ
        sigaction(SIGXFSZ, &act, NULL) ||
#endif
#ifdef SIGIO
        sigaction(SIGIO,   &act, NULL) ||
#endif
        sigaction(SIGPIPE, &act, NULL) ||
        sigaction(SIGALRM, &act, NULL))
        return errno = ENOTSUP;

  terminal_settings.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
  terminal_settings.c_cflag &= ~(CSIZE | PARENB);
  terminal_settings.c_cflag |= CS8;
  terminal_settings.c_cc[VMIN] = 0;
  terminal_settings.c_cc[VTIME] = 0;

    tcsetattr(terminal_descriptor, TCSANOW, &terminal_settings);

    /* Done. */
    return errno = 0;
}

void terminal_read(unsigned char *term_in) {
  char c;
  if (read(STDIN_FILENO, &c, 1) == 1) {
	  *term_in = c;
    int_req(3);
  }
}

