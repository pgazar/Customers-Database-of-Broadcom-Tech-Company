//Kenneth Ao, Team #8
//Pegah Zargarian
//main integrates all source files and header files, creating one working program.
//functions to UI and printing are placed in here

#include <iostream>
#include <fstream>
#include <sstream>
#include "Customer.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "StackADT.h"


using namespace std;

void add(HashTable<Customer>&, BinarySearchTree<Customer>&);
void printInstructions();
Customer deleteData(HashTable<Customer>&, BinarySearchTree<Customer>&);
void printTeam();
void searchPrimary(HashTable<Customer>&);
void SecondSearchManager(BinarySearchTree<Customer>&, void visit(Customer&), int compare(Customer, Customer));
void vDisplay(Customer&);
void iDisplay(Customer&, int);
void statistics(HashTable<Customer>&);
void writeToFile(string filename, Stack<Customer>&);
void writeData(HashTable<Customer>&);

template <class ItemType>
int compareSecondary(ItemType, ItemType);

/*~*~*~*
 Hash function: takes the key and returns the index in the hash table
 *~**/
int key_to_index(const Customer& key, int size)
{
    string k = key.getCusNum();
    int sum = 0;
    for (int i = 0; k[i]; i++)
        sum += k[i];
    return sum % size;
};

