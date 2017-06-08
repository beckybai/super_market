/*
 * information.h
 *
 *  Created on: Jun 7, 2017
 *      Author: becky
 */

#ifndef INFORMATION_H_
#define INFORMATION_H_

struct Customer_Info{
	int ID;
	char *username;
	char *password;
	int money; //a number show the money saved in the customer's pocket.
	int *items_buy; //an array which save the objects this customer buy in the past.
};

struct Administrator_Info{
	int ID;
	char *username;
	char *password;
	int profile;
};

struct Item_Info{
	int ID;
	float price;
	char *name;
	char *place_origin;
	int save_amount;
	int out_amount;
	char *place_now;
};


#endif /* INFORMATION_H_ */
