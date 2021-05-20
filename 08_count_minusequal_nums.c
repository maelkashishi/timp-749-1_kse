#include <stdio.h>

int
main()
{
    int n;
    (void)scanf("%d", &n);
    int i;
    int count = 0;
    for(i=1; i<=n; i++) {
        int dumb;
        (void)scanf("%d", &dumb);
        if (dumb <= 0) {
            count += 1;
        }
    }
    printf("%d", count);
    return 0;
}