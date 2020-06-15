#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <pthread.h>
using namespace std;

class letter {
public:
  string data, code;
  int count, order;
  letter *next;
	letter(string data = "E", int order = 0, letter *next = 0) : data(data), count(1), order(order), next(next) {}

  void print() {
    printf("Symbol: %s, Frequency: %d, Code: %s\n", data.c_str(), count, code.c_str());
  } 

  ~letter() {}
};

void swap(letter *high, letter *low) {
  swap(high->count, low->count);
	swap(high->data, low->data);
  swap(high->code, low->code);
  swap(high->order, low->order); 
	  // fake swaps, retain links
  return;
}

class letters {
public:
	letter *head;
  int count;
  letters(letter *head = 0, int count = 0) : head(head), count(count) {}

  void attach(string data) {
    if (head==0) { head = new letter(data, count); count++; return; }
    letter *cu = head;
    while (cu != 0) { 
      if (cu->data == data) { // match found
        cu->count++;
        return;
      }
      if (cu->next == 0) {  //end of list
        cu->next = new letter(data, count);
        count++;
        return;
      }
      cu = cu->next;
    }
  }

  void disp() {
    if (head == 0) { cout << "List empty.\n"; return; }
    letter *cu = head;
    while (cu != 0) {
      cu->print();
      cu = cu->next;
    }
  }

  void sort() { //bubblesort yikes
    letter *cu = head;
    if (cu == 0 || cu->next == 0) return;
    while (cu->next != 0) {
      letter *runner = head;
      while(runner->next != 0) {
        if (runner->count < runner->next->count) {
          swap(runner, runner->next);
        }
        else if (runner->count == runner->next->count) {
          if ((int)runner->data[0] < (int)runner->next->data[0])
            swap(runner,runner->next);
        }
        runner = runner->next;
      }
      cu = cu->next;
    }
  }

  void restore() { // reverse sort
	  letter *cu = head;
	  if (cu == 0 || cu->next == 0) return;
	  while (cu->next != 0) {
		  letter *runner = head;
		  while(runner->next != 0) {
			  if (runner->order > runner->next->order) {
				  swap(runner, runner->next);
			  }
			  runner = runner->next;
		  }
		  cu = cu->next;
	  }
  }


  ~letters() {}
};
