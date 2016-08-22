#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main (void)
{//you can upload an artile to build the tree, 
	HtTree * tree = buildTree("abbbccdefggghhiijjlllll llkmknkhboo!! prr");
	HtableHead* table=buildTable(tree);

	encode(table,"beep boop beer!");
	
	decode(tree,"00110011010011000010100000101110111");
	return 0;
}