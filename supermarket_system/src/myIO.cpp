/*
 * myIO.cpp
 *
 *  Created on: Jun 8, 2017
 *      Author: becky
 */
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "vector"
#include "information.h"
using namespace std;
//获得所有客户的信息，并以一个向量的形式返回
vector<Customer_Info*> get_customer_info(){
	FILE *fp;
	vector<Customer_Info*> CI_v;
	if(NULL==(fp=fopen("customer_info.txt","r"))){
		printf("error when opening the customer_info.txt");
		exit(-1);
	}
	else{
		char tmp_line[100];
//	    fp = fopen("in.txt", "r");//打开文件
	    while(fgets(tmp_line, sizeof(tmp_line), fp))//每次读取一行数据，直到读取失败。
	    {
	        printf("%s\n", tmp_line); //打印该行。
	        // The structure of this is username, password, money, items_buy.
	        Customer_Info* new_customer = new Customer_Info();
	        char* name = strtok( tmp_line, ",");
	        new_customer->username = name;
	        char* password = strtok(NULL, ",");
	        new_customer->password = password;
	        char* money = strtok(NULL, ",");
	        new_customer->money= atoi(money);

	        char* items = strtok(NULL, ",");

	        int* item_list = new int[100]; // 假设这个人最多买了100个东西啊。
	        char* token = strtok(items,"|");
	        int tmp_i = 0;
	        while( token != NULL)
	        {
	        	item_list[tmp_i] = atoi(token);
	            token = strtok( NULL, ” “);
	        }
	        new_customer->items_buy = item_list;
	        CI_v.push_back(new_customer);
	    }
	    fclose(fp);
	}
	return CI_v;
}



