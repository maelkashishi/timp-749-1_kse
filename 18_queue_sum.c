#include <stdio.h>

int
main ()
{
    int n;
    (void) scanf ("%d", &n);
    int i;
    int sum = 0;
    for (i = 1; i <= n; i++)
    {
        int dumb = 0;
        (void) scanf ("%d", &dumb);
        sum += dumb - i;
    }
    printf ("%d", sum);
    return 0;
}
