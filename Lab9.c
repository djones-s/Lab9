#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int	id;
	char name;
	int	order; 
};

#define hashSize 64 
// Fill out this structure
struct HashType
{
    struct RecordType * records[hashSize];
};

// Compute the hash function
int hash(int x)
{
    return x % hashSize;
};

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
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
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if (pHashArray->records[i] != NULL)
        {
            printf("index %d -> %d %c %d", i, pHashArray->records[i]->id, pHashArray->records[i]->name, pHashArray->records[i]->order);
            printf(" ");
        }
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords); //size of records?
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType hashStruct;
	for(int n = 0; n < hashSize; n++)
	{
	    hashStruct.records[n] = NULL;
	}
	
	for(int n = 0; n < recordSz; n++)
	{
	    struct RecordType *pRecord = pRecords + n;
	    int index = hash(pRecord->id);
	    hashStruct.records[index] = pRecord;
	}
	
	displayRecordsInHash(&hashStruct, hashSize);
	
	free(pRecords);
	
	return 0;
}
