#include <stdio.h>
#include <stdlib.h>

// RecordType
 struct RecordType
{
    int id;
    char name;
    int order;
	struct RecordType* next;
} ;

// Fill out this structure
struct HashType
{
	struct RecordType* record;
} ;

// Compute the hash function
int hash(int x, int tableSize)
{
	return x%tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
	int index = hash((int)record->name, tableSize);
	if(hashTable[index].record == NULL){
		hashTable[index].record = record;
	} else {
		struct RecordType* temp = hashTable[index].record;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = record;
	}
}

void displayRecordsInHash(struct HashType *hashTable, int tableSize) {
	for(int i = 0; i < tableSize; i++){

		struct RecordType *temp = hashTable[i].record;
        printf("\nIndex %d ", i+1);
		while(temp != NULL){
			printf("-> %d %c %d ", temp->id, temp->name, temp->order);
			temp = temp->next;
		}
	}
}

int main(void)
{
	printf("test");
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

	struct HashType *hashTable = (struct HashType*)calloc(1, sizeof(struct HashType));
	int hashTableSize = 11;
	for(int i = 0; i < recordSz; i++){
		insertRecord(hashTable, &pRecords[i], hashTableSize);
	}
	displayRecordsInHash(hashTable, hashTableSize);
    free(pRecords);
	free(hashTable);

    return 0;
}