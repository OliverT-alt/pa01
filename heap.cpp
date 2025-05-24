// heap.cpp
// Olover Tian

#include "heap.h"
#include <iostream>
using std::cout;

// Pushes a value into the heap, then ensures
// the heap is correctly arranged
void Heap::push(int value) {
  data.push_back(value);
  int i = int(data.size()) - 1;
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (data[i] < data[parent]) {
      int tmp = data[i];
      data[i] = data[parent];
      data[parent] = tmp;
      i = parent;
    } else {
      break;
    }
  }
}

// Pops the minimum value off the heap
// (but does not return it), then ensures
// the heap is correctly arranged
void Heap::pop() {
  if (data.empty()) return;
  data[0] = data.back();
  data.pop_back();

  int n = int(data.size());
  int i = 0;
  while (true) {
    int left  = 2*i + 1;
    int right = 2*i + 2;
    int smallest = i;

    if (left < n && data[left] < data[smallest]) {
      smallest = left;
    }
    if (right < n && data[right] < data[smallest]) {
      smallest = right;
    }
    if (smallest == i) break;

    // manual swap
    int tmp = data[i];
    data[i] = data[smallest];
    data[smallest] = tmp;
    i = smallest;
  }
}

// Returns the minimum element in the heap
int Heap::top(){
  if (empty()){
    cout<<"Error: heap is empty"
    return 0;
  }
  return data[0];
}

// Returns true if the heap is empty, false otherwise
bool Heap::empty(){
  return data.empty();
}
    