/*	
	*****************************************************
	This header contains access to numerous different way
	s of allocating memory in the heap, namely:
	LIFO - last in first out
	FIFO - first in first out
	
	Edit the data type that is stored in the memory by e
	diting the DATA_TYPE variable in buffer.h.
   	

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
  Buffer with acess methods:
  .length: the number of allowed elements in the buffer.
  .head:   the current location in memory of the top data point.
  .base:   the start position of the data buffer.
*/
Buffer lifo_init(uint16_t l);


/*
Checks the status of the buffer, making sure that it
has been initialized properly.

************************
USE:
  lbuf: any Buffer.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status lifo_check(Buffer* lbuf);


/*
Checks to see if the buffer is full.

*************************
USE:
  lbuf: any Buffer.
RETURNS:
  enum LB_FULL     1
  enum LB_NOT_FULL 2
  enum LB_ERROR    5
*/
Buffer_Status lifo_full_check(Buffer *lbuf);


/*
Checks to see if the buffer is empty.

**************************
USE:
  lbuf: any Buffer.
RETURNS:
  enum LB_EMPTY     3
  enum LB_NOT_EMPTY 4
  enum LB_ERROR     5
*/
Buffer_Status lifo_empty_check(Buffer *lbuf);



/*
Inserts the data in 'element' to Buffer lbuf.

**************************
USE:
  element: any element of the defined data type.
  lbuf:    any Buffer.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status lifo_push(DATA_TYPE element, Buffer *lbuf);


/*
Pulls the top-element out of the Buffer lbuf.

**************************
USE:
  lbuf: any Buffer.
RETURNS:
  DATA_TYPE
*/
DATA_TYPE lifo_pull(Buffer *lbuf);


/*
Frees the allocated data in the heap.

**************************
USE:
  lbuf: any Buffer.
RETURNS:
 void
*/
void lifo_reset(Buffer *lbuf);



#endif /* _DATASTRUCTURES_H  */
