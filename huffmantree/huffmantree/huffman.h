#pragma once
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//tree node;
typedef struct htNode{
	char symbol;
	struct htNode * left,*right;
}HtNode; 

//tree header!
typedef struct HtTree
{
	HtNode * root;
}HtTree;

//huffmantable node
typedef struct HtableNode
{
	char * code;
	char symbol;
	struct HtableNode *next; 
}HtableNode;

typedef struct HtableHead
{
	HtableNode * first;
	HtableNode * last;
}HtableHead;

HtTree * buildTree(char *inputString);
HtableHead * buildTable( HtTree * huffmanTree);
void encode(HtableHead *table, char * StringToEncode);
void decode(HtTree * head, char * StringToDecode);
#endif