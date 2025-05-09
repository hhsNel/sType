#define BG_RGB(R,G,B) "\033[48;2;" #R ";" #G ";" #B "m"
#define FG_RGB(R,G,B) "\033[38;2;" #R ";" #G ";" #B "m"
#define BG_256(C) "\033[48;5;" #C "m"
#define FG_256(C) "\033[38;5;" #C "m"
#define BG_USR(C) "\033[" #C "m"
#define FG_USR(C) "\033[0" #C "m"

#define TXT_BOLD "\033[22m"
#define TXT_BLINKING "\033[25m"

