/* CS 211 PA4
 * Created for: jc2549
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct line {
    int valid;    
    int age;
    unsigned long int id;
}Line;

typedef struct set {
    Line *line;
    //int index;
}Set;

int main(int argc, char **argv)
{
    int cachesize = atoi(argv[1]);
    //
    char *assoc = argv[2];
//    char *policy = argv[3];
    int blocksize = atoi(argv[4]);
    //in bytes
    char *filename = argv[5];

    int pmemread = 0;
    int pmemwrite = 0;
    int pcachehit = 0;
    int pcachemiss = 0;

    int memread = 0;
    int memwrite = 0;
    int cachehit = 0;
    int cachemiss = 0;

    int offsetnum = log(blocksize)/log(2);
    //printf("%d",offsetnum);
    int numsets;
    int numcachelines;
    int setnum; 
    int tagnum;
    unsigned long int address; 
    unsigned long int paddress; 
    char r_or_w[2];

    //int offset;
    int set;
    int pset;
    unsigned long int tag;
    unsigned long int ptag;

    //char discard[10];
    if(strcmp(assoc,"direct")==0){
        numcachelines = 1;
        numsets = cachesize/blocksize;
    } else if (strcmp(assoc,"assoc")==0){
        numcachelines = cachesize/blocksize;
        numsets = 1;
    }else{
        //printf("pee");
        strcpy(assoc,assoc+6*sizeof(char));
        numcachelines = atoi(assoc);
        
        numsets = cachesize/blocksize;
        numsets = numsets/numcachelines;
    }
    //printf("%d ",numsets);
    //printf("%d ",numcachelines);
    setnum = log(numsets)/log(2);
    //printf("%d",setnum);
    tagnum = 48 - setnum - offsetnum;
    
    Set *sets;
    sets = (Set*)malloc(numsets*sizeof(Set));

    Set *psets;
    psets = (Set*)malloc(numsets*sizeof(Set));
    // sets->line = (Line*)malloc(numcachelines*sizeof(Line));
    // printf("pee");
    //printf("%d %d\n",numsets,numcachelines);
    for(int i = 0; i<numsets; i++){
        sets[i].line = (Line*)malloc(numcachelines*sizeof(Line));
        psets[i].line = (Line*)malloc(numcachelines*sizeof(Line));
        //printf("pee");
        //sets[i].index = i;
        for(int j = 0; j<numcachelines; j++){
            //printf("%d %d// ",i,j);
            sets[i].line[j].valid = 0;
            sets[i].line[j].age = 0;
            sets[i].line[j].id = 0;

            psets[i].line[j].valid = 0;
            psets[i].line[j].age = 0;
            psets[i].line[j].id = 0;
        }
    }
    //printf("\n");
    



    FILE *fp;
    fp = fopen(filename, "r");
    int counta = 0;
    int pee = 0;
    while(fscanf(fp,"%*s %s ",r_or_w)==1){
        counta++;
        // if(counta == 8493){



        //     printf("%d %d %d ",pcachemiss,pcachehit,counta);



        //     for(int j = 0; j<numcachelines; j++){
        //         //printf("hi ");
        //         if(psets[0].line[j].age==numcachelines-1){
        //             printf("crud");
        //             printf("%d ",j);
        //         }
        //         if(psets[0].line[j].id==16819221){
                    
        //             printf("cockball");
        //         }
        //     }
        // }
        //printf("{%s}",r_or_w);
        //printf("%s",r_or_w);
        // if(strcmp(r_or_w,"R")!=0 && strcmp(r_or_w,"W")!=0){
        //     printf("opdsakod");
        //     break;
        // }
        //printf("%s ",r_or_w);
        

        fscanf(fp,"%lx",&address);
        //printf("[%d]",num);
        //printf("%llu ",address);
        //address = 281470681743360;
        //printf("[%d %d]",offsetnum,setnum);
        
        //offset = ((1 << offsetnum)-1) & address;
        
        address = address >> offsetnum;
        set = ((1 << setnum)-1) & address;
        tag = address >> setnum; 
        
        paddress = address;
        pset = set;
        ptag = tag;
        //printf("|%d %d|",offset,set);
        //printf("%llu %d %d %d %llu ",address,set,setnum,offsetnum,tag);
        // char buffer [50];
        // itoa(address,buffer,2);
        // printf("%s",buffer);
        //printf("\n",tag);
        int hit = 0;
        int phit = 0;
        //READ
        //printf("(%s)",r_or_w);
        if(strcmp(r_or_w,"R")==0){
            //strcpy(r_or_w,"");
            //printf("[%s]",r_or_w);
            //memread++;
            
            for(int i = 0; i<numcachelines;i++){
                //cache hit
                if(sets[set].line[i].valid == 1 && sets[set].line[i].id == tag){
                    cachehit++;
                    //pcachehit++;
                    //printf("|%llu| ",sets[set].line[i].id);
                    
                    hit = 1;
                } 
                if(psets[pset].line[i].valid == 1 && psets[pset].line[i].id == ptag){
                    //cachehit++;
                    pcachehit++;
                    //printf("|%llu| ",sets[set].line[i].id);     
                    
                    //  if(counta==8492){
                    //      printf("FUCK %d %d %d ",i,counta,pcachehit);
                    //      printf("%d ",psets[pset].line[i].age);
                    //  }
                    // if(counta==8501){
                    //     printf("DIUCK");
                    // }
                    phit = 1;
//                    break;
                } 
            }
            

//cache miss for regular
            if(hit == 0){
                cachemiss++;
                //pcachemiss++;
                memread++;
                

                for(int j = 0; j<numcachelines;j++){
                    if(sets[set].line[j].valid == 1){
                        sets[set].line[j].age++;
                    } else {
                        sets[set].line[j].id=tag;
                        sets[set].line[j].valid = 1;
                        break;
                    }
                    if(sets[set].line[j].age==numcachelines){
                        sets[set].line[j].age=0;
                        sets[set].line[j].id=tag;
                    }
                }
                
            }

            
            if(phit == 0){
                // if(counta==8491){
                //     printf("faihjsopiohafs ");
                // }
                pcachemiss++;                   //one too many at  
                // if(pcachemiss+pcachehit-counta==1){            //1692
                //     printf("pee ");
                //     //printf("d-%d ",counta);
                // }
                // if(pcachemiss+pcachehit-counta==2){            //1692
                //     //printf("balls ");
                //     printf("b-%d %d %d %d| ",pcachemiss,pcachehit,counta,phit);
                //     //printf()
                // }
                pmemread++;
//                if(pmemread>569612){              //3375
  //                      printf("r-%d ",counta);
    //                }
                

                for(int j = 0; j<numcachelines;j++){
                    if(psets[pset].line[j].valid == 1){
                        psets[pset].line[j].age++;
                    } else {
                        psets[pset].line[j].id=ptag;
                        psets[pset].line[j].valid = 1;
                        //printf("%d ",pset);
                        break;
                    }
                    if(psets[pset].line[j].age==numcachelines){
                        psets[pset].line[j].age=0;
                        psets[pset].line[j].id=ptag;
                    }
                }
                //printf("%llu ",paddress);
                paddress = paddress + 1;
                //printf("%llu ",paddress);
                pset = ((1 << setnum)-1) & paddress;
                ptag = paddress >> setnum;
                //printf("%d %llu\n",pset,ptag);

                for(int k = 0; k<numcachelines;k++){
                    if(psets[pset].line[k].valid == 1 && psets[pset].line[k].id == ptag){
                        phit = 1;
//                        break;
                    }
                }
                if(phit == 0){
                    pmemread++;
//                    if(pmemread>569612){          //3375
  //                      printf("p-%d ",counta);
    //                }
                    for(int j = 0; j<numcachelines;j++){
                        if(psets[pset].line[j].valid == 1){
                            psets[pset].line[j].age++;
                        } else {
                            psets[pset].line[j].id=ptag;
                            psets[pset].line[j].valid = 1;
                            //printf("|%d| ",pset);
                        
                            break;
                        }
                        if(psets[pset].line[j].age==numcachelines){
                            psets[pset].line[j].age=0;
                            psets[pset].line[j].id=ptag;
                            
                        }
                    }
                }

            }        
        

                
            






        //WRITE
        } 
        
        else if(strcmp(r_or_w,"W")==0){
            //write hit
            int hit = 0;
            int phit = 0;
            for(int i = 0; i<numcachelines;i++){
                if(sets[set].line[i].id == tag){
                    cachehit++;
                    memwrite++;
                    hit = 1;
                }
                if(psets[pset].line[i].id == ptag){
                    pcachehit++;
                    pmemwrite++;
                    phit = 1;
                    
//                    break;
                }
            }


            if(hit == 0){
                cachemiss++;
                //pcachemiss++;
                memread++;
                memwrite++;
                

                for(int j = 0; j<numcachelines;j++){
                    if(sets[set].line[j].valid == 1){
                        sets[set].line[j].age++;
                    } else {
                        sets[set].line[j].id=tag;
                        sets[set].line[j].valid = 1;
                        break;
                    }
                    if(sets[set].line[j].age==numcachelines){
                        sets[set].line[j].age=0;
                        sets[set].line[j].id=tag;
                    }
                }
                
                }






                if(phit == 0){
                
                pcachemiss++;
                // if(pcachemiss+pcachehit-counta==1){            //1692
                //     printf("shit ");
                //     //printf("d-%d ",counta);
                // }
                // if(pcachemiss+pcachehit-counta==2){            //1692
                //     //printf("dick ");
                //     printf("d-%d %d %d %d| ",pcachemiss,pcachehit,counta,phit);
                // }
                pmemread++;
//                if(pmemread>569612){
  //                      printf("pee");
    //                }
                pmemwrite++;
                

                for(int j = 0; j<numcachelines;j++){
                    if(psets[pset].line[j].valid == 1){
                        psets[pset].line[j].age++;
                    } else {
                        psets[pset].line[j].id=ptag;
                        psets[pset].line[j].valid = 1;
                        //printf("[%d] ",pset);
                        break;
                    }
                    if(psets[pset].line[j].age==numcachelines){
                        psets[pset].line[j].age=0;
                        psets[pset].line[j].id=ptag;
                    }
                }
                paddress = paddress + 1;
                pset = ((1 << setnum)-1) & paddress;
                ptag = paddress >> setnum;

                for(int k = 0; k<numcachelines;k++){
                    if(psets[pset].line[k].valid == 1 && psets[pset].line[k].id == ptag){
                        phit = 1;
//                        break;
                    }
                }
                if(phit == 0){
                    pmemread++;
//                    if(pmemread>569612){
  //                      printf("poo");
    //                }
                    for(int j = 0; j<numcachelines;j++){
                        if(psets[pset].line[j].valid == 1){
                            psets[pset].line[j].age++;
                        } else {
                            psets[pset].line[j].id=ptag;
                            psets[pset].line[j].valid = 1;
                            //printf("/%d/ ",pset);
                            break;
                        }
                        if(psets[pset].line[j].age==numcachelines){
                            psets[pset].line[j].age=0;
                            psets[pset].line[j].id=ptag;
                        }
                    }
                }
                
            }     



            //write miss

        } else {
            printf("SHIT");
        }
        
        // if(pcachemiss+pcachehit-counta==1){            //1692
        //             printf("pee %d %d %d\n",pcachemiss,pcachehit,counta);
        //             //printf("d-%d ",counta);
        //         }
        //         if(pcachemiss+pcachehit-counta==2 && pee == 0){
        //             pee = 1;
        //             printf("cock %d %d %d\n",pcachemiss,pcachehit,counta);
        //             //printf("d-%d ",counta);
        //         }

        //puts("");
        r_or_w[0] = 'p';
    }
    
    //printf("\n");
//printf("count%d",counta);
    printf("Prefetch 0\n");
    printf("Memory reads: %d\n",memread);
    printf("Memory writes: %d\n",memwrite);
    printf("Cache hits: %d\n",cachehit);
    printf("Cache misses: %d\n",cachemiss);
    printf("Prefetch 1\n");
    printf("Memory reads: %d\n",pmemread);
    printf("Memory writes: %d\n",pmemwrite);
    printf("Cache hits: %d\n",pcachehit);
    printf("Cache misses: %d",pcachemiss);

}