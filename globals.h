/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
int now_serving;	// customer's ID who is being served

//TODO - declare some semaphores
sem_t* barEmpty;
sem_t* custEnter; 
sem_t* drinkOrdered;
sem_t* makingDrink;
sem_t* drinkReady;
sem_t* custPaid;
sem_t* paymentConfirmed;
sem_t* custLeft;


#endif /* GLOBALS_H_ */
