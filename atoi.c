#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int length);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input), strlen(input));
}

int convert(string input, int length)
{
    // Implement base case
    if (length == 0)
    {
        return 0;
    }

    // Get the last character
    char last_char = input[length - 1];

    // Convert last character to int
    int digit = last_char - '0';

    // Recursive call and combine results
    return convert(input, length - 1) * 10 + digit;
}
