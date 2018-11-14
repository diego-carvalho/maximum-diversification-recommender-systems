/*
	arraylist.c
*/ 

#include <string.h>
#include "arraylist.h"

/*
  constants
*/
#define ARRAYLIST_INITIAL_CAPACITY 100
#define ARRAYLIST_CAPACITY_DELTA 100

static const size_t object_size = sizeof(Object);


/*
  structures
*/
struct Arraylist_Struct {
  int _current_capacity;
  Object *_data;
  int _size;
  const Boolean (*_equals)(const Object object_1, const Object object_2);
};


/*
  private function declarations
*/
static void *checked_malloc(const size_t size);


void arraylist_free(const Arraylist list)
{
  free(list->_data);
  free(list);
}

Arraylist arraylist_create(const Boolean (*equals)(const Object object_1, const Object object_2))
{
  Arraylist list;

  list = (Arraylist_Struct *)malloc(sizeof(struct Arraylist_Struct));
  list->_current_capacity = ARRAYLIST_INITIAL_CAPACITY;
  list->_data = (Object *) malloc(object_size * list->_current_capacity);
  list->_size = 0;
  list->_equals = equals;

  return list;
}

Boolean arraylist_add(const Arraylist list, Object object)
{
  int old_size = arraylist_size(list);
  int new_capacity;
  Object *new_data;

  (list->_size)++;
  if (old_size == list->_current_capacity)
    {
      new_capacity = list->_current_capacity + ARRAYLIST_CAPACITY_DELTA;
      new_data = (Object *) malloc(object_size * new_capacity);
      memcpy(new_data, list->_data, object_size * old_size);
      free(list->_data);
      (list->_data) = new_data;
      list->_current_capacity = new_capacity;
    }
  (list->_data)[old_size] = object;
  return TRUE;
}

Boolean arraylist_remove(const Arraylist list, const Object object)
{
  int length = arraylist_size(list);
  int last_index = length - 1;
  int new_size, new_capacity;
  int index;

  for (index = 0; index < length; index++)
  {
      if ((*list->_equals)(arraylist_get(list, index), object))
	{
	  (list->_size)--;
	  if (index < last_index)
	    {
	      memmove(list->_data + index, list->_data + index + 1, object_size * (last_index - index));
	      new_size = list->_size;
	      new_capacity = list->_current_capacity - ARRAYLIST_CAPACITY_DELTA;
	      if (new_capacity > new_size)
		{
		  list->_data = (Object *) realloc(list->_data, object_size * new_capacity);
		  list->_current_capacity = new_capacity;
		}
	    }
	  return TRUE;
	}
  }
  return FALSE;
}

Boolean arraylist_contains(const Arraylist list, const Object object)
{
  return (arraylist_index_of(list, object) > -1);
}

int arraylist_index_of(const Arraylist list, const Object object)
{
  int length = arraylist_size(list);
  int index;

  for (index = 0; index < length; index++)
    {
      if ((*list->_equals)(arraylist_get(list, index), object))
	{
	  return index;
	}
    }
  return -1;
}

Boolean arraylist_is_empty(const Arraylist list)
{
  return (0 == arraylist_size(list));
}

int arraylist_size(const Arraylist list)
{
  return list->_size;
}

Object arraylist_get(const Arraylist list, const int index)
{
  return list->_data[index];
}

void arraylist_clear(const Arraylist list)
{
  list->_data = (Object *)realloc(list->_data, object_size * ARRAYLIST_INITIAL_CAPACITY);
  list->_current_capacity = ARRAYLIST_INITIAL_CAPACITY;
  list->_size = 0;
}

static void *checked_malloc(const size_t size)
{
  void *data;

  data = malloc(size);
  if (data == NULL)
    {
      fprintf(stderr, "\nOut of memory.\n");
      fflush(stderr);
      exit(EXIT_FAILURE);
    }

  return data;
}

Object arraylist_remove_index(const Arraylist list, const int index)
{
  int length = arraylist_size(list);
  int last_index = length - 1;
  int new_size, new_capacity;
  Object o;

  o = list->_data[index];

  (list->_size)--;
  if (index < last_index)
  {
    memmove(list->_data + index, list->_data + index + 1, object_size * (last_index - index));
	new_size = list->_size;
	new_capacity = list->_current_capacity - ARRAYLIST_CAPACITY_DELTA;
	if (new_capacity > new_size)
	{
	  list->_data = (Object *)realloc(list->_data, object_size * new_capacity);
	  list->_current_capacity = new_capacity;
	}
  }

  return o;
}

void arraylist_sort(const Arraylist list, int (*compare)(const void * object_1, const void * object_2))
{
	qsort(list->_data,
		  arraylist_size(list),
		  sizeof(Object),
		  compare);
}
