//
//  main.cpp
//  textCounter
//
//  Created by Aj Gill on 10/27/18.
//  Copyright © 2018 Aj Gill. All rights reserved.
//

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>

//For ease of coding for the time being
using namespace std;

struct Paragraph{
    //For every paragraph, create a new map object with char key values and int count values
    map <char, int> charactersMap;
    int wordCount;
    //Function to print out the number of instances of each character
    void printOutAllInstances(){
        for(std::map<char,int>::iterator iter = charactersMap.begin(); iter != charactersMap.end(); ++iter)
        {
            cout << iter->first << ":" << iter->second << "\n";
        }
    }
    void initializeParagraph(){
        map<char, int>::iterator it;
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for(int i=0; i<alphabet.size();i++){
            charactersMap.insert(make_pair(alphabet[i],0));
        }
    }
    void printOutSortedOccurences(){
        map<int, string> occurencesMap;
        for(std::map<char,int>::iterator iter = charactersMap.begin(); iter != charactersMap.end(); ++iter)
        {
            if(occurencesMap.count(iter->second) != 0){
                map<int, string>::iterator itOM;
                //find returns an iterator to the found element
                itOM = occurencesMap.find(iter->second);
                    //Increment the count value
                itOM->second += iter->first;
            }
            else{
                string temp = "";
                temp += iter->first;
                occurencesMap.insert(make_pair(iter->second,temp));
            }
            
        }
        for(std::map<int,string>::iterator thispair = occurencesMap.begin(); thispair != occurencesMap.end(); ++thispair)
        {
            cout << thispair->first << ":" << thispair->second << "\n";
        }
    }
};

int main() {
    int paragraphCount = 0;
    string line;
    ifstream myFile("sample2.txt");
    //Vector holding Paragraph objects
    vector <Paragraph> vecOfParagraphs;
    //Iterate through file line by line which also equates to paragraph by paragraph
    while(getline(myFile, line))
    {
        //If it's just a new line, then string/paragraph is empty, skip
        if(line == ""){
            continue;
        }
        paragraphCount++;
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        Paragraph paragraph;
        paragraph.wordCount=0;
        paragraph.initializeParagraph();
        for(int i=0; i<line.size();i++){
            //For every space there is a new word
            if(line[i] == ' '){
                paragraph.wordCount++;
            }
            //For every period or comma, we must go to the next character
            else if(line[i] == ',' || line[i] == '.'){
                //do nothing
            }
            else{
                //Check if the key exists in the map
                //If it exists, then increment it's count value
                //if(paragraph.charactersMap.count(line[i]) != 0){
                    map<char,int>::iterator it;
                    //find returns an iterator to the found element
                    it = paragraph.charactersMap.find(line[i]);
                    //Increment the count value
                    it->second = it->second + 1;
                //}
                //If it doesn't exist, create a pair with that character and the count value of 1
                // else{
                //     paragraph.charactersMap.insert(make_pair(line[i],1));
                // }
            }
        }
        vecOfParagraphs.push_back(paragraph);
    }
    myFile.close();
    
    
    cout << "Paragraph count is: " << paragraphCount << "\n\n";
    
    for(int j=0; j<vecOfParagraphs.size();++j){
        cout << "Paragraph " << j+1 << ": \n";
        cout << "Word count is: " << vecOfParagraphs[j].wordCount << "\n";
        //vecOfParagraphs[j].printOutAllInstances();
        vecOfParagraphs[j].printOutSortedOccurences();
        cout << "\n";
    }
}
