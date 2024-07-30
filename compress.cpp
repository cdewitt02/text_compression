#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

//counts frequency of each int and stores into unordered map, references input txt file
unordered_map<char, int> frequency(ifstream& file){

    unordered_map<char, int> freq;

    if (file.is_open()){
        char ch;

        while (file.get(ch)) { 
            freq[ch]++;
        }

        file.close();

    }
    else{
        throw runtime_error("Unable to open file");
    }

    return freq;
}

int main(){

    ifstream file("sample.txt");
    unordered_map<char,int> freq; //contains frequency of each char
    try{
        freq = frequency(file);

        for (auto c : freq){
            cout << c.first << ": " << c.second << endl;
        }
    }catch (const runtime_error& e){
        cout << e.what() << endl;
    }


    return 0;
}