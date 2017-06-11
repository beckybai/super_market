 /*============================================================================
 Name        : test.cpp
 Author      : Becky
 Version     :
 Copyright   : Your copyright notice
 Description : Project for the C programming class
 ============================================================================
 */

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
//#include "myIO.cpp"
//#include "customer.cpp"
//#include "store.cpp"
//#include "information.h"


//#include "admin.c"
//#include "extra_tools.cpp"
using namespace std;
int get_num(){
	int i;
	scanf("%d",&i);
	return i;
}

//消费者信息
struct Customer_Info{
//	int ID;
	string username;
	string password;
	float money; //a number show the money saved in the customer's pocket.
	vector<int> items_buy; //an array which save the objects this customer buy in the past.
};

//管理者信息
struct Administrator_Info{
//	int ID;
	string username;
	string password;
//	int profile;
};

//商品信息
struct Good_Info{
	int ID;
	float price;
	string name;
	string place_origin;
	int save_amount;
	int out_amount;
	string place_now;
	// bool operator < (const Good_Info* g) cosnt{
	// 	return save_amount < g->save_amount;
	// }
};

bool good_up(const Good_Info* a,const Good_Info *b){
	return a->save_amount < b->save_amount;
}

bool good_down(const Good_Info* a,const Good_Info *b){
	return a->save_amount > b->save_amount;
}

//购物车信息
struct Shopping_Cart_Info{
	string name;
	string good_name;
	int ID;
	int num;
};

//排序所需结构
struct node{
	int value;
	int ID;
};

//升序
bool cmp_up(struct node a,  struct node b){
	if(a.value<b.value){
		return true;
	}
	return false;
}

//降序
bool cmp_down(struct node a, struct node b){
	if(a.value>b.value){
		return true;
	}
	return false;
}


// int up_sort(const void * a, const void * b) {
//     int diff = arr[*(int*)a] - arr[*(int*)b];
//     return  diff;
// }

// int down_sort(const void * a, const void * b) {
//     int diff = -arr[*(int*)a] + arr[*(int*)b];
//     return  diff;
// }

string get_string(){
	// printf("Input your user name\n");
	char tmp[101];
	scanf("%100s", tmp);
	fflush(stdin);
	string name= tmp;
	return name;
}

//打印出商品的信息
void print_good_store(Good_Info* good){
	printf("%d \t %.2f \t %s \t %s \t %d \t %d \t %s \n",good->ID,good->price,(good->name).c_str(),(good->place_origin).c_str(),good->save_amount,good->out_amount,(good->place_now).c_str());
}

vector<Administrator_Info*> get_administrator_info(){
	FILE *fp;
	vector<Administrator_Info*> CI_v;
	if(NULL==(fp=fopen("administrator_info.txt","r"))){
		printf("error when opening the customer_info.txt");
		exit(-1);
	}
	else{
		char tmp_line[100];
//	    fp = fopen("in.txt", "r");//打开文件
	    while(fgets(tmp_line, sizeof(tmp_line), fp))//每次读取一行数据，直到读取失败。
	    {
	        // printf("%s\n", tmp_line); //打印该行。
	        // The structure of this is username, password, money, items_buy.
	        Administrator_Info* new_admin = new Administrator_Info();
	        char* name = strtok( tmp_line, ",");
	        new_admin->username = name;
	        // printf("%s\n",name);
	        char* password = strtok(NULL, ",");
	        new_admin->password = password;
	        // printf("%s\n",password);
	    	CI_v.push_back(new_admin);
	    }
	}
	return CI_v;
}


//获得顾客的信息
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
	        // printf("%s\n", tmp_line); //打印该行。// TO DO: cancel this!!
	        // The structure of this is username, password, money, items_buy.
	        Customer_Info* new_customer = new Customer_Info();
	        char* name = strtok( tmp_line, ",");
	        new_customer->username = name;
	        char* password = strtok(NULL, ",");
	        new_customer->password = password;
	        char* money = strtok(NULL, ",");
	        new_customer->money= atoi(money);

	        // char* items = strtok(NULL, ",");

	        // vector<int> item_list; // 假设这个人最多买了100个东西啊。get_customer_info
	        // char* token = strtok(items,"|");
	        // int tmp_i = 0;
	        // while( token != NULL)
	        // {
	        // 	item_list.push_back(atoi(token));
	        //     token = strtok(NULL, "|");
	        //     tmp_i ++;
	        // }
	        // new_customer->items_buy = item_list;
	        CI_v.push_back(new_customer);
	    }
	    fclose(fp);
	}
	return CI_v;
}

