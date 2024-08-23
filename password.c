// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);
bool only_lower_alphabets(string s);
bool only_upper_alphabets(string s);
bool only_digits(string s);
bool only_symbols(string s);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    if(only_lower_alphabets(password) && only_upper_alphabets(password) && only_digits(password) && only_symbols(password))
    {
        return true;
    }
    return false;
}
bool only_lower_alphabets(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) && islower(s[i]))
        {
            return true;
        }
    }
    return false;
}
bool only_upper_alphabets(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]) && isupper(s[i]))
        {
            return true;
        }
    }
    return false;
}
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]))
        {
            return true;
        }
    }
    return false;
}
bool only_symbols(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (ispunct(s[i]))
        {
            return true;
        }
    }
    return false;
}
