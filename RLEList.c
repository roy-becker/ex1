#include "RLEList.h"
#include <stdlib.h>


#define NULL_CHAR 0
#define NULL_INPUT -1


struct RLEList_t 
{
	char val;
	int num;
	struct RLEList_t* next;
};


RLEList RLEListCreate() 
{
	RLEList list = malloc(sizeof(struct RLEList_t));

	if (list == NULL)
	{
		return NULL;
	}

	list->val = NULL_CHAR;
	list->num = 0;
	list->next = NULL;

	return list;
}


void RLEListDestroy(RLEList list) 
{
	while (list != NULL) 
	{
		RLEList toDelete = list;
		list = list->next;
		free(toDelete);
	}
}


RLEListResult RLEListAppend(RLEList list, char value) 
{
	if (list == NULL) 
	{
		return RLE_LIST_NULL_ARGUMENT;
	}
	
	while (list->next != NULL) 
	{
		list = list->next;
	}
	
	if (list->val == NULL_CHAR)
	{
		list->val = value;
	}

	if (list->val == value) 
	{
		list->num++;
	}
	else 
	{
		RLEList temp = malloc(sizeof(struct RLEList_t));
		
		if (temp == NULL) 
		{
			return RLE_LIST_OUT_OF_MEMORY;
		}
		
		temp->val = value;
		temp->num = 1;
		temp->next = NULL;

		list->next = temp;
	}
	
	return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list) 
{
	if (list == NULL) 
	{
		return NULL_INPUT;
	}

	int size = 0;
	
	while (list != NULL) 
	{
		size += list->num;
		list = list->next;
	}

	return size;
}


RLEListResult RLEListRemove(RLEList list, int index) 
{
	if (list == NULL)
	{
		return RLE_LIST_NULL_ARGUMENT;
	}

	if (index < 0)
	{
		return RLE_LIST_INDEX_OUT_OF_BOUNDS;
	}

	int counter = 0;

	RLEList previous = NULL;

	while (list != NULL)
	{
		if (index < counter + list->num)
		{
			list->num--;
			break;
		}
		
		counter += list->num;
		previous = list;
		list = list->next;
	}

	if (list == NULL)
	{
		return RLE_LIST_INDEX_OUT_OF_BOUNDS;
	}

	if (list->num > 0)
	{
		return RLE_LIST_SUCCESS;
	}

	RLEList toDelete = NULL;

	if (previous == NULL)
	{
		if (list->next == NULL)
		{
			list->val = NULL_CHAR;
			
			return RLE_LIST_SUCCESS;
		}

		toDelete = list->next;

		list->val = toDelete->val;
		list->num = toDelete->num;
		list->next = toDelete->next;
	}
	else
	{
		toDelete = list;

		if (list->next != NULL && previous->val == list->next->val)
		{
			previous->num += list->next->num;
			previous->next = list->next->next;
		}
		else
		{
			previous->next = list->next;
		}
	}

	toDelete->next = NULL;

	RLEListDestroy(toDelete);

	return RLE_LIST_SUCCESS;
}


char RLEListGet(RLEList list, int index, RLEListResult* result)
{
	if (list == NULL)
	{
		if (result != NULL)
		{
			*result = RLE_LIST_NULL_ARGUMENT;
		}

		return 0;
	}

	if (index < 0)
	{
		if (result != NULL)
		{
			*result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
		}
		
		return 0;
	}

	int counter = 0;

	while (list != NULL)
	{
		if (index < counter + list->num)
		{
			if (result != NULL)
			{
				*result = RLE_LIST_SUCCESS;
			}

			return list->val;
		}

		counter += list->num;
		list = list->next;
	}

	if (result != NULL)
	{
		*result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
	}
	
	return 0;
}


int numLength(int n)
{
	if (n < 10)
	{
		return 1;
	}

	return numLength(n / 10) + 1;
}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{
	if (list == NULL)
	{
		if (result != NULL)
		{
			*result = RLE_LIST_NULL_ARGUMENT;
		}

		return NULL;
	}

	if (list->val == NULL_CHAR)
	{
		char* out = {'\0'};

		if (result != NULL)
		{
			*result = RLE_LIST_SUCCESS;
		}

		return out;
	}

	int size = 0;

	RLEList temp = list;

	while (temp != NULL)
	{
		size += 1 + numLength(temp->num) + 1;
		temp = temp->next;
	}

	char* out = malloc(size + 1);

	if (out == NULL)
	{
		if (result != NULL)
		{
			*result = RLE_LIST_OUT_OF_MEMORY;
		}

		return NULL;
	}

	int counter = 0;

	while (list != NULL)
	{
		out[counter] = list->val;
		counter++;
		
		sprintf(out + counter, "%d", list->num);
		counter += numLength(list->num);

		out[counter] = '\n';
		counter++;

		list = list->next;
	}

	out[size] = '\0';

	if (result != NULL)
	{
		*result = RLE_LIST_SUCCESS;
	}

	return out;
}


RLEListResult RLEListMap(RLEList list, MapFunction mapFunction)
{
	if (list == NULL)
	{
		return RLE_LIST_NULL_ARGUMENT;
	}

	while (list != NULL)
	{
		list->val = mapFunction(list->val);

		list = list->next;
	}

	return RLE_LIST_SUCCESS;
}