/* Author: Timothy Kelley
   Description: This program reads in a database from vetDB.dat
   and stores the information in the clients array. Functions such
   as deleting a client, adding a new one, and printing bills can
   be used to the user's choice. Execution ends with overwritting
   vetDB.dat with stored data from the clients array in the same 
   format.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct Pet {
    string species, breed, name;  //the species, breed, and name of pet struct
    char gender;  //the gender: either 'f' or 'm'
    int age; //the age of the pet
};

struct Client {
    int acctNum;  //the number that will be used to find client
    string name, address; //the client's name and address on record
    float acctBalance; //active balance of client
    int howmany; //the number of pets to the client
    Pet pets[10]; //this array represents the database of pets
};
    
    //readClients reads all the clients from the file vetDB.dat
    void readClients(Client clients[], int & count, int & nextAcctNum);

    //readOne is called by readClients to read a single client from the file
    //it returns all the client information in a Client variable
    Client readOne(istream &);
    
    //findClient is called by printBill, printPet and deleteClient to find where the 
    //client is in the file based on the account number.  
    int findClient(const Client clients[], int count, int acctNum);
    
    //deleteClient delete's a client if they exist by finding where
    //they are in the clients array and then shifting all clients up
    //one slot in the array - i.e., if we were deleting the client at
    //index 5, then the client at 6 would move into 5, 7 would go to 6, etc.
    void deleteClient(Client clients[], int acctNum, int &count);
    
    //printBill prints the bill for a client based on account number
    void printBill(const Client clients[], int acctNum, int count);
    
    //printPet prints all the information for a specific client's pet
    //based on the pet's name.  It will have to call findClient first,
    //then if the client exists, it will ask for the pet name and
    //if the pet exists, then it will print the pet info
    void printPet(const Client clients[], int acctNum, int count);
    
    //addClient asks for all client information except the 
    //account number and also assuming there aren't
    //already 10 clients, and then it adds that information to the
    //client array.  nextAcctNum should be incremented and so should count
    void addClient(Client clients[], int & count, int & nextAcctNum);

    //printAll prints out the database of clients
    void printAll(const Client clients[], int count);
    
    //saveDB will write the count, then the nextAcctNum, then all the
    //client info in the same format that was in the original vetDB.dat file.
    //this data will be written to vetDB.dat - i.e., the file will be
    //overwritten.  Don't forget to close it after reading then reopen it
    //here for writing.
    void saveDB(Client clients[],int count, int nextAcctNum);

int main () {
    const int MAX_CLIENTS = 10; //Constant for max elements         
    Client clients[MAX_CLIENTS];//Client array with max elements
    int count, choice;          //actual number of clients and input for menu
    int acct, nextAcctNum;      //input for acct. search and next acct. 
    bool inExit = false;        //sentinel variable for exit
    
    //reads database, number of clients, and
    //next available acct. number from vetDB.dat
    readClients(clients, count, nextAcctNum); 
    
    while(!inExit) { 
        //Display functions for client management
        cout << "\n\nWhat would you like to do?" << endl;  
        cout << " 1.  Print out a bill for a client" << endl;
        cout << " 2.  Print out the information on a pet for a client" << endl;
        cout << " 3.  Add a client" << endl;
        cout << " 4.  Delete a client" << endl;
        cout << " 5.  Print the database of clients" << endl;
        cout << " 6.  Quit and write out the database" << endl;
                      
        //Input into choice var. and execute proper block from the case
        cin >> choice;    
        switch(choice) { 

            //Choice 1: prints bill from one account by calling
            //printBill with input of account number
            case 1: cout << "\n\nWhat is the account number ";
                    cin >> acct;
                    printBill(clients, acct, count);
                    break;
                    
            //Choice 2: prints pet info. from one account, calling
            //printPet with input of account number
            case 2: cout << "\n\nWhat is the account number ";
                    cin >> acct;
                    printPet(clients, acct, count);
                    break;
                    
            //Choice 3: adds client to client array by calling
            //addClient ONLY if count is less than set limit
            case 3: if(count < MAX_CLIENTS)
                        addClient(clients, count, nextAcctNum);
                    else
                        cout << "Client list has been maxed out at 10" << endl;
                    break;
                    
            //Choice 4: deletes active client from array and reorganizes
            //data by calling deleteClient with prompt input of acct. num.
            case 4: cout << "\n\nWhat is the account number ";
                    cin >> acct;
                    deleteClient(clients, acct, count);
                    break;
                    
            //Choice 5: prints all clients, their info., and pet
            //info. in a formatted table by calling printAll
            case 5: printAll(clients, count);
                    break;
                    
            //Choice 6: writes all database info. to output file
            //with a departing message, and assigns terminating 
            //value to inExit
            case 6: saveDB(clients, count, nextAcctNum);
                    cout << "\nYour datebase has been updated.   Goodbye." << endl;
                    inExit = true;
                    break;
                    
            //Message for invalid menu selection     
            default: cout << "\nInvalid menu selection" << endl;
            }
    }
    return 0;
}

//readOne is called by readClients to read a single client from the file
//it returns all the client information in a Client variable
Client readOne(istream & inFile) {
    Client t;  //temp for client being put into database
    
    inFile >> t.acctNum;     //recieve account number, name, address
    inFile.ignore(40, '\n'); //account balance, and the number of pets
    getline(inFile, t.name); //from file read
    getline(inFile, t.address);
    inFile >> t.acctBalance;
    inFile >> t.howmany;
    
    //for each pet, recieve pet species, breed,
    //name, gender, and age from file read
    for(int x = 0; x < t.howmany; x++) {
        inFile.ignore(40, '\n');  
        getline(inFile, t.pets[x].species);
        getline(inFile, t.pets[x].breed);
        getline(inFile, t.pets[x].name);
        inFile >> t.pets[x].gender;
        inFile >> t.pets[x].age;
    }
    
    return t;
}

//readClients reads all the clients from the file vetDB.dat
void readClients(Client clients[], int & count, int & nextAcctNum) {
    //input file stream for database
    ifstream inFile;
    inFile.open("vetDB.dat");
    
    //read in count of accounts and next acct. number
    inFile >> count; 
    inFile >> nextAcctNum;
    
    //for each account in count, read one account
    //from inFile and store into array database
    for(int i = 0; i < count; i++)
        clients[i] = readOne(inFile);
    
    inFile.close();
    return;
}

//findClient is called by printBill, printPet and deleteClient to find where the 
//client is in the file based on the account number.  
int findClient(const Client clients[], int count, int acctNum) {
    int i = 0;  //counter variable for index of clients
    
    //If input account number matches acct. num.,
    //return the index, if not return -1
    while(i < count) {
        if(clients[i].acctNum == acctNum)
            return i;
        i++;
    }
    return -1;
}

//deleteClient delete's a client if they exist by finding where
//they are in the clients array and then shifting all clients up
//one slot in the array - i.e., if we were deleting the client at
//index 5, then the client at 6 would move into 5, 7 would go to 6, etc.
void deleteClient(Client clients[], int acctNum, int &count) {
    //find index of matching account number
    int i = findClient(clients, count, acctNum);  
    
    if(i == -1) {  //if index not found, output message
        cout << "\nThe client wasn't found in the database\n" << endl;
    }
    else {   //if index found, overwrite each acct. with the one above it until the last
        for(int x = i; x < count; x++) {
            clients[x] = clients[x+1];
        }
        cout << "\nThe Client has been deleted" << endl;
        count--;  //decrease count by one
    }
}

//printBill prints the bill for a client based on account number
void printBill(const Client clients[], int acctNum, int count) {
    int i = findClient(clients, count, acctNum);  //integer for index of searching account number
    
    if(i == -1)  //if not found, output message 
       cout << "\nThe client wasn't found in the datebase\n" << endl;
    else { //if found, output name and balance of found account
       cout << "\nBill for " << clients[i].name << endl;
       cout << "Total owed is " << clients[i].acctBalance << endl;
    }
    return;
}

//printPet prints all the information for a specific client's pet
//based on the pet's name.  It will have to call findClient first,
//then if the client exists, it will ask for the pet name and
//if the pet exists, then it will print the pet info
void printPet(const Client clients[], int acctNum, int count) {
    int i = findClient(clients, count, acctNum);  //the index of matching account number
    int j = 0;  //counter for loop fiding pet name
    bool isFound = false;  //flag for loop finding pet name
    string pname;  //string for input pet name
    
    //if index not found (returns -1),
    //print that it wasn't found
    if(i == -1)
       cout << "\nThe client wasn't found in the datebase\n" << endl;
    
    else {
       //if index is found, input petname into pname
       cout << "What is the pet's name ";
       cin >> pname;
       
       //This loop goes through each iteration comparing each
       //pet's name associated with the target client to pname,
       //isFound will be updated to true if the 
       while(!isFound && j < clients[i].howmany) {
           if(clients[i].pets[j].name == pname){
               isFound = true;
           }
           j++;
       }
       
       //If pet is found from previous loop,
       //print out information for the pet
       if(isFound) {
           cout << "\nInformation for " << pname << left << endl;
           cout << setw(9) << "Species:" << clients[i].pets[j-1].species << endl;
           cout << setw(9) << "Breed:" << clients[i].pets[j-1].breed << endl;
           cout << setw(9) << "Gender:" << clients[i].pets[j-1].gender << endl;
           cout << setw(9) << "Age:" << clients[i].pets[j-1].age << endl;
       }
       else
           cout << "\nThe pet isn't in the database" << endl;
    }
    return;
}

//addClient asks for all client information except the 
//account number and also assuming there aren't
//already 10 clients, and then it adds that information to the
//client array.  nextAcctNum should be incremented and so should count
void addClient(Client clients[], int & count, int & nextAcctNum) {
    Client t; //temporary client for information input
    t.acctNum = nextAcctNum; //the account number will be nextAcctNum
    t.acctBalance = 0; //initialize the client's balance to 0
    
    //Recieve input for name, address, and number of pets
    //and put values the respective members of the client
    cout << "\nInput client information:" << endl;
    cin.ignore(40, '\n');
    cout << "Name: ";
    getline(cin, t.name);
    cout << "Address: ";
    getline(cin, t.address);
    cout << "Number of pets: ";
    cin >> t.howmany;
    
    //Input validation for 10 pets per client
    while(t.howmany > 10) {
        cout << "Only a maximum of 10 pets are accepted per client." << endl;
        cout << "Number of pets: ";
        cin >> t.howmany;
    }
    
    //For each pet, recieve species, breed, name,
    //gender, and age from input and initialize
    //member values of the pets array in the client.
    for(int x = 0; x < t.howmany; x++) {
        cin.ignore(40, '\n');
        cout << "Pet " << x+1 << " species: ";
        getline(cin, t.pets[x].species);
        cout << "Pet " << x+1 << " breed: ";
        getline(cin, t.pets[x].breed);
        cout << "Pet " << x+1 << " name: ";
        cin >> t.pets[x].name;
        cout << "Pet " << x+1 << " gender: ";
        cin >> t.pets[x].gender;
        cout << "Pet " << x+1 << " age: ";
        cin >> t.pets[x].age;
    }
    
    //Push temporary client to next slot in the clients array,
    //and increment the count and next account number.
    clients[count] = t;
    count++;
    nextAcctNum++;
    
    return;
}

//saveDB will write the count, then the nextAcctNum, then all the
//client info in the same format that was in the original vetDB.dat file.
//this data will be written to vetDB.dat - i.e., the file will be
//overwritten.
void printAll(const Client clients[], int count) {
    cout << "\n\nClient List:" << endl;
    
    //print all client info. in seperate lines
    //for each client in the database array.
    for(int i = 0; i < count; i++) {
        cout << clients[i].name << endl;
        cout << clients[i].acctNum << endl;
        cout << clients[i].address << endl;
        cout << clients[i].acctBalance << endl;
        cout << "Pets:" << endl;
        
        //print all pet info. in the same line
        //per the value of howmany of the client
        for(int x = 0; x < clients[i].howmany; x++) {
            cout << "\t" << clients[i].pets[x].name << "  "
                 << clients[i].pets[x].species << "  "
                 << clients[i].pets[x].breed << "  "
                 << clients[i].pets[x].gender << "  "
                 << clients[i].pets[x].age << endl;
                 
        }
        cout << endl << endl;
    }
}

//printAll prints out the database of clients
void saveDB(Client clients[],int count, int nextAcctNum) {
    //outFile will overwrite all database information
    //to same input file vetDB.dat.
    ofstream outFile ("vetDB.dat"); 
    
    //write the heading with the count and next account number
    outFile << count << endl;
    outFile << nextAcctNum << endl;
    outFile << endl;
    
    //This first part of this loop will write all members of 
    //the Client struct for each client in the array to vetDB.dat
    for(int i = 0; i < count; i++) {
        outFile << clients[i].acctNum << endl;
        outFile << clients[i].name << endl;
        outFile << clients[i].address << endl;
        outFile << clients[i].acctBalance << endl;
        outFile << clients[i].howmany << endl;
        
        //This nested loop will write all members of the 
        //Pet struct for each pet from howmany for each client.
        for(int j = 0; j < clients[i].howmany; j++) {
            outFile << clients[i].pets[j].species << endl;
            outFile << clients[i].pets[j].breed << endl;
            outFile << clients[i].pets[j].name << endl;
            outFile << clients[i].pets[j].gender << endl;
            outFile << clients[i].pets[j].age << endl;
        }
        outFile << endl;
    }
    outFile.close();
}
