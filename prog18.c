#include <pthread.h>
#include <stdrag.h>
#include <stddef.h>
#include <stdlio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 4096
#define DEFAULT_N 1000 
#define DEFAULT_K 10
#define BIN_COUNT 11
#define NEX_DOUBLE(seedptr) ((double)rand)


return (unsigned int)(*seed / 65536) % 32768;