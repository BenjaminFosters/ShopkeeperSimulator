#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void recipe_check(int meat, int herbs, int spices)
{
    printf("Checking recipes...\n");
    if (meat >= 5 && herbs >= 3 && spices >= 2)
    {
        printf("You can make Dragon Meat Soup!\n");
    }
    else
    {
        printf("Not enough ingredients for Dragon Meat Soup.\n");
    }
}

struct dragon_item
{
    char name[20];
    int stock;
    int price;
};

int main(void)
{
    int choice = 0;
    int meat = 10;
    int herbs = 10;
    int spices = 10;
    int gold = 10;
    int price;
    // int ca

    struct dragon_item soup;
    strcpy(soup.name, "Dragon Meat Soup");
    soup.stock = 0; // Starting stock
    soup.price = 5;

    srand((unsigned)time(NULL));

    do
    {
        printf("\nWelcome to my merchant traveler, what would you like to do?\n");
        printf("1. Serve customer\n");
        printf("2. Buy stuff\n");
        printf("3. Manage stock\n");
        printf("4. Exit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            if (soup.stock > 0)
            {
                int customer_type = rand() % 4;
                switch (customer_type)
                {
                case 0:
                    printf("Customer wants to buy a Dragon Meat Soup, How much would you charge for a Dragon Meat Soup?\n");
                    if (scanf("%d", &price) != 1)
                    {
                        price = 0;
                        while (getchar() != '\n')
                        {
                        }
                    }
                    if (price >= 2)
                    {
                        printf("Customer buys a Dragon Meat Soup.\n");
                        gold += price;
                        soup.stock -= 1;
                    }
                    else
                    {
                        if (rand() % 100 < 70)
                        {
                            printf("Customer is unhappy but buys a Dragon Meat Soup.\n");
                            gold += price;
                            soup.stock -= 1;
                        }
                        else
                        {
                            printf("Customer leaves angrily.\n");
                        }
                    }
                    break;
               case 1:
                     printf("Customer wants to buy a meal. How much would you charge for a meal?\n");
                    if (scanf("%d", &price) != 1)
                    {
                        price = 0;
                        while (getchar() != '\n')
                        {
                        }
                    }
                    if (price >= 2)
                    {
                        printf("Customer buys a meal.\n");
                        gold += price;
                        soup.stock -= 1;
                    }
                    else
                    {
                        if (rand() % 100 < 70)
                        {
                            printf("Customer is unhappy but buys a meal.\n");
                            gold += price;
                            soup.stock -= 1;
                        }
                        else
                        {
                            printf("Customer leaves angrily.\n");
                        }
                    }
                    break;
                case 2:
                    printf("Customer wants to buy a souvenir. How much would you charge for a souvenir?\n");
                    if (scanf("%d", &price) != 1)
                    {
                        price = 0;
                        while (getchar() != '\n')
                        {
                        }
                    }
                    if (price >= 5)
                    {
                        printf("Customer buys a souvenir.\n");
                        gold += price;
                        soup.stock -= 1;
                    }
                    else
                    {
                        if (rand() % 100 < 50)
                        {
                            printf("Customer is unhappy but buys a souvenir.\n");
                            gold += price;
                            soup.stock -= 1;
                        }
                        else
                        {
                            printf("Customer leaves angrily.\n");
                        }
                    }
                    break;
                case 3:
                    printf("Customer wants to buy a premium item. How much would you charge for a premium item?\n");
                    if (scanf("%d", &price) != 1)
                    {
                        price = 0;
                        while (getchar() != '\n')
                        {
                        }
                    }
                    if (price >= 10)
                    {
                        printf("Customer buys a premium item.\n");
                        gold += price;
                        soup.stock -= 1;
                    }
                    else
                    {
                        if (rand() % 100 < 30)
                        {
                            printf("Customer is unhappy but buys a premium item.\n");
                            gold += price;
                            soup.stock -= 1;
                        }
                        else
                        {
                            printf("Customer leaves angrily.\n");
                        }
                    }
                    break;
                }
            }
            else
            {
                printf("No stock to serve a customer.\n");
            }
            break;
        case 2:
            printf("Sell stuff functionality not implemented yet.\n");
            break;
        case 3:
        //    int manage_choice;
        //     printf("\n=== Manage Stock ===\n");
        //     printf("1. View Status");
        //     printf("2.Cook a Meal");
        //    if (scanf("%d", &manage_choice) != 1) {
        //     while (getchar() != '\n') {}
        //     printf("Invalid input.\n");
        //     break;
        //      } 
        //     if (manage_stock == 1) {
        //         printf("=== Current Status ===\n");
        //         printf("Gold : %d\n",&gold);
        //         printf("Stock: ")
        //     }

            // printf("Ingredients - Meat: %d, Herbs: %d, Spices: %d\n", meat, herbs, spices);
            // recipe_check(meat, herbs, spices);
            break;
        case 4:
            printf("Exiting the tavern. Safe travels!\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
