/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

/**
 * Main function
 */
int main(int argc, char **argv)
{
	if(argc < 2 || argc > 2){
		printf("Usage: ./theBar <numCustomers>\n");
		return -1;
	}
	printBanner();
	init(); // initialize semaphores

	num_threads = atoi(argv[1]);

	// TODO - fire off customer thread
	pthread_t custThreads[num_threads];

	long i;
	int args[num_threads];
	for(i=0; i<num_threads; i++){
		//prepare customer thread arg
		args[i] = i;

		pthread_create(&custThreads[i], NULL, customer, &args[i]);
	}

	// TODO - fire off bartender thread
	pthread_t bartenderThread;
	pthread_create(&bartenderThread, NULL, bartender, NULL);

	
	// TODO - wait for all threads to finish
	for(i=0; i<num_threads; i++){
		pthread_join(custThreads[i], NULL);
	}
	pthread_join(bartenderThread, NULL);


	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	// TODO - unlink semaphores
	sem_unlink("/barEmpty");
	sem_unlink("/custEnter");
	sem_unlink("/drinkOrdered");
	sem_unlink("/makingDrink");
	sem_unlink("/drinkReady");
	sem_unlink("/custPaid");
	sem_unlink("/paymentConfirmed");
	sem_unlink("/custLeft");
	
	
	// TODO - create semaphores
	barEmpty = sem_open("/barEmpty", O_CREAT, 0600, 0);
	custEnter = sem_open("/custEnter", O_CREAT, 0600, 0);
	drinkOrdered = sem_open("/drinkOrdered", O_CREAT, 0600, 0);
	makingDrink = sem_open("/makingDrink", O_CREAT, 0600, 0);
	drinkReady = sem_open("/drinkReady", O_CREAT, 0600, 0);
	custPaid = sem_open("/custPaid", O_CREAT, 0600, 0);
	paymentConfirmed = sem_open("/paymentConfirmed", O_CREAT, 0600, 0);
	custLeft = sem_open("/custLeft", O_CREAT, 0600, 0);

	
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	// TODO - close semaphores
	sem_close(barEmpty);
	sem_unlink("/barEmpty");

	sem_close(custEnter);
	sem_unlink("/custEnter");

	sem_close(drinkOrdered);
	sem_unlink("/drinkOrdered");

	sem_close(makingDrink);
	sem_unlink("/makingDrink");

	sem_close(drinkReady);
	sem_unlink("/drinkReady");

	sem_close(custPaid);
	sem_unlink("/custPaid");

	sem_close(paymentConfirmed);
	sem_unlink("/paymentConfirmed");

	sem_close(custLeft);
	sem_unlink("/custLeft");
}
