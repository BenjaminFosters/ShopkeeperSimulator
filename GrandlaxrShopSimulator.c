#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define BLUE  "\033[34m"
#define RESET "\033[0m"



struct meal
{
    char name[20];
    int stock;
    int base_price;
    int req_meat;
    int req_herbs;
    int req_spices;
};
struct customer{
    char name [20];
    int tolerance;
};
struct customer type[10]= {
    {"Knight", 10},
    {"Merchant", 15},
    {"Peasant", 3},
    {"Noble", 20},
    {"Adventurer", 5},
    {"Farmer", 5},
    {"Wealthy Merchant", 25},
    {"Goblin", -15},
    {"Priest", 5},
    {"Thief", -13}
};


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

void saveGame(
    const char *filename,
    int day,
    int gold,
    int reputation,
    int meat,
    int herbs,
    int spices,
    struct meal menu[4]
)
{
    FILE *fp = fopen(filename, "wb");  // write binary
    if (fp == NULL)
    {
        printf("Failed to save game.\n");
        return;
    }

    fwrite(&day, sizeof(int), 1, fp);
    fwrite(&gold, sizeof(int), 1, fp);
    fwrite(&reputation, sizeof(int), 1, fp);
    fwrite(&meat, sizeof(int), 1, fp);
    fwrite(&herbs, sizeof(int), 1, fp);
    fwrite(&spices, sizeof(int), 1, fp);

    fwrite(menu, sizeof(struct meal), 4, fp);

    fclose(fp);
    printf("✓ Game saved successfully!\n");
}

int loadGame(
    const char *filename,
    int *day,
    int *gold,
    int *reputation,
    int *meat,
    int *herbs,
    int *spices,
    struct meal menu[4]
)
{
    FILE *fp = fopen(filename, "rb");  // read binary
    if (fp == NULL)
    {
        printf("No save file found.\n");
        return 0; // failed
    }

    fread(day, sizeof(int), 1, fp);
    fread(gold, sizeof(int), 1, fp);
    fread(reputation, sizeof(int), 1, fp);
    fread(meat, sizeof(int), 1, fp);
    fread(herbs, sizeof(int), 1, fp);
    fread(spices, sizeof(int), 1, fp);

    fread(menu, sizeof(struct meal), 4, fp);

    fclose(fp);
    printf("✓ Game loaded successfully!\n");
    return 1; // success
}




void searchInventory(struct meal menu[4], int meat, int herbs, int spices)
{
    int choice;
    printf("\n=== Search & Sort Inventory ===\n");
    printf("1. Search meal by name\n");
    printf("2. Sort meals\n");
    printf("3. View ingredients\n");
    printf("Choice: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n') {}
        printf("Invalid input.\n");
        return;
    }

    if (choice == 1)
    {
        char search_name[30];
        int found = 0;

        printf("Enter meal name: ");
        scanf(" %[^\n]", search_name);

        for (int i = 0; i < 4; i++)
        {
            if (strcasecmp(search_name, menu[i].name) == 0)
            {
                printf("\n✓ Meal Found!\n");
                printf("Name: %s\n", menu[i].name);
                printf("Stock: %d\n", menu[i].stock);
                printf("Base Price: %d gold\n", menu[i].base_price);
                found = 1;
                break;
            }
        }

        if (!found)
            printf("✗ Meal not found.\n");
    }
    else if (choice == 2)
    {
        struct meal temp[4];
        memcpy(temp, menu, sizeof(temp));

        int sort_choice;
        printf("\nSort meals by:\n");
        printf("1. Name (A-Z)\n");
        printf("2. Stock (High → Low)\n");
        printf("3. Price (Low → High)\n");
        printf("Choice: ");

        if (scanf("%d", &sort_choice) != 1)
        {
            while (getchar() != '\n') {}
            printf("Invalid input.\n");
            return;
        }


        


        
        if (sort_choice == 1)
            sortByName(temp);
        else if (sort_choice == 2)
            sortByStock(temp);
        else if (sort_choice == 3)
            sortByPrice(temp);
        else
        {
            printf("Invalid sort option.\n");
            return;
        }

        printf("\n=== Sorted Meals ===\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%s | Stock: %d | Price: %dg\n",
                   temp[i].name,
                   temp[i].stock,
                   temp[i].base_price);
        }
    }
    else if (choice == 3)
    {
        printf("\nIngredients:\n");
        printf("Meat   : %d\n", meat);
        printf("Herbs  : %d\n", herbs);
        printf("Spices : %d\n", spices);
    }
    else
    {
        printf("Invalid option.\n");
    }
}




