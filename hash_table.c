// ============================================
// The HashTable class file
//
// Copyright 2022 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


/*
Student Name: Carter Eget
Date: 11/4/22
=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
    e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
    e.g. "_HashTable", "_HashTableEntry"

    Recall that in C, we have to type "struct" together with the name of the struct
    in order to initialize a new variable. To avoid this, in hash_table.h
    we use typedef to provide new "nicknames" for "struct _HashTable" and
    "struct _HashTableEntry". As a result, we can create new struct variables
    by just using:
        - "HashTable myNewTable;"
    or
        - "HashTableEntry myNewHashTableEntry;"
    
    The preceding underscore "_" simply provides a distinction between the names
    of the actual struct defition and the "nicknames" that we use to initialize
    new structs.
    [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
    the first letter is lower-case.
    e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
        It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
    as a distinction between function local variables and struct members.
    e.g. "num_buckets" is a member of "HashTable".
*/


/****************************************************************************
 * Include the Public Interface
 *
 * By including the public interface at the top of the file, the compiler can
 * enforce that the function declarations in the the header are not in
 * conflict with the definitions in the file. This is not a guarantee of
 * correctness, but it is better than nothing!
 ***************************************************************************/
#include "hash_table.h"

/****************************************************************************
 * Include other private dependencies
 *
 * These other modules are used in the implementation of the hash table module,
 * but are not required by users of the hash table.
 ***************************************************************************/
#include <stdlib.h> // For malloc and free
#include <stdio.h>  // For printf

/****************************************************************************
 * Hidden Definitions
 *
 * These definitions are not available outside of this file. However, because
 * the are forward declared in hash_table.h, the type names are
 * available everywhere and user code can hold pointers to these structs.
 ***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable
{
    /** The array of pointers to the head of a singly linked list, whose nodes
        are HashTableEntry objects */
    HashTableEntry **buckets;

    /** The hash function pointer */
    HashFunction hash;

    /** The number of buckets in the hash table */
    unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry
{
    /** The key for the hash table entry */
    unsigned int key;

    /** The value associated with this hash table entry */
    void *value;

    /**
     * A pointer pointing to the next hash table entry
     * NULL means there is no next entry (i.e. this is the tail)
     */
    HashTableEntry *next;
};

/****************************************************************************
 * Private Functions
 *
 * These functions are not available outside of this file, since they are not
 * declared in hash_table.h.
 ***************************************************************************/
/**
 * createHashTableEntry
 *
 * Helper function that creates a hash table entry by allocating memory for it on
 * the heap. It initializes the entry with key and value, initialize pointer to
 * the next entry as NULL, and return the pointer to this hash table entry.
 *
 * @param key The key corresponds to the hash table entry
 * @param value The value stored in the hash table entry
 * @return The pointer to the hash table entry
 */
static HashTableEntry *createHashTableEntry(unsigned int key, void *value)
{
	//Creates and allocates space on the heap for a new HashTableEntry
    HashTableEntry *New;
	New = (HashTableEntry *) malloc(sizeof(HashTableEntry));
	
	//Sets values for new HashTableEntry and returns pointer to the HashTableEntry
	New->next = NULL;
	New->key = key;
	New->value = value;
	return New;
}

/**
 * findItem
 *
 * Helper function that checks whether there exists the hash table entry that
 * contains a specific key.
 *
 * @param hashTable The pointer to the hash table.
 * @param key The key corresponds to the hash table entry
 * @return The pointer to the hash table entry, or NULL if key does not exist
 */
static HashTableEntry *findItem(HashTable *hashTable, unsigned int key)
{
	//Uses given key to determine num, the bucket number based on the hash function
    int num = hashTable->hash(key);
	//Points HashTableEntry* curr at the base of the proper bucket
	HashTableEntry* curr = hashTable->buckets[num];
	//While curr does not point at a NULL value
	while(curr != NULL)
	{
		//If curr->key equals the desired key
		if(curr->key == key)
			return curr;     //returns curr
		//Otherwise points curr to next HashTableEntry in the bucket
		curr = curr->next; 
	}
	//If not found, returns NULL
	return NULL;
}

