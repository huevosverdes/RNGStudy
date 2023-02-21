#include "Messaging.h"

Message *msgInit(double timeout, const char *text)
{
    Message *result = (Message*)malloc(sizeof(Message));
    result->timeout = timeout;
    result->text = (char*)malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(result->text, text);
}

void msgDelete(Message *msg)
{
    delete[] msg->text;
    delete msg;
}

void msgLog(Message *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vprintf(msg->text, args);
    va_end(args);

    printf("\n");
    fflush(stdout);

    sleep(msg->timeout);
}
