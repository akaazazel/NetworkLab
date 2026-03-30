#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int total_frames, window_size;
    int sent_count = 0;

    printf("Enter total number of frames: ");
    scanf("%d", &total_frames);

    printf("Enter window size: ");
    scanf("%d", &window_size);

    srand(time(0));

    int base = 1; // first unacknowledged frame

    while (base <= total_frames)
    {

        printf("\n--- Sending Window ---\n");

        // 1. Send frames in window
        for (int i = base; i < base + window_size && i <= total_frames; i++)
        {
            printf("Sending Frame %d\n", i);
            sent_count++;
        }

        // 2. Receive ACKs
        int success_count = 0;

        for (int i = base; i < base + window_size && i <= total_frames; i++)
        {
            int success = rand() % 2; // 0 = fail, 1 = success

            if (success)
            {
                printf("ACK received for Frame %d\n", i);
                success_count++;
            }
            else
            {
                printf("Timeout at Frame %d\n", i);
                printf("Go-Back-N: Retransmitting from Frame %d\n", i);
                break;
            }
        }

        // 3. Slide window
        base = base + success_count;
    }

    printf("\nTotal transmissions (including retransmissions): %d\n", sent_count);

    return 0;
}
