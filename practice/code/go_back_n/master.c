#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int total_frames, window_size;
    int total_count;

    printf("Enter the no of data to send: ");
    scanf("%d", &total_frames);

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    srand(time(0));

    int base = 1;

    while (base <= total_frames)
    {
        printf("\nSending Window...\n");
        for (int i = base; i < base + window_size && i <= total_frames; i++)
        {
            printf("Sending frame %d...\n", i);
            total_count++;
        }

        int success_count = 0;

        for (int i = base; i < base + window_size && i <= total_frames; i++)
        {
            int success = rand() % 3;

            if (success == 0)
            {
                printf("ACK %d recieved!!!\n", i);
                success_count++;
            }
            else
            {
                printf("Timeout for %d!!!\n", i);
                printf("Retransmitting from %d\n", i);
                break;
            }
        }

        base = base + success_count;

        printf("Total frames send: %d\n", total_count);
    }

    return 0;
}
