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


/* LIFO_INIT
Creates a LIFO-style buffer structure (object).

*************************
USE:
  uint16_t l: the number of data points required (max 65,535).
RETURNS:
  _LIFO_TYPE Buffer with acess methods:
  .length: the number of allowed elements in the buffer.
  .head:   the current location in memory of the top data point.
  .base:   the start position of the data buffer.
*/
_LIFO_TYPE lifo_init(uint16_t l);


/* LIFO_CHECK
Checks the status of the buffer, making sure that it
has been initialized properly.

************************
USE:
  _LIFO_TYPE lbuf: any _LIFO_TYPE Buffer.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status lifo_check(_LIFO_TYPE* lbuf);


/* LIFO_FULL_CHECK
Checks to see if the buffer is full.

*************************
USE:
  _LIFO_TYPE*: any _LIFO_TYPE.
RETURNS:
  enum LB_FULL     1
  Fenum LB_NOT_FULL 2
  enum LB_ERROR    5
*/
Buffer_Status lifo_full_check(_LIFO_TYPE *lbuf);


/* LIFO_EMPTY_CHECK
Checks to see if the buffer is empty.

**************************
USE:
  _LIFO_TYPE: any _LIFO_TYPE.
RETURNS:
  enum LB_EMPTY     3
  enum LB_NOT_EMPTY 4
  enum LB_ERROR     5
*/
Buffer_Status lifo_empty_check(_LIFO_TYPE *lbuf);


/* LIFO_PUSH
Inserts the data in 'element' to _LIFO_TYPE lbuf.

**************************
USE:
  DATA_TYPE: any element of the defined data type.
  _LIFO_TYPE*:    any _LIFO_TYPE.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_FULL     1
  enum LB_ERROR    5
*/
Buffer_Status lifo_push(DATA_TYPE element, _LIFO_TYPE *lbuf);


/* LIFO_PULL
Pulls the top-element out of the _LIFO_TYPE lbuf.

**************************
USE: 
  DATA_TYPE*: pointer to variable that will store data from buffer.
  _LIFO_TYPE*:    any _LIFO_TYPE.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_EMPTY 3
  enum LB_ERROR 5
  In case of error, sets element to a null pointer;
*/
Buffer_Status lifo_pull(DATA_TYPE* element, _LIFO_TYPE *lbuf);


/* LIFO_RESET
Frees the allocated memory in the heap.

**************************
USE:
  _LIFO_TYPE*: any _LIFO_TYPE.
RETURNS:
 void
*/
void lifo_reset(_LIFO_TYPE *lbuf);


/* FIFO_INIT
Initializes a First-In-First-Out buffer.

**************************
USE:
  uint16_t l: desired length of the buffer
RETURNS:
  _FIFO_TYPE buffer with access methos:
	.base: DATA_TYPE*: start of the buffer
	.head: DATA_TYPE*: last element of the buffer
	.tail: DATA_TYPE*: first element of the buffer
	.length: uint16_t: size of buffer
	.count: number of active elements in the buffer.

*/
_FIFO_TYPE fifo_init(uint16_t l);


/* FIFO_CHECK
Makes sure that the buffer is functioning properly.

***************************
USE:
  _FIFO_TYPE*
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status fifo_check(_FIFO_TYPE* fbuf);


/* FIFO_FULL_CHECK
Checks if the buffer is full.

***************************
USE:
  _FIFO_TYPE* buffer
RETURNS:
  enum LB_FULL     1
  enum LB_NOT_FULL 2
  enum LB_ERROR    5
*/
Buffer_Status fifo_full_check(_FIFO_TYPE* fbuf);


/* FIFO_EMPTY_CHECK
Checks if the buffer is empty.

**************************
USE:
  _FIFO_TYPE* buffer
RETURNS:
  enum LB_EMPTY     3
  enum LB_NOT EMPTY 4
  enum LB_ERROR     5
*/
Buffer_Status fifo_empty_check(_FIFO_TYPE* fbuf);

/* FIFO_PUSH
Puts an element into the buffer.

*****************************
USE:
  DATA_TYPE element: the data to be stored.
  _FIFO_TYPE* fbuf: any fifo-buffer
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_FULL     1
  enum LB_ERROR    5
*/
Buffer_Status fifo_push(DATA_TYPE element, _FIFO_TYPE* fbuf);


/* FIFO_PULL
Pulls an element out of a fifo buffer.

*******************************
USE:
  DATA_TYPE* element: pointer to location to store the pulled data at.
  _FIFO_TYPE* fbuf:   any fifo-buffer.
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_EMPTY    3
  enum LB_ERROR    5
*/
Buffer_Status fifo_pull(DATA_TYPE* element, _FIFO_TYPE* fbuf);


/* FIFO_RESET
Deletes the fifo-buffer and frees the allocated memory.

********************************
USE:
  _FIFO_TYPE* fbuf: any fifo-buffer
RETURNS:
  void
*/
void fifo_reset(_FIFO_TYPE* fbuf);


/* LL_INIT
Initializes a bi-directional linked-list buffer.

**********************************
USE:
  void
RETURNS:
  ll_Buffer: Linked-List buffer with access methods:
  .tail:   : the end node.
  .head    : the head node.
  .count   : the number of data nodes.

tail and head are of type ll_element with access methods:
  .previous: previous node
  .next    : next node
  .data    : data stored at node
*/
ll_Buffer ll_init(void);


/* LL_CHECK
Checks the status of the buffer.

**********************************
USE:
  ll_Buffer*
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_ERROR    5
*/
Buffer_Status ll_check(ll_Buffer* lbuf);


/* LL_EMPTY_CHECK
Checks if there are any nodes in the linked list.

**********************************
USE:
  ll_Buffer*
RETURNS:
  enum LB_EMPTY 3
  enum LB_NOT_EMPTY 4    
  enum LB_ERROR     5
*/
Buffer_Status ll_empty_check(ll_Buffer* lbuf);


/* LL_PUSH
Creates a new node and pushes data into it.

***********************************
USE:
  DATA_TYPE 
  ll_Buffer*
RETURNS:
  LB_NO_ERROR 0
  LB_FULL     2
  LB_ERROR    5
*/
Buffer_Status ll_push(DATA_TYPE data, ll_Buffer* lbuf);


/* LL_PULL
Gets data from the buffer and destroys node.

*************************************
USE:
  DATA_TYPE* data: pointer to variable where node data will be stored at.
  ll_Buffer
RETURNS:
  enum LB_NO_ERROR 0
  enum LB_EMPTY    3
  enum LB_ERROR    5
*/
Buffer_Status ll_pull(DATA_TYPE* data, ll_Buffer* lbuf);


/* LL_RESET
Destroys the buffer and frees all memory.

***************************************
USE:
  ll_Buffer*
RETURNS:
  void
*/
void ll_reset(ll_Buffer* lbuf);


#endif /* _DATASTRUCTURES_H  */
