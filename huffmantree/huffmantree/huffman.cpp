# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include"huffman.h"
# include"pQueue.h"

// MAX is 256 because entire ascii table with additional characters is 255
HtTree * buildTree(char *inputString)
{
	int * probability = (int*)malloc(sizeof(int)*MAX);
	for(int i=0;i<MAX;i++)
		probability[i]=0;

	for(int i =0; inputString[i]!='\0';i++)
		probability[(unsigned int)inputString[i]]++;

	pQueue * huffmanQueue;
	initPQueue(&huffmanQueue);

	for(int i=0; i<MAX;i++)
	{
		if(probability[i]!= 0)
		{
			HtNode * node=(HtNode*)malloc(sizeof(HtNode));

			node->left=NULL;
			node->right=NULL;
			node->symbol=(char)i;
			addPQueue( huffmanQueue, node, probability[i]);
		}
	}

	free(probability);
	
	while(huffmanQueue->size>1)
	{
		unsigned int priority;

		priority=huffmanQueue->first->priority;
		priority += huffmanQueue->first->next->priority;

		HtNode* pnew = (HtNode *)malloc(sizeof(HtNode));

		pnew->left = getPQueue(huffmanQueue);
		pnew->right = getPQueue(huffmanQueue);
		
		addPQueue(huffmanQueue,pnew,priority);
	}

	HtTree * tree= (HtTree *)malloc(sizeof(HtTree));
	
	tree->root =getPQueue(huffmanQueue);
	
	return tree;
}

void traverse(char code[256],HtableHead* table,int level, HtNode *T)
{
	if(T)
	{
		if(T->left == NULL && T->right == NULL)
		{
			code[level]='\0';
			HtableNode * node=(HtableNode *)malloc(sizeof(HtableNode));
			node->symbol=T->symbol;
			node->next=NULL;
			node->code = (char *) malloc(sizeof(strlen(code)+1));
			strcpy(node->code,code);

			if(table->first == NULL)
			{
				table->first=node;
				table->last=node;
			}
			else
			{
				table->last->next =node;
				table->last=node;
			}
		}
		
		if(T->left!= NULL)
		{
			code[level]='0';
			traverse(code,table,level+1,T->left);
		}

		if(T->right != NULL)
		{
			code[level]='1';
			traverse(code,table,level+1,T->right);
		}
	}
}

HtableHead * buildTable( HtTree * huffmanTree)
{
	HtNode * T=huffmanTree->root;

	char code[256];
	int level=0;
	HtableHead * table = (HtableHead*)malloc(sizeof(HtableHead));
	table->first=NULL;
	table->last=NULL;

	traverse(code,table,level,T);

	return table;
}

void encode(HtableHead *table, char * StringToEncode)
{
	HtableNode* temp;
	printf("Input:\n %s\n Encode:\n",StringToEncode);
	
	for(int i=0;StringToEncode[i]!='\0';i++)
	{
		temp=table->first;
		while(temp!=NULL && temp->symbol != StringToEncode[i])
			temp=temp->next;
		if(temp == NULL)
		{
			printf("\nSorry, we have no code for your \"%c\"\n try to add that character in the building huffmantree source String\n",StringToEncode[i]);
			exit(0);
		}
		else
		printf("%s",temp->code);
	}
	printf("\n");
}

void decode(HtTree* head, char * StringToDecode)
{
	
	HtNode* T= head->root;
	printf("\nDecoding\nInput string : %s\nDecoded string : ",StringToDecode);
	
	for(int i =0; StringToDecode[i]!='\0';i++)
	{
		if( T->left ==NULL && T->right == NULL)
		{
			printf("%c",T->symbol);
			T=head->root;
		}
		if(StringToDecode[i] =='0')
		{
			T= T->left;
		}
		if(StringToDecode[i]=='1')
		{
			T=T->right;
		}

		if(StringToDecode[i] !='0' && StringToDecode[i] !='1')
		{
			printf("wrong coding format!");
			return ;
		}
	}
	if(T->left ==NULL && T->right ==NULL)
	{
		printf("%c \n",T->symbol);
		T=head->root;
	}
	return;
}