//Implementation for File Input
//Counts the lines in the file, finds a size for the hash table, and populates the hashtable and the BST with Customer objects
HashTable<Customer> readData(string filename, BinarySearchTree<Customer>& tree) {
    string line = "";
    //create new file stream
    ifstream lineCounter(filename);
    int numLines = 0;

    // open file
    if (!lineCounter) {
        cout << "\"" << filename << "\" could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(lineCounter, line))
    {
        numLines++;
    }
    //close your file
    lineCounter.close();



    //create hash table
    int hashSize = numLines * 2;
    int divisor = 2;
    bool foundSize = false;
    while (!foundSize)
    {
        while (!foundSize || (divisor > hashSize))
        {
            if (!(divisor == hashSize) && ((hashSize % divisor) == 0)) {
                break;
            }
            else if (divisor == hashSize) {
                foundSize = true;
            }
            else
                divisor += 1;
        }
        if (!foundSize) {
            hashSize++;
            divisor = 2;
        }
    }

    HashTable<Customer> hash(hashSize);

    //create new file stream
    ifstream file(filename);
    // open file
    if (!file) {
        cout << "\"" << filename << "\" could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    // loop to extract all colleges
    line = "";

    while (getline(file, line)) {
        string  CusNum;
        string    name;
        string    city;
        string   state;
        string     zip;
        int    YTDsale;

        //get the first line
        stringstream ss(line);

        //extract data into variables
        ss >> CusNum;
        ss >> state;
        ss >> zip;
        ss >> YTDsale;
        ss >> city;

        ss.ignore();
        ss >> std::ws;
        getline(ss, city, ';');
        ss >> std::ws;
        getline(ss, name);

        //construct customer object and
        Customer c(CusNum, name, city, state, zip, YTDsale);
        //insert into tree
        tree.insert(c, compareSecondary);
        //insert into hash table
        hash.insert(c, key_to_index);

    }
    //close your file
    file.close();
    return hash;
}

void menu(HashTable<Customer>& table, BinarySearchTree<Customer>& tree) {
    int command = -1;
    Customer undoCustomer;
    Stack<Customer> deletedStack;

    while (command != 0) {
        printInstructions();
        cin >> command;
        if (command == 1)            //add data
            add(table, tree);
        else if (command == 2) {     //delete data
            Customer deletedCustomer = deleteData(table, tree);
            deletedStack.push(deletedCustomer);
            //std::cout << deletedStack.peek().getName();
        }
        else if (command == 3)      //find and display one element using primary key
            searchPrimary(table);
        else if (command == 4)      //find and display elements using secondary key
            SecondSearchManager(tree, vDisplay, compareSecondary);
        else if (command == 5)      //list data sorted by secondary key
            tree.inOrder(vDisplay);
        else if (command == 6)      //write data to file
            writeData(table);
        else if (command == 7)      //statistics
            statistics(table);
        else if (command == 8)      //help
            continue;
        else if (command == 9) {     //undo delete
            undoCustomer = deletedStack.pop();
            tree.insert(undoCustomer, compareSecondary);
            table.insert(undoCustomer, key_to_index);
        }
        else if (command == 10)      //hidden print indented tree option
            tree.printTree(iDisplay);
        else if (command == 11)      //hidden option, display names of team members
            printTeam();
        else if (command == 12)
        {
            Stack<Customer> stack;
            table.populateStack(stack);
            while (!stack.isEmpty())
            {
                Customer cus = stack.pop();
                vDisplay(cus);
            }
        }
    }
    cout << "Exiting program...";
}

void add(HashTable<Customer>& table, BinarySearchTree<Customer>& tree) {
    string  cosNum;
    string    name;
    string    city;
    string   state;
    string     zip;
    int    YTDsale;
    Customer found;
    Customer key;
    cout << "Please enter a new customer data to add:" << endl << "Customer Number: ";
    cin >> cosNum;
    key.setCusNum(cosNum);
    if (table.search(found, key, key_to_index) != -1)
        cout << endl << "Duplicate key: " << found.getCusNum() << " - rejected! " << endl;
    else
    {
        cin.ignore();
        cout << "State: ";
        cin >> state;
        cout << "Zip Code: ";
        cin >> zip;
        cout << "Year to Date Sales: ";
        cin >> YTDsale;
        cout << "City: ";
        getline(cin, city);
        cout << "Name: ";
        getline(cin, name);
        Customer newCustomer(cosNum, name, city, state, zip, YTDsale);
        table.insert(newCustomer, key_to_index);
        tree.insert(newCustomer, compareSecondary);
    }
}

void printInstructions() {
    cout << "1. Add Data" << endl << "2. Delete Data" << endl << "3. Find and Display Data Using Primary Key" << endl << "4. Find and Display Elements Using Secondary Key" << endl << "5. List Data Sorted by Secondary Key" << endl << "6. Write Data to File" << endl << "7. Statistics" << endl << "8. Help" << endl << "9. Undo Delete" << endl << "0. Quit" << endl;
    cout << "Enter a command: ";
}

void printTeam() {
    cout << "Team Members: Kenneth Ao, Masato Ishizuka, Joel Morancy, Pegah Zargarian" << endl;
}


Customer deleteData(HashTable<Customer>& table, BinarySearchTree<Customer>& bst) {
    string cusNo;
    cout << "Enter Customer Number to delete: ";
    cin >> cusNo;
    Customer deleteKey;
    Customer outCustomer;
    deleteKey.setCusNum(cusNo);
    if (table.remove(outCustomer, deleteKey, key_to_index))
        cout << "Deleted from Hash Table" << endl;
    if (bst.remove(outCustomer, compareSecondary))
        cout << "Deleted from Binary Search Tree" << endl;
    return outCustomer;
}

void searchPrimary(HashTable<Customer>& table) {

    Customer found; // will store a copy of the item found in the hash table
    string cusId;   // name to insert
    cout << "Enter customer Id or Q to quit: ";
    cin >> cusId;
    Customer aCustomer;
    Customer key;

    cout << "\n Primary Search\n";
    cout << "===================\n";


    while (cusId != "Q") {
        key.setCusNum(cusId);
        Customer found;
        // search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
        if (table.search(found, key, key_to_index) != -1)
            cout << endl << "Found: " << found.getName() << " " << found.getCusNum() << endl;
        else
            cout << endl << cusId << " not found!" << endl;
        cout << "Enter customer Id or Q to quit: ";
        cin >> cusId;
    }


    return;
}


void SecondSearchManager(BinarySearchTree<Customer>& custST, void visit(Customer&), int compare(Customer, Customer))
{
    string targetName;
    Customer aCustomer;

    cout << "\n Secondary Search\n";
    cout << "====================\n";
    cout << "\nEnter a Customer Name(or Q to stop searching) : " << endl;
    cin.ignore();
    getline(cin, targetName);
    while (toupper(targetName[0]) != 'Q')
    {
        if (toupper(targetName[0]) != 'Q') {
            for (unsigned int i = 0; i < targetName.size(); i++) {
                targetName.at(i) = toupper(targetName.at(i));
            }
            Customer target;
            target.setName(targetName);
            int numCustomersFound = 0;

            if (!custST.search(visit, target, numCustomersFound, compare))
                cout << "Customer "" << targetName << "" was not found in this list." << endl;
        }
        cout << "\nEnter a Customer Name(or Q to stop searching) : " << endl;
        getline(cin, targetName);
    }
    cout << "__END SEARCH SECTION__\n";
    return;
}

void statistics(HashTable<Customer>& table) {
    cout << "Load Factor: " << table.getLoadFactor() << endl;
    cout << "Number of Collisions: " << table.totalCollisions() << endl;
    cout << "Length of Longest Linked List: " << table.longestLinkedList() << endl;
}

void visit(Customer& customer) {
    vDisplay(customer);
}

void vDisplay(Customer& item)
{
    cout << endl << "Found: " << "Customer Name: " << item.getName() << endl;
    cout << "   Customer Number " << item.getCusNum() << endl;
    cout << "   City " << item.getCity() << endl;
    cout << "   State " << item.getState() << endl;
    cout << "   Zip " << item.getZip() << endl;
    cout << "   Year To Date Sale: $" << item.getYTD() << endl;
}

void iDisplay(Customer& item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item.getName() << endl;
}


template <class ItemType>
int compareSecondary(ItemType target, ItemType curNode) {
    if (target.getName() < curNode.getName())
        return -1;
    else if (target.getName() > curNode.getName())
        return 1;
    else
        return 0;
    /*if (target < curNode)
        return -1;
    else if (target > curNode)
        return 1;
    else
        return 0;*/

}

void writeData(HashTable<Customer>& table) {
    string newFile;
    cout << "Enter File Name to Write to:";
    cin >> newFile;
    Stack<Customer> copyStack;
    table.populateStack(copyStack);
    Stack<Customer> inOrderStack;
    while (!copyStack.isEmpty()) {
        inOrderStack.push(copyStack.pop());
    }
    writeToFile(newFile, inOrderStack);
}


//Implementation for File Output
//Takes a stack with Customoer objects, pops each one and outputs to a file in the same format as the original input file
void writeToFile(string filename, Stack<Customer>& stack)
{
    //create new file stream
    ofstream file("backup_" + filename);
    // open file
    if (!file) {
        cout << "\"" << filename << "\" could not be opened." << endl;
        exit(EXIT_FAILURE);
    }

    // loop to extract all customers
    while (!stack.isEmpty()) {
        Customer aCustomer = stack.pop();
        file << aCustomer.getCusNum() << " " << aCustomer.getState() << " " << aCustomer.getZip() << " " << aCustomer.getYTD() << " " << aCustomer.getCity() << "; " << aCustomer.getName() << endl;
    }
    //close your file
    file.close();
}

int main() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    BinarySearchTree<Customer> bst;
    HashTable<Customer> hashTable = readData(fileName, bst);
    menu(hashTable, bst);


    return 0;
}

