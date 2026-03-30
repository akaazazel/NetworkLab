#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int seq = 0;
int expected = 0;
int ack = -1;

int frame_lost;
int ack_lost;

void sender()
{
    printf("\nSENDER: Sending Frame %d...\n", seq);

    frame_lost = rand() % 3;

    if (frame_lost == 0)
    {
        printf("Frame Lost!!!\n");
        return;
    }
}

void reciever()
{
    if (frame_lost == 0)
    {
        printf("RECIEVER: No Frame Recieved!!!\n");
        return;
    }

    if (seq == expected)
    {
        printf("RECIEVER: Frame %d Recieved!!!\n", seq);
        ack = seq;
        expected = 1 - expected;
    }
    else
    {
        printf("RECIEVER: Duplicate Frame!!!\n");
        ack = 1 - expected;
    }

    ack_lost = rand() % 3;

    if (ack_lost == 0)
    {
        printf("ACK Lost!!!\n");
        return;
    }

    printf("SENDER: ACK %d recieved.\n", ack);

    if (ack == seq)
    {
        seq = 1 - seq;
    }
}

int main()
{
    srand(time(0));

    for (int i = 0; i < 10; i++)
    {
        sender();
        reciever();
    }

    return 0;
}
