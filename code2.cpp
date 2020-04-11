 /*
 * karan
 * CS280
 * Fall 2019
 */

#include <iostream>
#include <map>
#include <string.h>
#include <fstream>

using namespace std;


map <int,char> dict1;
map <char,int> dict2;
map <int,char> dict3;
map <char,int> dict4;

void dictionary(){
    for(int i=0; i<26; i++){
        dict1[i] = char(65+i);
    }    
    for(int i=0; i<26; i++){
        dict2[char(65+i)] = i;
    }
    
    for(int i=0; i<26; i++){
        dict3[i] = char(97+i);
    }  
    for(int i=0; i<26; i++){
        dict4[char(97+i)] = i;
    }
    return;
}

string rot13(string message){
    
    string ciphertext = "";
    for(int i=0; i<message.size(); i++){
        if(message[i] != ' '){
            if(isalpha(message[i])){
                if(isupper(message[i])){   
                    int num = (dict2[message[i]] + 13) % 26;
                    ciphertext += dict1[num];
                }else{
                    int num = (dict4[message[i]] + 13) % 26;
                    ciphertext += dict3[num];
                }
            }else{
                ciphertext += message[i];
            }
        }else{
            ciphertext += " ";
        }
    }
    return ciphertext;
}

int main(int argc, char *argv[]){
    
    dictionary();
    if (argc < 2) {
        cout << "MISSING COMMAND" << endl; 
        return -1;
    }
    if(strcmp(argv[1], "-r") && strcmp(argv[1], "-g") && strcmp(argv[1], "-e") && strcmp(argv[1], "-d") ){
        cout<< argv[1] << " NOT A VALID COMMAND" << endl;
        return -1;
    }
    
    if(strcmp(argv[1], "-r") == 0 ){
        if(argc == 2){
            string line;            
            while(getline(cin,line)){
                cout << rot13(line)<<endl;  
            }
        
        }else{
            string line;            
            ifstream infile;
            infile.open(argv[2]);
            if(infile.is_open() == false){
                cout << argv[2] << " FILE COULD NOT BE OPENED" <<endl;
            }else{
                while( getline( infile, line)){
                    cout << rot13(line) + "\n";
                }
            }
            infile.close();
        }
    }
    if(strcmp(argv[1], "-g") == 0){
        
        int pool[26];
        for( int i=0; i<26; i++ ){
            pool[i] = i;
        }        
        int poolsize = 26;
        srand( time(NULL) );
        int value; 
                
        for( int i=0; i<26; i++ ) {
            
            value = rand() % poolsize;
            while(i == pool[value] ){
                value = rand() % poolsize;
            }            
            cout << char('a' + i) << char('a' + pool[value]) << " ";
            pool[value] = pool[poolsize - 1];
            poolsize--;
        }                
    }
    if(strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0 ){
        map <char,char> caesorDict;                   
        ifstream infile;
        if(argc == 2){
            cout << "NO DICTIONARY GIVEN" ; 
            return -1;
        }else{
            string line; 
            string temp;
            infile.open(argv[2]);
            if(infile.is_open() == false){
                cout << argv[2] << " DICTIONARY COULD NOT BE OPENED" <<endl;
            }else{
                while(getline(infile,temp)){
                    line += temp;
                    caesorDict[temp[0]] = temp[1];
                }
                
                string alpha = "abcdefghijklmnopqrstuvwxyz";
                string compare = "";
                
                string temp = "";
                
                for(int i=0; i<line.length(); i++){
                    if(i%2 == 0){
                        compare.append(line,i,1);
                    
                        string part = alpha.substr(0,i/2+1);
                        
                        if(compare != part){
                            cout << "MISSING LETTER " << alpha[i/2] << endl;
                            return -1;
                        }
                    }else{
                        temp.append(line,i,1);
                    }                    
                }                 
                int res = 0;
                int x = 0;
                for(int i=0; i < temp.length(); i++){
                    for(int j=0; j<temp.length(); j++){
                        if(temp[j] == alpha[x]){
                            res++;
                        }
                    }
                    if(res != 1){
                        cout << "DUPLICATE CIPHERTEXT " << alpha[x] <<endl;
                        return -1;
                    }
                    x++;
                    res =0;
                }               
                infile.close();
            }
        }
        if(argc == 4){
            infile.open(argv[3]); 
            if(infile.is_open() == false){
                cout << argv[3] << " FILE COULD NOT BE OPENED" << endl;
                return -1;
            }else{
                string line;
                while(getline(infile,line)){     
                    string cypher = "";
                    for(int i=0; i<line.length(); i++){
                        if(isalpha(line[i])){
                            if(isupper(line[i])){
                                cypher += toupper(caesorDict[tolower(line[i])] ); 
                            }else{
                                cypher += caesorDict[line[i]];
                            }                            
                        }else{
                            cypher += line[i];
                        }                        
                    }
                    cout << cypher << endl;                         
                }                    
            }
            infile.close();            
        }
                
    }
}

        
   
              
               