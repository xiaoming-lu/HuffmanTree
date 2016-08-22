# include <stdlib.h>
# include <stdio.h>
# include "huffman.h"
# include "pQueue.h"

void initPQueue(pQueue ** queue)
{
	*queue =(pQueue *)malloc(sizeof(pQueue));
	(*queue)->first=NULL;
	(*queue)->size=0;

	return;
}

void addPQueue(pQueue *queue, HtNode * val, unsigned int priority)
{
	
	if(queue->size== MAX)
	{
		printf("queue is full !\n");
		return;
	}

		pQueueNode * pnew =(pQueueNode *) malloc(sizeof(pQueueNode));
		pnew->priority= priority;
		pnew->val= val;

	if( queue->size== 0 || queue->first==NULL)
	{
		pnew->next=NULL;
		queue->first= pnew;
		queue->size=1;
		return ;
	}
	
	if(priority <= queue->first->priority)
	{
	
		pnew->next=queue->first;
		queue->first= pnew;
		queue->size++;
		return;
	}
	else
	{
		pQueueNode * iterator = queue->first;
		while(iterator->next !=NULL)
		{
			if(priority <= iterator->next->priority)
			{
				pnew->next=iterator->next;
				iterator->next=pnew;
				queue->size++;
				return;
			}
			iterator= iterator->next;
		}
		if(iterator->next == NULL)
		{	
			pnew->next=NULL;
			iterator->next=pnew;
			queue->size++;
			return;
		}
	}
}


HtNode * getPQueue(pQueue * queue)
{
	HtNode *returnvalue;
	if(queue->size!=0 && queue->first!= NULL)
	{
		returnvalue=queue->first->val;
		queue->first=queue->first->next;
		queue->size--;
		return returnvalue;
	}
	else
	{
		printf("Queue is empty!");
		return NULL;
	}
}