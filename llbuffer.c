/*
	llbuffer.c
	*************************************************************
	Contains functions for a Linked-List-Buffer that can be used
	as an intermediary data storage when reading/writing unsynchr
	onized data. The buffer is stored in the heap. The LL is bidi
	rectional. The LL can be used if you're unsure whether or not
	you will have access to a sufficient amount of contignuous 
	memory for a LIFO or FIFO buffer.

	2020-11-30
	Johannes Westman
	*************************************************************

*/

#include<stdlib.h>
#include"buffer.h"


ll_Buffer ll_init(void){
  ll_Buffer* buf = (ll_Buffer*)malloc(sizeof(ll_Buffer));
  /*head*/
  ll_element* h = (ll_element*)malloc(sizeof(ll_element));
  h->previous = NULL;
  /*tail*/
  ll_element* t = (ll_element*)malloc(sizeof(ll_element));
  t->next = NULL;  

  buf->count = 0;
  buf->tail = t;
  buf->head = h;
  return *buf;
}


Buffer_Status ll_check(ll_Buffer* lbuf){
  if(lbuf->head == NULL || lbuf->tail == NULL) {
    return LB_ERROR;
  }
  else {
    return LB_NO_ERROR;
  }
}


Buffer_Status ll_empty_check(ll_Buffer* lbuf) {
  Buffer_Status status = ll_check(lbuf);
  if(status == LB_ERROR) {
    return LB_ERROR;
  }
  else if(lbuf->count <= 0){
    return LB_EMPTY;
  }
  else {
    return LB_NOT_EMPTY;
  }
}


Buffer_Status ll_push(DATA_TYPE data, ll_Buffer* lbuf){
  Buffer_Status status = ll_check(lbuf);
  ll_element* element = malloc(sizeof(ll_element));
  if(status == LB_ERROR){
    return LB_ERROR;
  }
  else if(element == NULL) {
    return LB_FULL;
  }
  else {
    element->data = data;
    element->next = lbuf->tail;
    if(lbuf->count == 0){
      (lbuf->tail)->previous = element;
      (lbuf->head)->next = element;
      element->previous = lbuf->head;
    }
    else {
      element->previous = (lbuf->tail)->previous;
      (lbuf->tail)->previous->next = element;
      (lbuf->tail)->previous = element;
    } 
    lbuf->count ++;
    return LB_NO_ERROR;
  }
}


Buffer_Status ll_pull(DATA_TYPE* data, ll_Buffer* lbuf) {
  Buffer_Status status = ll_check(lbuf);
  if(status == LB_ERROR){
    return LB_ERROR;
  }
  else if(lbuf->count == 0) {
    return LB_EMPTY;
  }
  else {
    /* pull the data */
    *data = (lbuf->head)->next->data;
    /* remove link to first node from 2nd node  */
    (lbuf->head)->next->next->previous = lbuf->head;
    ll_element* toDelete = (lbuf->head->next);
    /*remove link to first node from head*/
    (lbuf->head)->next = lbuf->head->next->next;
    /* delete first node */
    free(toDelete);
    lbuf->count --;
    return LB_NO_ERROR;
  }
}


void ll_reset(ll_Buffer* lbuf){
  free((ll_element*)lbuf->head);
  free((ll_element*)lbuf->tail);
  //free((ll_Buffer*)lbuf);
}
