
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Block {
	int block_size;
	struct Block* next_block;
};

const OVERHEAD_SIZE = sizeof(int) + sizeof(void*);// refers to size & pointer of a block
const POINTER_SIZE = sizeof(void*);
struct Block* free_head;

void my_initialize_heap(int size) {
	//YOUR CODE
	struct Block* first_block = (struct Block*)malloc(size);
	first_block->block_size = size - OVERHEAD_SIZE;
	first_block->next_block = 0;
	free_head = first_block;
}

void* my_alloc(int size) {
	if (size <= 0) {
		printf("Size must be greater than 0");
		return 0;
	}
	// size must be a multiple of POINTER_SIZE. So, if pointer_size is 4, size must be atleast 4, 8, 12...
	
    size = ((size + POINTER_SIZE - 1) / POINTER_SIZE) * POINTER_SIZE;

	// Iterators
	struct Block* curr = free_head;
	struct Block* prev = 0;

	bool found = false;
	// Iterare through each node, if a node has equal or more space than necessary to hold size, use that node.
	while (curr != NULL) {
		if (curr->block_size >= size) {
			found = true;
			// Determine if the current block can be split.
			if (curr->block_size >= size + OVERHEAD_SIZE + POINTER_SIZE) { // Splittable
				// Create a pointer to the newly split block's position then assign its structure members.
				//Your code
				struct Block* new_block = (struct Block*)((char*)curr + OVERHEAD_SIZE + size);
				new_block->block_size = curr->block_size - size - OVERHEAD_SIZE;
				new_block->next_block = curr->next_block;

				// Update Curr's block size as a result of splitting.
                                //Your code
				curr->block_size = size;
				curr->next_block = 0;

				// Adjust the double linked list, depending on whether curr is the head or not.
                                //Your code
				if (prev){
					prev->next_block = new_block;
				}
				else{
					free_head = new_block;
				}
				
			}

			else { // Not splittable
				// If curr is the head, curr's next block is the new head.
				//Your code
				if(prev){
					prev->next_block = curr->next_block;
				}
				
				// If curr is not the head, the previous block points to curr's next block.
				else {
					//Your code
					free_head = curr->next_block;
				}
			}
			// Since we found a block, no need to keep searching.
			break;
		}
		// Haven't found an available space yet.
		else {
			//Your code
			prev = curr;
			curr = curr->next_block;
		}
	}
	// Return a pointer to the allocated data, if possible.
	//Your code
	return (void*)((char*)curr + OVERHEAD_SIZE);
}

void my_free(void* data) {
	struct Block* freed_block = (struct Block*)((char*)data - OVERHEAD_SIZE);
	freed_block->next_block = free_head;
	free_head = freed_block;
}

int main(){
	return 0;
}