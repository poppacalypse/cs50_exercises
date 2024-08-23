// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    } 
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    // Initialise max value
    int max_value = array[0];

    // Loop through the array*
    for (int i = 1; i < n; i++)
    {
        // Compare and update max_value if necessary
        if (array[i] > max_value)
        {
            max_value = array[i];
        }
    }

    // Return the max value
    return max_value;
}

// * Start from the second element `int i = 1` since i've already initialized `max_value` with the first element. Makes the code slightly more efficient.