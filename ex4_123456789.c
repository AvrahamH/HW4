#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define BARCODE_LENGTH 12
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * main_interface = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Welcome to CORONA market!\n"\
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Manage market menu :\n"\
"	1. Add product\n"\
"	2. Remove product\n"\
"	3. Check which products are expired\n"\
"	4. Print all the products\n"\
"	5. Update product\n"\
"	6. EXIT SYSTEM\n"\
"Please choose operation[1-6]:";

//operation 1 constant strings

const char * adding_product_barcode = "Please enter product barcode:";
const char * barcode_already_exist = "This product already exist, please enter the number of products to add:";
const char * too_much_products = "Can't add more products, not enough space";
const char * adding_product_name = "Please enter product name:";
const char * adding_product_category = "Please enter product category:";
const char * adding_product_number = "Please enter number of products to add:";
const char * adding_product_price = "Please enter the price of the product:";
const char * adding_product_date = "Please enter expiration date of the product[dd/mm/yy]:";

//operation 2 constant strings
const char * store_empty = "The store is empty!";
const char * delete_barcode = "Please enter product barcode you want to delete:";
const char * delete_barcode_cant_find = "Couldn't find the product barcode, try again...";
const char * delete_barcode_succeed = "The product deleted successfully!";


//operation 3 constant strings
const char * expired_date_check = "What date you want to check[dd/mm/yy]:";
const char * expired_products = "~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "Product barcode: ";
const char * expired_product_date = "Product expiration date: ";


//operation 4 constant strings
const char * print_products_head = "~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n";
const char * print_no_products = "No products in the store!\n";
const char * print_products = "----------";
const char * print_product_name = "Product name: ";
const char * print_product_barcode = "Product barcode: ";
const char * print_product_category = "Product category: ";
const char * print_product_number = "Product available quantity: ";
const char * print_product_price = "Product price: ";
const char * print_product_expireDate = "Product expiration date: ";
const char * print_total_number = "Total number of products: ";

//operation 5 constant strings
const char * update_barcode = "Please enter product barcode you want to update:";
const char * update_barcode_notFound = "Couldn't find the product barcode, try again...";
const char * update_interface_string = ("What do you want to update?\n"\
	"	1. Product name\n"\
	"	2. Product category\n"\
	"	3. Product quantity\n"\
	"	4. Product price\n"\
	"	5. Product expiration date\n"\
	"Please choose operation [1-5]:");
const char * update_product_name = "Please enter new product name:";
const char * update_product_category = "Please enter new product category:";
const char * update_product_number = "Please enter new product quantity:";
const char * update_product_price = "Please enter new product price:";
const char * update_product_date = "Please enter new product expiration date[dd/mm/yy]:";

//operation 6 constant strings
const char * exitProgram = "exit...";

typedef struct date
{
	int year;
	int month;
	int day;
} date;

typedef struct product
{
	char * product_name;
	char * product_category;
	char * barcode;
	int available;
	double price;
	date * expire_date;
} product;

typedef struct super_market
{
	product ** product_list;
	int number_of_products;
} super_market;

/*Inputs: None
Return parameters : None
Function functionality : printing the memory allocation failure and exits the program if the allocaion failed*/
void printFailed() {
	printf("Failed to allocate memory\n");
	exit(1);
}

/*Inputs: None
Return parameters: new date* with allocated memory fot the variables
Function functionality: initializing a new with allocated memory for each variable*/
date* newDate() {
	date *result;
	if ((result = (date*)malloc(sizeof(date))) == NULL) printFailed();
	result->day = 0;
	result->month = 0;
	result->year = 0;
	return result;
}

/*Inputs: *str_date - string that represents the date in [dd/mm/yy] format, date pointer
Return parameters: None
Function functionality: converting the date string to date format and inserting it to a date pointer*/
void str_to_date(char *str_date, date *result) {
	result->day = (int)(str_date[0] - '0') * 10 + (int)(str_date[1] - '0');
	result->month = (int)(str_date[3] - '0') * 10 + (int)(str_date[4] - '0');
	result->year = (int)(str_date[6] - '0') * 10 + (int)(str_date[7] - '0');
}