//将顾客的信息写入文件
void write_customer_info(vector<Customer_Info*> vsi){
	//write back all the customer's information.
	FILE *fp;
	if(NULL==(fp=fopen("customer_info.txt","w"))){
		printf("error when opening the customer_info.txt");
		exit(-1);
	}
	else{
		Customer_Info *custom;
		int vsi_len = vsi.size();
		int tmp_i = 0;

		for(tmp_i;tmp_i<vsi_len;tmp_i++){
			custom = vsi[tmp_i];
			int tmp_j = 0;
			fprintf(fp,"%s,%s,%f",(custom->username).c_str(),(custom->password).c_str(),custom->money);
			int item_len = (custom->items_buy).size();
			for(tmp_j;tmp_j<item_len-1;tmp_j++){
				fprintf(fp,"%d|",custom->items_buy[tmp_j]);
			}
			if(item_len)
				fprintf(fp,"%d\n",custom->items_buy[item_len-1]);
			else
				fprintf(fp, "\n");
		}
		fclose(fp);
	}
}

void write_administrator_info(vector<Administrator_Info*> vsi){
	//write back all the customer's information.
	FILE *fp;
	if(NULL==(fp=fopen("administrator_info.txt","w"))){
		printf("error when opening the administrator_info.txt");
		exit(-1);
	}
	else{
		Administrator_Info *custom;
		int vsi_len = vsi.size();
		int tmp_i = 0;

		for(tmp_i;tmp_i<vsi_len;tmp_i++){
			custom = vsi[tmp_i];
			int tmp_j = 0;
			fprintf(fp,"%s,%s\n",(custom->username).c_str(),(custom->password).c_str());
		}
		fclose(fp);
	}
}

void print_good(Good_Info &good){
	printf("%d \t %.2f \t %s \t %s \t %d \t %d \t %s\n",good.ID,good.price,(good.name).c_str(),(good.place_origin).c_str(),good.save_amount,good.out_amount,(good.place_now).c_str());
}

//int ID;
//float price;
//char *name;
//char *place_origin;
//int save_amount;
//int out_amount;
//char *place_now;
vector<Good_Info*> get_goods_info(){
	FILE *fp;
	vector<Good_Info*> GI_v;
	if(NULL==(fp=fopen("good_info.txt","r"))){
		printf("error when opening the good_info.txt");
		exit(-1);
	}
	else{
		char tmp_line[100];
//	    fp = fopen("in.txt", "r");//打开文件
	    while(fgets(tmp_line, sizeof(tmp_line), fp))//每次读取一行数据，直到读取失败。
	    {
	        // printf("%s\n", tmp_line); //打印该行。
	        // The structure of this is username, password, money, items_buy.
	        Good_Info* good = new Good_Info();
	        // char* delim = ",";
	        char* ID = strtok( tmp_line, ",");
	        good->ID = atoi(ID);
	        // printf("%d",good->ID);
	        char* price = strtok(NULL,",");
	        good->price = atoi(price);
	        char* name = strtok(NULL, ",");
	        good->name = name;
	        // printf("%s\n",(good->name).c_str());
	        char* place_origin = strtok(NULL, ",");
	        good->place_origin = place_origin;
	        // printf("%s\n",(good->place_origin).c_str());
	        char* save_amount = strtok(NULL,",");
	        good->save_amount = atoi(save_amount);
	        // printf("%d",good->save_amount);
	        char* out_amount = strtok(NULL,",");
	        good->out_amount = atoi(out_amount);
	        char* place_now = strtok(NULL,",");
	        good->place_now = place_now;

	        // printf("%s\n",(good->name).c_str());
	        // print_good(*good);
	        GI_v.push_back(good);
	    }
	    fclose(fp);
	}
	return GI_v;
}

int check_password(string password){
	if(password.size()<6){
		printf("The length of the password has to be over 6\n");
		return 0;
	}

	FILE *fp;
	if(NULL==(fp=fopen("easy_password.txt","r"))){
		printf("error when opening the easy_password.txt\n");
		exit(-1);
	}
	else{
		char tmp_line[100];
		while(fgets(tmp_line,sizeof(tmp_line),fp)){
			// printf("%s", tmp_line);
			// printf("%s\n",line);
			// printf("%d",password.compare(tmp_line));
			if(password.compare(tmp_line)==-1){
				printf("your password is too simple!\n");
				return 0;
			}
		}
	}
	return 1;
}

