#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ll long long int

int transmission(ll i, ll N, ll tf, ll tt)
{
    while (i <= tf)
    {
        int z = 0;
        for (int k = i; k < i + N && k <= tf; k++)
        {
            printf("Sending frame %d...\n", k);
            tt++;
        }
        for (int k = i; k < i + N && k <= tf; k++)
        {
            int f = rand() % 2;
            if (!f)
            {
                printf("Acknowledgement for frame %d...\n", k);
                z++;
            }
            else
            {
                printf("Timeout!!! Frame number %d not recieved!\n", k);
                printf("Retransmitting window...\n");
                break;
            }
        }
        printf("\n");
        i = i + z;
    }
    return (tt);
}

int main()
{
    ll tf, N, tt = 0;

    printf("Enter the total number of frames: ");
    scanf("%lld", &tf);
    printf("Enter the window size: ");
    scanf("%lld", &N);

    ll i = 1;
    tt = transmission(i, N, tf, tt);
    printf("Total number of frames which were send and resend are: %lld...\n", tt);
    return 0;
}