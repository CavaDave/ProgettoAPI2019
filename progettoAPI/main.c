#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 520 //numero totale di entità
#define M 5
#define MAX_ENTITY_LENGHT 100
#define MAX_REL_LENGHT 40
#define ULONG_MAX 0xFFFFFFFFUL

/* Matrici per contare le relazioni
   Liste per i tipi di relazioni e un'altra per le entità */

/*
Salvataggio di una relazione

Hashmap per la corrispondenza chiave->nome entità e valore->posizione
   2 strutture:
   - hash per accesso diretto alla posizione dato il nome testuale entità
   - array N con i nomi testuali.
Matrice per ogni tipo di relazione <-


Calcolo del numero massimo di relazioni per output
Tengo traccia in una struttura o listaEntity delle entità con il numero maggiore di
relazioni entranti, aggiornandolo.

*/

// listaEntity dei nomi testuali entità + valore MAX da aggiornare
typedef struct s_list_entity{
    char name_entity[MAX_ENTITY_LENGHT+1];
    struct s_list_entity *next;
} t_list_entity;

// listaEntity delle relazioni
typedef struct s_list_rel{
    char name_rel[MAX_REL_LENGHT+1];
    struct s_list_rel *next;
} t_list_rel;

typedef struct output {
    t_list_entity *entity;
    t_list_rel *rel;
    int max;
} t_output;

typedef struct entity_coda {
    t_list_entity* entita;
    int pos;
} t_entity_coda;

// HashMap

struct node {
    char key[MAX_ENTITY_LENGHT+1];
    int val;
    struct node *next;
};

struct table {
    int size;
    struct node **list;
};

struct table* createTable(int size) {
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);

    int i = 0;
    for (i = 0; i < size; i++)
        t->list[i] = NULL;

    return t;
}

int hashCode(struct table *t, char key[]) {
    unsigned long int hash_val = 0;
    int i = 0;

    /* Convert our string to an integer */
    while (hash_val < ULONG_MAX && i < strlen(key)) {
        hash_val = hash_val << 8;
        hash_val += key[i];
        i++;
    }

    return hash_val % t->size;
}

void insert(struct table *t, char key[], int val) {
    int pos = hashCode(t, key);
    struct node *list = t->list[pos];
//    struct node newNode = (struct node)malloc(sizeof(struct node));
    struct node *temp = list;

    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            temp->val = val;
            return;
        }

        temp = temp->next;
    }

//    strcpy(newNode->key, key);
//    newNode->val = val;
//    newNode->next = list;
//    t->list[pos] = newNode;

    t->list[pos] = (struct node*)malloc(sizeof(struct node));
    t->list[pos]->next = list;
    strcpy(t->list[pos]->key, key);
    t->list[pos]->val = val;
}

int lookup(struct table *t, char key[]) {
    int pos = hashCode(t, key);
    struct node *list = t->list[pos];
    struct node *temp = list;

    while(temp){
        if(strcmp(temp->key, key) == 0){
            return temp->val;
        }

        temp = temp->next;
    }

    return -1; // not found
}

// Fine hash


// Inserisci in coda per l'output
t_list_entity* inserisci_coda (t_list_entity* output, t_list_entity node) {
    t_list_entity *tmp;

    //t_list_entity new=(t_list_entity)malloc(sizeof(t_list_entity));
//    memcpy(new->name_entity, node.name_entity, sizeof(node.name_entity));
//    new->next=NULL;

    if(output==NULL) {
        output = (t_list_entity*)malloc(sizeof(t_list_entity));
        memcpy(output->name_entity, node.name_entity, sizeof(node.name_entity));
        output->next = NULL;
        return output;
    }
//        return new;

    tmp=output;

    /*do {
        if(strcmp(tmp->name_entity, node.name_entity) == 0)
            return output;
        tmp = tmp->next;
    } while (tmp != NULL);*/

    if(tmp->next==NULL) {
        if(strcmp(tmp->name_entity, node.name_entity) == 0)
            return output;
    }

    while(tmp->next!=NULL) {
        if (strcmp(tmp->name_entity, node.name_entity) == 0)
            return output;
        tmp = tmp->next;
    }

//    tmp->next=new;
//    new->next=NULL;

    tmp->next = (t_list_entity*)malloc(sizeof(t_list_entity));
    memcpy(tmp->next->name_entity, node.name_entity, sizeof(node.name_entity));
    tmp->next->next = NULL;
    return output;

//    return output;
}

