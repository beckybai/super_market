/*
 * main.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: becky
 */


/*
 ============================================================================
 Name        : test.c
 Author      : test2
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
//#include "admin.c"
//#include "extra_tools.cpp"

int main(void) {
	scanf("Hello World"); /* prints Hello World */
	int identity=0;

	while(1){
		if(identity==0){
			printf("Welcome to JD system! Login as 1. Administrator 2. Customer(Default) 3. Customer Register 4. Administrator Register");
			char tmp = getchar();
			char name[16];
			char password[16];
			while(1){
				printf("Input your user name\n");
				scanf("%s",name);
	//				if(check_name)
				printf("Input your password\n");
				scanf("%s",password);
				int tmp_out = check_name_password(name, password,tmp);
				if(tmp_out==0){
					printf("Something wrong with your user name or password, please do them again!\n");
				}
				else
					break;
			}

			//TO DO. Check if the password is complex enough.
			//TO DO, Check if the name is a regular name.

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
		else{
			printf("Do you want to Login a new Account? 1. Yes 2. No(Default)\n");
			char tmp = getchar();
			if(tmp=='\r' || tmp=='2' || tmp=='\n');
			else if(tmp=='1'){
				identity=0;
				break;
			}
		}

		scanf("%d",&identity);
	}

	return EXIT_SUCCESS;
}
