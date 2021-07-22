#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
#include<dirent.h>
//#include <filesystem>
using namespace std;
#define _CRT_SECURE_NO_DEPRECATE  //for VS 2019

#define NODE_H

class Node {
    /*
        Generally size of the this node should be equal to the block size. Which will limit the number of disk access and increase the accesssing time.
        Intermediate nodes only hold the Tree pointers which is of considerably small size(so they can hold more Tree pointers) and only Leaf nodes hold
        the data pointer directly to the disc.

        IMPORTANT := All the data has to be present in the leaf node
    */
public:
    bool isLeaf;
    vector<int> keys;
    //Node* ptr2parent; //Pointer to go to parent node CANNOT USE check https://stackoverflow.com/questions/57831014/why-we-are-not-saving-the-parent-pointer-in-b-tree-for-easy-upward-traversal-in
    Node* ptr2next;              //Pointer to connect next node for leaf nodes
    union ptr {                  //to make memory efficient Node
        vector<Node*> ptr2Tree;  //Array of pointers to Children sub-trees for intermediate Nodes
        vector<FILE*> dataPtr;   // Data-Pointer for the leaf node

        ptr();   // To remove the error !?
        ~ptr();  // To remove the error !?
    } ptr2TreeOrData;

    friend class BPTree;  // to access private members of the Node and hold the encapsulation concept
public:
    Node();
};

class BPTree {
    /*
        ::For Root Node :=
            The root node has, at least two tree pointers
        ::For Internal Nodes:=
            1. ceil(maxIntChildLimit/2)     <=  #of children <= maxIntChildLimit
            2. ceil(maxIntChildLimit/2)-1  <=  #of keys     <= maxIntChildLimit -1
        ::For Leaf Nodes :=
            1. ceil(maxLeafNodeLimit/2)   <=  #of keys     <= maxLeafNodeLimit -1
    */
private:
    int maxIntChildLimit;                                   //Limiting  #of children for internal Nodes!
    int maxLeafNodeLimit;                                   // Limiting #of nodes for leaf Nodes!!!
    Node* root;                                             //Pointer to the B+ Tree root
    void insertInternal(int x, Node** cursor, Node** child);  //Insert x from child in cursor(parent)
    Node** findParent(Node* cursor, Node* child);
    Node* firstLeftNode(Node* cursor);

public:
    BPTree();
    BPTree(int degreeInternal, int degreeLeaf);
    Node* getRoot();
    int getMaxIntChildLimit();
    int getMaxLeafNodeLimit();
    void setRoot(Node*);
    string display(Node* cursor);
    pair<Node*, int> search(int key);
    void insert(int key, FILE* filePtr);
    string removeKey(int key);
    string removeInternal(int x, Node* cursor, Node* child);
};

//UTIL


Node* parent = NULL;

Node::ptr::ptr() {
}

Node::ptr::~ptr() {
}

Node::Node() {
    this->isLeaf = false;
    this->ptr2next = NULL;
}

BPTree::BPTree() {
    /*
        By Default it will take the maxIntChildLimit as 4. And
        maxLeafNodeLimit as 3.

        ::REASON FOR TWO SEPERATE VARIABLES maxIntChildLimit & maxLeafNodeLimit !!
        We are keeping the two seperate Orders
        because Internal Nodes can hold more values in one disc block
        as the size of the Tree pointer is small but the size of the
        data pointer in the leaf nodes is large so we can only put less
        nodes in the leafs as compared to the internal Nodes. Thats the
        reson to reperate out these to variables.

    */
    this->maxIntChildLimit = 4;
    this->maxLeafNodeLimit = 4;
    this->root = NULL;
}

BPTree::BPTree(int degreeInternal, int degreeLeaf) {
    this->maxIntChildLimit = degreeInternal;
    this->maxLeafNodeLimit = degreeLeaf;
    this->root = NULL;
}

int BPTree::getMaxIntChildLimit() {
    return maxIntChildLimit;
}

int BPTree::getMaxLeafNodeLimit() {
    return maxLeafNodeLimit;
}

Node* BPTree::getRoot() {
    return this->root;
}

void BPTree::setRoot(Node* ptr) {
    this->root = ptr;
}

Node* BPTree::firstLeftNode(Node* cursor) {
    if (cursor->isLeaf)
        return cursor;
    for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++)
        if (cursor->ptr2TreeOrData.ptr2Tree[i] != NULL)
            return firstLeftNode(cursor->ptr2TreeOrData.ptr2Tree[i]);

    return NULL;
}

