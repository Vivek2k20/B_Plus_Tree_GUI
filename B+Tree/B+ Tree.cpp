#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
#include <dirent.h>
#include <filesystem>
#include "B+ Tree.h"


#define _CRT_SECURE_NO_DEPRECATE  //for VS 2019




bool hasEnding (std::string const &fullString, std::string const &ending) 
{
    if (fullString.length() >= ending.length()) 
	{
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else 
	{
        return false;
    }
}


void printvec(vector<string> vec)
{
	for (auto a : vec) 
		cout<<a<<" ";
    cout << endl;
}

void printvec(vector<int> vec)
{
	for (auto a : vec) 
		cout<<a<<" ";
    cout << endl;
}


inline bool file_exists(string name) {
	name="./DBFiles/"+name+".txt";
	//cout<<"Checking if "<<name<<" exists"<<endl;
    if (FILE *file = fopen(name.c_str(), "r")) 
	{
        fclose(file);
        return true;
    } else 
	{
        return false;
    }   
}


inline bool isNumber(const string str)
{
    for (char const &c : str) {
        if (isdigit(c) == 0) 
			return false;
    }
    return true;
}




string importMethod(BPTree** bPTree) 
{
	int ch;
    string res;

    /*
	while(1)
	{
	cout<<"\n\n\t\t\tWARNING!!"<<endl;
	cout<<"This option is to import multiple record files into the tree at once.\nIt will scan the DBFiles folder and place all the files of the format \"RecordNo.txt\" in the B+ Tree.\nIt will insert only the Files/Records which are not already present in the tree\n\n";
	cout<<"STEPS TO IMPORT :\n";
	cout<<"\t1.Place the record text files in the DBFiles Folder\n\t2.Rename each file to the Record Number(The key that has to be used by B+ Tree)\n\nTo Continue \t: \tEnter 1\nTo Abort \t: \tEnter 2\nEnter your choice : ";
	cin>>ch;
	if(ch==2)
		return;
	else if(ch==1)
		break;
	else cout<<"Enter a valid choice.\n";
	};
    */
	DIR *dir; 
	struct dirent *diread;
    vector<string> files;

    if ((dir = opendir("./DBFiles")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        exit(1);
    }
	vector<string> textfiles;
    for (auto file : files) 
	{
		if (hasEnding(file,".txt"))
			textfiles.push_back(file.substr(0,file.size()-4));
	};
	vector<int> numbers;
	for (auto file : textfiles) 
	{
		if (isNumber(file))
		{
			if(file_exists(file))
				numbers.push_back(atoi(file.c_str()));
		}
	};
	//printvec(numbers);
	if(numbers.size()==0)
	{
		res="No eligible files found for importing!\n";
		return res;
	}
	for(int i=0;i<numbers.size();i++)
	{
		if((*bPTree)->search(numbers[i]).second==-1)
		{
			string fileName = "./DBFiles/";
			fileName += to_string(numbers[i]) + ".txt";
			FILE* filePtr = fopen(fileName.c_str(), "r");
			(*bPTree)->insert(numbers[i], filePtr);
			res=res+ "Insertion of Record No. : " + std::to_string(numbers[i])+" Successful"+"\n";
		};
	};
    return res;
}






void insertionMethod(BPTree** bPTree) {
    int rNo,dose;
    string name,vaccine,mNo;

    cout << "Please provide the Record No. : ";
    cin >> rNo;
	
	cout<<"Record "<<rNo<<" details :\n";
    cout << "Name : ";
    cin >> name ;
	cout<<"Mobile No. : ";
	cin>>mNo;
	cout<<"Vaccine(Covishield/Covaxin) : ";
	cin>> vaccine ;
	cout<<"Dose number(1/2) : ";
	cin>> dose;

    string fileName = "DBFiles/";
    fileName += to_string(rNo) + ".txt";
    FILE* filePtr = fopen(fileName.c_str(), "w");
    string userTuple = name + " " + mNo + " " + vaccine +" "+ to_string(dose) + "\n";
    fprintf(filePtr, userTuple.c_str());
	fclose(filePtr);
	filePtr = fopen(fileName.c_str(), "r");
    (*bPTree)->insert(rNo, filePtr);
    //fclose(filePtr);
    cout << "Insertion of Record No. : " << rNo << " Successful"<<endl;
}

void searchMethod(BPTree* bPTree) {
    int rNo;
    cout << "What's the Record No. to Search? ";
    cin >> rNo;
    pair<Node*,int> found=bPTree->search(rNo);
	if(found.second==-1)
		cout<<"Key Not found\n";
	else
	{
		Node* cursor=found.first;
		int idx=found.second;
		cout << "Hurray!! Key FOUND" << endl;
        cout << "Corresponding Tuple Data is: ";
        char ch = fgetc(cursor->ptr2TreeOrData.dataPtr[idx]);
        while (ch != EOF) {
            printf("%c", ch);
            ch = fgetc(cursor->ptr2TreeOrData.dataPtr[idx]);
        };
		cout<<endl;
	};
}

void printMethod(BPTree* bPTree) {
    int opt;
    cout << "Press \n\t1.Hierarical-Display \n\t2.Sequential-Display\n";
    cin >> opt;
    if (opt == 1)
        bPTree->display(bPTree->getRoot());
    else
        bPTree->seqDisplay(bPTree->getRoot());
}

void deleteMethod(BPTree* bPTree) {
    cout << "Showing you the Tree, Choose a key from here: " << endl;
    bPTree->display(bPTree->getRoot());
 
    int tmp;
    cout << "Enter a key to delete: " << endl;
    cin >> tmp;
    bPTree->removeKey(tmp);

    //Displaying
    bPTree->display(bPTree->getRoot());
}

int main() {
    /*
		Please have a look at the default schema to get to know about the table
		Reference - img/database.jpg
	*/

    cout << "\n***Welcome to DATABASE SERVER***\n"
         << endl;

    bool flag = true;
    int option;

    int maxChildInt = 4, maxNodeLeaf = 3;
    cout << "Please provide the value to limit maximum child Internal Nodes can have: ";
    cin >> maxChildInt;
    cout << "\nAnd Now Limit the value to limit maximum Nodes Leaf Nodes can have: ";
    cin >> maxNodeLeaf;

    BPTree* bPTree = new BPTree(maxChildInt, maxNodeLeaf);

    do {
        cout << "\nPlease provide the queries with respective keys : " << endl;
        cout << "\tPress 1: Import \n\tPress 2: Insertion \n\tPress 3: Search \n\tPress 4: Print Tree\n\tPress 5: Delete Key In Tree\n\tPress 6: ABORT!" << endl;
        cin >> option;

        switch (option) {
			case 1:
				importMethod(&bPTree);
				break;
            case 2:
                insertionMethod(&bPTree);
                break;
            case 3:
                searchMethod(bPTree);
                break;
            case 4:
                printMethod(bPTree);
                break;
            case 5:
                deleteMethod(bPTree);
                break;
			case 6:
				flag=false;
				break;
            default:
                cout<<"Enter valid option !"<<endl;
        }
    }while (flag);

    return 0;
}
