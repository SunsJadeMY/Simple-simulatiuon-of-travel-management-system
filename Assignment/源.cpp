/*
========================================
@Project: Trip Plan System
@Author: SunBoWen
@Student ID: X00158731
@Date: 2021/11
========================================
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

//customer information
struct Customer {
	string name;
	string gender;
	int age;
	double budget;
	string startdate;
	string enddate;
};

//sites information
struct Site {
	int number;
	string name;
	string place;
	double cost;
};

//each customer will have one or more sites for trip
struct Trip {
	string sitename;
	Trip* next;
};

//First Level Menu
char MainMenu();//MainMenu to choose function

//Second Level Menu
char SecondMenu(char option);//point to specified function according to option input
int AddCusMenu();//Add New Customer
void CustomerList();//Display Customer Information
void SiteList();//Display Site Information
void TripPlan();//Make Trip Plans for customer
void TripList();//Display Trip Information
void Search();//Search Customer Information or Trip Plan 
void EditCusMenu();//Edit the existing customer information

//Third Level Menu
void Search(Customer* cus, string name, int num);//search specified customer information by customer`s name
void Search(string name);//search specified customer`s trip plan information by customer`s name
void SiteScreen(Site site[], int num, int upper = 0, int lower = 0);//display the sites that meet the cost requirements

//Sort Function
void CustomerNameSort(int num);
//read data of customer
void readcus(Customer*& cusarray, int& size);
	//edit customer data stored
void editinfo(Customer* cus);
//add sites to list
void addsitetotrip(string sn);
//remove list
string remove(void);
//Inline Function
//when add new customer, AddCusMenu() will store the original number of customer and every time register a new customer the number will plus 1
//then the number will be passed into CustomerNameSort() function, compared to the number the function read from customer.txt
//and take the bigger one to read all the customer information
inline int cusnum(int n1, int n2) {
	return (n1 < n2) ? n2 : n1;
}
//The queue is initially
Trip* head = NULL;
Trip* tail = NULL;

//main function
int main() {
	char option = 'z';
	while (option != 'q') {
		option = SecondMenu(MainMenu());
	}
}

/*--------------------------------------------------
*
*---------------First Level Menu---------------
*
*--------------------------------------------------
*/

//main menu: show the options of different functions
char MainMenu() {
	char choice;

	cout << "----------Main Menu----------" << endl;
	cout << "Welcome to use Customer Trip System" << endl;
	cout << "Enter letter to choose function" << endl;
	cout << "a: Register a new Customer Information" << endl;
	cout << "b: Customer List" << endl;
	cout << "c: Site List" << endl;
	cout << "d: Make Plan" << endl;
	cout << "e: Plan List" << endl;
	cout << "f: Search" << endl;
	cout << "g; Edit Customer Information" << endl;
	cout << "Enter q to quit" << endl;
	cin >> choice;
	
	cout << " " << endl;

	return choice;
}

//point to different function according to the option input
char SecondMenu(char option) {
	int i = 0;
	switch (option)
	{
	//Add new customers
	case 'a': {
		i = AddCusMenu();
		CustomerNameSort(i);
		break;
	}
	//list the customer menu
	case 'b': {
		CustomerList();
		break;
	}
	//list the site menu
	case 'c': {
		SiteList();
		break;
	}
	//make a trip plan for a customer
	case 'd': {
		TripPlan();
		break;
	}
	//list the trip menu
	case 'e': {
		TripList();
		break;
	}
	//search information menu
	case 'f': {
		Search();
		break;
	}
	//edit customer information menu
	case 'g': {
		EditCusMenu();
		break;
	}
	default:
		break;
	}

	return option;
}

