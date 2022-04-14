/*
 * customer.c
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
#include "customer.h"



/**
 * This is what the thread will call.
 * Do not touch.
 */
void* customer(void* args)
{
	unsigned int *custID = (unsigned int*) args;
	custTravelToBar(*custID);
	custArriveAtBar(*custID);
	custPlaceOrder();
	custBrowseArt();
	custAtRegister();
	custLeaveBar();
	return NULL;
}


/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(unsigned int custID)
{
	//TODO - synchronize
	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);

	time_t t;
	srand((unsigned) time(&t));

	int travelTime = (rand() % 4999980) + 20;
	
	usleep(travelTime);
}


/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(unsigned int custID)
{
	//TODO - synchronize
	sem_wait(barEmpty); //Wait for the bar to empty before entering
	
	now_serving = custID;

	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);

	sem_post(custEnter); //Let the bartender know you are there
}


/**
 * The customer in the bar places an order
 */
void custPlaceOrder()
{
	//TODO - synchronize
	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", now_serving);
	
	sem_post(drinkOrdered); //Let the bartender know you put your drink order in

}


/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt()
{
	//TODO - synchronize
	sem_wait(makingDrink);//now that the bartender is making your drink you can go browse the wall at
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", now_serving);

	time_t t;
	srand((unsigned) time(&t));

	int browseTime = (rand() % 3999997) + 3;
	
	usleep(browseTime); //browse for a random amount of time
}


/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister()
{
	//TODO - synchronize

	sem_wait(drinkReady);//wait to pay until you drink is ready

	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", now_serving);

	

	sem_post(custPaid); //let the bartender know you paid
}


/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar()
{
	//TODO - synchronize
	sem_wait(paymentConfirmed); // wait to leave until the payment is confirmed
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", now_serving);
	sem_post(custLeft); // let the bartender know you left
}