/*Inputs: user's input barcode
Return parameters: new product* with allocated memory for the variables
Function functionality: initializing a new product with allocated memory for each variable and filling it with user's input*/
product* newProduct(char * barcode) {
	product *result = (product*)malloc(sizeof(product));
	if (result == NULL)
		printFailed();

	char product_name[MAX_PRODUCT_NAME_LENGTH + 1], product_category[MAX_CATEGORY_LENGTH + 1], str_date[9];

	printf("%s", adding_product_name);
	scanf("\n%[^\n]s", product_name);

	printf("%s", adding_product_category);
	scanf("\n%[^\n]s", product_category);

	if ((result->product_name = (char*)malloc(strlen(product_name) + 1)) == NULL) printFailed();
	strcpy(result->product_name, product_name);

	if ((result->product_category = (char*)malloc(strlen(product_category) + 1)) == NULL) printFailed();
	strcpy(result->product_category, product_category);

	if ((result->barcode = (char*)malloc(strlen(barcode) + 1)) == NULL) printFailed();
	strcpy(result->barcode, barcode);

	printf("%s", adding_product_number);
	scanf("%d", &result->available);

	printf("%s", adding_product_price);
	scanf("%lf", &result->price);

	printf("%s", adding_product_date);
	scanf("%s", str_date);

	result->expire_date = newDate();
	str_to_date(str_date, result->expire_date);
	
	return result;
}

/*Inputs: product pointer of an existing product
Return parameters: None
Function functionality: freeing the allocated memory for each variable that has been allocated and finally of the received product pointer*/
void freeProduct(product *product) {
	free(product->product_name);
	free(product->product_category);
	free(product->barcode);
	free(product->expire_date);
	free(product);
}

/*Inputs: None
Return parameters: new super_market* with allocated memory for the variables
Function functionality: initializing a new super_market with allocated memory for each variable*/
super_market* newSuper_market() {
	super_market *result = (super_market*)malloc(sizeof(super_market));
	if (result == NULL) printFailed();

	if ((result->product_list = (product**)calloc(0, sizeof(product*))) == NULL) printFailed();
	result->number_of_products = 0;
	return result;
}

/*Inputs: super_market pointer of existing super_market
Return parameters: None
Function functionality: freeing the allocated memory for each variable that has been allocated and finally of the received super_market pointer*/
void freeSuper_market(super_market *super) {
	for (int i = 0; i < super->number_of_products; i++)
		freeProduct(super->product_list[i]);
	free(super);
}

/*Inputs: super_market pointer, index of the product that the user wish to update, and a user_input that is what he wants to update
Return parameters: None
Function functionallity: updating a field of a product in accordance to the user */
void updateOpt(super_market *super, int index, int input) {
	switch (input) {
	case 1:
		free(super->product_list[index]->product_name);
		printf("%s", update_product_name);
		if (NULL == (super->product_list[index]->product_name = (char*)malloc(MAX_PRODUCT_NAME_LENGTH + 1))) printFailed();
		scanf("%s", super->product_list[index]->product_name);
		break;

	case 2:
		free(super->product_list[index]->product_category);
		printf("%s", update_product_category);
		if (NULL == (super->product_list[index]->product_name = (char*)malloc(MAX_CATEGORY_LENGTH + 1))) printFailed();
		scanf("%s", super->product_list[index]->product_category);
		break;

	case 3:
		printf("%s",update_product_number);
		scanf("%d", &super->product_list[index]->available);
		break;

	case 4:
		printf("%s", update_product_price);
		scanf("%lf", &super->product_list[index]->price);
		break;

	case 5:
		printf("%s",update_product_date );
		char str_date[9];
		scanf("%s", str_date);
		str_to_date(str_date, super->product_list[index]->expire_date);
		break;
	}
}