Node** BPTree::findParent(Node* cursor, Node* child) {
    /*
        Finds parent using depth first traversal and ignores leaf nodes as they cannot be parents
        also ignores second last level because we will never find parent of a leaf node during insertion using this function
    */

    if (cursor->isLeaf || cursor->ptr2TreeOrData.ptr2Tree[0]->isLeaf)
        return NULL;

    for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++) {
        if (cursor->ptr2TreeOrData.ptr2Tree[i] == child) {
            parent = cursor;
        }
        else {
            //Commenting To Remove vector out of bound Error: 
            //new (&cursor->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
            Node* tmpCursor = cursor->ptr2TreeOrData.ptr2Tree[i];
            findParent(tmpCursor, child);
        }
    }

    return &parent;
}




bool hasEnding(std::string const& fullString, std::string const& ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}


void printvec(vector<string> vec)
{
    for (auto a : vec)
        cout << a << " ";
    cout << endl;
}

void printvec(vector<int> vec)
{
    for (auto a : vec)
        cout << a << " ";
    cout << endl;
}


inline bool file_exists(string name) {
    name = "./DBFiles/" + name + ".txt";
    //cout<<"Checking if "<<name<<" exists"<<endl;
    if (FILE* file = fopen(name.c_str(), "r"))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}


inline bool isNumber(const string str)
{
    for (char const& c : str) {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}




string importMethod(BPTree** bPTree)
{
    string res = "";
    int ch;
    /*
    while (1)
    {
        cout << "\n\n\t\t\tWARNING!!" << endl;
        cout << "This option is to import multiple record files into the tree at once.\nIt will scan the DBFiles folder and place all the files of the format \"RecordNo.txt\" in the B+ Tree.\nIt will insert only the Files/Records which are not already present in the tree\n\n";
        cout << "STEPS TO IMPORT :\n";
        cout << "\t1.Place the record text files in the DBFiles Folder\n\t2.Rename each file to the Record Number(The key that has to be used by B+ Tree)\n\nTo Continue \t: \tEnter 1\nTo Abort \t: \tEnter 2\nEnter your choice : ";
        cin >> ch;
        if (ch == 2)
            return;
        else if (ch == 1)
            break;
        else cout << "Enter a valid choice.\n";
    };
    */
    DIR* dir;
    struct dirent* diread;
    vector<string> files;

    if ((dir = opendir("./DBFiles")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir(dir);
    }
    else {
        perror("opendir");
        exit(1);
    }
    vector<string> textfiles;
    for (auto file : files)
    {
        if (hasEnding(file, ".txt"))
            textfiles.push_back(file.substr(0, file.size() - 4));
    };
    vector<int> numbers;
    for (auto file : textfiles)
    {
        if (isNumber(file))
        {
            if (file_exists(file))
                numbers.push_back(atoi(file.c_str()));
        }
    };
    //printvec(numbers);
    if (numbers.size() == 0)
    {
        res = res + "No eligible files found for importing!\n";
        return res;
    }
    int count = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        if ((*bPTree)->search(numbers[i]).second == -1)
        {
            string fileName = "./DBFiles/";
            fileName += to_string(numbers[i]) + ".txt";
            FILE* filePtr = fopen(fileName.c_str(), "r");
            (*bPTree)->insert(numbers[i], filePtr);
            fclose(filePtr);
            count++;
        };
    };
    if (count == 0)
        res = "No new files found for importing!\n";
    else
        res = "Insertion of " + to_string(count) + " records successful!\n";
    return res;
}






string insertionMethod(BPTree** bPTree, int rNo, string name, string vaccine, string mNo, int dose) {
    /*
    int rNo, dose;
    string name, vaccine, mNo;

    cout << "Please provide the Record No. : ";
    cin >> rNo;

    cout << "Record " << rNo << " details :\n";
    cout << "Name : ";
    cin >> name;
    cout << "Mobile No. : ";
    cin >> mNo;
    cout << "Vaccine(Covishield/Covaxin) : ";
    cin >> vaccine;
    cout << "Dose number(1/2) : ";
    cin >> dose;
    */
    string res;
    string fileName = "./DBFiles/";
    fileName += to_string(rNo) + ".txt";
    FILE* filePtr = fopen(fileName.c_str(), "w");
    string userTuple ="Name : "+ name + "\nMobile : " + mNo + "\nVaccine : " + vaccine + "\nDose : " + to_string(dose) + "\n";
    fprintf(filePtr, userTuple.c_str());
    fclose(filePtr);
    filePtr = fopen(fileName.c_str(), "r");
    (*bPTree)->insert(rNo, filePtr);
    fclose(filePtr);
    res = res + "Insertion of Record No. : " + to_string(rNo) + " Successful\n";
    return res;
}

string searchMethod(BPTree* bPTree, int rNo) {
    /*
    int rNo;
    cout << "What's the Record No. to Search? ";
    cin >> rNo;
    */
    string res;
    pair<Node*, int> found = bPTree->search(rNo);
    if (found.second == -1)
        res = "Record not found!\n";
    else
    {
        Node* cursor = found.first;
        int idx = found.second;
        /*
        string filename = "./DBFiles/"+to_string(rNo) + ".txt";
        ifstream f(filename);
        if (f) {
            ostringstream ss;
            ss << f.rdbuf(); // reading data
            res = ss.str();
        }
        else res = "File found,But unable to open.\n";
        */
        char ch = fgetc(cursor->ptr2TreeOrData.dataPtr[idx]);
        while (ch != EOF) {
            res = res + ch;
            ch = fgetc(cursor->ptr2TreeOrData.dataPtr[idx]);
        };
        fseek(cursor->ptr2TreeOrData.dataPtr[idx], 0, SEEK_SET);
        res = res + "\n";
    };
    return res;
}

/*
void printMethod(BPTree* bPTree) {
    int opt;
    cout << "Press \n\t1.Hierarical-Display \n\t2.Sequential-Display\n";
    cin >> opt;
    if (opt == 1)
        bPTree->display(bPTree->getRoot());
    else
        bPTree->seqDisplay(bPTree->getRoot());
}
*/

string deleteMethod(BPTree* bPTree, int tmp) {
    /*
    cout << "Showing you the Tree, Choose a key from here: " << endl;
    bPTree->display(bPTree->getRoot());

    int tmp;
    cout << "Enter a key to delete: " << endl;
    cin >> tmp;
    */
    string res = bPTree->removeKey(tmp);
    return res;
    /*
    //Displaying
    bPTree->display(bPTree->getRoot());
    */
}


//INSERTION//

void BPTree::insert(int key, FILE* filePtr) {  //in Leaf Node
    /*
        1. If the node has an empty space, insert the key/reference pair into the node.
        2. If the node is already full, split it into two nodes, distributing the keys
        evenly between the two nodes. If the node is a leaf, take a copy of the minimum
        value in the second of these two nodes and repeat this insertion algorithm to
        insert it into the parent node. If the node is a non-leaf, exclude the middle
        value during the split and repeat this insertion algorithm to insert this excluded
        value into the parent node.
    */

    if (root == NULL) {
        root = new Node;
        root->isLeaf = true;
        root->keys.push_back(key);
        new (&root->ptr2TreeOrData.dataPtr) std::vector<FILE*>;
        //// now, root->ptr2TreeOrData.dataPtr is the active member of the union
        root->ptr2TreeOrData.dataPtr.push_back(filePtr);

        //cout << key << ":ROOT!!" << endl;
        return;
    }
    else {
        Node* cursor = root;
        Node* parent = NULL;
        //searching for the possible position for the given key by doing the same procedure we did in search
        while (cursor->isLeaf == false) {
            parent = cursor;
            int idx = std::upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();
            cursor = cursor->ptr2TreeOrData.ptr2Tree[idx];
        }

        //now cursor is the leaf node in which we'll insert the new key
        if (cursor->keys.size() < maxLeafNodeLimit) {
            /*
                If current leaf Node is not FULL, find the correct position for the new key and insert!
            */
            int i = std::upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();
            cursor->keys.push_back(key);
            cursor->ptr2TreeOrData.dataPtr.push_back(filePtr);

            if (i != cursor->keys.size() - 1) {
                for (int j = cursor->keys.size() - 1; j > i; j--) {  // shifting the position for keys and datapointer
                    cursor->keys[j] = cursor->keys[j - 1];
                    cursor->ptr2TreeOrData.dataPtr[j] = cursor->ptr2TreeOrData.dataPtr[j - 1];
                }

                //since earlier step was just to inc. the size of vectors and making space, now we are simplying inserting
                cursor->keys[i] = key;
                cursor->ptr2TreeOrData.dataPtr[i] = filePtr;
            }
            //cout << "Inserted successfully: " << key << endl;
        }
        else {
            /*
                DAMN!! Node Overflowed :(
                HAIYYA! Splitting the Node .
            */
            vector<int> virtualNode(cursor->keys);
            vector<FILE*> virtualDataNode(cursor->ptr2TreeOrData.dataPtr);

            //finding the probable place to insert the key
            int i = std::upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();

            virtualNode.push_back(key);          // to create space
            virtualDataNode.push_back(filePtr);  // to create space

            if (i != virtualNode.size() - 1) {
                for (int j = virtualNode.size() - 1; j > i; j--) {  // shifting the position for keys and datapointer
                    virtualNode[j] = virtualNode[j - 1];
                    virtualDataNode[j] = virtualDataNode[j - 1];
                }

                //inserting
                virtualNode[i] = key;
                virtualDataNode[i] = filePtr;
            }
            /*
                BAZINGA! I have the power to create new Leaf :)
            */

            Node* newLeaf = new Node;
            newLeaf->isLeaf = true;
            new (&newLeaf->ptr2TreeOrData.dataPtr) std::vector<FILE*>;
            //// now, newLeaf->ptr2TreeOrData.ptr2Tree is the active member of the union

            //swapping the next ptr
            Node* temp = cursor->ptr2next;
            cursor->ptr2next = newLeaf;
            newLeaf->ptr2next = temp;

            //resizing and copying the keys & dataPtr to OldNode
            cursor->keys.resize((maxLeafNodeLimit) / 2 + 1);//check +1 or not while partitioning
            cursor->ptr2TreeOrData.dataPtr.reserve((maxLeafNodeLimit) / 2 + 1);
            for (int i = 0; i <= (maxLeafNodeLimit) / 2; i++) {
                cursor->keys[i] = virtualNode[i];
                cursor->ptr2TreeOrData.dataPtr[i] = virtualDataNode[i];
            }

            //Pushing new keys & dataPtr to NewNode
            for (int i = (maxLeafNodeLimit) / 2 + 1; i < virtualNode.size(); i++) {
                newLeaf->keys.push_back(virtualNode[i]);
                newLeaf->ptr2TreeOrData.dataPtr.push_back(virtualDataNode[i]);
            }

            if (cursor == root) {
                /*
                    If cursor is root node we create new node
                */

                Node* newRoot = new Node;
                newRoot->keys.push_back(newLeaf->keys[0]);
                new (&newRoot->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
                newRoot->ptr2TreeOrData.ptr2Tree.push_back(cursor);
                newRoot->ptr2TreeOrData.ptr2Tree.push_back(newLeaf);
                root = newRoot;
                //cout << "Created new Root!" << endl;
            }
            else {
                // Insert new key in the parent
                insertInternal(newLeaf->keys[0], &parent, &newLeaf);
            }
        }
    }
}

void BPTree::insertInternal(int x, Node** cursor, Node** child) {  //in Internal Nodes
    if ((*cursor)->keys.size() < maxIntChildLimit - 1) {
        /*
            If cursor is not full find the position for the new key.
        */
        int i = std::upper_bound((*cursor)->keys.begin(), (*cursor)->keys.end(), x) - (*cursor)->keys.begin();
        (*cursor)->keys.push_back(x);
        //new (&(*cursor)->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
        //// now, root->ptr2TreeOrData.ptr2Tree is the active member of the union
        (*cursor)->ptr2TreeOrData.ptr2Tree.push_back(*child);

        if (i != (*cursor)->keys.size() - 1) {  // if there are more than one element
            // Different loops because size is different for both (i.e. diff of one)

            for (int j = (*cursor)->keys.size() - 1; j > i; j--) {  // shifting the position for keys and datapointer
                (*cursor)->keys[j] = (*cursor)->keys[j - 1];
            }

            for (int j = (*cursor)->ptr2TreeOrData.ptr2Tree.size() - 1; j > (i + 1); j--) {
                (*cursor)->ptr2TreeOrData.ptr2Tree[j] = (*cursor)->ptr2TreeOrData.ptr2Tree[j - 1];
            }

            (*cursor)->keys[i] = x;
            (*cursor)->ptr2TreeOrData.ptr2Tree[i + 1] = *child;
        }
        //cout << "Inserted key in the internal node :)" << endl;
    }
    else {  //splitting
       // cout << "Inserted Node in internal node successful" << endl;
        //cout << "Overflow in internal:( HAIYAA! splitting internal nodes" << endl;

        vector<int> virtualKeyNode((*cursor)->keys);
        vector<Node*> virtualTreePtrNode((*cursor)->ptr2TreeOrData.ptr2Tree);

        int i = std::upper_bound((*cursor)->keys.begin(), (*cursor)->keys.end(), x) - (*cursor)->keys.begin();  //finding the position for x
        virtualKeyNode.push_back(x);                                                                   // to create space
        virtualTreePtrNode.push_back(*child);                                                           // to create space

        if (i != virtualKeyNode.size() - 1) {
            for (int j = virtualKeyNode.size() - 1; j > i; j--) {  // shifting the position for keys and datapointer
                virtualKeyNode[j] = virtualKeyNode[j - 1];
            }

            for (int j = virtualTreePtrNode.size() - 1; j > (i + 1); j--) {
                virtualTreePtrNode[j] = virtualTreePtrNode[j - 1];
            }

            virtualKeyNode[i] = x;
            virtualTreePtrNode[i + 1] = *child;
        }

        int partitionKey;                                            //exclude middle element while splitting
        partitionKey = virtualKeyNode[(virtualKeyNode.size() / 2)];  //right biased
        int partitionIdx = (virtualKeyNode.size() / 2);

        //resizing and copying the keys & TreePtr to OldNode
        (*cursor)->keys.resize(partitionIdx);
        (*cursor)->ptr2TreeOrData.ptr2Tree.resize(partitionIdx + 1);
        (*cursor)->ptr2TreeOrData.ptr2Tree.reserve(partitionIdx + 1);
        for (int i = 0; i < partitionIdx; i++) {
            (*cursor)->keys[i] = virtualKeyNode[i];
        }

        for (int i = 0; i < partitionIdx + 1; i++) {
            (*cursor)->ptr2TreeOrData.ptr2Tree[i] = virtualTreePtrNode[i];
        }

        Node* newInternalNode = new Node;
        new (&newInternalNode->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
        //Pushing new keys & TreePtr to NewNode

        for (int i = partitionIdx + 1; i < virtualKeyNode.size(); i++) {
            newInternalNode->keys.push_back(virtualKeyNode[i]);
        }

        for (int i = partitionIdx + 1; i < virtualTreePtrNode.size(); i++) {  // because only key is excluded not the pointer
            newInternalNode->ptr2TreeOrData.ptr2Tree.push_back(virtualTreePtrNode[i]);
        }

        if ((*cursor) == root) {
            /*
                If cursor is a root we create a new Node
            */
            Node* newRoot = new Node;
            newRoot->keys.push_back(partitionKey);
            new (&newRoot->ptr2TreeOrData.ptr2Tree) std::vector<Node*>;
            newRoot->ptr2TreeOrData.ptr2Tree.push_back(*cursor);
            //// now, newRoot->ptr2TreeOrData.ptr2Tree is the active member of the union
            newRoot->ptr2TreeOrData.ptr2Tree.push_back(newInternalNode);

            root = newRoot;
            //cout << "Created new ROOT!" << endl;
        }
        else {
            /*
                ::Recursion::
            */
            insertInternal(partitionKey, findParent(root, *cursor), &newInternalNode);
        }
    }
}

//SEARCH//



pair<Node*, int> BPTree::search(int key) {
    if (root == NULL) {
        //cout << "NO Tuples Inserted yet" << endl;
        return make_pair(root, -1);
    }
    else {
        Node* cursor = root;
        while (cursor->isLeaf == false) {
            /*
                upper_bound returns an iterator pointing to the first element in the range
                [first,last) which has a value greater than �val�.(Because we are storing the
                same value in the right node;(STL is doing Binary search at back end)
            */
            int idx = std::upper_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();
            cursor = cursor->ptr2TreeOrData.ptr2Tree[idx];  //upper_bound takes care of all the edge cases
        }

        int idx = std::lower_bound(cursor->keys.begin(), cursor->keys.end(), key) - cursor->keys.begin();  //Binary search

        if (idx == cursor->keys.size() || cursor->keys[idx] != key) {
            //cout<<"Key Not Found!\n";
            return make_pair(root, -1);
        }
        /*
            We can fetch the data from the disc in main memory using data-ptr
        */
        return make_pair(cursor, idx);

        /*
            Back-Up Code for fetching the file pointer

        string fileName = "DBFiles/";
        string data;
        fileName += to_string(key) + ".txt";
        FILE* filePtr = fopen(fileName.c_str(), "r");
        cout << "Hurray!! Key FOUND" << endl;
        cout << "Corresponding Tuple Data is: ";
        char ch = fgetc(filePtr);
        while (ch != EOF) {
            printf("%c", ch);
            ch = fgetc(filePtr);
        }
        fclose(filePtr);
        cout << endl;
        */
    }
}


//DELETION//


string BPTree::removeKey(int x) {
    string res = "";
    Node* root = getRoot();

    // If tree is empty
    if (root == NULL) {
        res = "B+ Tree is Empty\n";
        return res;
    }

    Node* cursor = root;
    Node* parent;
    int leftSibling, rightSibling;

    // Going to the Leaf Node, Which may contain the *key*
    // TO-DO : Use Binary Search to find the val
    while (cursor->isLeaf != true) {
        for (int i = 0; i < cursor->keys.size(); i++) {
            parent = cursor;
            leftSibling = i - 1;//left side of the parent node
            rightSibling = i + 1;// right side of the parent node

            if (x < cursor->keys[i]) {
                cursor = cursor->ptr2TreeOrData.ptr2Tree[i];
                break;
            }
            if (i == cursor->keys.size() - 1) {
                leftSibling = i;
                rightSibling = i + 2;// CHECK here , might need to make it negative
                cursor = cursor->ptr2TreeOrData.ptr2Tree[i + 1];
                break;
            }
        }
    }

    // Check if the value exists in this leaf node
    int pos = 0;
    bool found = false;
    for (pos = 0; pos < cursor->keys.size(); pos++) {
        if (cursor->keys[pos] == x) {
            found = true;
            break;
        }
    }

    if (found == false) {
        res = res + "Key Not Found in the Tree\n";
        return res;
    }

    /* WHY CHECK AGAIN FOR INVALID KEY IN THE SET WHEN FOUND IS SET TO FALSE IF ITS INVALID?
    auto itr = lower_bound(cursor->keys.begin(), cursor->keys.end(), x);

    if (itr == cursor->keys.end()) {
        cout << "Key Not Found in the Tree" << endl;
        return;
    }
    */

    // Delete the respective File and FILE*
    string fileName = "DBFiles/" + to_string(x) + ".txt";
    char filePtr[256];
    strcpy(filePtr, fileName.c_str());
    fclose(cursor->ptr2TreeOrData.dataPtr[pos]);
    //delete cursor->ptr2TreeOrData.dataPtr[pos];//avoid memory leaks
    if (remove(filePtr) == 0)
        res = res + "SuccessFully Deleted file: " + fileName + "\n";
    else
        res = res + "Unable to delete the file: " + fileName + "\n";
    // Shifting the keys and dataPtr for the leaf Node
    for (int i = pos; i < cursor->keys.size() - 1; i++) {
        cursor->keys[i] = cursor->keys[i + 1];
        cursor->ptr2TreeOrData.dataPtr[i] = cursor->ptr2TreeOrData.dataPtr[i + 1];
    }
    int prev_size = cursor->keys.size();
    cursor->keys.resize(prev_size - 1);
    cursor->ptr2TreeOrData.dataPtr.resize(prev_size - 1);

    // If it is leaf as well as the root node
    if (cursor == root) {
        if (cursor->keys.size() == 0) {
            // Tree becomes empty
            setRoot(NULL);
            //res = res + "Ohh!! Our Tree is Empty Now :(" + "\n";
        }
    }

    res = res + "Deleted " + to_string(x) + " From Leaf Node successfully\n";
    if ((cursor->keys.size() >= (getMaxLeafNodeLimit() + 1) / 2)||(cursor==root)) {
        //Sufficient Node available for invariant to hold
        return res;
    }

    //res = res + "UnderFlow in the leaf Node Happended\n";
    //res = res + "Starting Redistribution...\n";

    //1. Try to borrow a key from leftSibling
    if (leftSibling >= 0) {
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];

        //Check if LeftSibling has extra Key to transfer
        if (leftNode->keys.size() >= (getMaxLeafNodeLimit() + 1) / 2 + 1) {

            //Transfer the maximum key from the left Sibling
            int maxIdx = leftNode->keys.size() - 1;
            cursor->keys.insert(cursor->keys.begin(), leftNode->keys[maxIdx]);
            cursor->ptr2TreeOrData.dataPtr.insert(cursor->ptr2TreeOrData.dataPtr.begin(), leftNode->ptr2TreeOrData.dataPtr[maxIdx]);

            //resize the left Sibling Node After Tranfer
            leftNode->keys.resize(maxIdx);
            leftNode->ptr2TreeOrData.dataPtr.resize(maxIdx);

            //Update Parent
            parent->keys[leftSibling] = cursor->keys[0];
            //res = res + "Transferred from left sibling of leaf node\n";
            return res;
        }
    }

    //2. Try to borrow a key from rightSibling
    if (rightSibling < parent->ptr2TreeOrData.ptr2Tree.size()) {
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];

        //Check if RightSibling has extra Key to transfer
        if (rightNode->keys.size() >= (getMaxLeafNodeLimit() + 1) / 2 + 1) {

            //Transfer the minimum key from the right Sibling
            int minIdx = 0;
            cursor->keys.push_back(rightNode->keys[minIdx]);
            cursor->ptr2TreeOrData.dataPtr
                .push_back(rightNode->ptr2TreeOrData.dataPtr[minIdx]);

            //resize the right Sibling Node After Tranfer
            rightNode->keys.erase(rightNode->keys.begin());
            rightNode->ptr2TreeOrData.dataPtr.erase(rightNode->ptr2TreeOrData.dataPtr.begin());

            //Update Parent
            parent->keys[rightSibling - 1] = rightNode->keys[0];
            //res = res + "Transferred from right sibling of leaf node\n";
            return res;
        }
    }

    // Merge and Delete Node
    if (leftSibling >= 0) {// If left sibling exists
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];
        //Transfer Key and dataPtr to leftSibling and connect ptr2next
        for (int i = 0; i < cursor->keys.size(); i++) {
            leftNode->keys.push_back(cursor->keys[i]);
            leftNode->ptr2TreeOrData.dataPtr
                .push_back(cursor->ptr2TreeOrData.dataPtr[i]);
        }
        leftNode->ptr2next = cursor->ptr2next;
        //res = res + "Merging two leaf Nodes\n";
        res = res + removeInternal(parent->keys[leftSibling], parent, cursor);//delete parent Node Key
        //delete cursor;
    }
    else if (rightSibling <= parent->keys.size()) {
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];
        //Transfer Key and dataPtr to rightSibling and connect ptr2next
        for (int i = 0; i < rightNode->keys.size(); i++) {
            cursor->keys.push_back(rightNode->keys[i]);
            cursor->ptr2TreeOrData.dataPtr
                .push_back(rightNode->ptr2TreeOrData.dataPtr[i]);
        }
        cursor->ptr2next = rightNode->ptr2next;
        //res = res + "Merging two leaf Nodes\n";
        res = res + removeInternal(parent->keys[rightSibling - 1], parent, rightNode);//delete parent Node Key
        //delete rightNode;
    }
    return res;
}

