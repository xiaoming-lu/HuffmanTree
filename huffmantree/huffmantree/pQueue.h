#pragma once
#ifndef _PQUEUE_H
#define _PQUEUE_H

#include "huffman.h"
#define MAX 256

typedef struct pQueueNode
{
	HtNode * val;
	unsigned int priority;
	struct pQueueNode * next;
}pQueueNode;

//Queue header
typedef struct pQueueHead
{
	unsigned int size;
	pQueueNode * first;
}pQueue;

void initPQueue(pQueue ** queue);
void addPQueue(pQueue * queue, HtNode* val, unsigned int priority);
HtNode * getPQueue(pQueue * queue);


#endif