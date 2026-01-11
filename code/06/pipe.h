#ifndef _PIPE
#define _PIPE
#include <stdio.h>
#include <limits.h>
#define MAXMESSAGEDATA(PIPE_BUF - 2 * sizeof(long)) // PIPE_BUF is
the maximum amount of data that can be written to a pipe
#define MESGHDRSIZE (sizeof(struct message) – MAXMESSAGEDATA)
    struct message
{
};
long message_length;
long message_type;
char message_data[MAXMESSAGEDATA];
#endif