t_output addrel_case (int matrice[][N], t_list_entity ent2, t_output output, int i, int j) {
    int count = 0, k = 0;
    t_list_entity *tmp=NULL;

    matrice[i][j]=1;

    for (k = 0; k < N; k++) {
        if (matrice[k][j] == 1)
            count++;
    }

    // Comparo count a max di output per la relazione corrente
    // se count < max -> chissene
    // se count = max -> aggiungo ent2 alla lista di entità di output[relazione_corrente] [OPZIONALE ORA: ordino la lista in ordine alfabetico]
    // se count > max -> ent2 è il nuovo massimo

    if(count>=output.max) {
        if(count==output.max) {
            output.entity= inserisci_coda(output.entity, ent2);
        }
        else {
            while(output.entity!=NULL) {
                tmp=output.entity;
                output.entity=output.entity->next;
                free(tmp);
            }
            output.entity= inserisci_coda(output.entity, ent2);
        }
        output.max = count;
    }

    return output;
}


t_list_entity* libera_nodo (t_list_entity* output, t_list_entity node) {
    t_list_entity *tmp=NULL, *prec=NULL;

    tmp=output;
    if(strcmp(tmp->name_entity, node.name_entity)==0) { // TODO strcmp o memcmp -> in caso di reinserimento della stessa entità memcmp non funziona (cambiano gli indirizzi)
        if (tmp->next == NULL) { //l'elemento da eliminare è la testa, ed è anche l'unico elemento
            //free(output);   // TODO ricontrolla questa free, Dennis dice di metterle ma da' errore
            return NULL;
        }
        tmp=tmp->next;    //Se il next è diverso da NULL, allora il massimo era condiviso tra più entità -> ritorno la lista dal secondo elemento
        free(output);
        return tmp;
    }
    else {
        while(tmp!=NULL) {
            if(strcmp(tmp->name_entity, node.name_entity)==0) {
                prec->next = tmp->next;
                free(tmp);
                break;
            }
            prec=tmp;
            tmp = tmp->next;
        }
    }
    return output;
}


t_output delrel_case (int matrice[][N], t_list_entity ent2, t_output output, t_list_entity* listEntity, int posizione, int i, int j) {
    int count=0, k=0;
    t_list_entity *tmp=NULL;

    for (k = 0; k < N; k++) {
        if (matrice[k][j] == 1)
            count++;
    }
    matrice[i][j] = 0;

    if(count==output.max) {
        count=count-1;
        output.entity=libera_nodo(output.entity, ent2);

        if(output.entity!=NULL)
            return output;          //il massimo era condiviso con altre entità
        else {
            // Il massimo era unico, quindi lo ricalcolo
            output.max=output.max-1;
            if(output.max!=0) {
                j = 0;
                while (j <= posizione) {        // posizione è il numero di entità presenti
                    count=0;
                    i = 0;
                    while (i <= posizione) {
                        if (matrice[i][j] == 1)
                            count++;
                        i++;
                    }
                    if (count == output.max) {
                        tmp = listEntity;
                        k = 0;
                        while (k < j) {
                            tmp = tmp->next;
                            k++;
                        }
                        output.entity = inserisci_coda(output.entity, *tmp);
                        output.max = count;
                    }
                    j++;

                }
            }
        }
    }
    return output;
}


