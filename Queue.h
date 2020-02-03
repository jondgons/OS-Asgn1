#ifndef QUEUE_H
#define QUEUE_H

#include "GlobalVars.txt"

/**
 *@file Queue.h | Queue.c
 *@author Ethan Seiner
 *@date Jan. 11, 2020
 *@brief The purpose is to create a Queue struct and organize functions related to a Queue in the same file.
 */

/**
 *@struct Queue
 *This struct represents a queue.
 *@author Ethan Seiber
 *@var endQueue: An int that records the index of the end of the queue which is the index after the last element of the queue.
 *@var size: An int that represents the number of elements in the queue.
 *@var queueCap: An unsigned int to represent the capacity of the queue.
 *@var queue: An int array to represent putting data in a queue.
 */
struct Queue{
  int endQueue;
  int size;
  unsigned int queueCap;
  char** queue[SIZE]; 
};

/**
 *This function takes a Queue and an int and puts it in the Queue.
 *@author Ethan Seiber
 *@param que: A Queue struct pointer for data to be stored.
 *@param num: This is the int that will be stored in the Queue struct.
 *@date Jan. 11, 2020
 *@return Returns nothing because there is no need because the variable being modified is a Queue pointer.
 */
void push(struct Queue* que, char**);

/**
 *This function will remove the int from the beginning of the Queue.
 *@author Ethan Seiber
 *@param que: A Queue pointer that will be modified inside the function.
 *@date Jan. 11, 2020
 *@return Returns an int that is pulled out of the Queue.
 */
char** pop(struct Queue* que);

#endif
