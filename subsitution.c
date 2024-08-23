#include <cs50.h>
#include <ctype.h>
#
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_alphabets(string s);
bool has_unique_chars(string key);

// Get key (cmd line)
int main(int argc, string argv[])
{
    // Validate key
    if (argc !=2)
    {
        printf("Usage: ./subsitution key\n");
        return 1;
    }
    // Check for non-alphabetic characters
    if (!only_alphabets(argv[1]))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    // Check key length
    int length = strlen(argv[1]);
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Check for repeated characters (case-insensitive)
    if (!has_unique_chars(argv[1]))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else
    {
        // Get plaintext
        string text = get_string("plaintext:  ");
        printf("ciphertext: ");
        // Encipher
        for (int i = 0; i < strlen(text); i++)
        {
            // Get the current char
            char c = text[i];
            // For each alphabetic char, determine what letter it maps to
            if (isalpha(c))
            {
                char base;
                char encrypted;
                int index;

                if (isupper(c))
                {
                    base = 'A';
                    index = c - base;
                    encrypted = toupper(argv[1][index]);
                }
                else
                {
                    base = 'a';
                    index = c - base;
                    encrypted = tolower(argv[1][index]);
                }
                // Print ciphertext
                printf("%c", encrypted);
            }
            else
            {
                printf("%c", c);
            }
        printf("\n");
        printf("All good!\n");
        return 0;
      }
    }
}

bool only_alphabets(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool has_unique_chars(string key)
{
    int occured[26] = {0};
    for (int i = 0; i < strlen(key); i++)
    {
        int index = toupper(key[i]) - 'A';
        if (occured[index])
        {
            return false;
        }
        occured[index] = 1;
    }
    return true;
}
