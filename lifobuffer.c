/*
	lifobuffer.c
	************************************************************
	Contains functions for a LIFO-style buffer that can be used 
	as an intermediary storage of data when the reading/writing 
	between two processes is unsynchronized. The buffer is store
	d in the heap. Use a mutex lock if the read/write process is
	multi threaded.

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
  buf.count = 0;
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
  else if (lbuf->count >= lbuf->length) {
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
  else if(lbuf->head == lbuf->base && lbuf->count == 0){
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
  if(status == LB_ERROR) {
    return LB_ERROR;
  }
  else if (status == LB_FULL){
    return LB_FULL;
  }
  else {
    lbuf->count ++;
    *(lbuf->head) = element;
    if( lbuf->count < lbuf->length) {
      lbuf->head ++;
    }
    return LB_NO_ERROR;
  }
}


Buffer_Status lifo_pull(DATA_TYPE* element, _LIFO_TYPE* lbuf){
  Buffer_Status status;
  status = lifo_empty_check(lbuf);
  if (status == LB_EMPTY){
    return LB_EMPTY;
  }
  else if(status == LB_ERROR) {
    return LB_ERROR;
  }
  else {
    lbuf->count --;
    *element = *(lbuf->head);
    if( lbuf->count != 0){
      lbuf->head --;
    }
    return LB_NO_ERROR;
  }
}


void lifo_reset(_LIFO_TYPE* lbuf){
  free((DATA_TYPE*)lbuf->base);
}
