// Practice using structs
// Practice writing a linear search function

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to the Krusty Krab!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    menu[0].item = "Krabby Patty";
    menu[0].price = 1.25;

    menu[1].item = "Krabby Meal";
    menu[1].price = 3.50;

    menu[2].item = "Salty Sea Dog";
    menu[2].price = 1.25;

    menu[3].item = "Footlong";
    menu[3].price = 2.00;

    menu[4].item = "Sailors Surprise";
    menu[4].price = 3.00;

    menu[5].item = "Golden Loaf";
    menu[5].price = 2.00;

    menu[6].item = "Coral Bits";
    menu[6].price = 1.50;

    menu[7].item = "Kelp Shake";
    menu[7].price = 2.00;

    menu[8].item = "Kelp Rings";
    menu[8].price = 1.50;

    menu[9].item = "Seafoam Soda";
    menu[9].price = 1.50;

    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    // Implement linear search
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        // Compare item with menu[i].item using strcasecmp
        if (strcasecmp(item, menu[i].item) == 0)
        {
            return menu[i].price;
        }
    }
    return 0.0;
}

// 3 different methods of adding items:

// 1. Separate statements
// Most straightforward, easy to understand for beginners.
// void add_items(void)
// {
//     menu[0].item = "Burger";
//     menu[0].price = 9.5;

//     menu[1].item = "Vegan Burger";
//     menu[1].price = 11.0;
// }

// 2. Array initialisation
// Reduce repetitive code. Use an array of structs to initialise the menu.
// Initialise all items at once, then copy them to the `menu` array.
// void add_items(void)
// {
//     menu_item items[] = {
//         {"Burger", 9.5},
//         {"Vegan Burger", 11.0},
//         // ... add more items ...
//     };

//     for (int i = 0; i < NUM_ITEMS && i < sizeof(items) / sizeof(items[0]); i++)
//     {
//         menu[i] = items[i];
//     }
// }

// 3. Index variable
// Used to keep track of positions in an array. More for dynamic or complex scenarios.
// void add_items(void)
// {
//     int index = 0;
//     menu[index].item = "Burger";
//     menu[index].price = 9.5;
//     index++;

//     menu[index].item = "Vegan Burger";
//     menu[index].price = 11.0;
//     index++;
// }
