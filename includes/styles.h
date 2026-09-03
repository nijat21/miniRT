#ifndef STYLES_H
#define STYLES_H

/* ── Reset ─────────────────────────────────────────────── */

#define RESET "\033[0m"

/* ── Styles ────────────────────────────────────────────── */

#define BOLD "\033[1m"
#define DIM "\033[2m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define REVERSE "\033[7m"

/* ── Regular colors ───────────────────────────────────── */

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

/* ── Bright colors ────────────────────────────────────── */

#define BRIGHT_BLACK "\033[90m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"

/* ── Useful combinations ──────────────────────────────── */

#define SUCCESS GREEN BOLD
#define ERROR RED BOLD
#define WARNING YELLOW BOLD
#define INFO CYAN BOLD
#define MUTED DIM
#define HEADER BLUE BOLD

/* ── Test symbols ─────────────────────────────────────── */

#define PASS GREEN "✓" RESET
#define FAIL RED "✗" RESET
#define ARROW CYAN "→" RESET

#endif // STYLES_H
