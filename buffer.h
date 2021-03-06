/*
	*********************************************************************
	This header includes definitions for construction the buffer struct t
	hat is used to store information in the heap for various applications
	that can be found in datastruct.h.
	Each buffer type is either PACKED or PADDED (standard). The packed 
	types are offered in case the system has limited memory (e.g. embed
	ded systems).
	NOTE: packed variables are potentially unsafe on some systems. Only u
	se them if you are sure you know what you are doing.

	
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

#ifndef _LIFO_TYPE
#define _LIFO_TYPE LIFO_Buffer
#endif /* _LIFO_TYPE  */

#ifndef _FIFO_TYPE
#define _FIFO_TYPE FIFO_Buffer
#endif /* _FIFO_TYPE  */


typedef enum Buffer_Status{
  LB_NO_ERROR = 0,
  LB_FULL,
  LB_NOT_FULL,
  LB_EMPTY,
  LB_NOT_EMPTY,
  LB_ERROR,
} Buffer_Status;


typedef struct LIFO_Buffer{
  uint16_t length;
  volatile DATA_TYPE* base;
  volatile DATA_TYPE* head;
  } LIFO_Buffer;


typedef struct LIFO_Buffer_packed{
  uint16_t length;
  volatile DATA_TYPE* base;
  volatile DATA_TYPE* head;
} __attribute__((packed)) LIFO_Buffer_packed;


typedef struct FIFO_Buffer {
  uint16_t count;
  uint16_t length;
  volatile DATA_TYPE* head;
  volatile DATA_TYPE* base;
  volatile DATA_TYPE* tail;
} FIFO_Buffer;


typedef struct FIFO_Buffer_packed{
  uint16_t count;
  uint16_t length;
  volatile DATA_TYPE* head;
  volatile DATA_TYPE* base;
  volatile DATA_TYPE* tail;
} __attribute__((packed)) FIFO_Buffer_packed;


typedef struct ll_element ll_element;
struct ll_element{
  ll_element* next;
  ll_element* previous;
  DATA_TYPE data;
};


typedef struct ll_Buffer {
  ll_element* head;
  ll_element* tail;
  uint16_t count;
} ll_Buffer;
 
#endif /* _BUFFER_H */
