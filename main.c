#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BLUE  "\033[34m"
#define RESET "\033[0m"

/* ===================== STRUCT ===================== */
struct meal
{
    char name[20];
    int stock;
    int base_price;
    int req_meat;
    int req_herbs;
    int req_spices;
};

/* ===================== SORT HELPERS ===================== */
void sortByName(struct meal temp[4])
{
    struct meal swap;
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 4; j++)
            if (strcmp(temp[i].name, temp[j].name) > 0)
            {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
}

void sortByStock(struct meal temp[4])
{
    struct meal swap;
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 4; j++)
            if (temp[i].stock < temp[j].stock)
            {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
}

void sortByPrice(struct meal temp[4])
{
    struct meal swap;
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 4; j++)
            if (temp[i].base_price > temp[j].base_price)
            {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
}

/* ===================== SEARCH ===================== */
void searchInventory(struct meal menu[4], int meat, int herbs, int spices)
{
    int choice;
    printf("\n=== Search Inventory ===\n");
    printf("1. Search meal by name\n");
    printf("2. Sort meals\n");
    printf("3. View ingredients\n");
    printf("Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n');
        return;
    }

    if (choice == 1)
    {
        char name[30];
        printf("Enter meal name: ");
        scanf(" %[^\n]", name);

        for (int i = 0; i < 4; i++)
        {
            if (strcasecmp(name, menu[i].name) == 0)
            {
                printf("Found: %s | Stock: %d | Price: %d\n",
                       menu[i].name, menu[i].stock, menu[i].base_price);
                return;
            }
        }
        printf("Meal not found.\n");
    }
    else if (choice == 2)
    {
        struct meal temp[4];
        memcpy(temp, menu, sizeof(temp));

        int s;
        printf("Sort by:\n");
        printf("1. Name\n");
        printf("2. Stock\n");
        printf("3. Price\n");
        printf("Choice: ");
        scanf("%d", &s);

        if (s == 1) sortByName(temp);
        else if (s == 2) sortByStock(temp);
        else if (s == 3) sortByPrice(temp);
        else return;

        for (int i = 0; i < 4; i++)
            printf("%s | Stock: %d | Price: %d\n",
                   temp[i].name, temp[i].stock, temp[i].base_price);
    }
    else if (choice == 3)
    {
        printf("Meat: %d | Herbs: %d | Spices: %d\n", meat, herbs, spices);
    }
}

