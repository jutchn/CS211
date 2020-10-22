#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

typedef struct node {
        int value;
        struct node *left;
        struct node *right;
} Node;

Node* searchbst(Node* head,int value){
    if (head == NULL){ 
        printf("absent\n");
        return head; 
    }
    if (head->value == value){
        printf("present\n");
        return head;
    }

    if (head->value < value) 
       return searchbst(head->right, value); 
    
    return searchbst(head->left, value); 

}

Node *newNode(int value){
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->value = value; 
    temp->left = NULL;
    temp->right = NULL; 
    return temp; 
}

Node* addbst(Node* node, int value){
    if (node == NULL) {
        printf("inserted\n");
    return newNode(value); 
    }

    if (value < node->value) 
        (node->left)  = addbst(node->left, value); 
    else if (value > node->value) 
        (node->right) = addbst(node->right, value);   
    else {
        printf("not inserted\n");
        return node;  
    }
    return node; 

}
Node * inordpred(Node* head){
    Node* temp = head;
    while(temp && temp->left != NULL){
        temp = temp->left;
    } 
    return temp;
}

Node* delbst(Node* head, int value){
    if(head == NULL){
        printf("absent\n");
        return head;
    }
    if (value < head->value) {
        head->left = delbst(head->left,value);
    } else if (value > head->value) {
        head->right = delbst(head->right,value);
    } else {
        if(head->left == NULL){
            Node *temp = head->right;
            free(head);
            printf("deleted\n");
            return temp;
        } else if(head->right == NULL) {
            Node *temp = head->left;
            free(head);
            printf("deleted\n");
            return temp;
        }
        Node* temp = inordpred(head->right);
        head->value = temp->value;
        head->right = delbst(head->right, temp->value);
        free(temp);
    }
    return head;
}



void printbst(Node* head){
    //printf("aa\n");
    if(head != NULL){
        printf("(");
        printbst(head->left);
        printf("%d",head->value);
        printbst(head->right);
        printf(")");
    } //else {printf("bb");}
}

int main(int argc, char **argv) {

    char ispd[6];
    int data;
    Node* head = NULL;
    while (scanf("%s",ispd) != EOF){
            if(*ispd != 'p'){
               scanf("%d",&data);
            }         
            if(*ispd == 'f'){
               break;
            }
            if(*ispd == 'i'){
               //printf("|i|\n");
               head = addbst(head,data);
            } else if(*ispd == 's'){
               //printf("|s|\n");
               searchbst(head, data);
            } else if(*ispd == 'p'){
               //printf("|p|\n");
               printbst(head);
               printf("\n");
            } else if(*ispd == 'd'){
               //printf("|d|\n");
               head = delbst(head, data);
            } 
    }//scanf("%*[^\n]");
}
