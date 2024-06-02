//Omar Shahwan
//Program serves as an inventory tool which uses linked lists made of node structs to add, delete, clear all, print all, or search for different names or values in the inventory

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct node{
    char name[31]; //name of item for the inventory
    int amount;
    struct node* next;
};
struct node* insert(struct node* list);
struct node* delete(struct node* list);
void search(struct node* list);
struct node* clear(struct node* list);
void print_all(struct node* list);


int main() {
    //initializing varibales
    char code;
    int amount;
    struct node* item_list = NULL;

    while (1){
        printf("Operation Code:\ntype 'a' for adding to the list, 's' for searching, 'p' for printing the list, 'd' to delete an item, 'c' to clear the list, and 'q' for quit.\n");
        printf("Select operation: ");
        scanf(" %c", &code);
        code = tolower(code);
        
        switch (code){   //case by case operation scenarios to call on the appropriate function
        case 'a': item_list = insert(item_list);
            break;
        case 's': search(item_list);
            break;
        case 'p': print_all(item_list);
            break;
        case 'd': item_list = delete(item_list);
            break;
        case 'c': item_list = clear(item_list);
            break;
        case 'q': return 0;
        default: for(int num; (num = getchar()) != '\n' && num != EOF;); //clears any remaining characters in the input buffer up to and including the newline character
        printf("Code not valid, try again...\n\n");
            break;
        }
    }    
}

struct node* insert(struct node* list){
    struct node* new = malloc(sizeof(struct node)); //new item being inserted
    if (new == NULL){ //In case of error
        printf("Error found in allocating memory for new item\n\n");
        return list;
    }

    printf("Enter your item name: ");
    scanf(" %30[^\n]", new->name); //Reads up to 30 characters or until newline

    for(int i = 0; i < strlen(new->name); i++) {  // Convert the item name to uppercase
        new->name[i] = toupper(new->name[i]);
    }

    if (list == NULL){
        printf("How many of this item will you be inserting? ");
        if (scanf("%d", &new->amount) != 1 || new->amount < 0) {
            printf("Invalid input! Amount should be a positive number.\n\n");
            free(new);
            while (getchar() != '\n'); // Clear invalid input from buffer
            return list;
        }   
        printf("You now have %d %s\n\n", new->amount, new->name);
        new->next = NULL;
        return new;
    }
    struct node* current = list;
    struct node* previous = NULL;

    while(current != NULL){
        if(strcmp(current->name, new->name) == 0){
            int num;
            char ans;
            printf("%d %s are already in the inventory\n", current->amount, current->name);
            printf("Do you wish to add more of the current item? (y or n) ");
            scanf(" %c", &ans);
            if(ans == 'y' || ans == 'Y'){
                printf("Enter number of items you wish to add: ");
                if(scanf("%d", &num) != 1 || num < 0){
                    printf("Invalid input! Amount should be a positive number.\n\n");
                    while (getchar() != '\n'); // Clear invalid input from buffer
                    return list;
                }
            
                current->amount += num;
                printf("You now have %d %s\n\n", current->amount, current->name);
            }
            printf("\n\n"); //ans == 'n'
            return list;
        }
        previous = current;
        current = current->next;
    }
    //else if strcmp!= 0 after iterating through list
    printf("How many of this item will you be inserting? ");
    if (scanf("%d", &new->amount) != 1 || new->amount < 0) {
        printf("Invalid input! Amount should be a positive number.\n\n");
        free(new);
        while (getchar() != '\n'); // Clear invalid input from buffer
        return list;
    }
    printf("You now have %d %s\n\n", new->amount, new->name);
    
    new->next = current;
    if(previous == NULL)
        return new;
    previous->next = new;
    return list;
}
struct node* delete(struct node* list)
{
    if(list == NULL){
        printf("Inventory is empty, nothing to delete!\n\n");
        return NULL;
    }
    char name[31];
    printf("Enter item you wish to delete: ");
    scanf(" %30[^\n]", name);
    for(int i = 0; i < strlen(name); i++) {  // Convert the item name to uppercase
        name[i] = toupper(name[i]);
    }
    
    struct node* current = list;
    struct node* previous = NULL;
    while(current!=NULL){
        
        if(strcmp(name, current->name) == 0){
        int num;
        printf("There are currently %d of that item. How many would you like to delete? ", current->amount);
        if (scanf("%d", &num) != 1 || num < 0) {
            printf("Invalid input! Amount should be a positive number.\n\n");
            while (getchar() != '\n'); // Clear invalid input from buffer
            return list;
        }
            if(current->amount - num <= 0)
            {
                printf("You have none of that item left, it has been removed from inventory.\n\n");
                if (previous == NULL){
                    list = current->next;
                    free(current);
                    return list;
                }
                previous->next = current->next; //previous != NULL
                free(current);
                return list;
            }
        
        //else if(current->amount - num > 0)
        current->amount -= num;
        printf("You now have %d %s items left\n\n", current->amount, current->name);
        return list;
        }
        previous = current;
        current=current->next;
    }
    //else if strcmp!= 0 after iterating through list
    printf("Item not found, please try again.\n\n");
    return list;
}

void search(struct node* list){
    if (list == NULL){
        printf("No items currently in inventory\n\n");
        return;
    }
    char name[31];
    printf("Enter item you wish to search for: ");
    scanf(" %30[^\n]", name);
    
    for(int i = 0; i < strlen(name); i++) {  // Convert the item name to uppercase
        name[i] = toupper(name[i]);
    }

    struct node* current = list;
    while(current!=NULL){
        if(strcmp(name, current->name) == 0){
            printf("Item found! There are currently %d of that item.\n\n", current->amount);
            return;
        }
        current=current->next;
    }
    //else if strcmp!= 0
    printf("Item not found, please try again.\n\n");
    return;
        
}

struct node* clear(struct node* list){
    struct node* temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
    printf("Inventory cleared successfully!\n\n");
    return NULL;
}
void print_all(struct node* list){
    if (list == NULL) {
        printf("Inventory is empty.\n\n");
        return;
    }

    struct node *current = list;
    struct node *index = NULL;
    struct node temp;

    while (current != NULL) {
        index = current->next;
        while (index != NULL) { //nested loop to organize linked list into alphabetical order when printed
            if (strcasecmp(current->name, index->name) > 0) {
                //Swap amounts
                temp.amount = current->amount;
                current->amount = index->amount;
                index->amount = temp.amount;
                //Swap names
                strcpy(temp.name, current->name);
                strcpy(current->name, index->name);
                strcpy(index->name, temp.name);
            }
            index = index->next;
        }
        current = current->next;
    }
    current = list;
    printf("Name\tAmount\n");
    while (current != NULL) {
        printf("%s\t%d\n", current->name, current->amount);
        current = current->next;
    }
    printf("\n\n");
}