//pone la cella della della matrice uguale a 0 e ricalcola il massimo
t_output elimina_cella (int matrice[][N], t_output output, t_list_entity* listEntity, int riga, int colonna, int posizione) {
    t_list_entity *tmp=NULL, *temp=NULL, *tmp1=NULL;
    int count=0, k=0;

    matrice[riga][colonna] = 0;
    tmp=listEntity;
    while(k<colonna) {
        tmp = tmp->next;
        k++;
    }

    //tmp ora è l'entità alla posizione j esima -> valuto se è uno dei massimi
    temp=output.entity;
    while(temp!=NULL) {
        if(strcmp(tmp->name_entity, temp->name_entity)==0) {        // TODO strcmp o memcmp? Stessa cosa di sopra
            //tmp è uno dei massimi -> valuto se è l'unico massimo o è uno dei tanti
            output.entity=libera_nodo(output.entity, *tmp);
            if(output.entity==NULL) {
                // L'output delle entità è una lista vuota -> il massimo era unico, quindi lo ricalcolo da capo
                output.max = output.max - 1;
                if(output.max!=0) {
                    colonna = 0;
                    while (colonna <= posizione) {
                        count=0;
                        riga = 0;
                        while (riga <= posizione) {
                            if (matrice[riga][colonna] == 1)
                                count++;
                            riga++;
                        }
                        // count==massimo corrente della nuova entità j
                        if (count == output.max) {
                            tmp1 = listEntity;
                            k = 0;
                            while (k < colonna) {
                                tmp1 = tmp1->next;
                                k++;
                            }
                            output.entity = inserisci_coda(output.entity, *tmp1);
                            output.max = count;
                        }
                        colonna++;
                    }
                }
                else
                    return output;
            }
        }
        temp=temp->next;
    }
    return output;
}

t_output delent_max (int matrice[][N], t_output output, t_list_entity* listEntity, int posizione) {
    t_list_entity *tmp = NULL, *tmp1 = NULL;
    int count = 0, i = 0, j=0, k=0;

    output.max = 0;
    j = 0;
    while (j <= posizione) {
        count = 0;
        i = 0;
        while (i <= posizione) {
            if (matrice[i][j] == 1)
                count++;
            i++;
        }
        if (count >= output.max) {
            tmp1 = listEntity;
            k = 0;
            while (k < j) {
                tmp1 = tmp1->next;
                k++;
            }
            if (count == output.max) {
                output.entity = inserisci_coda(output.entity, *tmp1);
            }
            else {
                while (output.entity != NULL) {
                    tmp = output.entity;
                    output.entity = output.entity->next;
                    free(tmp);
                }
                output.entity = inserisci_coda(output.entity, *tmp1);
            }
            output.max = count;
        }
        j++;
    }
    return output;
}


// Inserisce in coda nella liste delle entità;
t_entity_coda InserisciInCoda_entity (t_list_entity* listaEntity, t_list_entity entity_input) {
    t_list_entity *nuovo, *tmp;
    int posizione = 0;
    t_entity_coda coda;

    nuovo = (t_list_entity*) malloc(sizeof(t_list_entity));
    memcpy(nuovo->name_entity, entity_input.name_entity, sizeof(entity_input.name_entity));
    nuovo->next=NULL;

    if(listaEntity==NULL) { // la lista è vuota, il nuovo elemento avrà posizione 0
        nuovo->next=NULL;
        coda.entita=nuovo;
        coda.pos=posizione;
        return coda;
    }

    posizione=1;        // c'è almeno un elemento e quindi la posizione da qui in avanti partirà da 1
    tmp=listaEntity;
    while(tmp->next!=NULL) {
        tmp = tmp->next;
        posizione++;
    }

    tmp->next=nuovo;
    nuovo->next=NULL;

    coda.pos=posizione;
    coda.entita=listaEntity;

    return coda;
}


// Inserisce in coda per la lista delle relazioni;
t_list_rel* InserisciInCoda_rel (t_list_rel* listaRelazioni, t_list_rel rel_input) {
    t_list_rel *nuovo=NULL, *temp=listaRelazioni;
    int str_cmp=0;

    nuovo = (t_list_rel*) malloc(sizeof(t_list_rel));
    memcpy(nuovo->name_rel, rel_input.name_rel, sizeof(rel_input.name_rel));
    nuovo->next=NULL;

    if(listaRelazioni==NULL)
        return nuovo;

    str_cmp=strcmp(temp->name_rel, rel_input.name_rel);
    while(temp->next!=NULL) {
        if(str_cmp==0)
            return listaRelazioni;
        else
            temp=temp->next;
        str_cmp=strcmp(temp->name_rel, rel_input.name_rel);
    }
    if(str_cmp!=0)
        temp->next=nuovo;
    nuovo->next=NULL;

    return listaRelazioni;
}

