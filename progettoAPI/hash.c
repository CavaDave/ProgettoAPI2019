#include <stdio.h>
#include <stlib.h>

#define N 520 //numero totale di entità
#define M 5
#define MAX_ENTITY_LENGHT 100
#define MAX_REL_LENGHT 40

struct node {
    char key[MAX_ENTITY_LENGHT+1];
    int val;
    struct node *next;
} node;

struct s_table {
    int size;
    struct node **list;
} t_table;

struct t_table *createTable(int size) {
    int i;
    struct t_table *t=(struct t_table*)malloc(sizeof(struct t_table));
    t->size=size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    for(i=0; i<size; i++)
        t->list[i]=NULL;
    return t;
}

int hashCode (struct table *t, int key) {
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}

void insert(struct table *t,int key,int val){
    int pos= hashCode(t, key);
    struct node *list=t->list[pos];
    struct node *temp=list;

    while(temp) {
        if (temp->key == key) {
            temp->val = val;
            return;
        }
        temp = temp->next;
    }

    struct node *newNode= (struct node*)malloc(sizeof(struct node));
    newNode->key=key;
    newNode->val=val;
    newNode->next=list;
    t->list[pos]=newNode;
}


int lookup(struct table *t, int key) {
    int pos=hashCode(t,key);
    struct node *list=t->list[pos];
    struct node *temp=list;
    while(temp) {
        if(temp->key==key)
            return temp->val;
        temp=temp->next;
    }
    return -1;
}

int main () {
    struct table *t= createTable(N);
    insert(t, entità, massimo);
    lookup(t, entita);
    return 0;
}


t_max_calc_results calcolo_maxassoluto (int max_assoluto, int massimo, t_list_entity entity_output, t_list_entity ent, table *tab) {
    int w=0, str_cmp=0;
    t_max_calc_results result;
    result.max = 0;
    t_list_entity temp;


            if (massimo >= max_assoluto) {
                if (massimo == max_assoluto) {  //il massimo dell'array è uguale al massimo in entrata
                    memcpy(temp.name_entity, ent.name_entity, sizeof(ent.name_entity));
                    str_cmp=memcmp(entity_output.name_entity, ent.name_entity, sizeof(ent.name_entity));
                    if (str_cmp < 0)
                        strcat(strcat(entity_output.name_entity, " "), ent.name_entity);
                    if (str_cmp > 0){
                        strcat(strcat(temp.name_entity, " "), entity_output.name_entity);
                        memcpy(entity_output.name_entity, temp.name_entity, sizeof(temp.name_entity));
                        concat = 1;
                    }
                } else {
                    memcpy(entity_output.name_entity, ent.name_entity, sizeof(ent.name_entity));   //l'entità con più relazioni entranti sarà l'elemento corrente
                }
                max_assoluto = massimo;
            }
        }


    result.max = max_assoluto;
    result.entity = entity_output;

    return result;
}


for(m=0;m<M;m++){
if(matriceMassimi[m][j] == maxAssoluti[m] && matriceMassimi[m][j]!=0){
matriceMassimi[m][j] = 0;
max_results = calcolo_maxassoluto(maxAssoluti[m], matriceMassimi[m], output_entity[m], listaEntity);
maxAssoluti[m] = max_results.
max;
output_entity[m] = max_results.
entity;
}
else
matriceMassimi[m][j] = 0; //pongo a 0 il massimo corrispondente all'entità in posizione j
}



t_max_calc_results calcolo_maxassoluto (int max, int max_array[], t_list_entity entity_output, t_list_entity *listaEntity) {
    int w=0, str_cmp=0;
    t_max_calc_results result;
    result.max = 0;
    t_list_entity temp;
    int concat = 0;

    while(listaEntity!=NULL && w<N) {
        if(memcmp(entity_output.name_entity, "", sizeof(""))==0) {
            memcpy(entity_output.name_entity, listaEntity->name_entity, sizeof(listaEntity->name_entity));
            if(max_array[w]!=0)
                max=max+1;
        }
        else{
            if (max_array[w] >= max) {
                if (max_array[w] == max) {  //il massimo dell'array è uguale al massimo in entrata
                    memcpy(temp.name_entity, listaEntity->name_entity, sizeof(listaEntity->name_entity));
                    str_cmp=memcmp(entity_output.name_entity, listaEntity->name_entity, sizeof(listaEntity->name_entity));
                    if (str_cmp < 0)
                        strcat(strcat(entity_output.name_entity, " "), listaEntity->name_entity);
                    if (str_cmp > 0){
                        strcat(strcat(temp.name_entity, " "), entity_output.name_entity);
                        memcpy(entity_output.name_entity, temp.name_entity, sizeof(temp.name_entity));
                        concat = 1;
                    }
                } else {
                    memcpy(entity_output.name_entity, listaEntity->name_entity,sizeof(listaEntity->name_entity));   //l'entità con più relazioni entranti sarà l'elemento corrente
                }
                max = max_array[w];
            }
        }
        if(concat) {
            while (max_array[w+1] == max) {
                if (listaEntity->next != NULL) {
                    listaEntity = listaEntity->next;
                    w++;
                }
                else
                    break;
            }
        }
        else
            listaEntity=listaEntity->next;

        concat=0;
        w++;
    }

    result.max = max;
    result.entity = entity_output;

    return result;
}