/*--------------------------------------------------
*
*---------------Second Level Menu---------------
*
*--------------------------------------------------
*/
//add new customer
int AddCusMenu() {
	ifstream ip("customer.txt");
	ofstream op("customer.txt", ios::out | ios::app);

	//read the number of customer stored in the file
	int num;
	ip >> num;

	Customer cusinfo;
	char next = 'n';
	char confirm = 'y';

	do {
		cout << "Customer Information Registration" << endl;

		cout << "Name:";
		cin >> cusinfo.name;

		cout << "Gender(male/female):";
		cin >> cusinfo.gender;

		cout << "Age:";
		cin >> cusinfo.age;
		//check the age input is integer
		while (cin.fail()) {
			if (cin.fail()) {
				cin.clear();
				cout << "Enter the right age" << endl;
				while (cin.get() != '\n')
					continue;
				cin >> cusinfo.age;
			}
		}

		cout << "Budget:";
		cin >> cusinfo.budget;

		cout << "Start Date(yyyy.mm.dd):";
		cin >> cusinfo.startdate;

		cout << "End Date(yyyy.mm.dd):";
		cin >> cusinfo.enddate;

		//Check the Information 
		cout << cusinfo.name << " " << cusinfo.gender << " " << cusinfo.age << " " << cusinfo.budget << " " << cusinfo.startdate << " " << cusinfo.enddate << endl;
		cout << "Confirm the Register Information[y/n]:";
		cin >> confirm;
		//Information is correct and then write into file
		if (confirm == 'y') {
			cout << "Waiting for Record" << endl;
			if (num == 0)
				op << endl;
			op << cusinfo.name << " ";
			op << cusinfo.gender << " ";
			op << cusinfo.age << " ";
			op << cusinfo.budget << " ";
			op << cusinfo.startdate << " ";
			op << cusinfo.enddate << endl;
			cout << "Register successfully" << endl;
			num++;
		}
		//ask if add one more
		cout << "Add another Customer Information?[y/n]:";
		cin >> next;
	} while (next == 'y');

	cout << " " << endl;

	ip.close();
	op.close();

	return num;
}

//display the customer information stored in the file
void CustomerList() {
	cout << "----------Customer List----------" << endl;
	//customer information is stored in customer.txt file
	ifstream ip("customer.txt");
	int num;
	ip >> num;//the number of customers stored in the file

	//Basic information
	cout << "There are " << num << "customers registered now" << endl;
	cout << "Name " << "Gender " << "Age " << "Budget " << "StartDate " << "EndDate" << endl;

	//Display the customer information
	Customer* cus;
	cus = new Customer[num];
	for (int i = 0; i < num; i++) {
		ip >> cus[i].name >> cus[i].gender >> cus[i].age >> cus[i].budget >> cus[i].startdate >> cus[i].enddate;
		cout << cus[i].name << " " << cus[i].gender << " " << cus[i].age << " " << cus[i].budget << " " << cus[i].startdate << " " << cus[i].enddate << endl;
	}
	
	ip.close();
	cout << " " << endl;
}

//display the site information stored in the file
void SiteList() {
	cout << "----------Site List----------" << endl;
	//sites information is stored in site.txt file
	ifstream ip("site.txt");
	int num;
	ip >> num;//the number of sites stored in the file

	//Basic information
	cout << "There are " << num << "sites can choose to travel" << endl;
	cout << "Number " << "Country " << "Position " << "Expected Cost" << endl;//attributes

	//Display the site information
	Site* sd;
	sd = new Site[num];
	for (int i = 0; i < num; i++) {
		ip >> sd[i].number >> sd[i].name >> sd[i].place >> sd[i].cost;
		cout << sd[i].number << " " << sd[i].name << " " << sd[i].place << " " << sd[i].cost << endl;
	}
	ip.close();

	//filter to show sites that meet the cost requirements
	char ask;
	int upper, lower;
	cout << "Any cost requirements?[y/n]:";
	cin >> ask;
	if (ask == 'y') {
		//get the upper and lower bound
		cout << "Enter the upper limitation:";
		cin >> upper;
		cout << "Enter the lower limitation:";
		cin >> lower;
		SiteScreen(sd, num, upper, lower);
	}
	cout << " " << endl;
}

/*
* make a trip plan for customers
* will calculate the total cost
*/
void TripPlan() {
	//open files
	ifstream site("site.txt");
	ifstream tr("trip.txt");
	ofstream tripplan("trip.txt", ios::out | ios::app);

	cout << "----------Trip Plan Making----------" << endl;

	string name;
	cout << "Enter the customer name:";
	cin >> name;

	//display the sites
	int sitenum;
	site >> sitenum;//the amount of sites
	Site* sd;
	sd = new Site[sitenum];
	for (int i = 0; i < sitenum; i++) {
		site >> sd[i].number >> sd[i].name >> sd[i].place >> sd[i].cost;
		cout << sd[i].number << " " << sd[i].name << " " << sd[i].place << " " << sd[i].cost << endl;
	}

	//select the sites
	int n = -1;
	int count = 0;
	int cost = 0;
	cout << "Enter the number of sites(from 1 to 46 and 0 for quit):";
	cin >> n;
	while (n > 0 && n <= 46) {
		addsitetotrip(sd[n-1].name);
		count++;//count how many sites added
		cost += sd[n - 1].cost;//count the total cost
		cout << "Enter the number of sites(from 1 to 46 and 0 for quit):";
		cin >> n;
	}

	//write the customer name and selected sites to file
	tripplan << endl;
	tripplan << name << " ";
	tripplan << cost << " ";
	for (int i = 0; i < count; i++) {
		tripplan << remove() << " ";
	}
	tripplan << endl;

	site.close();
	tripplan.close();
	cout << " " << endl;
}

