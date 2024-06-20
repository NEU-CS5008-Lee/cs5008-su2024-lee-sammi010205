// name: Fang Huang
// email: huang.fang@northeastern.edu

// Hash table with doubly linked list for chaning/
#include <stdio.h>
#include <stdlib.h> 

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; 

// node struct
struct node {

    // Add your code here
    int key;
    int value;
    struct node* next;
    struct node* previous;

};

// bucket struct
struct bucket{

    // Add your code here
    struct node* head;
    int count;

};

// create a new node
struct node* createNode(int key, int value){

    // Add your code here
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL){
	    printf("Memory allocation failed.\n");
    }
    newNode -> key = key;
    newNode -> value = value;
    newNode -> next = NULL;
    newNode -> previous = NULL;

    return newNode;
}

//  hash function with %
int hashFunction(int key){
    return key % BUCKET_SIZE;
}

//  insert a new key
void add(int key, int value){
    int hashIndex = hashFunction(key);
    
    // Add your code here
    struct node* node = createNode(key, value);
    if (node == NULL) {
	    printf("Memory allocation failed.\n");
	    return;
    }
    // If the index position is empty:
    if (hashTable[hashIndex].head == NULL){
	    hashTable[hashIndex].head = node;
    }else{
	    node -> next = hashTable[hashIndex].head;
	    hashTable[hashIndex].head -> previous = node;
	    hashTable[hashIndex].head = node;
    }
    hashTable[hashIndex].count ++;
    return;

}

// remove a key
void remove_key(int key){
    int hashIndex = hashFunction(key);

    // Add your code here
	struct node* Node = hashTable[hashIndex].head;
	struct node* Previous;
	struct node* Next;

	if (Node == NULL){
		printf("No key found.\n");
		return;
	}
	while (Node != NULL) {
		if (Node -> key == key){
			Previous = Node->previous;
			Next = Node->next;
			if (Previous!=NULL){
				Previous -> next = Next;
			}else{
				hashTable[hashIndex].head = Next;
			}
			if (Next != NULL) {
				Next -> previous = Previous;
			}
			hashTable[hashIndex].count --;
			return;
				
		}else {
			Node = Node -> next;
		}
	}
	printf("No key found.\n");
	return;

}

// search a value using a key
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;

    // Add your code here
    while (node != NULL) {
   	 if (node -> key == key) {
		    printf("key = [ %d ], value = [ %d ]\n", node->key, node->value);
		    return;
  	  }else{
		    node = node -> next;
  	  }
    }
    printf("No key found.\n");
    return;

}

void display(){
    struct node* iterator;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key: %d, val: %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    
    add(0, 1);
    add(1, 10);
    add(11, 12);
    add(21, 14);
    add(31, 16);
    add(5, 18);
    add(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    search(11);
    search(1);
}
