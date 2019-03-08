
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, const char * argv[]) {
    
    map<string, string> substitutions;
    ifstream subs;
    ifstream words;
    
    subs.open(argv[1]);
    words.open(argv[2]);
    
    //NO SUBSTITUIONS FILE
    if( subs.is_open() == false ) {
        cout<< argv[1] <<"BAD FILENAME thisIsNotValid"<<endl;
        subs.close();
        return -1;
    }
    
    //NO ARGS
    if(argc < 2){
        cout<< "TWO FILENAMES REQUIRED" <<endl;
        return 0;
    }
    
    
    //TOO FEW ARGS
    if(argc < 3){
        cout<< "TWO FILENAMES REQUIRED" <<endl;
        return 0;
    }
    
    //TOO MANY ARGS
    if(argc > 3){
        cout<< "TWO FILENAMES REQUIRED" <<endl;
        return 0;
    }
    
    subs.open(argv[1]);
    words.open(argv[2]);
    
    //NO SUBSTITUIONS FILE
    if( subs.is_open() == false ) {
        cout<< "BAD FILENAME thisIsNotValid"<<endl;
        subs.close();
        return -1;
    }
    
    //NO WORDS FILE
    if(words.is_open() == false){
        cout<< "BAD FILENAME thisIsNotValid"<<endl;
        words.close();
        return -1;
    }
    
    //PROCESSING SUBS FILE
    string key;
    string value;
    string j;
    char k;
    int wordCount = 0;
    while(subs.get(k)){
        if(!isspace(k)){
            if(isalpha(k)){
                j+= tolower(k);
            }
            if(ispunct(k)){
                if(j.length() != 0){
                    if( isalpha(subs.peek()) ){
                        j+=k;
                    }
                }
            }
        }else{
            if(j.length() != 0){
                wordCount++;
                if(wordCount == 1){
                    key = j;
                }
                if(wordCount == 2){
                    value = j;
                } 
                if(k == '\n' ){
                    if(wordCount == 2){
                        map<string, string>:: iterator subItr;
                        subItr = substitutions.find(key);
                        if(subItr != substitutions.end()){//if found: replace
                            substitutions.insert(pair<string, string>(key,value));
                        }else{
                            cout<<"key: '" << key << "' value: '" << value << "'" <<endl;
                            substitutions.insert(pair<string, string>(key,value));
                        }
                    }
                     wordCount = 0;  
                }
                
                j = "";
            }
            
            
        }
    }
    
    //PRINTING WORDS FILE
    int numChanges = 0;
    bool cap;
    string front;
    string middle;
    string capMiddle;
    string back;
    string s;
    char w; 
    
    while(words.get(w)){
        if(!isspace(w)){
            if(middle.length() == 0){
                if(ispunct(w)){
                    front+=w;
                }
                if(isalpha(w)){
                    if(isupper(w)){
                        cap = true;    
                    }else{
                        cap = false;
                    }
                    middle+= w;
                }
            }else{
                if(ispunct(w)){
                    if(isalpha(words.peek())){
                        middle+= w;
                    }else{
                       back+=w; 
                    }
                }else{
                    middle+=w;
                }
            }
        }else{
            
            string temp;
            for(int i = 0; i<middle.length(); i++){
                temp+=tolower(middle[i]);
            }
            
            map<string, string>:: iterator wordItr;
            wordItr = substitutions.find(temp);
            
            
            if(wordItr != substitutions.end()){
                numChanges++;
                middle = substitutions.at(temp);
                
                if(cap){ 
                    for(int i=0; i<middle.length(); i++){
                        if(i==0){
                            capMiddle+=toupper(middle[i]);
                        }else{
                            capMiddle+=middle[i];   
                        }
                    }
                    middle = capMiddle;
                }
            }
            
            s+= front+=middle+=back+=w;
            
            cout<< s;
            front = "";
            middle = "";
            capMiddle = "";
            back = "";
            s = "";
        }
    }
    if(numChanges > 0){
        cout<< "NUMBER OF CHANGES: "<<numChanges<<endl;
    }
    
    return 0;
}