int roll_chance(int price,int base_price,int reputation)
{
    float ratio= (float)price / (float)base_price;
    int chance;
if (price > base_price * 3)
    chance = 0;
else
    if (ratio <=1.0) 
    chance =95;
    else if (ratio <1.2) 
    chance = 80;
    else if (ratio <1.5) 
    chance = 55;
    else if (ratio <2.0)
     chance = 20;
    else if (ratio <3.0)
     chance =15;
    else
     chance =5;

//reputation mult
chance+= reputation /20;

return chance;
}


void loading_crafting()
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
    printf("Checking recipes...\n");
    if (meat >= 5 && herbs >= 3 && spices >= 2)
    {
        printf("You can make a Meal!\n");
    }
    else
    {
        printf("Not enough ingredients.\n");
    }
}

void buyStuff(int *gold, int *meat, int *herbs, int *spices)
{
    int choice, qty;
    int meat_price = 3 + rand() % 3;    // 3–5
    int herbs_price = 2 + rand() % 2;   // 2–3
    int spices_price = 4 + rand() % 3;  // 4–6
    int meat_stock = 5 +rand() % 11;   // 20–30
    int herbs_stock = 5+ rand() % 11;  // 15–25
    int spices_stock = 10 + rand() % 11; // 10–20

    do {
        printf("\n=== Supplier Market ===\n");
        printf("Supplier stock today!!!\n");
        printf("Gold: %d\n", *gold);
        printf("1. Meat   (%dg) (stock: %d)\n", meat_price, meat_stock);
        printf("2. Herbs  (%dg) (stock: %d)\n", herbs_price, herbs_stock);
        printf("3. Spices (%dg) (stock: %d)\n", spices_price, spices_stock);
        printf("4. Leave\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            return;
        }

        if (choice < 1 || choice > 4) {
            printf("Invalid Option, try again!\n");
        }
    } while (choice < 1 || choice > 4);


    if (choice == 4) return;

    printf("Quantity: ");
    if (scanf("%d", &qty) != 1 || qty <= 0) {
        while (getchar() != '\n');
        printf("Invalid quantity.\n");
        return;
    }

    int cost = 0;

    if (choice == 1) cost = qty * meat_price;
    else if (choice == 2) cost = qty * herbs_price;
    else if (choice == 3) cost = qty * spices_price;
    else {
        printf("Invalid choice.\n");
        return;
    }

    if (*gold < cost) {
        printf("Not enough gold! You need %d gold.\n", cost);
        return;
    }

    *gold -= cost;

    if (choice == 1) *meat += qty;
    else if (choice == 2) *herbs += qty;
    else if (choice == 3) *spices += qty;

    printf("Purchase successful! Spent %d gold.\n", cost);
}

 void startaDay(
    struct meal menu[4],
    int *gold,
    int *reputation,
    int day
 )
 {
 char customer_type[10][20] = {"Knight", "Merchant", "Peasant", "Noble", 
                                          "Adventurer", "Farmer", "Wealthy Merchant", 
                                          "Goblin", "Priest", "Thief"};
    int customer_type_index = rand() % 10; //RNG for random customer type
    int meal_index = rand() % 4; // RNG for random meal
    printf("======Day %d======\n", day);
    printf("%s wants to buy a %s,\n", customer_type[customer_type_index], 
           menu[meal_index].name);
     printf("is there any stock? (yes/no)\n");
    char response[10];
    scanf("%9s", response);
    if (strcmp(response, "yes") == 0 && menu[meal_index].stock <= 0){
       printf("But you have no stock! They leave angrily. -10 reputation.\n");//lying response
         *reputation -= 10;}
    
    if (strcmp (response,"no") == 0)
    {
        printf("You told %s there is no stock. They leave disappointed.\n", //honest response
               customer_type[customer_type_index]);
        return;
    }
    if (strcmp(response, "yes") != 0)
    {
        printf("Invalid response. The customer leaves confused.\n"); //invalid response
        return;
    }
    if (strcmp(response, "yes") == 0 && menu[meal_index].stock > 0) //normal respone
    {
        printf("Great !, %s wants to buy a %s, How much would you charge?\n Base Price : %d gold\n", 
               customer_type[customer_type_index], menu[meal_index].name, menu[meal_index].base_price);
        int price;
        if (scanf("%d", &price) != 1)
        {
            price = 0;
            while (getchar() != '\n') {}
        }
        if (price <= 0)
        {
            printf("Invalid price! %s leaves angrily. -10 reputation.\n", //if user input negative number
                   customer_type[customer_type_index]);
            *reputation -= 10;
        }
        else
        {
            //calculate chance
            int chance=roll_chance(price,menu[meal_index].base_price,*reputation);
                chance+=type[customer_type_index].tolerance;
               //clamp
                if (chance >95) chance =95;
                if (chance <0) chance =0;
            //roll RNG 
            int roll = rand() % 100;
            if (roll< chance)
            {
               // printf("[DEBUG] Chance: %d%%, Roll: %d\n", chance, roll); //debug line to see chance vs roll
                printf("%s buy a %s.\n", 
                       customer_type[customer_type_index], menu[meal_index].name); //if the RNG hits
                *gold += price;
                menu[meal_index].stock -= 1;
            }

        else
            {
                printf("%s refuses and leaves angrily.\n", customer_type[customer_type_index]); //if RNG doesnt hits
            }
        }
    }
    return;
 }
 