// int* save_amount_sort(int *seq, int len){
// 	int* perm = new int[len];
// 	int tmp_i = 0;
// 	for(tmp_i=0;tmp_i<len;tmp_i++){
// 		perm[i]=i;
// 	}
// 	qsort()

// }


void write_goods_info(vector<Good_Info*> vgi){
	FILE *fp;
	if(NULL==(fp=fopen("good_info.txt","w"))){
		printf("error when opening the customer_info.txt\n");
		exit(-1);
	}
	else{
		Good_Info *good = new Good_Info();
		int vsi_len = vgi.size();
		int tmp_i = 0;

		for(tmp_i;tmp_i<vsi_len;tmp_i++){
			good  = vgi[tmp_i];
			fprintf(fp,"%d,%f,%s,%s,%d,%d,%s",good->ID,good->price,(good->name).c_str(),(good->place_origin).c_str(),good->save_amount,good->out_amount,(good->place_now).c_str());
		}
		fclose(fp);
	}
}

void delete_good(vector<Good_Info*> good_list,int tmp_delete){
		int flag =  0;
		int good_list_size = good_list.size();
		int tmp_i = 0;
		for(tmp_i=0;tmp_i<good_list_size;tmp_i++){
			if(good_list[tmp_i]->ID==tmp_delete){
				good_list.erase(good_list.begin()+tmp_i);
				flag=1;
			}
		}
		if(flag){
			printf("You have successfully delete the object!\n");
		}
		else{
			printf("Can't find the object you want to delete!\n");
		}
}



void write_cart(string name, int ID, string good_name, int num ){
	FILE *fp;
	if(NULL==(fp=fopen("cart_info.txt","a"))){
		printf("error when opening the cart_info.txt");
		exit(-1);
	}
	else{
		fprintf(fp,"%s,%d,%s,%d\n",name.c_str(),ID,good_name.c_str(),num);
	}
	fclose(fp);
}



vector<Shopping_Cart_Info*> get_cart_info(){
	FILE* fp;
	vector<Shopping_Cart_Info*> sci;
	if(NULL==(fp=fopen("cart_info.txt","r"))){
		printf("error when opening the cart_info.txt");
		exit(-1);
	}
	else{
		char tmp_line[100];
//	    fp = fopen("in.txt", "r");//打开文件
	    while(fgets(tmp_line, sizeof(tmp_line), fp))//每次读取一行数据，直到读取失败。
	    {
	        printf("%s\n", tmp_line); //打印该行。
	        // The structure of this is username, password, money, items_buy.
	        Shopping_Cart_Info* cart = new Shopping_Cart_Info();
	        // char *delim = ",";
	        char* name = strtok(tmp_line, ",");
	        cart->name = name;
	        char* id = strtok(NULL, ",");
	        cart->ID = atoi(id);
//	        good->place_origin = place_origin;
	        char* good_name = strtok(NULL,",");
	        cart->good_name = good_name;
	        char* num = strtok(NULL,",");
	        cart->num = atoi(num);
	        sci.push_back(cart);
	    }
	    fclose(fp);
	    return sci;
	}
}

vector<Shopping_Cart_Info*> get_buy_info(){
	FILE* fp;
	vector<Shopping_Cart_Info*> sci;
	if(NULL==(fp=fopen("buy_info.txt","r"))){
		printf("error when opening the buy_info.txt");
		exit(-1);
	}
	else{
		char tmp_line[100];
//	    fp = fopen("in.txt", "r");//打开文件
	    while(fgets(tmp_line, sizeof(tmp_line), fp))//每次读取一行数据，直到读取失败。
	    {
	        // printf("%s\n", tmp_line); //打印该行。
	        // The structure of this is username, password, money, items_buy.
	        Shopping_Cart_Info* cart = new Shopping_Cart_Info();
	        // char *delim = ",";
	        char* name = strtok(tmp_line, ",");
	        cart->name = name;
	        char* id = strtok(NULL, ",");
	        cart->ID = atoi(id);
//	        good->place_origin = place_origin;
	        char* good_name = strtok(NULL,",");
	        cart->good_name = good_name;
	        char* num = strtok(NULL,",");
	        cart->num = atoi(num);
	        sci.push_back(cart);
	    }
	    fclose(fp);
	    return sci;
	}
}


