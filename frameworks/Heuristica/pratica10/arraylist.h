/*
	arraylist.h
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>


/*
  constants
*/
#undef TRUE
#define TRUE 1

#undef FALSE
#define FALSE 0


/*
  type definitions
*/
#undef Boolean
#define Boolean short unsigned int

#undef Object
#define Object void*

typedef struct Arraylist_Struct *Arraylist;


/*
  function declarations
*/
void arraylist_free(const Arraylist list);
Arraylist arraylist_create(const Boolean (*equals)(const Object object_1, const Object object_2));
Boolean arraylist_add(const Arraylist list, Object object);
Boolean arraylist_remove(const Arraylist list, const Object object);
Object arraylist_remove_index(const Arraylist list, const int index);
Boolean arraylist_contains(const Arraylist list, const Object object);
int arraylist_index_of(const Arraylist list, const Object object);
Boolean arraylist_is_empty(const Arraylist list);
int arraylist_size(const Arraylist list);
Object arraylist_get(const Arraylist list, const int index);
void arraylist_clear(const Arraylist list);
void arraylist_sort(const Arraylist list, int (*compare)(const void * object_1, const void * object_2));


#endif /* __defined_arraylist_h */
