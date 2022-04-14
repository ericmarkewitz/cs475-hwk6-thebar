/*
 * bartender.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "bartender.h"

#include <sys/time.h>

/**
 * Code for bartender thread.
 * Do not touch.
 */
void *bartender(void *args)
{
	int i;
	for (i = 0; i < num_threads; i++)
	{
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer()
{
	// TODO - synchronize
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
	sem_post(barEmpty); //Let customers outside know one person can come in

	sem_wait(custEnter); //Wait for a customer to enter
	
}

/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink()
{
	// TODO - synchronize
	sem_wait(drinkOrdered);
	

	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");

	sem_post(makingDrink);
	
	//Making drink now
	time_t t;
	srand((unsigned) time(&t));

	int mixTime = (rand() % 999995) + 5;
	
	usleep(mixTime); //make the drink for a random amount of time
}

/**
 * Gets payment from the correct customer
 */
void receivePayment()
{
	// TODO - synchronize
	// at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");
	sem_post(drinkReady); //hand the customer their drink

	sem_wait(custPaid); //wait until the customer has paid

	// got paid by the customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
	sem_post(paymentConfirmed); //let the customer know you got their payment
	
	sem_wait(custLeft); //wait until the customer has left to let someone else in
}
