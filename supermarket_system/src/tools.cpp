/*
 * extra_tools.c
 *
 *  Created on: Jun 8, 2017
 *      Author: becky
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector"
#include "myIO.cpp"


int check_name_password(char* name, char*password, char tmp){
	switch(tmp){
		case '1':
			Adminstrator(name,password);
			break;
		case '2':
			Customer(name, password);
			break;
		case '3':
			Customer_R(name, password);
			break;
		case '4':
			Adminstrator_R(name, password);
			break;
		default:
			Customer(name, password);
			break;
	}
}