/* ===================== UTILITY ===================== */
void loading_crafting(void)
{
    printf("Crafting");
    for (int i = 0; i < 5; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

void recipe_check(int meat, int herbs, int spices)
{
    if (meat >= 5 && herbs >= 3 && spices >= 2)
        printf("You can craft meals.\n");
    else
        printf("Not enough ingredients.\n");
}

/* ===================== DAY LOGIC ===================== */
void startaDay(struct meal menu[4], int *gold, int *rep, int day)
{
    char customers[5][20] = {"Knight", "Merchant", "Peasant", "Noble", "Adventurer"};
    int c = rand() % 5;
    int m = rand() % 4;

    printf("\n=== Day %d ===\n", day);
    printf("%s wants %s\n", customers[c], menu[m].name);

    if (menu[m].stock <= 0)
    {
        printf("No stock. Reputation -10\n");
        *rep -= 10;
        return;
    }

    int price;
    printf("Enter price: ");
    scanf("%d", &price);

    if (price >= menu[m].base_price || rand() % 100 < 70)
    {
        printf("Sale successful!\n");
        *gold += price;
        menu[m].stock--;
    }
    else
    {
        printf("Customer left angrily.\n");
    }
}

/* ===================== MENU HELPERS ===================== */
void printMainMenu(void)
{
    printf(BLUE);
    printf("=====================================================\n");
    printf("||                                                 ||\n");
    printf("||   ██████╗ ██████╗  █████╗ ███╗   ██╗██████╗     ||\n");
    printf("||  ██╔════╝ ██╔══██╗██╔══██╗████╗  ██║██╔══██╗    ||\n");
    printf("||  ██║  ███╗██████╔╝███████║██╔██╗ ██║██║  ██║    ||\n");
    printf("||  ██║   ██║██╔══██╗██╔══██║██║╚██╗██║██║  ██║    ||\n");
    printf("||  ╚██████╔╝██║  ██║██║  ██║██║ ╚████║██████╔╝    ||\n");
    printf("||   ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝     ||\n");
    printf("||                                                 ||\n");
    printf("||        G R A N D L A X R   T A V E R N          ||\n");
    printf("||       \"Where Legends Rest & Ale Flows\"          ||\n");
    printf("||                                                 ||\n");
    printf("=====================================================\n");
    printf(RESET);
    printf("1. Start a Day\n");
    printf("2. Buy stuff\n");
    printf("3. Manage stock\n");
    printf("4. Search inventory\n");
    printf("5. Exit\n");
    printf("Choice: ");
}

int getMenuChoice(void)
{
    int c;
    while (1)
    {
        if (scanf("%d", &c) == 1 && c >= 1 && c <= 5)
            return c;

        while (getchar() != '\n');
        printf("Invalid choice. Try again: ");
    }
}

/* ===================== HANDLERS ===================== */
void handleStartDay(struct meal menu[4], int *gold, int *rep, int *day)
{
    int stock = 0;
    for (int i = 0; i < 4; i++) stock += menu[i].stock;

    if (stock == 0)
    {
        printf("No stock to sell.\n");
        return;
    }

    startaDay(menu, gold, rep, *day);
    (*day)++;
}

void handleManageStock(
    struct meal menu[4],
    int *meat,
    int *herbs,
    int *spices,
    int gold)
{
    int c;
    printf("\n1. View Status\n2. Cook Meal\nChoice: ");
    scanf("%d", &c);

    if (c == 1)
    {
        printf("Gold: %d\n", gold);
        printf("Meat:%d Herbs:%d Spices:%d\n", *meat, *herbs, *spices);
        for (int i = 0; i < 4; i++)
            printf("%s: %d\n", menu[i].name, menu[i].stock);

        recipe_check(*meat, *herbs, *spices);
    }
    else if (c == 2)
    {
        for (int i = 0; i < 4; i++)
            printf("%d. %s\n", i + 1, menu[i].name);

        int m;
        scanf("%d", &m);
        m--;

        if (*meat >= menu[m].req_meat &&
            *herbs >= menu[m].req_herbs &&
            *spices >= menu[m].req_spices)
        {
            loading_crafting();
            *meat -= menu[m].req_meat;
            *herbs -= menu[m].req_herbs;
            *spices -= menu[m].req_spices;
            menu[m].stock++;
            printf("Crafted %s!\n", menu[m].name);
        }
        else
            printf("Not enough ingredients.\n");
    }
}

/* ===================== MAIN ===================== */
int main(void)
{
    int meat = 10, herbs = 10, spices = 10;
    int gold = 10, reputation = 50, day = 1;
    int choice;

    struct meal menu[4] = {
        {"Dragon Meat Soup", 0, 5, 5, 3, 2},
        {"Lamb Chop", 0, 8, 7, 2, 3},
        {"Salad", 0, 3, 0, 8, 1},
        {"Premium Steak", 0, 10, 4, 1, 5}
    };

    srand((unsigned)time(NULL));

    do
    {
        printMainMenu();
        choice = getMenuChoice();

        switch (choice)
        {
            case 1:
                handleStartDay(menu, &gold, &reputation, &day);
                break;
            case 2:
                printf("Buy stuff not implemented.\n");
                break;
            case 3:
                handleManageStock(menu, &meat, &herbs, &spices, gold);
                break;
            case 4:
                searchInventory(menu, meat, herbs, spices);
                break;
            case 5:
                printf("Goodbye!\n");
                break;
        }

    } while (choice != 5);

    return 0;
}