void write_cart_info(vector<Shopping_Cart_Info*> sci){
	FILE* fp;
	if(NULL==(fp=fopen("cart_info.txt","w"))){
		printf("error when opening the cart_info.txt");
		exit(-1);
	}
	else{
		int sci_len = sci.size();
		int tmp_i = 0;
		for(tmp_i;tmp_i<sci_len;tmp_i++){
			Shopping_Cart_Info* cart = sci[tmp_i];
			fprintf(fp,"%s,%d,%s,%d\n",(cart->name).c_str(),cart->ID,(cart->good_name).c_str(),cart->num);
		}
	}
	fclose(fp);
}

void write_buy_info(vector<Shopping_Cart_Info*> sci){
	FILE* fp;
	if(NULL==(fp=fopen("buy_info.txt","w"))){
		printf("error when opening the buy_info.txt");
		exit(-1);
	}
	else{
		int sci_len = sci.size();
		int tmp_i = 0;
		for(tmp_i;tmp_i<sci_len;tmp_i++){
			Shopping_Cart_Info* cart = sci[tmp_i];
			fprintf(fp,"%s,%d,%s,%d\n",(cart->name).c_str(),cart->ID,(cart->good_name).c_str(),cart->num);
		}
	}
	fclose(fp);
}


void scan_good_store(){
	vector<Good_Info*> good_list = get_goods_info();
	while(1){
		printf("what do you want to do? Please enter the 0 to leave the system, otherwise the change will not be saved! \n");
		printf("1. Scan the goods in the store\n");
		printf("2. Delete the goods\n");
		printf("3. Add new goods to the store\n");
		printf("4. Revise the information of the goods\n");
		printf("5. Rank according to the left amount\n"); //TO DO!!!
		printf("0, Exist\n");
		int tmp_char=get_num() ;
		// scanf("%c",&tmp_char);
		fflush(stdin);
		int tmp_i = 0;
		switch(tmp_char){
		case 1:{
			int good_list_size = good_list.size();
			printf("---------------------------------------------------------\n");
			printf("No\tID\tPrice\tName\tOrigin_place\tSave_amount\tOut_amount\tPlace_now\n");
			printf("---------------------------------------------------------\n");

			for(tmp_i=0;tmp_i<good_list_size;tmp_i++){
				printf("%d\t",tmp_i);
				print_good_store(good_list[tmp_i]);
			}

			for(tmp_i=0;tmp_i<good_list_size;tmp_i++){
				if(good_list[tmp_i]->save_amount <10){
					printf("This number of %s is not enough !\n", good_list[tmp_i]->name);
				}
			}
			break;
		}
		case 2:{
			printf("Please input the id of the object you want to delete!\n");
			int tmp_delete;
			scanf("%d",&tmp_delete);
			delete_good(good_list,tmp_delete);
			break;
		}
		case 3:{
			//int ID;
			//float price;
			//char *name;
			//char *place_origin;
			//int save_amount;
			//int out_amount;
			//char *place_now;
			Good_Info* new_one = new Good_Info();
			printf("Input the ID\n");
			int tmp_ID;scanf("%d",&tmp_ID);
			fflush(stdin);
			new_one->ID = tmp_ID;
			printf("Input the price\n");
			float price;scanf("%f",&price);fflush(stdin);
			new_one->price = price;
			printf("Input the name\n");
			new_one->name = get_string();
			printf("Input the place origin\n");
			new_one->place_origin = get_string();
			printf("Input the store where it exists\n");
			new_one->place_now = get_string();
			new_one->place_now +='\n';
			printf("Input the total amount\n");
			int tmp_amount;scanf("%d",&tmp_amount);fflush(stdin);
			new_one->save_amount = tmp_amount;
			new_one->out_amount = 0; //Since it is a new good, no one has ever buy it ;)
			good_list.push_back(new_one);
			break;
		}
		case 4:{
			int good_list_size = good_list.size();
			printf("Please input the id of the object you want to revise!\n");
			int tmp_delete;
			scanf("%d",&tmp_delete);fflush(stdin);
			int flag =  0;
			for(tmp_i=0;tmp_i<good_list_size;tmp_i++){
				if(good_list[tmp_i]->ID==tmp_delete){
					// good_list.erase(good_list.begin()+tmp_i);
					flag=1;
					break;
				}
			}
			if(flag){
				printf("which information do you want to change? 1. ID 2. price 3. place_origin 4. place_now,5. save_amount 6. out_amount\n");
				int tmp_choice =get_num();
				fflush(stdin);
				printf("give a new one,please\n");
				switch(tmp_choice){
					case 1:
						int tmp_ID;scanf("%d",&tmp_ID);fflush(stdin);
						good_list[tmp_i]->ID = tmp_ID;
						break;
					case 2:
						float price;scanf("%f",&price);fflush(stdin);
						good_list[tmp_i]->price = price;
						break;
					case 3:
						good_list[tmp_i]->place_origin= get_string();
						break;
					case 4:
						good_list[tmp_i]->place_now = get_string();
						break;
					case 5:{
						int tmp_amount;scanf("%d",&tmp_amount);fflush(stdin);
						good_list[tmp_i]->save_amount = tmp_amount;
						break;
					}
					case 6:{
						int tmp_amount;scanf("%d",&tmp_amount);fflush(stdin);
						good_list[tmp_i]->out_amount = tmp_amount;
						break;
					}
					default:
						printf("Oh! you shouldn't come here.\n");
						break;
				}
			}
			else{
				printf("Can't find the object you want to delete!\n");
			}
			break;
		}
		case 5:{
			int good_list_size = good_list.size();
			printf("Do you want to have up-sort(0) or down-sort(1)?\n");
			int tmp = get_num();
			if(tmp){
				sort(good_list.begin(),good_list.end(),good_up);
			}
			else
				sort(good_list.begin(),good_list.end(),good_down);

			break;
		}

		case 0:{
			write_goods_info(good_list);//Write all the things back to the file.
			printf("Bye!\n");
			return;
		}

		default:{
			printf("More function is waiting to be written!\n");
			break;
		}
		}
	}
}