//display the trip plan stored in file
void TripList() {
	cout << "----------Trip Menu----------" << endl;

	//trip information is stored in trip.txt file
	ifstream plan("trip.txt");

	//Basic information
	cout << "CustomerName " << "Total Cost" << "SiteNames " << endl;//attributes

	//Display the trip information
	char ch[1024];
	while(plan){
		plan.getline(ch, 1024);//read the whole line
		cout << ch << endl;//print
	}

	plan.close();
	cout << " " << endl;
}

//search customer information or trip plan according to name
void Search() {
	//open files
	ifstream cus("customer.txt");
	//read customer information
	int cusnum;
	cus >> cusnum;
	Customer* cusinfo;
	cusinfo = new Customer[cusnum];
	for (int i = 0; i < cusnum; i++) {
		cus >> cusinfo[i].name >> cusinfo[i].gender >> cusinfo[i].age >> cusinfo[i].budget >> cusinfo[i].startdate >> cusinfo[i].enddate;
	}
	//select which information to display
	int option = 0;
	string searchname;
	do {
		cout << "1. Search the Customer Information" << endl;
		cout << "2. Search the Customer`s Trip Plan" << endl;
		cout << "3. Search all the information" << endl;
		cout << "4. Quit Search" << endl;
		cout << "Enter the number:" << endl;
		cin >> option;
		cout << "Enter the customer name:";
		cin >> searchname;

		switch (option) {
		//print customer information
		case 1 : {
			Search(cusinfo, searchname, cusnum);
			break;
		}
		//print trip plan
		case 2 : {
			Search(searchname);
			break;
		}
		//print both
		case 3: {
			Search(cusinfo, searchname, cusnum);
			Search(searchname);
			break;
		}
		default:
			break;
		}

	} while (option != 4);

	cus.close();
	cout << " " << endl;
}

//edit customer information according to the name input
void EditCusMenu() {
	cout << "----------Edit Customer Information----------" << endl;
	Customer* cusarray = NULL;
	int size;
	readcus(cusarray, size);//read customer information

	//input the customer name that needs editing
	string cusnameedit;
	cout << "Enter the customer name that needs editing:";
	cin >> cusnameedit;

	//find and edit
	Customer temp;
	for (int i = 0; i < size; i++) {
		if (cusarray[i].name == cusnameedit) {
			temp = cusarray[i];
			editinfo(&temp);
			cusarray[i] = temp;
		}
	}

	//open file customer.txt to write
	ofstream op("customer.txt");
	//write the number of customer firstly
	op << size << endl;
	//write the sorted customer information
	for (int i = 0; i < size; i++) {
		op << cusarray[i].name << " ";
		op << cusarray[i].gender << " ";
		op << cusarray[i].age << " ";
		op << cusarray[i].budget << " ";
		op << cusarray[i].startdate << " ";
		op << cusarray[i].enddate << endl;
	}
	op.close();
	//after editing, sort again
	CustomerNameSort(size);
	cout << " " << endl;

}

/*--------------------------------------------------
*
*---------------Third Level Menu---------------
*
*--------------------------------------------------
*/