int main(void)
{
    int choice = 0;
    int meat = 10;
    int herbs = 10;
    int spices = 10;
    int gold = 10;
    int reputation = 50;
    int day = 1;
    int price;
    
    struct meal menu[4];

    // Initialize meals
    strcpy(menu[0].name, "Dragon Meat Soup");
    menu[0].stock = 0;
    menu[0].base_price = 5;
    menu[0].req_meat = 5;
    menu[0].req_herbs = 3;
    menu[0].req_spices = 2;
    
    strcpy(menu[1].name, "Lamb Chop");
    menu[1].stock = 0;
    menu[1].base_price = 8;
    menu[1].req_meat = 7;
    menu[1].req_herbs = 2;
    menu[1].req_spices = 3;
    
    strcpy(menu[2].name, "Salad");
    menu[2].stock = 0;
    menu[2].base_price = 3;
    menu[2].req_meat = 0;
    menu[2].req_herbs = 8;
    menu[2].req_spices = 1;
    
    strcpy(menu[3].name, "Premium Steak");
    menu[3].stock = 0;
    menu[3].base_price = 10;
    menu[3].req_meat = 4;
    menu[3].req_herbs = 1;
    menu[3].req_spices = 5;
    
    srand((unsigned)time(NULL));

    do
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
        printf("||       \"Where Legends rest and kings eat\"        ||\n");
        printf("||                                                 ||\n");
        printf("=====================================================\n");
        printf(RESET);
        printf("\nWelcome to Grandlaxr Tavern!, what would you like to do today?\n");
        printf("1. Start a Day\n");
        printf("2. Buy stuff\n");
        printf("3. Manage stock\n");
        printf("4. Search Inventory\n");
        printf("5. Save Game\n");
        printf("6. Load Game\n");
        printf("7. Exit\n");
        printf("Choice: ");
        
     while (1) {
        if (scanf("%d", &choice) != 1) {
        // Not an integer
        while (getchar() != '\n');
        printf("Invalid choice, try again\n");
        continue;
    }

        if (choice < 1 || choice > 7) {
        // Integer but out of range
        printf("Invalid choice, try again\n");
        continue;
    }

    // Valid input
    break;
}

        switch (choice)
        {
        case 1:
        {
           
            int total_stock = 0;
            for (int i = 0; i < 4; i++)
            {
                total_stock += menu[i].stock;
            }

            if (total_stock <= 0)
            {
                printf("You have no stock to sell! Please manage your stock first.\n");
                break;
            }
            else 
            {
            startaDay(menu, &gold, &reputation, day);
            }

            day ++;
            break;
        }
       case 2:
            buyStuff(&gold, &meat, &herbs, &spices);
            break;

        case 3:
        {
            int manage_choice;
            printf("\n=== Manage Stock ===\n");
            printf("1. View Status\n");
            printf("2. Cook a Meal\n");
            printf("Choice: ");
            
            if (scanf("%d", &manage_choice) != 1)
            {
                while (getchar() != '\n') {}
                printf("Invalid input.\n");
                break;
            }
            
            if (manage_choice == 1)
            {
                printf("\n=== Current Status ===\n");
                printf("Gold: %d\n", gold);
                printf("Ingredients - Meat: %d, Herbs: %d, Spices: %d\n", meat, herbs, spices);
                printf("Reputation: %d\n", reputation);
                
                printf("\nMeal Stock:\n");
                for (int i = 0; i < 4; i++)
                {
                    printf("  %s: %d (base price: %dg)\n", 
                           menu[i].name, menu[i].stock, menu[i].base_price);
                }
                recipe_check(meat, herbs, spices);
            }
            else if (manage_choice == 2)
            {
                printf("\n=== Craft Menu ===\n");
                for (int i = 0; i < 4; i++)
                {
                    printf("%d. %s (needs: %d meat, %d herbs, %d spices)\n", 
                           i+1, menu[i].name, menu[i].req_meat, 
                           menu[i].req_herbs, menu[i].req_spices);
                }
                printf("Choice: ");
                
                int meal_choice;
                if (scanf("%d", &meal_choice) != 1 || meal_choice < 1 || meal_choice > 4)
                {
                    while (getchar() != '\n') {}
                    printf("Invalid choice.\n");
                    break;
                }
                
                // Check if enough ingredients
                int idx = meal_choice - 1;
                if (meat >= menu[idx].req_meat && 
                    herbs >= menu[idx].req_herbs && 
                    spices >= menu[idx].req_spices)
                {
                    loading_crafting();
                    meat -= menu[idx].req_meat;
                    herbs -= menu[idx].req_herbs;
                    spices -= menu[idx].req_spices;
                    menu[idx].stock += 1;
                    printf("✓ Successfully crafted 1 %s!\n", menu[idx].name);
                    printf("Remaining: Meat: %d, Herbs: %d, Spices: %d\n", meat, herbs, spices);
                }
                else
                {
                    printf("✗ Not enough ingredients!\n");
                    printf("Need: %d meat, %d herbs, %d spices\n", 
                           menu[idx].req_meat, menu[idx].req_herbs, menu[idx].req_spices);
                    printf("Have: %d meat, %d herbs, %d spices\n", meat, herbs, spices);
                }
            }
            break;
        }
        case 4:
            searchInventory(menu, meat, herbs, spices);
            break;
        case 5:
            saveGame("savegame.dat",day,gold,reputation,meat,herbs,spices,menu);
            break;
        case 6:
            loadGame("savegame.dat",&day,&gold,&reputation,&meat,&herbs,&spices,menu);
            break;
        case 7:
            printf("Exiting the tavern. Safe travels!\n");
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    } while (choice != 7);

    return 0;
}