void scan_good(Customer_Info* customer){
	vector<Good_Info*> good_list = get_goods_info();
	int good_list_size = good_list.size();
	int tmp_i = 0;

	printf("------------------------Goods_Info---------------------------------\n");
	printf("No\tID\tPrice\tName\tOrigin_place\tSave_amount\tOut_amount\tPlace_now\n");
	printf("-------------------------------------------------------------------\n");


	for(tmp_i;tmp_i<good_list_size;tmp_i++){
		printf("%d\t",tmp_i);
		print_good(*good_list[tmp_i]);
	}

	while(1){
		printf("What do you like ? Please print the ID of the good, thanks! press -1 to exit\n");
		int tmp_id;
		scanf("%d",&tmp_id);fflush(stdin);

		// printf("test_error!\n");

		if(tmp_id==-1)
			break;

		int flag = 0;
		int this_one = 0;
		for(tmp_i=0;tmp_i<good_list_size;tmp_i++){
			if(tmp_id==good_list[tmp_i]->ID){
				this_one = tmp_i;
				flag = 1;
					// printf("test_error!\n");

			}
		}
		// printf("test_error!\n");

		if(!flag){
			printf("We don't have the thing you want to buy! Please choice another one! \n ");
			continue;
		}

		// printf("test_error2!\n");

		if(good_list[this_one]->save_amount==0){
			printf("Sorry, this good has already been sold out!\n");
		}
		else{
			printf("How much do you want to buy? ");
			int tmp_num;
			scanf("%d",&tmp_num);fflush(stdin);
			if(tmp_num>good_list[this_one]->save_amount){
				tmp_num = good_list[this_one]->save_amount;
				printf("We don't have enough thing... So you can only buy %d.",good_list[this_one]->save_amount);
			}

			printf("Add this thing to your shopping cart!\n");
			write_cart(customer->username, good_list[this_one]->ID, good_list[this_one]->name,tmp_num);
			good_list[this_one]->save_amount -= tmp_num;
			write_goods_info(good_list);
		}
	}
}

void print_shopping_cart(Customer_Info*customer){
	vector<Shopping_Cart_Info*> sci = get_cart_info();
	int sci_len = sci.size();
	int tmp_i = 0;
	printf("-----------------------Your Shopping_Cart_Info----------------------------\n");
	printf("ID\tname\tnumber\n");
	printf("--------------------------------------------------------------------------\n");

	for(tmp_i;tmp_i<sci_len;tmp_i++){
		if(sci[tmp_i]->name==customer->username && sci[tmp_i]->num!=0)
			printf("%d\t%s\t%d\n",sci[tmp_i]->ID,(sci[tmp_i]->good_name).c_str(),sci[tmp_i]->num);
	}
}