/*Inputs: product pointer of an existing product and a date pointer
Return parameters: int to indicate if the product expired
Function functionallity: retruns if a product expired or not*/
int isExpired(product *product_date ,date *expire_date) {
	if (expire_date->year < product_date->expire_date->year)
		return 0;
	if (expire_date->year > product_date->expire_date->year)
		return 1;
	if (expire_date->month < product_date->expire_date->month)
		return 0;
	if (expire_date->month > product_date->expire_date->month)
		return 1;
	if (expire_date->day < product_date->expire_date->day)
		return 0;
	return 1;
}

/*Inputs: product pointer of an existing product 
Return parameters: None
Function functionallity: prints the expired product*/
void printExpired(product *print_product) {
	printf("%s%s\n", expired_product_name, print_product->product_name);
	printf("%s%s\n", expired_product_barcode, print_product->barcode);
	printf("%s%d/%d/%d\n", expired_product_date, print_product->expire_date->day, print_product->expire_date->month, print_product->expire_date->year);

}

/*Inputs: product pointer of an existing product
Return parameters: None
Function functionallity: printing the input product in a given format*/
void printProduct(product *prod) {
	printf("%s%s\n", print_product_name, prod->product_name);
	printf("%s%s\n", print_product_barcode, prod->barcode);
	printf("%s%s\n", print_product_category, prod->product_category);
	printf("%s%d\n", print_product_number, prod->available);
	printf("%s%g\n", print_product_price, prod->price);
	printf("%s%d/%d/%d\n", print_product_expireDate, prod->expire_date->day, prod->expire_date->month, prod->expire_date->year);
}

/*Inputs: *super - supermarket to check, barcode - barcode to check
Return parameters: int to indicate if the product exists
Function functionality: comparing the existing barcodes at the supermarket to the barcode parameter,
and returning 0 if it doesn't exists, or 1 if it exists*/
int check_exist(super_market *super, char *barcode) {
	for (int i = 0; i < super->number_of_products; i++){
		if (!strcmp(super->product_list[i]->barcode, barcode)) {
			printf("%s", barcode_already_exist);
			int prod_add = 0;
			scanf("%d", &prod_add);
			super->product_list[i]->available += prod_add;
			printf("Additional %d products of %s added\n", prod_add, super->product_list[i]->product_name);
			return 1;
		}
	}
	return 0;
}

/*Inputs: existing super_market
Return parameters: None
Function functionality: adding a new product from user's input by creating a new product and adding it to super
also checking if it's possible to add another product or adding more products of an existing one*/
void addProduct(super_market * super)
{
	char barcode[BARCODE_LENGTH + 1];
	printf("%s", adding_product_barcode);
	scanf("%s", barcode);

	if(check_exist(super, barcode)) return;

	if (super->number_of_products == MAX_NUM_PRODUCTS) {
		printf("%s", too_much_products);
		return;
	}
	
	product *new_product = newProduct(barcode);

	super->number_of_products++;
	if ((super->product_list = realloc(super->product_list, super->number_of_products*(sizeof(product*)))) == NULL) printFailed();

	(super->product_list)[super->number_of_products - 1] = new_product;		//inserting new_product to the super's product list
	printf("The product %s -barcode:%s ,added successfully\n", new_product->product_name, new_product->barcode);
}											 

/*Inputs: super_market pointer of an existing super_market
Return parameters: None
Function functionallity: printing the entire supermarket by printing each product with printProduct or a message if it's empty*/
void printSuper(super_market *super) {
	printf("%s", print_products_head);
	if (super->number_of_products == 0) {
		printf("%s", print_no_products);
		return;
	}
	for (int i = 0; i < super->number_of_products; i++) {
		printf("%s\n", print_products);
		printProduct(super->product_list[i]);
	}
	printf("%s%d\n", print_total_number, super->number_of_products);
}

