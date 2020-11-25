/*
	************************************************************
	Contains functions for a LIFO-style buffer that can be used as
	an intermediary storage of data when the reading/writing bet
	ween two processes is unsynchronized. This program was writt
	en for datatypes of uint8_t, however, the data type can be m
	anipulated into any required type by changing the DATA_TYPE 
	variable with the #define preprocessor command in the target
	file. The buffer is stored in the heap.
	Use a mutex lock if the read/write process is multi threaded.

	USE:
	Compile this into an object file (gcc lifobuffer.c -c) and l
	ink it to your main file (gcc lifobuffer.o main.c -o executa
	ble).
	
	2020-11-13
	Johannes Westman
	*************************************************************
*/


#include<stdlib.h>
#include "datastruct.h"


_LIFO_TYPE lifo_init(uint16_t l){
  _LIFO_TYPE buf;
  buf.length = l;
  buf.base = (DATA_TYPE*)malloc(l);
  if (! buf.base){
    buf.length = 0;
  }
  buf.head = buf.base;
  return buf;
}


Buffer_Status lifo_check(_LIFO_TYPE* lbuf){
  /* check pointers */
  if ( !lbuf || !(lbuf->head) || !(lbuf->base) ){
    return LB_ERROR;
  }
  return LB_NO_ERROR;
}


Buffer_Status lifo_full_check(_LIFO_TYPE* lbuf){
  Buffer_Status status = lifo_check(lbuf);
  if (status == LB_ERROR){
    return LB_ERROR;
  }
  /* check if the buffer is full  */
  else if (lbuf->head >= (lbuf->base + lbuf->length) ) {
    return LB_FULL;
  }
  return LB_NOT_FULL;
}


Buffer_Status lifo_empty_check(_LIFO_TYPE* lbuf){
  Buffer_Status status;
  status = lifo_check(lbuf);
  if(status == LB_ERROR){
    return LB_ERROR;
  }
  /* check if buffer is empty */
  else if(lbuf->head == lbuf->base){
    return LB_EMPTY;
  }
  else
  {
    return LB_NOT_EMPTY;
  }
}


Buffer_Status lifo_push(DATA_TYPE element, _LIFO_TYPE* lbuf){
  Buffer_Status status;
  status = lifo_full_check(lbuf);
  if(status != LB_NOT_FULL) {
    return LB_ERROR;
  }
  lbuf->head ++;
  *(lbuf->head) = element;
  return LB_NO_ERROR;
}


DATA_TYPE lifo_pull(_LIFO_TYPE* lbuf){
  Buffer_Status status;
  status = lifo_empty_check(lbuf);
  if (status != LB_NOT_EMPTY){
    return 0; /*this will depend on your application*/
  }
  DATA_TYPE element = *(lbuf->head);
  lbuf->head --;
  return element;
}


void lifo_reset(_LIFO_TYPE* lbuf){
  free((DATA_TYPE*)lbuf->base);
}
