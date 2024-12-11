#include <stdio.h>

int main( void )
{
    int i;

    char *arr[50] = {"C","C++","Java","VBA"};
    char **ptr = arr;

    char input[50];
    scanf("%s", &input);
    ptr[4] = input;

    for ( i = 0; i < 5; i++ )
        printf("String %d : %s\n", i+1, ptr[i] );

    return 0;
}