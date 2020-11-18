/*
	*********************************************************************
	This header includes definitions for construction the buffer struct t
	hat is used to store information in the heap for various applications
	that can be found in datastruct.h.

	
	2020-11-16
	Johannes Westman
	*********************************************************************
*/

#ifndef _BUFFER_H
#define _BUFFER_H

#include<stdint.h>
#ifndef DATA_TYPE
#define DATA_TYPE uint8_t
#endif /* DATA_TYPE */


typedef enum Buffer_Status{
  LB_NO_ERROR = 0,
  LB_FULL,
  LB_NOT_FULL,
  LB_EMPTY,
  LB_NOT_EMPTY,
  LB_ERROR,
} Buffer_Status;

typedef struct Buffer{
  uint16_t length;
  volatile DATA_TYPE* base;
  volatile DATA_TYPE* head;
  } Buffer;

#endif /* _BUFFER_H */