void print_buy_info(Customer_Info *customer){
	vector<Shopping_Cart_Info*> sci = get_buy_info();
	int sci_len = sci.size();
	int tmp_i = 0;
	printf("-----------------------Things you already buy-----------------------------\n");
	printf("ID\tname\tnumber\n");
	printf("--------------------------------------------------------------------------\n");

	for(tmp_i;tmp_i<sci_len;tmp_i++){
		if(sci[tmp_i]->name==customer->username && sci[tmp_i]->num!=0)
			printf("%d\t%s\t%d\n",sci[tmp_i]->ID,(sci[tmp_i]->good_name).c_str(),sci[tmp_i]->num);
	}
}

void return_goods(Customer_Info * customer){
	vector<Shopping_Cart_Info*> sci = get_buy_info();
	vector<Good_Info*> good_list = get_goods_info();
	int good_list_size = good_list.size();
	print_buy_info(customer);
	printf("Print the ID of the object you want to give it back?\n");
	int tmp_back;
	int tmp_back_num;
	scanf("%d",&tmp_back);
	int flag =  0;
	int tmp_i = 0;
	for(tmp_i=0;tmp_i<good_list_size;tmp_i++){
		if(good_list[tmp_i]->ID==tmp_back){
			// good_list.erase(good_list.begin()+tmp_i);
			flag=1;
			printf("Print the number of the object you want to give it back. Please do not over the things you already buy \n");
			scanf("%d",&tmp_back_num);
			break;
		}
	}
	if(flag){
		good_list[tmp_i]->save_amount += tmp_back_num;
		customer->money += good_list[tmp_i]->price * tmp_back_num;
		printf("Now, your pocket has %f Yuan\n", customer->money);
		sci.erase(sci.begin()+tmp_i);
		write_goods_info(good_list);
		write_buy_info(sci);
	}
	else{
		printf("You may input the wrong info.\n");
	}

}

void clear_cart(Customer_Info*customer){
	//1st: find the user's record in the shopping cart file;
	vector<Shopping_Cart_Info*> sci = get_cart_info(); // THings in the shoppoing cart
	vector<Shopping_Cart_Info*> buy_good = get_buy_info();
	printf("Be sure of the safe1\n");
	vector<Good_Info*> gi  = get_goods_info(); // Things in the store

	// vector<Customer_Info*> ci = get_customer_info(); // Get the information of all the customers.
		printf("Be sure of the safe2\n");
	int sci_len = sci.size();
	int gi_len = gi.size();
	printf("shopping cart size: %d\n", sci_len);

	int tmp_i = 0;
	string username = customer->username;

	int total_expense = 0;

	for(tmp_i=0;tmp_i<sci_len;tmp_i++)
	{
		int tmp_j = 0;
		Shopping_Cart_Info* tmp_sci = sci[tmp_i];
		Shopping_Cart_Info* tmp_buy = new Shopping_Cart_Info();

		int ID = tmp_sci->ID;
		string name = tmp_sci->name;
		int num_buy = tmp_sci ->num;
		if(username==name){
			for(tmp_j;tmp_j<gi_len;tmp_j++){
				if(ID == gi[tmp_j]->ID){
					printf("Be sure of the safe3\n");
					if(gi[tmp_j]->save_amount >= tmp_sci->num){	//2ed: check if there are enough things in the storage.
						gi[tmp_j]->save_amount -=tmp_sci->num;
						total_expense += gi[tmp_j]->price * tmp_sci->num;
						sci[tmp_i]->num = 0;
						if(total_expense > customer->money){
							printf("Sorry, you can only buy %s because you don't have enough money!", sci[tmp_i]->name);
							continue;
						}
						else{
							customer->money = customer->money - total_expense;
							tmp_buy->ID = ID;
							tmp_buy->good_name = gi[tmp_j]->name;
							tmp_buy->name = name;
							tmp_buy->num = num_buy;
							buy_good.push_back(tmp_buy);
						}
						// TO DO  Change the information of the customer.
					}
					else if(gi[tmp_j]->save_amount>0){
						printf("Sorry for that, we don't have enough things\n");
						total_expense +=gi[tmp_j]->price * gi[tmp_j]->save_amount;
						if(total_expense > customer->money){
							printf("Sorry, you can only buy these things because you don't have enough money!");
						}
						else{
							sci[tmp_i]->num -= gi[tmp_j]->save_amount;
							gi[tmp_j]->save_amount = 0;
							customer->money = customer->money - total_expense;
							tmp_buy->ID = ID;
							tmp_buy->good_name = gi[tmp_j]->name;
							tmp_buy->name = name; 
							tmp_buy->num = gi[tmp_j]->save_amount;
							buy_good.push_back(tmp_buy);
						}
					}
					else{
						printf("Sorry, we don't have that thing now\n");
					}
				}
			}
		}
	}
	printf("-----------------------------------------------------------\n");
	printf("Attention!\n You spend %d Yuan in total\n",total_expense);
	printf("You still have %.2f Yuan in yoru account\n", customer->money);
	printf("-----------------------------------------------------------\n");


	vector<Shopping_Cart_Info*>::iterator it = sci.begin();
	// printf("%d",(**it).num);
	// printf("233\n"); 
	tmp_i = 0;
	for(it;it!=sci.end();)
    {
    	// printf("num: %d",(*it)->num);
        if(sci[tmp_i++]->num==0){ // Delete the things in the cart which the customer has already bought.
        	// printf("Safe Alert!\n");
        	// ++it;
            it=sci.erase(it);    //删除元素，返回值指向已删除元素的下一个位置    
        }
        else
            ++it;    //指向下一个位置
    }
	// for(tmp_i=0;tmp_i<sci_len;tmp_i++){
	// 	if(sci[tmp_i]->num==0){
	// 		sci.erase(sci.begin()+tmp_i);
	// 		// sci_len--;
	// 		// tmp_i--;
	// 	}
	// }

	//3rd: update the storage. update the shopping cart.
	write_goods_info(gi);
	write_cart_info(sci);
	write_buy_info(buy_good);
	//TO DO  Update the information of the customer.
}


