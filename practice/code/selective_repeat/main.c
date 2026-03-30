#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main()
{
    int total_frames, window_size;
    int ack[MAX] = {0}; // 0 = not received, 1 = received
    int sent_count = 0;

    printf("Enter total frames: ");
    scanf("%d", &total_frames);

    printf("Enter window size: ");
    scanf("%d", &window_size);

    srand(time(0));

    int base = 1;

    while (base <= total_frames)
    {

        printf("\n--- Sending Window ---\n");

        // 1. Send frames in window
        for (int i = base; i < base + window_size && i <= total_frames; i++)
        {

            if (ack[i] == 0)
            {
                printf("Sending Frame %d\n", i);
                sent_count++;

                int success = rand() % 2;

                if (success)
                {
                    printf("✅ ACK received for Frame %d\n", i);
                    ack[i] = 1;
                }
                else
                {
                    printf("❌ Frame %d lost (will resend later)\n", i);
                }
            }
        }

        // 2. Slide window (only if base is acknowledged)
        while (ack[base] == 1 && base <= total_frames)
        {
            base++;
        }
    }

    printf("\nTotal transmissions: %d\n", sent_count);

    return 0;
}
