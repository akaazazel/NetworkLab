#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main()
{
    int total_frames, window_size;
    int ack[MAX] = {0};
    int sent_count = 0;

    printf("Frames: ");
    scanf("%d", &total_frames);
    printf("Window: ");
    scanf("%d", &window_size);

    srand(time(0));

    int lost[window_size];
    int base = 1;

    while (base <= total_frames)
    {
        printf("\nSending Window\n");

        int lost_index = 0;

        for (int i = 0; i < window_size; i++)
        {
            lost[i] = 0;
        }

        for (int i = base; i < base + window_size && i <= total_frames; i++)
        {
            if (ack[i] == 0)
            {
                printf("Sending Frame %d...\n", i);
                sent_count++;

                int success = rand() % 3;

                if (success == 0)
                {
                    printf("✅ ACK %d recieved.\n", i);
                    ack[i] = 1;
                }
                else
                {
                    printf("❌ Frame %d lost!!!\n", i);
                    lost[lost_index] = i;
                    lost_index++;
                }
            }
        }

        printf("\n");
        for (int i = 0; i < window_size; i++)
        {
            if (lost[i] != 0)
            {
                printf("%d | ", lost[i]);
            }
        }
        printf("\n");

        while (ack[base] == 1 && base <= total_frames)
        {
            base++;
        }
    }

    printf("\nTotal: %d", sent_count);

    return 0;
}
