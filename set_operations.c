/*
Program that computes set operations (union, intersection, difference, etc.)
in C. 

Uses a linked-list as the data structure for the sets.

David Schmidle.

*/


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define SIZE 50

typedef struct node{
    char name[SIZE];
    struct node *next;

} node;


void addNode(node *header, char* name);
void clear(node *header);
void print(node *header);
void printSets(node **sets, int num_sets);
void copy(node *s1, node *s2);
void removeNode(node *header, char* name);
void unionSets(node* destination, node* source1, node* source2);
void intersection(node* destination, node* source1, node* source2);
void symmetricdifference(node* destination, node* source1, node* source2);
void freeSets(node **sets, int num_sets);
int compareTo(char *string1, char *string2);

int main(int argc, char **argv){
    int num_sets, i, user_set_option;
    int source_set, source_set2, destination_set;
    node** sets;
    char user_option;
    char inBuff[SIZE];
    char user_string[SIZE]; /* for adding or removing nodes */
    
    printf("\nEnter the number of sets to create: ");
    fgets(inBuff, SIZE, stdin);
    sscanf(inBuff, "%d", &num_sets);

    sets = malloc(sizeof(node*) * num_sets); /* create num_sets pointers (headers) for linked lists */
    for(i = 0; i < num_sets; i++){
        sets[i] = malloc(sizeof(node));
        strcpy(sets[i]->name, "END");
        sets[i]->next = NULL;
    }

    do{
        printf("\n\nChoose from the menu prompt below:");
        printf("\n\t***** Menu Options *****");
        printf("\n\t%-20s %s", "Add String:", "a or A");
        printf("\n\t%-20s %s", "Remove String:", "r or R");
        printf("\n\t%-20s %s", "Union:", "u or U");
        printf("\n\t%-20s %s", "Intersection:", "i or I");
        printf("\n\t%-20s %s", "Symmetric Difference:", "s or S");
        printf("\n\t%-20s %s", "Copy:", "c or C");
        printf("\n\t%-20s %s", "Clear:", "z or Z");
        printf("\n\t%-20s %s", "Print Set:", "p");
        printf("\n\t%-20s %s", "Print All Sets:", "P");
        printf("\n\t%-20s %s", "Quit:", "q or Q");
        printf("\nSelect an Option: ");
        fgets(inBuff, SIZE, stdin);
        sscanf(inBuff, "%c", &user_option);

        if(user_option == 'a' || user_option == 'A'){
            printf("\nEnter set to add to: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &user_set_option);
            printf("\nEnter string to add: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%s", user_string);


            addNode(sets[user_set_option], user_string);
        }

        
        if(user_option == 'r' || user_option == 'R'){
            printf("\nSelect a set to remove from: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &user_set_option);
            printf("\nSelect a name to remove: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%s", user_string);

            removeNode(sets[user_set_option], user_string);
        }

        
        if(user_option == 'u' || user_option == 'U'){
            printf("\nSelect a set for destination: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &destination_set);
            printf("\nFirst set for union: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set);
            printf("\nSecond set for union: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set2);

            clear(sets[destination_set]);

            unionSets(sets[destination_set], sets[source_set], sets[source_set2]);

        }

        if(user_option == 'i' || user_option == 'I'){
            printf("\nSelect a set for destination: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &destination_set);
            printf("\nFirst set for intersection: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set);
            printf("\nSecond set for intersection: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set2);

            clear(sets[destination_set]);

            intersection(sets[destination_set], sets[source_set], sets[source_set2]);

        }

        if(user_option == 's' || user_option == 'S'){
            printf("\nSelect a set for destination: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &destination_set);
            printf("\nFirst set for symmetric difference: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set);
            printf("\nSecond set for symmetric difference: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set2);

            clear(sets[destination_set]);

            symmetricdifference(sets[destination_set], sets[source_set], sets[source_set2]);
            symmetricdifference(sets[destination_set], sets[source_set2], sets[source_set]);
        }


        if(user_option == 'c' || user_option == 'C'){
            printf("\nEnter set to copy to: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &destination_set);

            printf("\nEnter set to copy from: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &source_set);

            clear(sets[destination_set]);
            copy(sets[destination_set], sets[source_set]);
            printf("\n%s",sets[destination_set]->name);
        }

        if(user_option == 'z' || user_option == 'Z'){
            printf("\nSelect a set to clear: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &user_set_option);
            clear(sets[user_set_option]);

        }

        if(user_option == 'p'){
            printf("\nEnter set to print: ");
            fgets(inBuff, SIZE, stdin);
            sscanf(inBuff, "%d", &user_set_option);
            printf("\nSet %d: ", user_set_option);
            print(sets[user_set_option]);
        }

        if(user_option == 'P'){
            printSets(sets, num_sets);
        }
        
        if(user_option == 'q' || user_option == 'Q'){
            freeSets(sets, num_sets);
            free(sets);
            exit(0);
        }

    } while(1);

    return 0;
}

void addNode(node* header, char* name){
    node* aux;
    while(header != NULL){
        if(compareTo(header->name, "END") == 0){
            aux = malloc(sizeof(node));
            strcpy(aux->name, header->name);
            aux->next = header->next;

            strcpy(header->name, name);

            header->next = aux;
            break;
        }
        else if(compareTo(header->name, name) < 0){
            header = header->next;
                
        } else if (compareTo(header->name, name) > 0){
            aux = malloc(sizeof(node));
            strcpy(aux->name, header->name);
            aux->next = header->next;

            strcpy(header->name, name);

            header->next = aux;
            break;

        } else {
            printf("\n%s already in set", name);
            break;
        }
    }
}

void clear(node* header){
    node *traverser;
    traverser = header;

    if(compareTo(header->name, "END") == 0){
        printf("\nSet is already cleared. returning to menu");
        return;
    }

    while(compareTo(traverser->name, "END") != 0){
        removeNode(traverser, traverser->name);
    }
}

void print(node* header){
    printf("{");
    while(compareTo(header->name, "END") != 0){
        printf("%s", header->name);
        header = header->next;
        if(compareTo(header->name, "END") != 0){
            printf(", ");
        }
    }
    printf("}");
}

void printSets(node **sets, int num_sets){
    int i; 
    for(i = 0; i < num_sets; i++){
        printf("\nSet %d: ", i);
        print(sets[i]);
    }

}

void copy(node *s1, node *s2){
    if(compareTo(s2->name, "END") == 0){
        return;
    } else {
        addNode(s1, s2->name);
        copy(s1->next, s2->next);
    }

}

void removeNode(node *header, char *name){
    node* aux;
    if(compareTo(header->name, "END") == 0){
        printf("\n%s not found in set", name);
        return;
    }
    if(compareTo(header->name, name) == 0){
        aux = header->next;
        strcpy(header->name, aux->name);
        header->next = aux->next;
        free(aux);
        return;
    } else {
        removeNode(header->next, name);
    }

}

void unionSets(node* destination, node* set1, node* set2){
    if((compareTo(set1->name, "END") == 0) && (compareTo(set2->name, "END") == 0)){
        /* both sets are empty */
        return;
    }

    else if(compareTo(set1->name, "END") == 0 && (compareTo(set2->name, "END") != 0)){
        /* set1 is empty but set2 still has content */
        addNode(destination, set2->name);
        unionSets(destination, set1, set2->next);
    }

    else if(compareTo(set2->name, "END") == 0 && (compareTo(set1->name, "END") != 0)){
        /* set2 is empty but set1 still has content */
        addNode(destination, set1->name);
        unionSets(destination, set1->next, set2);
    }

    else if(compareTo(set1->name, set2->name) == 0){
        /* set1 and set2 name currently equal, only adds one name to destination */
        addNode(destination, set1->name);
        unionSets(destination, set1->next, set2->next);

    } else if (compareTo(set1->name, set2->name) < 0){
        /* adds alpbetically */
        addNode(destination, set1->name);
        unionSets(destination, set1->next, set2);
    } else { 
        /* adds alpbetically */
        addNode(destination, set2->name);
        unionSets(destination, set1, set2->next);
    }

}

void intersection(node* destination, node* set1, node* set2){
    if(compareTo(set1->name, "END") == 0 || compareTo(set2->name, "END") == 0){
        /* both sets empty */
        return;
    }
    else if(compareTo(set1->name, set2->name) == 0){
        addNode(destination, set1->name);
        intersection(destination, set1->next, set2->next);
    }
 
    else if(compareTo(set1->next->name, "END") == 0){
        intersection(destination, set1, set2->next);
    }

    else if(compareTo(set2->next->name, "END") == 0){
        intersection(destination, set1->next, set2);
    }

    else {
        intersection(destination, set1, set2->next);
    }

}

void symmetricdifference(node* destination, node* set1, node* set2){
    node* aux_set2_start = set2;
    while(compareTo(set1->name, "END") != 0 && compareTo(set2->name, "END") != 0){
        if(compareTo(set1->name, set2->name) == 0){
            /* names are equal */
            set1 = set1->next;
            aux_set2_start = set2; 
        } else {
            if(compareTo(set2->next->name, "END") == 0){
                /* set 1 name is unique between set1 and set2 */
                addNode(destination, set1->name);
                set1 = set1->next;
                set2 = aux_set2_start;
            } else {
                /* compare with next item in set2 */
                set2 = set2->next;
            }
        }

    }

}

void freeSets(node **sets, int num_sets){
    node * traverser, * aux;
    int i;
    for(i = 0; i < num_sets; i++){
        traverser = sets[i];
        do{
            aux = traverser->next;
            printf("freeing %s, ", traverser->name);
            free(traverser);
            traverser = aux;
        }while(traverser != NULL);
    }
}

int compareTo(char *string1, char *string2){
    int i;
    for(i = 0; i < strlen(string1); i++){
        if(tolower(string1[i]) < tolower(string2[i])){
            return -1;
        } if(string1[i] > string2[i]){
            return 1;
        }
    }
    return 0;

}

