#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct node {
        int value;
        struct node *next;
} Node;

void delete(Node **head, int value, int *size) {
    Node *temp = malloc(sizeof(Node));
    if(*head == NULL){
        return;
    }
    temp = *head; 
    if(temp->value == value){
        *head = temp->next;
        *size = *size - 1;
    //  free(temp);
    } else {
        while(temp->next != NULL){
            if(temp->next->value == value){
                temp->next = temp->next->next;
                *size = *size - 1;
            } else {
                temp = temp->next;
            } 
        }
        //printf("|%d|\n", *size);
        //*size = *size + 1;
        //printf("[%d]\n", *size);

    }   
}
void sortedInsert(Node** head, Node* newnode){
    Node* temp;
    if(*head == NULL || (*head)->value >= newnode->value){
        newnode->next = *head;
        *head = newnode;
    } else {
        temp = *head;
        while (temp->next!=NULL&&temp->next->value < newnode->value){
            temp = temp->next;
        }
        newnode->next=temp->next;
        temp->next=newnode;
    }
}

void printList(Node *head) 
{ 
    Node *temp = head; 
    while(temp != NULL) 
    { 
        printf(" %d", temp->value); 
        temp = temp->next; 
    } 
    //free(temp);
} 
void removeDupes(Node* head, int *size){
    Node* temp = head;
    Node* next;
    if(temp == NULL)
    return;
    while(temp->next!=NULL){
        if(temp->value == temp->next->value){
            next = temp->next->next;
            free(temp->next);
            temp->next = next;
            *size = *size - 1;
        } else {
            temp = temp->next;
        }
    }
}

int main(int argc, char **argv) {
    char iord[6];
    int size = 0;
    int data;
//    char *filename = argv[1];
    //printf("%s\n",filename);
//    FILE *fp;
    Node* head = NULL;
//    fp = fopen(filename, "r");
    
//    if(fp == NULL){
        //printf("duck");
//        perror(filename);
//        return 0;
//    }
    while (scanf("%s %d",iord, &data) != EOF){
        //printf("|%s| |%d|\n",iord, data);
        if(*iord == 'i'){
            //printf("i");
            size++;
            Node *list = malloc(sizeof(Node));
            list->value = data;
            list->next = NULL;
            sortedInsert(&head, list);
            removeDupes(head, &size);
        } else if (*iord == 'd'){
            //printf("d");
            //size--;
            delete(&head, data, &size);
        } //else printf("fuck");
    printf("%d :",size);
    printList(head);
    printf("\n");
    }
    
//    fclose(fp);
}