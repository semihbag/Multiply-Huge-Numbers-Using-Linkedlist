#include<stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Node{
	int data;
	struct Node *nextPtr;
	
}Node;

void readDataFromFile(FILE *fptr, struct Node **head, int *len){
	//check whether is there file or not
	if (fptr != NULL){
		int i = 0;
		char c;
		while(1){
			c = fgetc(fptr);
			int x = (int)c;
			if ((x >= 48) && (x <= 57) && (c != '\n') && (x != -1)){
				struct Node* newNode = malloc(sizeof(struct Node));
				newNode->data = x - 48;
				newNode->nextPtr = NULL;
				newNode->nextPtr = (*head);
				(*head) = newNode;
			}
			else{
				break;
			}	
			i++;			
		}
		*len = i;
	}
	else{
		printf("No such file found");
	}
}


void multiplyWithNumber(struct Node **num, struct Node **key, int base, int number){
	struct Node *currend = malloc(sizeof(struct Node));
	struct Node *currendKey = malloc(sizeof(struct Node));
	currend = *num;
	int carry = 0;
	int data, res;
	int a = 1;
	while(1){
		if(a){
			struct Node *start = malloc(sizeof(struct Node));
			data = currend->data;
			res = (data*number) + carry;
			start->data = res%base;
			start->nextPtr = NULL;
			*key = start;
			currendKey = *key;
			carry = res/base;
			a = 0;
		}
		else{
			struct Node *newNode = malloc(sizeof(struct Node));
			data = currend->data;
			res = (data*number) + carry;
			newNode->data = res%base;
			newNode->nextPtr = NULL;
			currendKey->nextPtr = newNode;
			currendKey = currendKey->nextPtr;
			carry = res/base;
		}
		
		if(currend->nextPtr != NULL){
			currend = currend->nextPtr;
		}
		else{
			if(carry == 0){
				break;
			}
			else{
				struct Node *newNode = malloc(sizeof(struct Node));
				newNode->data = carry;
				carry = 0 ;
				newNode->nextPtr = NULL;
				currendKey->nextPtr = newNode;
				currendKey = currendKey->nextPtr;

				break;				
			}
		}
	}
}


void createBaseTable(struct Node **baseNum, int base, struct Node* list[]){	
	struct Node *headBase = malloc(sizeof(struct Node));
	headBase = *baseNum;
	int i = 0;
	for(i=0 ; i<base ; i++){
		struct Node *newNode = malloc(sizeof(struct Node));
		multiplyWithNumber(&headBase,&newNode,base,i);
		list[i] = newNode;
	}	
}


void sum(struct Node **baseNum, int power, struct Node **head,int base){	
	if (*head == NULL){
		struct Node *tempB = malloc(sizeof(struct Node));
		struct Node *tempH = malloc(sizeof(struct Node));
		tempB = *baseNum;
		struct Node *startNode = malloc(sizeof(struct Node));
		startNode->data = tempB->data;
		startNode->nextPtr = NULL;
		*head = startNode;
		tempH = *head;
		if(tempB->nextPtr != NULL){
			tempB = tempB->nextPtr;
			while(1){
				struct Node *newNode = malloc(sizeof(struct Node));
				newNode->data = tempB->data;
				newNode->nextPtr = NULL;
				tempH->nextPtr = newNode;
				tempH = newNode;
				if(tempB->nextPtr != NULL){
					tempB = tempB->nextPtr;
				}
				else{
					break;
				}		
			}
		}
	}
	else{
		struct Node *currendSumNode = malloc(sizeof(struct Node));
		currendSumNode = *head;
		int i = 0;
		for(i=0 ; i<power ; i++){
			if(currendSumNode->nextPtr != NULL){
				currendSumNode = currendSumNode->nextPtr;
			}
			else{
				struct Node *newNode = malloc(sizeof(struct Node));
				newNode->data = 0;
				newNode->nextPtr = NULL;
				currendSumNode->nextPtr = newNode;
				currendSumNode->nextPtr = currendSumNode;
			}
		}
		int baseData;
		int sumData;
		int carry = 0;
		struct Node *currendBaseNode = malloc(sizeof(struct Node));
		currendBaseNode = *baseNum;
		int total;
		while(1){
			baseData = currendBaseNode->data;
			sumData = currendSumNode->data;
			total = baseData + sumData + carry;
			currendSumNode->data = total%base;
			carry = total/base;
			if(currendBaseNode->nextPtr != NULL){
				currendBaseNode = currendBaseNode->nextPtr;
				if(currendSumNode->nextPtr != NULL){
					currendSumNode = currendSumNode->nextPtr;
				}
				else{
					struct Node *newNode = malloc(sizeof(struct Node));
					newNode->data = 0;
					newNode->nextPtr = NULL;
					currendSumNode->nextPtr = newNode;
					currendSumNode = currendSumNode->nextPtr;					
				}
			}
			else{
				if (carry == 0){
					break;
				}
				else{
					struct Node *newNode = malloc(sizeof(struct Node));
					newNode->data = carry;
					carry = 0 ;
					newNode->nextPtr = NULL;
					currendSumNode->nextPtr = newNode;
					currendSumNode = currendSumNode->nextPtr;
					break;
				}
			}
		}
	}
}


