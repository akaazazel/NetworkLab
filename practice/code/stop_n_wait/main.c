#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int seq = 0;      // sender sequence number
int expected = 0; // receiver expected sequence
int ack = -1;

int frame_lost;
int ack_lost;

void sender();
void receiver();

int main()
{
    srand(time(0));

    for (int i = 0; i < 10; i++)
    {
        sender();
        receiver();
    }
    return 0;
}

void sender()
{
    printf("\nSENDER: Sending frame %d\n", seq);

    frame_lost = rand() % 3; // 0 = lost, else success

    if (frame_lost == 0)
    {
        printf("Frame LOST\n");
        return; // simulate timeout → resend later
    }
}

void receiver()
{
    if (frame_lost == 0)
    {
        printf("RECEIVER: No frame received\n");
        return;
    }

    if (seq == expected)
    {
        printf("RECEIVER: Frame %d received correctly\n", seq);

        ack = seq;
        expected = 1 - expected; // alternate 0 ↔ 1
    }
    else
    {
        printf("RECEIVER: Duplicate frame %d\n", seq);
        ack = 1 - expected;
    }

    ack_lost = rand() % 3;

    if (ack_lost == 0)
    {
        printf("ACK LOST\n");
        return;
    }

    printf("SENDER: ACK %d received\n", ack);

    if (ack == seq)
    {
        seq = 1 - seq; // move to next frame
    }
}
