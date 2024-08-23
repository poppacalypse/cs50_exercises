#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user for some text
    string text = get_string("Enter your text: ");

    // Count number of letters, words, and sentences in the text
    int letters = count_letters(text);
    printf("Letters: %i\n", letters);

    int words = count_words(text);
    printf("Words: %i\n", words);

    int sentences = count_sentences(text);
    printf("Sentences: %i\n", sentences);

    // Compute the Coleman-Liau index
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("C-L index: %f\n", index);

    // Print the grade level
    printf("Grade: %d\n", (int) round(index));
}

int count_letters(string text)
{
    // Return the number of letters in text
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
             count++;
        }
    }
    return count;
}

int count_words(string text)
{
    // Return the number of words in text
    int count = 0;
    bool in_word = false;
    bool has_letter = false;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            has_letter = true;
            in_word = true;
        }
        else if (isspace(text[i]))
        {
            if (in_word && has_letter)
            {
                count++;
            }
            in_word = false;
            has_letter = false;
        }
    }

    // Count the last word if it ends without a space
    if (in_word && has_letter)
    {
        count++;
    }
    return count;
}

int count_sentences(string text)
{
  // Return the number of sentences in text
    int count = 0;
    int words = count_words(text);

    if (words >= 1)
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                count++;
            }
        }
    }
    return count;
}
