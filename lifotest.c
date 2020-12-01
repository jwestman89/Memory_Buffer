/*
	**********************************************************************
	Applying a 2-core LIFO buffer with a Mutex lock.
	
	2020-11-17
	Johannes Westman
	**********************************************************************
*/

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include"datastruct.h"
#include<pthread.h>
#include<stdbool.h>

#define SIZE 5
#define WAIT_LONG  10000000000
#define WAIT_SHORT 1000000000
/* #define RAND_MAX 255 */

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile bool threadRunning = true;

void* write_to(void* buffer){
  LIFO_Buffer* lbuf = (LIFO_Buffer*)buffer;
  int i = 0;
  Buffer_Status pushStatus;
  while(i<SIZE+10) {
    /*uint8_t val = (uint8_t)rand();*/
    uint8_t val = (uint8_t)i;
    pthread_mutex_lock(&mutex);
    pushStatus = lifo_push(val,lbuf);
    pthread_mutex_unlock(&mutex);
    if(pushStatus == LB_ERROR){
      printf("Buffer error (push request failed)\n");
      threadRunning = false;
      return NULL;
    }
    else if(pushStatus == LB_FULL){
      printf("Buffer is full\n");
    }
    else {
    printf("Pushed %d\n", val);
    i++;    
    for(int j=0; j<WAIT_SHORT; j++); /* delay */
    }  
}
  threadRunning = false;
  return NULL;
}


void* read_from(void* buffer){
  LIFO_Buffer* lbuf = (LIFO_Buffer*)buffer;
  uint8_t val;
  Buffer_Status pullStatus;
  while(threadRunning == true) { 
    pthread_mutex_lock(&mutex);
    pullStatus = lifo_pull(&val, lbuf);
    pthread_mutex_unlock(&mutex);
    if(pullStatus == LB_EMPTY){
      //printf("Buffer is empty.\t"); /*no line break*/
    }
    else if(pullStatus == LB_ERROR){
      printf("Buffer error. Pull request failed.");
    }
    else {
      printf("%d pulled\n", val);
      for(int j=0; j<WAIT_LONG; j++); /* delay  */
    }
  }
  return NULL;
}


int main(){
  /* check the status of the buffer  */
  LIFO_Buffer lbuf = lifo_init(SIZE);
  Buffer_Status status = lifo_check(&lbuf);
  if(status != LB_NO_ERROR) {
    printf("error in buffer initialization\n");
    return -1;
  }
  /* create tthe threads */
  pthread_t writer,reader;
  pthread_create(&writer, NULL, write_to, (void*)&lbuf);
  pthread_create(&reader, NULL, read_from, (void*)&lbuf);
  
  /* close threads */
  pthread_join(writer, NULL);
  pthread_join(reader, NULL);

  /* free the buffer memory*/
  lifo_reset(&lbuf);
  printf("\nEND\n");
  return 1;
}