if (memcmp(tmp->name_entity, output[0].entity.name_entity, sizeof(output[0].entity.name_entity)) == 0) {
tmp = listaEntity;
for (j = 0; j < N; j++) {
for (k = 0; k < N; k++) {
if (mat1[k][j] == 1)
count++;
}
if (count >= output[0].max) {
if (count == output[0].max)
memcpy(output[0].entity.next, tmp->name_entity, sizeof(tmp->name_entity));
else {
memcpy(output[0].entity.name_entity, tmp->name_entity,sizeof(tmp->name_entity));
}
output[0].max = count;
}
tmp = tmp->next;
}
}
memcpy(tmp->name_entity, "$$$", sizeof("$$$"));





if(matrice[i][j]==1) {
for (k = 0; k < N; k++) {
if (matrice[k][j] == 1)
count++;
}
matrice[i][j] = 0;
if (count == output.max) {
count = count - 1;
output.max=output.max-1;
tmp = listEntity;
j=0;
while (tmp != NULL && j<N) {
for (i = 0; i < N; i++) {
if (matrice[i][j] == 1)
count2++;
}
if (count2 >= output.max && output.max!=0) {
if (count2 == output.max)
// inserimento in coda da fare
output.entity= inserisci_coda(output.entity, );
else
memcpy(output.entity.name_entity, tmp->name_entity, sizeof(tmp->name_entity));
output.max = count2;
}
tmp = tmp->next;
j++;
}
}
}







while(output[0].entity!= NULL) {
if(memcmp(tmp->name_entity, output[0].entity->name_entity, sizeof(output[0].entity->name_entity))==0) {
if(tmp==output[0].entity && tmp->next==NULL)
//tmp è l
//tmp è tra i massimi
i=0;
j=0;
while(j<posizione) {
while(i<posizione) {
if(mat1[i][j]==1)
count++;
i++;
}
if(count>=output[0].max) {
tmp=listaEntity;
k = 0;
while (k < j) {
tmp = tmp->next;
k++;
}
tmp2 = tmp;
if(count==output[0].max)
//inserimento in coda da fare TODO
output->entity=inserisci_coda(output->entity, *tmp2);
else {
tmp=listaEntity;
while(tmp!=NULL) {
next=tmp->next;
free(tmp);
tmp=next;
}
output->entity=inserisci_coda(output->entity, *tmp2);
}
output[0].max=count;
}
j++;
}
}
output[0].entity=output[0].entity->next;
}
}




tmp=output[k].entity;
while(tmp!=NULL) {
if(memcmp(ent1.name_entity, tmp->name_entity, sizeof(tmp->name_entity))==0) {   // l'entità da eliminare era un massimo assoluto
output[k].entity = libera_nodo(output[k].entity, ent1);
if(output[k].entity==NULL) // la lista vuota -> ent1 era l'unico massimo, altrimenti se !=NULL il massimo era condiviso e quindi resta uguale
output[k].max = 0;
}
tmp=tmp->next;
}


void rimuovi_elemento(t_list_entity *output, t_list_entity node) {
    t_list_entity tmp=*output, next=NULL;

    if(memcmp(tmp.name_entity, node.name_entity, sizeof(node.name_entity))==0)
    {
        *output = tmp->next;
        free(tmp);
    }
    else
    {
        while(tmp->next->val != node)
            tmp = tmp->next;

        next = tmp->next;
        tmp->next = tmp->next->next;
        free(next);
    }
}

void canc(struct list *s){

    struct list *start, *prev;
    int b;
    printf("INSERISCI L'ELEMENTO DA ELIMINARE\n");
    scanf("%d",&b);
    prev=s;
    start=s;
    while(s){
        if(s->a==b){
            while(prev->next!=s)
                prev=prev->next;
            prev->next=s->next;
            s->next=NULL;

        }
        s=s->next;
    }
    s=start;
    printf("LA NUOVA LISTA SARÀ\n");
    while(s){

        printf("%d ",s->a);
        s=s->next;

    }

}





tmp=output;
if(strcmp(tmp->name_entity, node.name_entity)==0) { // TODO strcmp o memcmp -> in caso di reinserimento della stessa entità memcmp non funziona (cambiano gli indirizzi)
if (tmp->next == NULL) { //l'elemento da eliminare è la testa, ed è anche l'unico elemento
// free(output);   // TODO ricontrolla questa free, Dennis dice di metterle ma da' errore
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