void bubbleSort(t_list_entity* output) {
    int scambio=0;
    t_list_entity *next=NULL, *tmp=NULL, current;

    do {
        scambio=0;
        tmp=output;
        next=output->next;
        while(next!=NULL) {
            if(memcmp(tmp->name_entity, next->name_entity, sizeof(next->name_entity))>0) {
                memcpy(current.name_entity, tmp->name_entity, sizeof(tmp->name_entity));
                memcpy(tmp->name_entity, next->name_entity, sizeof(next->name_entity));
                memcpy(next->name_entity, current.name_entity, sizeof(current.name_entity));
                scambio=1;
            }
            tmp=tmp->next;
            next=next->next;
        }
    }while(scambio==1);
}


int main (int argc, char * argv[]) {
    // Massimi assoluti di ogni relazione
    //int maxAssoluti[M]={0};

    // Matrici delle relazioni e inizializzo
    int mat1[N][N]={{0}};
    int mat2[N][N]={{0}};
    int mat3[N][N]={{0}};
    int mat4[N][N]={{0}};
    int mat5[N][N]={{0}};

    // Array di liste con entità output
    //t_list_entity output_entity[M];

    // Struttura di output
    t_output output[M], current[M], output_reale[M];

    // HashMap
    struct table *tab = createTable(N);

    // Risultato dell'inserimento in coda di ListaEntity (con posizione)
    t_entity_coda coda;

    char input[MAX_ENTITY_LENGHT+1];
    int i=0, j=0, k=0, none = 0 /* se stampa none o i valori */;
    int scambio=0, posizione=0;
    int str_cmp = 0;

    t_list_entity *listaEntity = NULL, *tmp=NULL, *tmp1=NULL;
    t_list_entity ent1, ent2;
    t_list_rel *listaRelazioni=NULL, *temp=NULL;
    t_list_rel rel;



    // leggo l'input
    //printf("Inizio l'esecuzione. Inserire il comando:\n");
    scanf("%s", input);
    //printf("Input rilevato:%s\n",input);


    // Scansiono l'input e in base alla prima scanf identifico il comando
    while(memcmp(input, "end",sizeof("end"))!=0) {
        //printf("Gestisco le azioni in base all'input\n");

        if(memcmp(input, "addent",sizeof("addent"))==0) {		// Primo comando, addent;
            //printf("Inserisci l'entità\n");
            scanf("%s", ent1.name_entity);
            ent1.next = NULL;

            if (lookup(tab, ent1.name_entity) == -1) {
                coda = InserisciInCoda_entity(listaEntity, ent1);
                posizione=coda.pos;
                listaEntity=coda.entita;
                insert(tab, ent1.name_entity, posizione);
            }
        }

        if(memcmp(input, "delent", sizeof("delent"))==0) {		// Secondo comando, delent;
            //printf("Inserisci l'entità da eliminare:\n");
            scanf("%s", ent1.name_entity);
            //printf("%s riconosciuta\n", ent1.name_entity);


            if(lookup(tab, ent1.name_entity)==-1){
                //printf("La listaEntity è vuota oppure l'entità non esiste\n");
            }
            else {
                i=lookup(tab, ent1.name_entity);
                //printf("La posizione è %d\n", i);

                tmp = listaEntity;
                j = 0;
                while (j < i) {
                    tmp = tmp->next;
                    j++;
                }
                // i corrisponde alla posizione dell'entità da eliminare

                 for(j=0; j<N; j++) {
                    mat1[j][i]=0;
                    mat2[j][i]=0;
                    mat3[j][i]=0;
                    mat4[j][i]=0;
                    mat5[j][i]=0;
                }

                for (j = 0; j < N; j++) {        //elimino le relazioni fissata la riga
                    if(mat1[i][j]==1)
                        output[0]=elimina_cella(mat1, output[0], listaEntity, i, j, posizione);
                    if(mat2[i][j]==1)
                        output[1]=elimina_cella(mat2, output[1], listaEntity, i, j, posizione);
                    if(mat3[i][j]==1)
                        output[2]=elimina_cella(mat3, output[2], listaEntity, i, j, posizione);
                    if(mat4[i][j]==1)
                        output[3]=elimina_cella(mat4, output[3], listaEntity, i, j, posizione);
                    if(mat5[i][j]==1)
                        output[4]=elimina_cella(mat5, output[4], listaEntity, i, j, posizione);

                }

                for(k=0; k<M; k++) {
                    tmp1=output[k].entity;
                    while(tmp1!=NULL) {
                        if (strcmp(tmp->name_entity, tmp1->name_entity) == 0) {
                            output[k].entity=libera_nodo(output[k].entity, *tmp);
                            if(output[k].entity==NULL) {
                                switch (k) {
                                    case 0: output[0]=delent_max(mat1, output[0], listaEntity, posizione);
                                            break;
                                    case 1: output[1]=delent_max(mat2, output[1], listaEntity, posizione);
                                            break;
                                    case 2: output[2]=delent_max(mat3, output[2], listaEntity, posizione);
                                            break;
                                    case 3: output[3]=delent_max(mat4, output[3], listaEntity, posizione);
                                            break;
                                    case 4: output[4]=delent_max(mat5, output[4], listaEntity, posizione);
                                            break;
                                    default: break;
                                }
                            }

                        }
                        tmp1=tmp1->next;
                    }
                }

                insert(tab, ent1.name_entity, -1);
               // memcpy(ent1.name_entity, "$$$", sizeof("$$$"));
               // memcpy(tmp->name_entity, "$$$", sizeof("$$$"));
               // insert(tab, ent1.name_entity, i);

                //free(tmp);
            }
        }


        if(memcmp(input, "addrel", sizeof("addrel"))==0) {		// Terzo comando, addrel;
            //printf("comando addrel ricevuto. Inserire la prima entità\n");
            scanf("%s", ent1.name_entity);
            //printf("Inserire la seconda entità\n");
            scanf("%s", ent2.name_entity);

            //printf("look1: %d, look2= %d\n",lookup(tab, ent1.name_entity),  lookup(tab, ent2.name_entity));

            if (lookup(tab, ent1.name_entity) != -1 && lookup(tab, ent2.name_entity) != -1) {
                //printf("Inserire il nome della relazione\n");
                scanf("%s", rel.name_rel);
                //printf("Relazione %s ricevuta\n", rel.name_rel);

                listaRelazioni=InserisciInCoda_rel(listaRelazioni, rel);
                rel.next=NULL;

                temp=listaRelazioni;
                k=0;
                //str_cmp = memcmp(rel.name_rel, temp->name_rel, sizeof(MAX_REL_LENGHT));
                while(temp->next!=NULL) {
                    if(strcmp(rel.name_rel, temp->name_rel)!=0){
                        temp = temp->next;
                        k++;
                        //str_cmp = memcmp(rel.name_rel, temp->name_rel, sizeof(MAX_REL_LENGHT));
                    }
                    else
                        break;

                }
                //printf("k=%d\n", k);

                i=lookup(tab, ent1.name_entity);
                j=lookup(tab, ent2.name_entity);

                switch(k){
                    case(0):
                        if(mat1[i][j]==0)
                            output[k] = addrel_case(mat1, ent2, output[k], i, j);
                        break;
                    case(1):
                        if(mat2[i][j]==0)
                            output[k] = addrel_case(mat2, ent2, output[k], i, j);
                        break;
                    case(2):
                        if(mat3[i][j]==0)
                            output[k] = addrel_case(mat3, ent2, output[k], i, j);
                        break;
                    case(3):
                        if(mat4[i][j]==0)
                            output[k] = addrel_case(mat4, ent2, output[k], i, j);
                        break;
                    case(4):
                        if(mat5[i][j]==0)
                            output[k] = addrel_case(mat5, ent2, output[k], i, j);
                        break;
                    default:
                        break;
                }
            }
        }


        if(memcmp(input, "delrel", sizeof("delrel"))==0) {		// Quarto comando, delrel;
           // printf("comando %s ricevuto\nInserire la prima entità\n", input);
            scanf("%s", ent1.name_entity);
           // printf("Inserire la seconda entità\n");
            scanf("%s", ent2.name_entity);
           // printf("Inserire il nome della relazione\n");
            scanf("%s", rel.name_rel);
           // printf("Relazione %s riconosciuta\n", rel.name_rel);

            if (lookup(tab, ent1.name_entity) != -1 && lookup(tab, ent2.name_entity) != -1) {
                temp=listaRelazioni;
                k=0;
                while(temp!=NULL) {
                    if(strcmp(rel.name_rel, temp->name_rel)!=0){
                        temp = temp->next;
                        k++;
                    }
                    else
                        break;
                }

                if(temp!=NULL) {
                 // printf("k=%d\n", k);

                    i=lookup(tab, ent1.name_entity);
                    j=lookup(tab, ent2.name_entity);

                    switch (k) {
                        case (0):
                            if(mat1[i][j]==1)
                                output[k] = delrel_case(mat1, ent2, output[k], listaEntity, posizione, i, j);
                            break;
                        case (1):
                            if(mat2[i][j]==1)
                                output[k] = delrel_case(mat2, ent2, output[k], listaEntity, posizione, i, j);
                            break;
                        case (2):
                            if(mat3[i][j]==1)
                                output[k] = delrel_case(mat3, ent2, output[k], listaEntity, posizione, i, j);
                            break;
                        case (3):
                            if(mat4[i][j]==1)
                                output[k] = delrel_case(mat4, ent2, output[k], listaEntity, posizione, i, j);
                            break;
                        case (4):
                            if(mat5[i][j]==1)
                                output[k] = delrel_case(mat5, ent2, output[k], listaEntity, posizione, i, j);
                            break;
                        default:
                            break;
                    }
                }
            }
        }


        if(memcmp(input, "report", sizeof("report"))==0) {		// Quinto comando, report OUTPUT;
            i = 0;

            temp = listaRelazioni;

            while(temp!=NULL) {
                i++;
                temp=temp->next;
            }
            // i corrisponde al numero di tipi di relazioni esistenti

            temp=listaRelazioni;
            for(k=0; k<i && temp!=NULL; k++) {
                output_reale[k].max = output[k].max;
                output_reale[k].entity=output[k].entity;
                output_reale[k].rel=temp;
                //output_reale[k].rel=InserisciInCoda_rel(output_reale[k].rel, *temp); //  TODO: DENNIS DICE CHE E' MEGLIO
                temp = temp->next;
            }

            if(listaRelazioni==NULL || listaRelazioni->next==NULL)
                ;
            else {
                do {
                    scambio = 0;
                    for(k=0; k<i-1; k++) {
                        current[k] = output_reale[k];
                        str_cmp=memcmp(output_reale[k].rel, output_reale[k+1].rel, sizeof(output_reale[k+1].rel->name_rel));
                        if(str_cmp>0) {
                            output_reale[k]=output_reale[k+1];
                            output_reale[k+1]=current[k];
                            scambio=1;
                        }
                    }
                } while(scambio==1);
            }

            if(listaEntity!=NULL)
                for (k = 0; k < M; k++) {
                    if (output_reale[k].entity != NULL && output_reale[k].entity->next != NULL)
                            bubbleSort(output_reale[k].entity);
                }
            

            none = 0;

            for(k=0;k<M;k++){
                if(output_reale[k].max!=0){
                    none = 1;
                    break;
                }
            }

            if(none==0) {
                printf("none");
            }
            else {
                //le relazioni sono già in ordine, stampo in base al valore del massimo
                for(k=0;k<M;k++)
                    if(output_reale[k].max>0) {
                        //printf("%s ", output_reale[k].rel->name_rel);
                        fputs(output_reale[k].rel->name_rel, stdout);
                        fputs(" ", stdout);
                        tmp=output_reale[k].entity;
                        while(tmp!=NULL) {
                            //printf("%s ", tmp->name_entity);
                            fputs(tmp->name_entity, stdout);
                            fputs(" ", stdout);
                            tmp=tmp->next;
                        }
                        printf("%d; ", output_reale[k].max);
                    }
            }
            printf("\n");
        }

       // printf("Inserisci il comando successivo:\n");
        scanf("%s", input);

    }
    return 0;
}