string get_name(){
	printf("Input your user name\n");
	char *tmp = new char[101];
	scanf("%s", tmp);fflush(stdin);
	string name= tmp;
	return name;
}

string get_password(){
	printf("Input your user password\n");
	char *tmp = new char[101];
	scanf("%s", tmp);fflush(stdin);
	// printf("hieheihei\n");
	string password= tmp;
	return password;
}



Customer_Info* check_customer_info(vector<Customer_Info*> vci, string name, string password){
	Customer_Info* this_one;
	int tmp_i = 0;
	int total_customer = vci.size();
	for(tmp_i;tmp_i<total_customer;tmp_i++){
		if(name==vci[tmp_i]->username){
			if(password==vci[tmp_i]->password){
				// printf("%d",vci[tmp_i]->password);
				return vci[tmp_i];
			}
			else{
				printf("You password is incorrect!\n");
				return 0;
			}
		}
	}

	printf("You hasn't register on our website. Please register first.\n");
	return 0;
}

Administrator_Info* check_admin_info(vector<Administrator_Info*> vai, string name, string password){
	Administrator_Info* this_one;
	int tmp_i = 0;
	int total_customer = vai.size();
	for(tmp_i;tmp_i<total_customer;tmp_i++){
		if(name == vai[tmp_i]->username){
			printf("password:%s, %s\n",password.c_str(), (vai[tmp_i]->password).c_str());
			if(password.compare(vai[tmp_i]->password)==-1){
				return vai[tmp_i];
			}
			else{
				printf("You password is incorrect!\n");
				return 0;
			}
		}
	}
	printf("You hasn't register on our website. Please register first.\n");
	return 0;
}


void Adminstrator(){
	string name = get_name();
	string password = get_password();
	vector<Administrator_Info*> vai = get_administrator_info();
	Administrator_Info* this_one = check_admin_info(vai,name,password);
	//1st, check the rightness of the name and the password.
	//2ed, several choices for the administrator.
	if(this_one){
		printf("Congratulations! You have logged in!\n");
		scan_good_store();
	}
	else{
		printf("there is something wrong with your username or password!\n");
	}
}

void Customer(){
	vector<Customer_Info*> customer_list = get_customer_info();
	while(1){
		string name = get_name();
		string password = get_password();
		// Check the information of this customer.
		Customer_Info* this_one = check_customer_info(customer_list,name, password);
		if(this_one){
			float money = this_one->money;
			printf("You still have %f Yuan.\n",money);
			if(money<100){
				printf("Do you want charge your account?(1-Y/0-n)");
				// char choice = getchar();
				int choice =get_num();
				fflush(stdin);
				if(choice==1){
					printf("Input the money: ");
					float charge;
					scanf("%f",&charge);fflush(stdin);
					this_one->money = this_one->money+charge;
					printf("Now, you have %f Yuan", this_one->money);
				}
			}

			while(1){
				printf("what do you want to do ?\n");
				printf("1. Check the things you already buy\n");
				printf("2. Scan the goods in the store\n");
				printf("3. Check your shopping Cart\n");
				printf("4. Clear your Cart, Buy\n");
				printf("5. Send back the good\n");
				printf("-1 exit\n");
				// char a = 'a';
				int tmp_char = get_num();
				switch(tmp_char){
					case 1:
						print_buy_info(this_one);
						break;
					case 2:
						scan_good(this_one);
						break;
					case 3:
						print_shopping_cart(this_one);
						break;
					case 4:
						clear_cart(this_one);
						break;
					case 5:
						return_goods(this_one);
						break;

					case -1:
						write_customer_info(customer_list);
						printf("Thanks for your log in, Good bye!\n");
						return;
					default:
						printf("PLease input a right number\n");
						// char tmp ;
						break;
				}
			}
		}
	}
}

