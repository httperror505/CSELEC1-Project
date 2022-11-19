// Semifinals Project for CSElec1 - Parallel and Distributed Computing
// Made by: John Rey Tolosa and Jhon Mark Fuentes (BSCS 2A)

// Library files used
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

// variable definition
#define decart 0.5
#define scantime 0.5
#define packitemnum 0.50
#define packnumbox 10
#define packnumbag 5
#define receipttime 0.3

using namespace std;


double Total_Lane_Queue_Time;

struct CustomerQueue {
	int itemNum;
	string Prefered_Packaging;
	int Number_Packaging;
	string Prefered_Payment;
	string Cash_type;
};

// function for parsing data
CustomerQueue extractData(string line)
{
	size_t pos = 0;
	size_t npos = -1;
	string delimiter = " ";
	string data[5] = {""};
	int data_index = 0;
	
	while ((pos = line.find(delimiter)) != npos) {
	    data[data_index] = line.substr(0, pos);
	    line.erase(0, pos + delimiter.length());
	    data_index++;
	}
	data[data_index] = line;
	
	stringstream ss;
	
	CustomerQueue temp;
	
	for (int i = 0; i < 5; i++) {
		string d = *(data + i);
		if (i == 0 || i == 2) {
			ss << d;
			if (i == 0) {
				ss >> temp.itemNum;
			} else if (i == 2) {
				ss >> temp.Number_Packaging;
			}
			ss.clear();
			ss.str("");
		} else if (i == 1) {
			temp.Prefered_Packaging = d;
		} else if (i == 3) {
			temp.Prefered_Payment = d;
		} else if (i == 4) {
			temp.Cash_type = d;
		}
	}
	return temp;
}

// function for printing the parsed data
void print_input(CustomerQueue n, int index)
{
	// variable declaration
	float Total_Decarting_Time;
	float Total_Scanning_Time;
	float Total_Packing_Time;
	float Total_Paying_Time;
	float Total_Reciept_Printing_Time;
	int Idle_Time;
	float Total_Customer_Queue_Time;	
	int Customer_Number;

	// Display of Inputs
	
	Customer_Number = index + 1;
	
	cout << "Customer #" << Customer_Number << endl;
	cout << "No. of Cart Items: " << n.itemNum << endl;
	cout << "Preferred Packaging: " << n.Prefered_Packaging << endl;
	cout << "Number of Box: " << n.Number_Packaging << endl;
	
	// function for determining and displaying whether the payment is exact or not
	if(n.Cash_type == "e"){
		cout << "Preferred Payment Method: " << n.Prefered_Payment << " (exact) " << endl;
	}
	else if(n.Cash_type == "ne"){
		cout << "Preferred Payment Method: " << n.Prefered_Payment << " (not exact) " << endl;
	}
	else {
		cout << "Preferred Payment Method: " << n.Prefered_Payment << endl;
	}
	
	cout << "------------------------------------------------\n";
		 
	// Computes and Displays the Total Decarting Time 
	Total_Decarting_Time = n.itemNum * decart;
	cout << "Total De-Carting Time: " << Total_Decarting_Time << endl;
	
	// Computes and Displays the Total Scanning Time
	Total_Scanning_Time =  n.itemNum * scantime;
	cout << "Total Scanning Time: "  << Total_Scanning_Time << endl;
	
	// Determines the Prefered Packaging
	// Computes and Displays the Total Packing Time
	if(n.Prefered_Packaging == "box"){
		Total_Packing_Time = (n.itemNum * packitemnum) + (n.Number_Packaging * packnumbox);
		cout << "Total Packing Time: " << Total_Packing_Time << endl;
	} 
	else if (n.Prefered_Packaging == "bag") {
		Total_Packing_Time = (n.itemNum * packitemnum) + (n.Number_Packaging * packnumbag);
		cout << "Total Packing Time: " << Total_Packing_Time << endl;
	}
	
	// Determines the Prefered Payment and display the corresponding paying time value
	// if the prefered payment method is cash, determines the whether exact or not exact payment
	if(n.Prefered_Payment == "cash"){
		if(n.Cash_type == "e"){
			Total_Paying_Time = 15;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
		else if(n.Cash_type == "ne"){
			Total_Paying_Time = 20;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
	}
	// if the preferred payment method us digita
	if(n.Prefered_Payment == "digital"){
		Total_Paying_Time = 15;
		cout << "Total Paying Time: " << Total_Paying_Time << endl;
	}
	
	// Computes and Display the Total Receipt Printing Time
	Total_Reciept_Printing_Time = (n.itemNum * receipttime) + 2;
	cout << "Total Receipt Printing Time: " << Total_Reciept_Printing_Time << endl;
	
	// distinguishing the idle time
	if(index == 0){
		Idle_Time = 0;
		cout << "Idle Time: " <<  Idle_Time << endl;
	} else if(index > 0){
		Idle_Time = 3;
		cout << "Idle Time: " <<  Idle_Time << endl;
	}
	
	// Computes and Displays the Total Customer Queue Time
	Total_Customer_Queue_Time = Total_Decarting_Time + Total_Scanning_Time + Total_Packing_Time + Total_Paying_Time + Total_Reciept_Printing_Time + Idle_Time;
	cout << "Total Customer-Queue Time: " << Total_Customer_Queue_Time << endl;
	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	
	// computation in getting the total lane queue time of all customers
    Total_Lane_Queue_Time += Total_Customer_Queue_Time;

	  
		 
}


int main( )
{
	// getting the data from a file in the directory
	ifstream in_stream;
	
	in_stream.open("file.in");
	
	if(in_stream.fail())
    {
        cout<<"Input file opening failed.\n";
        exit(1);
    } 
	
	int Number_Of_Customer;
	
	in_stream >> Number_Of_Customer;
		
	cout << "No. of Customers:: " << Number_Of_Customer << endl;
	cout << "================================================\n";
	
	CustomerQueue queue[Number_Of_Customer];
	
	CustomerQueue n;
		
	string line;
	
	int index = 0;
	
	while (getline(in_stream, line)) {
		if (line.length() > 0) {
			queue[index] = extractData(line);
			print_input(queue[index],index);
			index++;
		}
	}

    cout << "Total Lane Queue Time: " << Total_Lane_Queue_Time;
	
	return 0;
}