string BPTree::removeInternal(int x, Node* cursor, Node* child) {
    Node* root = getRoot();
    string res = "";
    // Check if key from root is to deleted
    if (cursor == root) {
        if (cursor->keys.size() == 1) {
            // If only one key is left and matches with one of the
            // child Pointers
            if (cursor->ptr2TreeOrData.ptr2Tree[1] == child) {
                setRoot(cursor->ptr2TreeOrData.ptr2Tree[0]);
                //delete cursor;
                //cout << "Wow! New Changed Root" << endl;
                return res;
            }
            else if (cursor->ptr2TreeOrData.ptr2Tree[0] == child) {
                setRoot(cursor->ptr2TreeOrData.ptr2Tree[1]);
                //delete cursor;
                //cout << "Wow! New Changed Root" << endl;
                return res;
            }
        }
    }

    // Deleting key x from the parent
    int pos;
    for (pos = 0; pos < cursor->keys.size(); pos++) {
        if (cursor->keys[pos] == x) {
            break;
        }
    }
    for (int i = pos; i < cursor->keys.size() - 1; i++) {
        cursor->keys[i] = cursor->keys[i + 1];
    }
    cursor->keys.resize(cursor->keys.size() - 1);

    // Now deleting the ptr2tree
    for (pos = 0; pos < cursor->ptr2TreeOrData.ptr2Tree.size(); pos++) {
        if (cursor->ptr2TreeOrData.ptr2Tree[pos] == child) {
            break;
        }
    }

    for (int i = pos; i < cursor->ptr2TreeOrData.ptr2Tree.size() - 1; i++) {
        cursor->ptr2TreeOrData.ptr2Tree[i] = cursor->ptr2TreeOrData.ptr2Tree[i + 1];
    }
    cursor->ptr2TreeOrData.ptr2Tree
        .resize(cursor->ptr2TreeOrData.ptr2Tree.size() - 1);

    // If there is No underflow. Phew!!
    if (cursor->keys.size() >= (getMaxIntChildLimit() + 1) / 2 - 1) {
        res = res + "Deleted " + to_string(x) + " from internal node successfully\n";
        return res;
    }

    //cout << "UnderFlow in internal Node! What did you do :/" << endl;

    if (cursor == root) {
        return res;
    }

    Node** p1 = findParent(root, cursor);
    Node* parent = *p1;

    int leftSibling, rightSibling;

    // Finding Left and Right Siblings as we did earlier
    for (pos = 0; pos < parent->ptr2TreeOrData.ptr2Tree.size(); pos++) {
        if (parent->ptr2TreeOrData.ptr2Tree[pos] == cursor) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }

    // If possible transfer to leftSibling
    if (leftSibling >= 0) {
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];

        //Check if LeftSibling has extra Key to transfer
        if (leftNode->keys.size() >= (getMaxIntChildLimit() + 1) / 2) {

            //transfer key from left sibling through parent
            int maxIdxKey = leftNode->keys.size() - 1;
            cursor->keys.insert(cursor->keys.begin(), parent->keys[leftSibling]);
            parent->keys[leftSibling] = leftNode->keys[maxIdxKey];

            int maxIdxPtr = leftNode->ptr2TreeOrData.ptr2Tree.size() - 1;
            cursor->ptr2TreeOrData.ptr2Tree
                .insert(cursor->ptr2TreeOrData.ptr2Tree.begin(), leftNode->ptr2TreeOrData.ptr2Tree[maxIdxPtr]);

            //resize the left Sibling Node After Tranfer
            leftNode->keys.resize(maxIdxKey);
            leftNode->ptr2TreeOrData.dataPtr.resize(maxIdxPtr);

            return res;
        }
    }

    // If possible transfer to rightSibling
    if (rightSibling < parent->ptr2TreeOrData.ptr2Tree.size()) {
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];

        //Check if LeftSibling has extra Key to transfer
        if (rightNode->keys.size() >= (getMaxIntChildLimit() + 1) / 2) {

            //transfer key from right sibling through parent
            int maxIdxKey = rightNode->keys.size() - 1;
            cursor->keys.push_back(parent->keys[pos]);
            parent->keys[pos] = rightNode->keys[0];
            rightNode->keys.erase(rightNode->keys.begin());

            //transfer the pointer from rightSibling to cursor
            cursor->ptr2TreeOrData.ptr2Tree
                .push_back(rightNode->ptr2TreeOrData.ptr2Tree[0]);
            cursor->ptr2TreeOrData.ptr2Tree
                .erase(cursor->ptr2TreeOrData.ptr2Tree.begin());

            return res;
        }
    }

    //Start to Merge Now, if None of the above cases applied
    if (leftSibling >= 0) {
        //leftNode + parent key + cursor
        Node* leftNode = parent->ptr2TreeOrData.ptr2Tree[leftSibling];
        leftNode->keys.push_back(parent->keys[leftSibling]);

        for (int val : cursor->keys) {
            leftNode->keys.push_back(val);
        }

        for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++) {
            leftNode->ptr2TreeOrData.ptr2Tree
                .push_back(cursor->ptr2TreeOrData.ptr2Tree[i]);
            cursor->ptr2TreeOrData.ptr2Tree[i] = NULL;
        }

        cursor->ptr2TreeOrData.ptr2Tree.resize(0);
        cursor->keys.resize(0);

        removeInternal(parent->keys[leftSibling], parent, cursor);
        //cout << "Merged with left sibling" << endl;
    }
    else if (rightSibling < parent->ptr2TreeOrData.ptr2Tree.size()) {
        //cursor + parentkey +rightNode
        Node* rightNode = parent->ptr2TreeOrData.ptr2Tree[rightSibling];
        cursor->keys.push_back(parent->keys[rightSibling - 1]);

        for (int val : rightNode->keys) {
            cursor->keys.push_back(val);
        }

        for (int i = 0; i < rightNode->ptr2TreeOrData.ptr2Tree.size(); i++) {
            cursor->ptr2TreeOrData.ptr2Tree
                .push_back(rightNode->ptr2TreeOrData.ptr2Tree[i]);
            rightNode->ptr2TreeOrData.ptr2Tree[i] = NULL;
        }

        rightNode->ptr2TreeOrData.ptr2Tree.resize(0);
        rightNode->keys.resize(0);

        removeInternal(parent->keys[rightSibling - 1], parent, rightNode);
        //cout << "Merged with right sibling\n";
    }
}

//DISPLAY//


string BPTree::display(Node* cursor) {
    /*
        Depth First Display

    if (cursor != NULL) {
        for (int i = 0; i < cursor->keys.size(); i++)
            cout << cursor->keys[i] << " ";
        cout << endl;
        if (cursor->isLeaf != true) {
            for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++)
                display(cursor->ptr2TreeOrData.ptr2Tree[i]);
        }
    }
    */
    string res;
    /*
        Level Order Display
    */
    if (cursor == NULL)
    {
        res="No Data in the Database yet!\n";
        return res;
    }
    queue<Node*> q;
    q.push(cursor);
    if (q.empty())
    {
        res= "No Data in the Database yet!\n";
        return res;
    };
    //cout << "\nHere is your File Structure" << endl;
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            Node* u = q.front(); q.pop();

            //printing keys in self
            for (int val : u->keys)
                res = res + to_string(val) + " ";

            res = res + "|| ";//to seperate next adjacent nodes

            if (u->isLeaf != true) {
                for (Node* v : u->ptr2TreeOrData.ptr2Tree) {
                    q.push(v);
                }
            }
        }
        res = res + "\n";
    };
    return res;
}