void printNumber(struct Node **num){
	struct Node* currenNode = malloc(sizeof(struct Node));
	currenNode->nextPtr = NULL;
	currenNode = *num;
	int key;
	while(1){
		printf("%d",currenNode->data);
		if((currenNode->nextPtr != NULL)){
			currenNode = currenNode->nextPtr;
		}
		else{
			break;
		}
	}	
}

void printNumberReverse(struct Node **num){
	struct Node *currendNode = malloc(sizeof(struct Node));
	struct Node *currendNewNode = malloc(sizeof(struct Node));
	currendNode->nextPtr = NULL;
	currendNewNode->nextPtr = NULL;
	
	currendNode = *num;
	
	while(1){
		currendNewNode->data = currendNode->data;
		
		if(currendNode->nextPtr != NULL){
			currendNode = currendNode->nextPtr;
			struct Node *newNode = malloc(sizeof(struct Node));
			newNode->nextPtr = currendNewNode;
			currendNewNode = newNode;
		}
		else{
			break;
		}
	}
	printNumber(&currendNewNode);
}


void convertToDecimal(struct Node **num, struct Node **result, int base){
	struct Node *currendNum = malloc(sizeof(struct Node));
	struct Node *power = malloc(sizeof(struct Node));
	power->data = 1;
	power->nextPtr = NULL;
	struct Node *total = NULL;	
	currendNum = *num;
	
	int data;
	
	while(1){
		data = currendNum->data;
		struct Node *sumPiece = NULL;
		multiplyWithNumber(&power,&sumPiece,10,data);	
		sum(&sumPiece,0,&total,10);			
		struct Node *newPower = NULL;
		multiplyWithNumber(&power,&newPower,10,base);
		power = newPower;
		
		if(currendNum->nextPtr != NULL){
			currendNum = currendNum->nextPtr;
		}
		else{
			break;
		}
	}
	printNumberReverse(&total);
}




int main(int argc,char* argv[]){
	if(argc==1){
		printf("Error message!");
	}
    if(argc>=2)
    {
    	FILE* input_file = fopen(argv[1], "r");
		
		struct Node *num1Ptr = NULL;
		struct Node *num2Ptr = NULL;
		struct Node *convertedNumPtr = NULL;
		
		int num1Len, num2Len;	
		int *num1lenPtr = &num1Len;
		int *num2lenPtr = &num2Len;	
		int base;
		
		readDataFromFile(input_file, &num1Ptr, num1lenPtr);
		readDataFromFile(input_file, &num2Ptr, num2lenPtr);
		fscanf(input_file, "%d", &base);
		fclose(input_file);
	
		struct Node *list[base];
		struct Node *sumPtr = NULL;
		struct Node *currendPtr = NULL;
		int data;
		
		
		if(num1Len>num2Len){
			createBaseTable(&num1Ptr,base,list);
			int i = 0;
			currendPtr = num2Ptr;
			for(i=0 ; i<num2Len ; i++){
				data = currendPtr->data;
				sum(&(list[data]),i,&sumPtr,base);
				if(currendPtr->nextPtr != NULL){
					currendPtr = currendPtr->nextPtr;
				}
			}
		}
		else{
			createBaseTable(&num2Ptr,base,list);
			int i = 0;
			currendPtr = num1Ptr;
			for(i=0 ; i<num1Len ; i++){
				data = currendPtr->data;
				sum(&(list[data]),i,&sumPtr,base);
				if(currendPtr->nextPtr != NULL){
					currendPtr = currendPtr->nextPtr;
				}
			}
		}
		

		printNumberReverse(&num1Ptr);
		printf("\n");
		printNumberReverse(&num2Ptr);
		printf("\n");
		printNumberReverse(&sumPtr);
		printf("\n");
		convertToDecimal(&num1Ptr,&convertedNumPtr,base);
		printf("\n");
		convertToDecimal(&num2Ptr,&convertedNumPtr,base);
		printf("\n");
		convertToDecimal(&sumPtr,&convertedNumPtr,base);
	

		return 0 ;

	}
}