void Customer_R(){
	while(1){
		vector<Customer_Info*> customer_list = get_customer_info();
		string name = get_name();
		string password ;
		while(1){
		password = get_password();
		if(!check_password(password)){
			printf("Your password is not permitted!\n");
		}
		else
			break;
		}
		printf("Reinput the password please\n");
		string password2 = get_password();


		if(password==password2){
			int tmp_i = 0;
			int total_customer = customer_list.size();
			printf("%d",total_customer);
			for(tmp_i=0;tmp_i<total_customer;tmp_i++){
				if(name == customer_list[tmp_i]->username){
					printf("This name has been registered on our website. Please load in or change another user name.\n");
					break;
				}
			}
			Customer_Info* new_customer = new Customer_Info();
			printf("2332\n");
			new_customer->username = name;
			new_customer->password = password;
			printf("Do you want to charge?(1 yes/0 no)\n");
			int tmp_d = get_num();
			if(tmp_d ==1){
				printf("Input the amount:");
				int money;
				scanf("%d",&money);fflush(stdin);
				new_customer->money = money;
			}
			else
				new_customer->money = 0;

			customer_list.push_back(new_customer); // Add new person to the list.
			write_customer_info(customer_list);
			printf("successfully registered, please login in later\n");
			break;

		}
		else
			printf("password is different at two times\n");
	}
}

void Adminstrator_R(){
	while(1){
		string name = get_name();
		vector<Administrator_Info*> administrator_list = get_administrator_info();
		string password ;
		while(1){
			password = get_password();
			if(!check_password(password)){
				printf("Your password is not permitted!\n");
			}
			else
				break;
		}
		printf("Reinput the password please\n");
		string password2 = get_password();
		if(password==password2){
			Administrator_Info* this_one;
			int tmp_i = 0;
			int total_customer = administrator_list.size();
			for(tmp_i;tmp_i<total_customer;tmp_i++){
				if(name==administrator_list[tmp_i]->username){
					printf("This name has been registered on our website. Please load in or change another user name.\n");
					break; // this person can choice to login or to register at a outer function.
				}
			}
			// new_admin
			Administrator_Info* new_admin = new Administrator_Info();
			new_admin->username = name;
			new_admin->password = password;
			administrator_list.push_back(new_admin); // Add new person to the list.
			write_administrator_info(administrator_list);
			printf("successfully register a new administrator!\n");
			break;

		}
		else
			printf("password is different at two times\n");
	}
}


int main(void) {
	// printf("Hello World");  prints Hello World 
	int identity=0; //

	while(1){
		if(identity==0){
			printf("Welcome to JD system! Login as 1. Administrator 2. Customer(Default) 3. Customer Register 4. Administrator Register -1 Exit\n");
			int tmp ;
			scanf("%d",&tmp);
			fflush(stdin);
			char name[16];
			char password[16];
//			while(1){

				switch(tmp){
					case 1:
						Adminstrator();
						break;
					case 2:
						Customer();
						break;
					case 3:
						Customer_R();
						break;
					case 4:
						Adminstrator_R();
						break;
					case -1:
						identity = 1;
						break;
//						return 0;
					default:
						Customer();
						break;
				}
//			}

			//TO DO. Check if the password is complex enough.
			//TO DO, Check if the name is a regular name.

		}
		else{
			printf("Do you want to Login a new Account? 1. Yes 2. No(Default)\n");
			int tmp;
			// printf("waht??\n");
			scanf("%d",&tmp);
			fflush(stdin);
			if(tmp=='\r' || tmp==2 || tmp=='\n'){

				printf("Welcome you come back next time!\n");
				break; //Real exist the system.
				return 0;
			}
			else if(tmp==1){
				identity=0;
			}
		}

		// scanf("%d",&identity);
	}

	return EXIT_SUCCESS;
}
