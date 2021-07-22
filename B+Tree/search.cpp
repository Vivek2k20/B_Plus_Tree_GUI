#include <iostream>
#include<algorithm>
#include<string>
#include<bits/stdc++.h>
#include "B+ Tree.h"





pair<Node*,int> BPTree::search(int key) {
    if (root == NULL) {
        //cout << "NO Tuples Inserted yet" << endl;
        return make_pair(root,-1);
    } else {
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
            return make_pair(root,-1);
        }
		/*
			We can fetch the data from the disc in main memory using data-ptr
		*/
		return make_pair(cursor,idx);
		
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