#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class MinHeap {
private:

    vector<T> data;

    // heapifyup
    void heapifyup(int index){

        if(index <= 0){
            return;
        }

        int parent_index = (index-1)/2;

        //if not using standard type will need to overload operator
        if(data[index] < data[parent_index]){
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

        if(left < data.size() && data[index] > data[left]){
            swap(data[index], data[left]);
            heapifydown(left);
        }else if (right < data.size() && data[index] > data[right]){
            swap(data[index], data[left]);
            heapifydown(right);
        }

        return;
    }

public:

    // insert(): inserts element n into heap
    void insert(T n){
        data.push_back(n);
        heapifyup(data.size()-1);
    }

    // poll(): deletes the minimum element of heap
    T poll(){
        T res;
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

};


int main(){

    MinHeap<int> heap;

    // Test 1: Insert elements and check min element
    heap.insert(5);
    heap.insert(3);
    heap.insert(8);
    heap.insert(1);
    heap.insert(4);

    std::cout << "Test 1 - Expected min: 1, Actual min: " << heap.poll() << std::endl;

    // Test 2: Poll elements and check order
    std::cout << "Test 2 - Expected order: 3, 4, 5, 8\n";
    while (true) {
        try {
            std::cout << heap.poll() << " ";
        } catch (const std::runtime_error& e) {
            std::cout << std::endl;
            break;
        }
    }

    // Test 3: Poll from empty heap should throw exception
    try {
        heap.poll();
        std::cout << "Test 3 - Expected exception, but poll() did not throw" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Test 3 - Caught expected exception: " << e.what() << std::endl;
    }

    // Test 4: Insert elements again and check min element
    heap.insert(7);
    heap.insert(2);
    heap.insert(6);

    std::cout << "Test 4 - Expected min: 2, Actual min: " << heap.poll() << std::endl;

    return 0;

    return 0;
}