/****************************************************************************
 * Public Interface Functions
 *
 * These functions implement the public interface as specified in the header
 * file, and make use of the private functions and hidden definitions in the
 * above sections.
 ****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable *createHashTable(HashFunction hashFunction, unsigned int numBuckets)
{
    // The hash table has to contain at least one bucket. Exit gracefully if
    // this condition is not met.
    if (numBuckets == 0)
    {
        printf("Hash table has to contain at least 1 bucket...\n");
        exit(1);
    }

    // Allocate memory for the new HashTable struct on heap.
    HashTable *newTable = (HashTable *)malloc(sizeof(HashTable));

    // Initialize the components of the new HashTable struct.
    newTable->hash = hashFunction;
    newTable->num_buckets = numBuckets;
    newTable->buckets = (HashTableEntry **)malloc(numBuckets * sizeof(HashTableEntry *));

    // As the new buckets are empty, init each bucket as NULL.
    unsigned int i;
    for (i = 0; i < numBuckets; ++i)
    {
        newTable->buckets[i] = NULL;
    }

    // Return the new HashTable struct.
    return newTable;
}

void destroyHashTable(HashTable *hashTable)
{
    // 1. Loop through each bucket of the hash table to remove all items.
    //      1a. set temp to be the first entry of the ith bucket
    //      1b. delete all entries
       
    // 2. Free buckets
    
    // 3. Free hash table
	//Creates temporary HashTableEntry pointers
	HashTableEntry* temp;
	HashTableEntry* now;
	
	//Loops through each bucket
	for(int i = 0; i < hashTable->num_buckets; i++)
	{
		//Sets HashTableEntry point temp equal to the base of the ith bucket
		temp = hashTable->buckets[i];
		//While temp is not NULL
		while (temp != NULL)
		{
			now = temp->next;    //Points now to the entry after temp
			free(temp->value);   //Frees value at the HashTableEntry that temp is pointing at
			free(temp);			 //Frees the HashTableEntry that temp is pointing at
			temp = now;          //Points temp to now (temp->next)
		}
	}
	free(hashTable->buckets);    //Frees all of the empty buckets in the hashTable
	free(hashTable);             //Frees the hashTable
}

void *insertItem(HashTable *hashTable, unsigned int key, void *value)
{
    //1. First, we want to check if the key is present in the hash table.
        
    //2. If the key is present in the hash table, store new value and return old value

    //3. If not, create entry for new value and return NULL
	
	//Points HashTableEntry pointer point equal to HashTableEntry with the specified key
	HashTableEntry* point = findItem(hashTable, key);
	//Sets pointer temp equal to the base of the proper bucket containing the given key
	int num = hashTable->hash(key);
	HashTableEntry* temp = hashTable->buckets[num];
	if(point == NULL)     //If HashTableEntry with key does not exist
	{
		//Pointer tail equals new HashTableEntry with specified key and value
		HashTableEntry* tail = createHashTableEntry(key, value);
		//If bucket is empty, point base to tail
		if(temp == NULL)
			hashTable->buckets[num] = tail;
		//Otherwise, loop through the list and add tail to the end of the list
		else
		{
			while(hashTable->buckets[num]->next)
			{
				hashTable->buckets[num] = hashTable->buckets[num]->next;
			}
			hashTable->buckets[num]->next = tail;
			hashTable->buckets[num] = temp;
		}
		return NULL;
		
	}
	else                  //If HashTableEntry with key does exist
	{
		//Returns old value and updates HashTableEntry's value
		void *old = point->value;
		point->value = value;
		return old;
	}
}

void *getItem(HashTable *hashTable, unsigned int key)
{
    //1. First, we want to check if the key is present in the hash table.

    //2. If the key exist, return the value
    
    //3. If not. just return NULL
	HashTableEntry* point = findItem(hashTable, key);
	//If HashTable with given key does not exist, return NULL
	if(point == NULL)
		return NULL;
	//Else return the value at the pointer
	else
		return point->value;
}

void *removeItem(HashTable *hashTable, unsigned int key)
{
    //1. Get the bucket number and the head entry
    
    //2. If the head holds the key, change the head to the next value, and return the old value
    
    //3. If not the head, search for the key to be removed 
    
    //4. Uf the key is not present in the list, return NULL
    
    //5. Unlink node from the list and return old value
	//Sets pointer temp equal to the base of the proper bucket containing the given key
	int num = hashTable->hash(key);
	HashTableEntry* temp = hashTable->buckets[num];
	//Creates temporary HashTableEntry pointers
	HashTableEntry* now;
	HashTableEntry* copy;
	
	//If the bucket is empty, return NULL
	if(temp == NULL)     
		return NULL;
	//If the head holds the key
	if(temp->key == key) 
	{
		//Removes first entry in the bucket and returns the value stored within the removed HashTableEntry
		void *value = temp->value;
		temp = hashTable->buckets[num]->next;
		free(hashTable->buckets[num]);
		hashTable->buckets[num] = temp;
		return value;
	}
	//Loops through the bucket to find HashTableEntry with given key
	while(temp != NULL) 
	{
		if(temp->key == key)
			break;
		now = temp;
		temp = temp->next;
	}
	//If the key is not in the list, return NULL
	if(temp == NULL)   
		return NULL;
	//If the key is in the list 
	else               
	{
		//Remove the HashTableEntry with the given key and return the value it stored
		void *value = temp->value;
		copy = temp;
		temp = temp->next;
		free(copy);
		now->next = temp;
		return value;
	}	
}

void deleteItem(HashTable *hashTable, unsigned int key)
{
    //1. Remove the entry and free the returned data
	free(removeItem(hashTable, key));
}
