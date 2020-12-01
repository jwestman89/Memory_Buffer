/*	
	fifobuffer.c
	***************************************************************
	Contains functions for a FIFO-styled buffer that can be used as
	an intermediary storage when reading/writing data is unsynchron
	ized. The buffer is stoed in the heap. Use Mutex locks when rea
	ding/writing to the buffer.
	The implemented buffer is circular but does not overwrite old d
	ata. If the buffer is full it will throw an error message.

	2020-11-26
	Johannes Westman
	***************************************************************
*/


#include<stdlib.h>
#include"buffer.h"

_FIFO_TYPE fifo_init(uint16_t l){
  _FIFO_TYPE buf;
  buf.length = l;
  buf.base = (DATA_TYPE*)malloc(l);
  if(! buf.base) {
    buf.length = 0;
  }
  buf.head = buf.base;
  buf.tail = buf.base;
  buf.count = 0;
  return buf;
}


Buffer_Status fifo_check(_FIFO_TYPE* fbuf){
  if(!fbuf || !(fbuf->head) || !(fbuf->tail) || !(fbuf->base)){
    return LB_ERROR;
  }
  return LB_NO_ERROR;
}


Buffer_Status fifo_full_check(_FIFO_TYPE* fbuf) {
  Buffer_Status status = fifo_check(fbuf);
  if(status == LB_ERROR){
    return LB_ERROR;
  }
  else if(fbuf->count == fbuf->length){
    return LB_FULL;
  }
  else {
    return LB_NOT_FULL;
  }
}


Buffer_Status fifo_empty_check(_FIFO_TYPE* fbuf){
  Buffer_Status status = fifo_check(fbuf);
  if(status == LB_ERROR){
    return LB_ERROR;
  }
  else if(fbuf->count == 0){
    return LB_EMPTY;
  }
  else{
    return LB_NOT_EMPTY;
  }
}


Buffer_Status fifo_push(DATA_TYPE element, _FIFO_TYPE* fbuf){
  Buffer_Status status = fifo_full_check(fbuf);
  if(status == LB_ERROR){
    return LB_ERROR;
  }
  else if(status == LB_FULL){
    return LB_FULL;
  }
  else {
    if(fbuf->head == (fbuf->base + fbuf->length)) {
      fbuf->head = fbuf->base;
    }
    else {
      fbuf->head ++;
    }
  }
  *(fbuf->head) = element;
  fbuf->count ++;
  return LB_NO_ERROR;
}


Buffer_Status fifo_pull(DATA_TYPE* element, _FIFO_TYPE* fbuf){
  Buffer_Status status = fifo_empty_check(fbuf);
  if(status == LB_ERROR) {
    return LB_ERROR; 
  }
  else if(status == LB_EMPTY){
    return LB_EMPTY; 
  }
  else {
    *element = *(fbuf->tail);
    fbuf->count --;
    if(fbuf->tail >= (fbuf->base + fbuf->length) ) {
      fbuf->tail = fbuf->base;
    }
    else {
      fbuf->tail ++;
    }
    return LB_NO_ERROR;
  }
}


void fifo_reset(_FIFO_TYPE* fbuf){
  free((DATA_TYPE*)fbuf->base);
}