/*Inputs: super_market pointer of an existing super_market
Return parameters: None
Function functionallity: removes a product from the super_market according to the barcode that the user puts */
void removeProduct(super_market *super) {
	int check_barcode = 0, i ,j;
	char barcode[BARCODE_LENGTH + 1];
	if (super->number_of_products == 0) {
		printf("%s",store_empty);
		return;
	}
	printf("%s", delete_barcode);
	scanf("%s", barcode);
	while (check_barcode == 0)
	{
		for (i = 0; i < super->number_of_products; i++) {
			if (!strcmp(super->product_list[i]->barcode, barcode)) {
				for (j = i + 1; j < super->number_of_products; j++) {
					super->product_list[j - 1] = super->product_list[j];
				}
				super->number_of_products -= 1;
				if (super->number_of_products > 0) {
					if ((super->product_list = realloc(super->product_list, (super->number_of_products)*(sizeof(product*)))) == NULL)
						printFailed();
				}
				check_barcode = 1;
				printf("%s\n", delete_barcode_succeed);
				break;
			}
		}
		if (check_barcode != 0)
			break;
		printf("%s\n", delete_barcode_cant_find);
		printf("%s", delete_barcode);
		scanf("%s", barcode);
	}
}

/*Inputs: super_market pointer of an existing super_market
Return parameters: None
Function functionallity: take a date from the user and check if a product exists that expires in that date with isExpired and if
exists prints them with printExpired*/
void checkExpired(super_market *super) {
	char str_date[9];
	date *check_date = newDate();
	printf("%s", expired_date_check);
	scanf("%s", str_date);
	str_to_date(str_date, check_date);
	printf("%s", expired_products);
	for (int i = 0; i < super->number_of_products; i++) {
		if (isExpired(super->product_list[i],check_date))
			printExpired(super->product_list[i]);
	}
}

/*Inputs: super_market pointer
Return parameters: None
Function functionallity: updating a field of a product in accordance to the user*/
void UpdateProduct(super_market *super) {
	int check_barcode = 0 , user_input ,i ;
	char barcode[BARCODE_LENGTH + 1];
	if (super->number_of_products == 0) {
		printf("No products in the store!\n");
	}
	printf("%s", update_barcode);
	scanf("%s", barcode);
	while (check_barcode == 0)
	{
		for ( i = 0; i < super->number_of_products; i++) {
			if (!strcmp(super->product_list[i]->barcode, barcode)) {
				check_barcode = 1;
				break;
			}
		}
		if (check_barcode != 0)
			break;
		printf("%s\n", update_barcode_notFound);
		printf("%s", update_barcode);
		scanf("%s", barcode);		
	} 
	printf("%s", update_interface_string);
	scanf("%d", &user_input);
	updateOpt(super, i, user_input);

}

/*Inputs: super_market pointer
Return parameters: None
Function functionallity: freeing the memory which was allocated to the supermarket and exiting the program*/
void exitSuper(super_market *super) {
	printf("%s", exitProgram);
	freeSuper_market(super);
	exit(0);
}

/*Inputs: super_market pointer
Return parameters: None
Function functionallity: the main interface of the supermarket, starting the relevant function by user's input*/
void user_input(super_market *super)
{
	int user_input = 0;
	do {
		printf("%s", main_interface);
		scanf("%d", &user_input);
		switch (user_input)
		{
		case 1:
			addProduct(super);
			break;
		case 2:
			removeProduct(super);
			break;
		case 3:
			checkExpired(super);
			break;
		case 4:
			printSuper(super);
			break;
		case 5:
			UpdateProduct(super);
			break;
		case 6:
			exitSuper(super);
		default:
			break;
		}
	} while (user_input != 6);
}

int main() {
	super_market *super = newSuper_market();
	user_input(super);
	
	return 0;
}