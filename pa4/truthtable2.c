#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct val {
    char *var;
    int hit;    
    int index;
};

struct gate {
    int kind;
    int size; 
    int *params; 
    struct gate* next;
};

int power(int x){
    
    int product = 1;
    for(int i = 0; i<x;i++){
        product = product * 2;
    }
    return product;
}

int main(int argc, char **argv) {    
    char *filename = argv[1];

    FILE *fp;
    fp = fopen(filename, "r");
//    char inputWord[20];
  //  char outputWord[20];
    char var[17];
    int numInput = 0;
    int numOutput = 0;
    int numValues = 0;
    int size;
    //fscanf(fp,"%16s ",inputWord);
    fscanf(fp,"%*s %d",&numInput);
    //printf("%d\n",numInput);
    //struct val *values =  malloc(numInput*sizeof(struct val));
    struct val *values;
    values =  (struct val*)malloc(numInput*sizeof(struct val));
    //values->var = (char*)malloc(17*sizeof(char));

    size = numInput*sizeof(struct val);
    
    
    for(int i = 0; i<numInput; i++){
        
        // char *temp = var;
        // printf("%s",temp);
        struct val* add = (struct val*)malloc(sizeof(struct val)); 
        add->var = (char*)malloc(17*sizeof(char));
        add->hit = 1;
        add->index = i;
        fscanf(fp," %16s",add->var);
        values[i].var = add->var;
        values[i].index = add->index;
        values[i].hit = add->hit;
        // printf("%s",values[i].var);
        //printf(".%s. ",values[0].var);
        numValues++;
    }
    
    //fscanf(fp,"%16s ",outputWord);
    fscanf(fp,"%*s %d",&numOutput);
    //printf("%d",numOutput);
    int ass = numOutput;
    //printf(",%s, ",values[0].var);
    //printf(",%s, ",values[1].var);

    struct val* temp = values;
    values = (struct val*)malloc(size+numOutput*sizeof(struct val));
    //printf("num%d",numValues);
    memcpy(values, temp,numValues*sizeof(struct val));
    //values = realloc(values,size+numOutput*sizeof(struct val));

    // printf("pee");
    // printf(".%s. ",values[0].var);
    // printf(".%d. ",values[0].index);
    // printf("pee");
    // printf(".%s. ",values[1].var);
    // printf(".%d. ",values[1].index);
    size = size+numOutput*sizeof(struct val);

    for(int i = 0; i<numOutput; i++){
        //fscanf(fp," %16s",var);
        //values[i + numInput].var = var;
        //values[i + numInput].hit = 1;
        //printf("%s",values[i].var);

        struct val* add = (struct val*)malloc(sizeof(struct val)); 
        add->var = (char*)malloc(17*sizeof(char));
        add->hit = 1;
        add->index = i + numInput;
        fscanf(fp," %16s",add->var);
        values[i + numInput].var = add->var;
        values[i + numInput].index = add->index;
        values[i + numInput].hit = add->hit;
        // printf("%s",values[i+numInput].var);
        //printf(".%s. ",values[0].var);
        numValues++;
    }

    // printf("\npee\n");
    //int both = numInput+numOutput;
    int param = 0;
    char gateName[20];
    gateName[0] = 'z';
    gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
    
    struct gate* first;
    first = (struct gate*)malloc(sizeof(struct gate));
    first->params = (int*)malloc(sizeof(int));
    first->size = 0;
    first->next = NULL;
    first->kind = -1;
    first->params[0] = -1; 
    struct gate *head = first;
    
    
    //printf("%d",head->kind);
    //printf("%d",head->params[0]);
    //printf("\n");
    while(fscanf(fp,"%11s",gateName)!=EOF){
        //printf("poo");
        //printf("%s",gateName);
        while(head->next!=NULL){
            
           head = head->next;
            
        }
        //AND 1
        if(gateName[0]=='A'){
            
            struct gate* ANDgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            ANDgate = (struct gate*)malloc(sizeof(struct gate));
            ANDgate->params = (int*)malloc(3*sizeof(int));
            
            //printf("%d",both);
            ANDgate->kind = 1;
            // printf("|%d| ",ANDgate->kind);
            ANDgate->size = 0;
            ANDgate->next = NULL;
            
            for(int j = 0; j<3; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = (struct val*)malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
//                     char pee[17];
// strcpy(pee,var);
                    strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    ANDgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",ANDgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    ANDgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",ANDgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = ANDgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //NOT 0
        else if(gateName[2]=='T'){
            
            struct gate* NOTgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            NOTgate = (struct gate*)malloc(sizeof(struct gate));
            NOTgate->params = (int*)malloc(2*sizeof(int));
            
            //printf("%d",both);
            NOTgate->kind = 0;
            // printf("|%d| ",NOTgate->kind);
            NOTgate->size = 0;
            NOTgate->next = NULL;
            
            for(int j = 0; j<2; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
        //                     char pee[17];
                // strcpy(pee,var);
                    strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    NOTgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",NOTgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    NOTgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",NOTgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = NOTgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //OR 2
        else if(gateName[0]=='O'){
            
            struct gate* ORgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            ORgate = (struct gate*)malloc(sizeof(struct gate));
            ORgate->params = (int*)malloc(3*sizeof(int));
            
            //printf("%d",both);
            ORgate->kind = 2;
            // printf("|%d| ",ORgate->kind);
            ORgate->size = 0;
            ORgate->next = NULL;
            
            for(int j = 0; j<3; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
//                     char pee[17];
// strcpy(pee,var);
strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    ORgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",ORgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    ORgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",ORgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = ORgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }
        
        //NAND 3
        else if(gateName[2]=='N'){
            
            struct gate* NANDgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            NANDgate = (struct gate*)malloc(sizeof(struct gate));
            NANDgate->params = (int*)malloc(3*sizeof(int));
            
            //printf("%d",both);
            NANDgate->kind = 3;
            // printf("|%d| ",NANDgate->kind);
            NANDgate->size = 0;
            NANDgate->next = NULL;
            
            for(int j = 0; j<3; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
//                     char pee[17];
// strcpy(pee,var);
strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    NANDgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",NANDgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    NANDgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",NANDgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = NANDgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //NOR 4
        else if(gateName[0]=='N'&&gateName[2]=='R'){
            
            struct gate* NORgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            NORgate = (struct gate*)malloc(sizeof(struct gate));
            NORgate->params = (int*)malloc(3*sizeof(int));
            
            //printf("%d",both);
            NORgate->kind = 4;
            // printf("|%d| ",NORgate->kind);
            NORgate->size = 0;
            NORgate->next = NULL;
            
            for(int j = 0; j<3; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
//                     char pee[17];
// strcpy(pee,var);
strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    NORgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",NORgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    NORgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",NORgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = NORgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //XOR 5
        else if(gateName[0]=='X'){
            
            struct gate* XORgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            XORgate = (struct gate*)malloc(sizeof(struct gate));
            XORgate->params = (int*)malloc(3*sizeof(int));
            
            //printf("%d",both);
            XORgate->kind = 5;
            // printf("|%d| ",XORgate->kind);
            XORgate->size = 0;
            XORgate->next = NULL;
            
            for(int j = 0; j<3; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
//                     char pee[17];
// strcpy(pee,var);
strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    XORgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",XORgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    XORgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",XORgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = XORgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //DECODER 6
        else if(gateName[0]=='D'){
            int numSelect;
            fscanf(fp," %d",&numSelect); 

            struct gate* DECODERgate;
            int siz = numSelect+power(numSelect);
            DECODERgate = (struct gate*)malloc(sizeof(struct gate));
            DECODERgate->params = (int*)malloc(siz*sizeof(int));
            
            //printf("%d",both);
            DECODERgate->kind = 6;
            // printf("|%d| ",DECODERgate->kind);
            DECODERgate->size = numSelect;
            DECODERgate->next = NULL;
            
            for(int j = 0; j<siz; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
                    // char pee[17];
                    // strcpy(pee,var);
                    strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    DECODERgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",DECODERgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    DECODERgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",DECODERgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = DECODERgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //MULTIPLEXER 7
        else if(gateName[0]=='M'){
            int numSelect;
            fscanf(fp," %d",&numSelect);

            struct gate* MULTIPLEXERgate;
            int siz = 1+numSelect+power(numSelect);
            MULTIPLEXERgate = (struct gate*)malloc(sizeof(struct gate));
            MULTIPLEXERgate->params = (int*)malloc(siz*sizeof(int));
            
            //printf("%d",both);
            MULTIPLEXERgate->kind = 7;
            // printf("|%d| ",MULTIPLEXERgate->kind);
            MULTIPLEXERgate->size = numSelect;
            MULTIPLEXERgate->next = NULL;
            
            for(int j = 0; j<siz; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                

                // printf("%d ",numValues);
                int bool = -1;
                //printf("%s  ",var);
                
                for(int i = 0; i<numValues; i++){
                    //printf(" ---%s %s--- \n",var,values[i].var);

                    // if(strncmp(var,"1",4) == 0){
                    //     //printf("cokckc");
                    //     var[0] = 'f';
                    //     var[1] = 'u';
                    //     var[2] = 'c';
                    //     var[3] = 'k';
                    // }
                    // if(strncmp(var,"0",4) == 0){
                    //     //printf('dickc');
                    //     var[0] = 'c';
                    //     var[1] = 'o';
                    //     var[2] = 'c';
                    //     var[3] = 'k';
                    // }
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strncmp(var,values[i].var,16)==0){
                        //printf("%s  ",var);
                        // printf("shit");
                        bool = i;
                        // printf(" *%s %s* ",var,values[i].var);
                        // printf("  %d %d  ",bool,i);
                        break;
                    }
                }

                

                if(bool==-1){
                    
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
                    // char pee[17];
                    // strcpy(pee,var);

                    strcpy(add->var,var);

                    //printf("(((((%s))))))",add->var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    //printf("%s %d ",values[numValues].var,values[numValues].index);
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    MULTIPLEXERgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",MULTIPLEXERgate->params[param]);
                    //both++;
                    numValues = numValues + 1;
                    //printf("%d ",numValues);
                } else {
                    // printf("-%s-",var);
                    // printf("doodoo");
                    MULTIPLEXERgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",MULTIPLEXERgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = MULTIPLEXERgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }

        //PASS 8
        else {
            
            struct gate* PASSgate;
            //(struct gate*)malloc(sizeof(struct gate));
            //printf("poo");
            //ANDgate->params 
            PASSgate = (struct gate*)malloc(sizeof(struct gate));
            PASSgate->params = (int*)malloc(2*sizeof(int));
            
            //printf("%d",both);
            PASSgate->kind = 8;
            // printf("|%d| ",PASSgate->kind);
            PASSgate->size = 0;
            PASSgate->next = NULL;
            
            for(int j = 0; j<2; j++){
                //printf("shid");
                fscanf(fp," %16s",var);
                // printf("%d ",numValues);
                int bool = -1;
                
                for(int i = 0; i<numValues; i++){
                    
                    // printf(var);
                    // printf("-");
                    // printf(values[i].var);
                    // printf(" dick ");
                    if(strcmp(var,values[i].var)==0){
                        // printf("shit");
                        bool = i;
                        break;
                    }
                }
                if(bool==-1){
                    // printf("crap");
                    //values = realloc(values,size+1*sizeof(struct val));

                    struct val* temp = values;
                    values = malloc(size+1*sizeof(struct val));
                    //printf("num%d",numValues);
                    memcpy(values, temp,numValues*sizeof(struct val));
                    
                    size = size+1*sizeof(struct val);
                    
                    struct val* add = malloc(sizeof(struct val)); 
                    add->var = (char*)malloc(17*sizeof(char));
                    add->hit = 1;
                    add->index = numValues;
                    //char pee[17];
                    //strcpy(pee,var);
                    strcpy(add->var,var);
                    values[numValues].var = add->var;
                    values[numValues].index = add->index;
                    values[numValues].hit = add->hit;
                    
                    // values[both].var = var;
                    // values[both].hit = 1;
                    
                    PASSgate->params[param] = numValues;
                    // printf("-%d-",numValues);
                    // printf("=%d=",param);
                    // printf("(%d) ",PASSgate->params[param]);
                    //both++;
                    numValues++;
                } else {
                    // printf("doodoo");
                    PASSgate->params[param] = bool;
                    // printf(".%d.",bool);
                    // printf(",%d,",param);
                    // printf("(%d) ",PASSgate->params[param]);
                    bool = -1;
                }
                //printf("poo");
                param++;
                //printf("%d",param);
            }
            
            head->next = PASSgate;
            param = 0;
            gateName[0] = 'z';
            gateName[1] = 'z';
            gateName[2] = 'z';
            gateName[3] = 'z';
        }




    
    
    
    }
    //printf("doodko");
    first = first->next;
    int shit = 0;
    int piss = 0;
    int boo = 0;
    int dsaj = 0;
    for(int i = 0; i<numValues; i++){
            char one[17];
            strcpy(one,"1");
            char zero[17];
            strcpy(zero,"0");
            if(strcmp(values[i].var,one)==0){
                //printf("pee");
                values[i].hit = 1;
                boo = 1;
                //printf("%d",i);
                shit = i;
            }
            if(strcmp(values[i].var,zero)==0){
                //printf("poo");
                values[i].hit = 0;
                //printf("%d",i);
                dsaj = 1;
                piss = i;
            }
        }
    // printf("\n");
    //printf("%d ",numValues);
    // printf("%d\n",power(numInput));
    for(int i = 0; i<power(numInput);i++){
        struct gate* gates = first;
        
        int bit;
        int outcome = i;
        int var = numInput-1;
        for(bit = 0; bit<=numInput; bit++){
            if(outcome / power(var) != 0){
                values[bit].hit = 1;
                outcome -= power(var); 
            } else {
                values[bit].hit = 0;
            }
            var--;
        }
//printf("|%d| ",values[0].hit);
        if(boo==1)
        values[shit].hit = 1;
        if(dsaj == 1)
        values[piss].hit = 0;
        
  //      printf("|%d| ",values[0].hit);

        while(gates!=NULL){
            //NOT
            if(gates->kind == 0){
                if(values[gates->params[0]].hit == 0){
                    values[gates->params[1]].hit = 1;
                } 
                if(values[gates->params[0]].hit == 1){
                    values[gates->params[1]].hit = 0;
                }
            }
            //AND
            else if(gates->kind == 1){
                // printf("pee");
                //printf(" -%d %d- ",values[gates->params[0]].hit,values[gates->params[1]].hit);

                if((values[gates->params[0]].hit == 1) && (values[gates->params[1]].hit == 1)){
                    //printf("pee");
                    values[gates->params[2]].hit = 1;
                } else {
                    //printf("poo");
                    values[gates->params[2]].hit = 0;
                }
            }
            //OR
            else if(gates->kind == 2){
                if((values[gates->params[0]].hit == 0) && (values[gates->params[1]].hit == 0)){
                    values[gates->params[2]].hit = 0;
                } else {
                    values[gates->params[2]].hit = 1;
                }
            }
            //NAND
            else if(gates->kind == 3){
                if((values[gates->params[0]].hit == 1) && (values[gates->params[1]].hit == 1)){
                    values[gates->params[2]].hit = 0;
                } else {
                    values[gates->params[2]].hit = 1;
                }
            }
            //NOR
            else if(gates->kind == 4){
                if((values[gates->params[0]].hit == 0) && (values[gates->params[1]].hit == 0)){
                    values[gates->params[2]].hit = 1;
                } else {
                    values[gates->params[2]].hit = 0;
                }
            }
            //XOR
            else if(gates->kind == 5){
                if(values[gates->params[0]].hit == values[gates->params[1]].hit){
                    values[gates->params[2]].hit = 0;
                } else {
                    values[gates->params[2]].hit = 1;
                }
            }
            //DECODER
            else if(gates->kind == 6){
                int nom = gates->size;
                //turn into binary
                int sum = 0;
                for(int i = 0; i<nom;i++){
                    sum = sum + power(i) * values[gates->params[nom-i-1]].hit;
                }
                for(int l = 0; l<power(nom);l++){
                    values[gates->params[nom+l]].hit = 0;
                }
                //values[gates->params[nom+power(nom)-sum-1]].hit = 1;
                values[gates->params[nom+sum]].hit = 1;
                
            }
            //MULTIPLEXER
            else if(gates->kind == 7){
                // printf("     **%d    ",values[5].hit);
                // printf(" -%d %d- ",values[gates->params[0]].hit,values[gates->params[1]].hit);
                
                int nom = gates->size;
                //printf("%d",nom);
                int sum = 0;
                int chosen;
                for(int i = 0; i<nom;i++){
                    sum = sum + power(i) * values[gates->params[power(nom) + nom-i-1]].hit;
                }
                chosen = values[gates->params[sum]].hit;
                // printf(" $%d ",chosen);
                values[gates->params[nom+power(nom)]].hit = chosen;
                // printf("//%d//",gates->params[nom+power(nom)]);
                // printf(" / %d / ",values[gates->params[nom+power(nom)]].hit);
            }
            //PASS
            else {
                values[gates->params[1]].hit = values[gates->params[0]].hit;
            }
            // printf("pp");
            // printf("%d ",gates->kind);
            // printf("%d ",gates->params[0]);
            // printf("%d ",gates->params[1]);
            // printf("%d ",gates->params[2]);
            // printf("pee\n");
            gates = gates->next;
        }
        //printf("%d",numInput);
        //printf("|%d| ",values[0].hit);
        for(int k = 0; k <numInput;k++){
            
            printf("%d ",values[k].hit);
        }
        printf("|");
        // printf(" %d",values[3].hit);
        // printf("----%d----", numOutput);
        for(int l = 0; l <ass;l++){
            //printf("poe");
            printf(" %d",values[l+numInput].hit);
            //printf("cock %d cock",l+numInput);
        }
        printf("\n");
        //printf("%d %d %d | \n",values[0].hit,values[1].hit,values[2].hit);
        //printf("\n\n");
        
    }

}
