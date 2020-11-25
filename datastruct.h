/*	
	*****************************************************
	This header contains access to numerous different way
	s of allocating memory in the heap, namely:
	LIFO - last in first out
	FIFO - first in first out
	
	Edit the data type that is stored in the memory by e
	diting the DATA_TYPE variable with a preprocessor com
	mand.
	ex. #define DATA_TYPE int

	If you want to use packed data structures due to memo
	ry limitations set _LIFO/FIFO_TYPE to _LIFO_TYPE_pac
	ked. The default is 0. WARNING: Packed variables are 
	potentially unsafe on some systems. Do not use them i
	f you are unsure.
	ex. #define _LIFO_TYPE _LIFO_TYPE_packed;
   	

	2020-11-16
	Johannes Westman 
	*****************************************************
*/

#ifndef _DATASTRUCTURES_H
#define _DATASTRUCTURES_H

/* Include the general buffer structure  */
#include "buffer.h"


/* 
Creates a LIFO-style buffer structure (object).

*************************
USE:
  l: the number of data points required (max 65,535).
RETURNS:
  LIFO Buffer with acess methods:
  .length: the number of allowed elements in the buffer.
  .head:   the current location in memory of the top data point.
  .base:   the start position of the data buffer.
*/
_LIFO_TYPE lifo_init(uint16_t l);


/*
Checks the status of the buffer, making sure that it
has been initialized properly.

************************
USE:
  lbuf: any _LIFO_TYPE.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status lifo_check(_LIFO_TYPE* lbuf);


/*
Checks to see if the buffer is full.

*************************
USE:
  lbuf: any _LIFO_TYPE.
RETURNS:
  enum LB_FULL     1
  Fenum LB_NOT_FULL 2
  enum LB_ERROR    5
*/
Buffer_Status lifo_full_check(_LIFO_TYPE *lbuf);


/*
Checks to see if the buffer is empty.

**************************
USE:
  lbuf: any _LIFO_TYPE.
RETURNS:
  enum LB_EMPTY     3
  enum LB_NOT_EMPTY 4
  enum LB_ERROR     5
*/
Buffer_Status lifo_empty_check(_LIFO_TYPE *lbuf);



/*
Inserts the data in 'element' to _LIFO_TYPE lbuf.

**************************
USE:
  element: any element of the defined data type.
  lbuf:    any _LIFO_TYPE.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status lifo_push(DATA_TYPE element, _LIFO_TYPE *lbuf);


/*
Pulls the top-element out of the _LIFO_TYPE lbuf.

**************************
USE:
  lbuf: any _LIFO_TYPE.
RETURNS:
  DATA_TYPE
*/
DATA_TYPE lifo_pull(_LIFO_TYPE *lbuf);


/*
Frees the allocated data in the heap.

**************************
USE:
  lbuf: any _LIFO_TYPE.
RETURNS:
 void
*/
void lifo_reset(_LIFO_TYPE *lbuf);



#endif /* _DATASTRUCTURES_H  */
