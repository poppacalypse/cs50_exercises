// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string normspeak);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            string leetspeak = replace(argv[i]);

            if (isspace(i))
            {
                printf(" ");
            }

            printf("%s", leetspeak);
        }
    }
    printf("\n");
}

string replace(string input)
{
    string output = input;
    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        char c = input[i];
        switch (c)
        {
            case 'a':
            case 'A':
                output[i] = '6';
                break;

            case 'e':
            case 'E':
                output[i] = '3';
                break;

            case 'i':
            case 'I':
                output[i] = '1';
                break;

            case 'o':
            case 'O':
                output[i] = '0';
                break;

            default:
                break;
        }
    }
    return output;
}
