#include<stdio.h>
#include<memory.h> 
#include<string.h> 
#include<time.h>
#define FALSE 0
#define TRUE 1
#define HASHFUNC 7
typedef int STATUS;
typedef struct _NODE
{
    int data;
    struct _NODE* next;
}NODE;

typedef struct _HASH_TABLE
{
    NODE* value[HASHFUNC];
}HASH_TABLE;
HASH_TABLE* create_hash_table()
{
    HASH_TABLE* pHashTbl = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    memset(pHashTbl, 0, sizeof(HASH_TABLE));
    return pHashTbl;
}
NODE* find_data_in_hash(HASH_TABLE* pHashTbl, int data)
{
    NODE* pNode;
    if(NULL ==  pHashTbl)
        return NULL;

    if(NULL == (pNode = pHashTbl->value[data % HASHFUNC]))
        return NULL;

    while(pNode){
        if(data == pNode->data)
            return pNode;
        pNode = pNode->next;
    }
    return NULL;
}
STATUS insert_data_into_hash(HASH_TABLE* pHashTbl, int data)
{
    NODE* pNode;
    if(NULL == pHashTbl)
        return FALSE;

    if(NULL == pHashTbl->value[data % HASHFUNC]){
        pNode = (NODE*)malloc(sizeof(NODE));
        memset(pNode, 0, sizeof(NODE));
        pNode->data = data;
        pHashTbl->value[data % HASHFUNC] = pNode;
        return TRUE;
    }

    if(NULL != find_data_in_hash(pHashTbl, data))
        return FALSE;

    pNode = pHashTbl->value[data % HASHFUNC];
    while(NULL != pNode->next)
        pNode = pNode->next;

    pNode->next = (NODE*)malloc(sizeof(NODE));
    memset(pNode->next, 0, sizeof(NODE));
    pNode->next->data = data;
    return TRUE;
}
STATUS delete_data_from_hash(HASH_TABLE* pHashTbl, int data)
{
    NODE* pHead;
    NODE* pNode;
    if(NULL == pHashTbl || NULL == pHashTbl->value[data % HASHFUNC])
        return FALSE;

    if(NULL == (pNode = find_data_in_hash(pHashTbl, data)))
        return FALSE;

    if(pNode == pHashTbl->value[data % HASHFUNC]){
        pHashTbl->value[data % HASHFUNC] = pNode->next;
        free(pNode);
        return TRUE;
    }

    pHead = pHashTbl->value[data % HASHFUNC];
    while(pNode != pHead ->next)
        pHead = pHead->next;
    pHead->next = pNode->next;

}
void print_hash_data(HASH_TABLE* pHashTbl)  
{  
    NODE* pNode;  
    int i=0;  
    if (NULL == pHashTbl)  
    {  
        printf("ERROR:The hash is NULL\n");  
    }  
    
    printf("[Hash idx]     [value]\n");  
    do   
    {     
        printf("   %d-------------",i);  
        if (NULL == pHashTbl->value[i])  
        {  
            i++;  
            printf("NULL\n");  
            continue;  
        }  
  
        pNode = pHashTbl->value[i];  
          
        while(pNode)  
        {  
            printf("%d ",pNode->data);  
            pNode = pNode->next;  
        }  
        printf("\n");  
        i++;  
    } while (i<HASHFUNC);  
  
    printf("\n");  
} 
 int main()
{
    HASH_TABLE* hashtable=create_hash_table();
    srand(time(NULL));
    int array[50];
    for (int i=0; i<50; i++){
        array[i] = rand()%100;
    } 
    for (int i=0; i<50; i++){
        insert_data_into_hash(hashtable,array[i]);
    }
    printf("Constuct hash table with mod 7\n" );
    print_hash_data(hashtable);
    int delete[10]={1,2,3,4,5,6,7,8,9,10};
    for (int j=0;j<10;j++){
        delete_data_from_hash(hashtable,delete[j]);
    }
    printf("After deleting\n" );
    print_hash_data(hashtable);
    return 0;

}