//Recursive Function
//search the customer information in the file by his name
void Search(Customer* cus, string name, int num) {
	if (num > 0) {
		//check if next customer name matches
		if (cus[num - 1].name != name)
			return Search(cus, name, num - 1);
		//match the condition, print the customer information
		else {
			cout << "Customer Information is shown:" << endl;
			cout << "Name: " << cus[num - 1].name << endl;
			cout << "Gender: " << cus[num - 1].gender << endl;
			cout << "Age: " << cus[num - 1].age << endl;
			cout << "Budget: " << cus[num - 1].budget << endl;
			cout << "Start Date: " << cus[num - 1].startdate << endl;
			cout << "End Date: " << cus[num - 1].enddate << endl;
		}
	}
	//customer not found
	else {
		cout << "No customer called " << name << " is registered in system" << endl;
	}
}
//search the customer`s trip plan in the file
void Search(string name) {
	ifstream ip("trip.txt");
	if (!ip.is_open())
		cout << "File Error Open" << endl;
	int flag = 0;
	char data[1024];
	while (!ip.eof()) {
		string sname;
		ip >> sname;
		ip.getline(data, 1024);
		if (sname == name) {
			cout << sname << " " << data << endl;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		cout << "No customer called " << name << endl;
}

/*--------------------------------------------------
*
*---------------Functions---------------
*
*--------------------------------------------------
*/
//Sorting Function
//sort the customer information according to the Alphabetical order of name
void CustomerNameSort(int num) {
	//customer information is stored in customer.txt file
	ifstream ip("customer.txt");
	int num1;
	ip >> num1;//the number of customers stored in the file

	//return the bigger one
	num1 = cusnum(num1, num);
	
	//Display the customer information
	Customer* cus;
	cus = new Customer[num1];
	for (int i = 0; i < num1; i++) {
		ip >> cus[i].name >> cus[i].gender >> cus[i].age >> cus[i].budget >> cus[i].startdate >> cus[i].enddate;
	}
	//bubble sort
	Customer temp;
	for (int i = 0; i < num1; i++) {
		for (int j = 0; j < num1 - 1; j++) {
			if (cus[j].name > cus[j + 1].name) {
				temp = cus[j];
				cus[j] = cus[j + 1];
				cus[j + 1] = temp;
			}
		}
	}
	//open file customer.txt to write
	ofstream op("customer.txt");
	//write the number of customer firstly
	op << num1 << endl;
	//write the sorted customer information
	for (int i = 0; i < num1; i++) {
		op << cus[i].name << " ";
		op << cus[i].gender << " ";
		op << cus[i].age << " ";
		op << cus[i].budget << " ";
		op << cus[i].startdate << " ";
		op << cus[i].enddate << endl;
	}

	ip.close();
	op.close();
	cout << " " << endl;
}

//display sites meeting the cost requirements
void SiteScreen(Site site[], int num, int upper, int lower) {
	//upper cost must bigger than lower cost and is not equal to 0
	if (upper > lower && upper != 0) {
		for (int i = 0; i < num; i++) {
			if (site[i].cost >= lower && site[i].cost <= upper) {
				cout << site[i].number << " " << site[i].name << " " << site[i].place << " " << site[i].cost << endl;
			}
		}
	}
}

//read customer information
void readcus(Customer*& cusarray, int& size) {
	//open file
	ifstream ip("customer.txt");
	if (ip.is_open())
		cout << "File Exists" << endl;
	ip >> size;
	cusarray = new Customer[size];
	//read
	for (int i = 0; i < size; i++) {
		ip >> cusarray[i].name >> cusarray[i].gender >> cusarray[i].age >> cusarray[i].budget >> cusarray[i].startdate >> cusarray[i].enddate;
	}
	ip.close();
}

//edit the information of customer
void editinfo(Customer* cus) {
	cout << "----------Edit Process----------" << endl;
	string name;
	string gender;
	int age;
	double budget;
	string startdate;
	string enddate;

	//get the information input
	cout << "Name:";
	cin >> name;

	cout << "Gender(male/female):";
	cin >> gender;

	cout << "Age:";
	cin >> age;

	cout << "Budget:";
	cin >> budget;

	cout << "Start Date(yyyy.mm.dd):";
	cin >> startdate;

	cout << "End Date(yyyy.mm.dd):";
	cin >> enddate;

	//Check the Information
	cout << name << " " << gender << " " << age << " " << budget << " " << startdate << " " << enddate << endl;
	cout << "Confirm the Register Information[y/n]:";
	char confirm = 'n';
	cin >> confirm;
	//Information is correct and then store
	if (confirm == 'y') {
		cout << "Waiting for Record" << endl;
		cus->name = name;
		cus->gender = gender;
		cus->age = age;
		cus->budget = budget;
		cus->startdate = startdate;
		cus->enddate = enddate;
		cout << "Edit successfully" << endl;
	}
}

void addsitetotrip(string sn) {
	Trip* temp;
	temp = new Trip;
	if (temp == NULL)
		cout << "Error overflow" << endl;
	else {
		//place site in trip
		temp->sitename = sn;
		temp->next = NULL;
		//add to list
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}
	}
}

string remove(void) {
	Trip* temp;
	string n;
	//queue empty
	if (head == NULL) {
		cout << "Error underflow" << endl;
		n = 'none';
	}
	else {
		//get the site at the top
		n = head->sitename;
		//remove
		temp = head;
		head = head->next;
		delete temp;
		//check if queue is empty
		if (head == NULL)
			tail = NULL;
	}
	return n;
}