#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <tuple>

using namespace std;

struct MinHeapNode{

    int freq;
    char character;

    MinHeapNode* left;
    MinHeapNode* right;

};

class MinHeap {
private:

    vector<MinHeapNode> data;

    // heapifyup
    void heapifyup(int index){

        if(index <= 0){
            return;
        }

        int parent_index = (index-1)/2;

        if(data[index].freq < data[parent_index].freq){
            swap(data[index], data[parent_index]);
            heapifyup(parent_index);
        }else{
            return;
        }

    }
    // heapifydown
    void heapifydown(int index){
        int left = 2*index+1;
        int right = 2*index+2;

        if(left < data.size() && data[index].freq > data[left].freq){
            swap(data[index], data[left]);
            heapifydown(left);
        }else if (right < data.size() && data[index].freq > data[right].freq){
            swap(data[index], data[left]);
            heapifydown(right);
        }

        return;
    }

public:

    MinHeapNode peek(){
        return data[0];
    }

    // insert(): inserts element n into heap
    void insert(MinHeapNode n){
        data.push_back(n);
        heapifyup(data.size()-1);
    }

    // poll(): deletes the minimum element of heap
    MinHeapNode poll(){
        MinHeapNode res;
        if(data.size() == 0){
            throw runtime_error("Tried to poll empty heap");
        } 
        else{
            res = data[0];
            data[0] = data.back();
            data.pop_back();
            heapifydown(0);
        }

        return res;
    }

    bool isSizeOne(){
        return data.size() == 1;
    }

};


MinHeap buildHuffmanTree(MinHeap minHeap){
    MinHeap huffTree;
    while(!minHeap.isSizeOne()){

        MinHeapNode inner_node;

        MinHeapNode left = minHeap.poll();
        MinHeapNode right = minHeap.poll();

        inner_node.character = '\0';
        inner_node.freq = left.freq + right.freq;


        inner_node.left = new MinHeapNode(left);  
        inner_node.right = new MinHeapNode(right); 

        minHeap.insert(inner_node);

    }

    huffTree.insert(minHeap.poll());


    return huffTree;
}

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
string getArr(const vector<int>& arr, int n) {
    string s = "";
    for (int i = 0; i < n; ++i)
        s += to_string(arr[i]);
    return s;
}

void get_codes(MinHeapNode* root, vector<int>& arr, int top, unordered_map<char, string>& map) {
    if (root->left) { 
        if (top < arr.size()) {
            arr[top] = 0;
        } else {
            arr.push_back(0);
        }
        get_codes(root->left, arr, top + 1, map); 
    }    
  
    if (root->right) { 
        if (top < arr.size()) {
            arr[top] = 1;
        } else {
            arr.push_back(1);
        }
        get_codes(root->right, arr, top + 1, map); 
    }

    if (root->character != '\0') {
        map[root->character] = getArr(arr, top);
    }
}

unordered_map<char, string> get_codes_wrapper(MinHeapNode* root) {
    unordered_map<char, string> map;
    vector<int> arr;
    get_codes(root, arr, 0, map);
    return map;
}

bool isLeaf(MinHeapNode n){
    return (n.character != '\0');
}

void encode(string input_file, unordered_map<char, string> huffmanCode){

    string output, input;

    ifstream inFile(input_file);
    ofstream outFile("outfile.txt");

    string encodedString;
    char ch;
    while (inFile.get(ch)) {
        encodedString += huffmanCode[ch];
    }

    outFile << encodedString;

    inFile.close();
    outFile.close();




}
void decode(MinHeapNode* root){

    string line;

    ifstream inFile("outfile.txt");

    string encodedString;
    getline(inFile, encodedString);

    string decoded_str = "";
    MinHeapNode* current = root;
    for(char bit : encodedString){
       
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (current->character != '\0') {
            decoded_str += current->character;
            current = root;
        }
    }
    ofstream outFile ("decoded.txt");

    outFile<<decoded_str;
}



int main(int argc, char* argv[]){
    string filename = "sample.txt";

    ifstream file(filename);

    unordered_map<char,int> freq; //contains frequency of each char

    try{
        freq = frequency(file);

        for (auto c : freq){
            cout << c.first << ": " << c.second << endl;
        }
    }catch (const runtime_error& e){
        cout << e.what() << endl;
    }

    MinHeap minHeap;

    for (auto n : freq){

        MinHeapNode minHeapNode;

        minHeapNode.freq = n.second;
        minHeapNode.character = n.first;

        minHeap.insert(minHeapNode);
    }

    MinHeap huffmanTree = buildHuffmanTree(minHeap);

    MinHeapNode node = huffmanTree.poll();

    int arr[100], top = 0; 

    unordered_map<char, string> map;

    map = get_codes_wrapper(&node);

    encode("sample.txt", map);
    decode(&node);

    return 0;
}