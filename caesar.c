#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{

    // Make sure program was run with just one command-line argument
    // Make sure every character in argv[1] is a digit
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        printf("Your string-key is %s\n", argv[1]);

        // Convert argv[1] from a `string` to an `int`
        int k = atoi(argv[1]);
        printf("Your int-key is %i\n", k);

        // Prompt user for plaintext
        string text = get_string("plaintext:  ");

        // Print ciphertext
        printf("ciphertext: ");

        // Loop through each character in the plaintext
        for (int i = 0; i < strlen(text); i++)
        {
            // Get the current char
            char current_char = text[i];

            // Rotate the char and print it
            char rotated_char = rotate(current_char, k);
            printf("%c", rotated_char);
        }

        printf("\n");

        return 0;
    }
}

bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    // For each character in plaintext:
    // Check if the char is alphabetic
    if (isalpha(c))
    {
        // Determine the "base" char ('A' for uppercase, 'a' for lowercase)
        char base;
        if (isupper(c))
        {
            base = 'A';
        }
        else
        {
            base = 'c';
        }

        // Calculate the position in the alphabet (0-25)
        int position = c - base;

        // Rotate the character if it's a letter
        // Formula: c[i] = (p[i] + k) % 26
        int new_position = (position + n) % 26;

        // Convert back to a char and return
        return base + new_position;
    }
    else
    {
        // If it's not alphabetic, return unchanged
        return c;
    }

    return 0;
}
