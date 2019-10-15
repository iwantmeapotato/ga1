#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "ArgumentManager.h"
using namespace std;

class Player {
public:
  string name, position;
  int number, index;
  Player *next, *prev;
  Player(string name, int number, string position) {
    this->name = name; this->number = number; this->position = position;
    next = 0; prev = 0;
  }

  void print() {
      cout << "[" << index << "]  " <<name << ", " << number << ", " << position << '\n';
  }
};

class Team {
  Player *head, *tail;
public:
  int size;
  Team() {
    head = 0; tail = 0;
  }
  bool isempty() { if (head == 0) return true; return false;}
  void add_beg(Player *temp) {
    if (isempty()) tail = temp;
    temp->next = head;
    head = temp;
  }
  void add_end(Player *temp) {
    if (isempty()) add_beg(temp);
    else {
      tail->next = temp;
      tail = tail->next;
      tail->next = 0;
    }
  }
  void print() {
    Player *temp = head;
    while (temp != nullptr) {
      temp->print();
      cout << '\n';
      temp = temp->next;
    }
  }
  bool sort() {
    if (isempty()) return 0;
    Player *temp = head;
    for (int i = 0; i < size - 1; i++) {
      temp = head;
      for (int j = 0; j < size - 1 - i; j++) {
        if (temp->name.compare(temp->next->name) > 0) {
          swap(temp->name, temp->next->name);
          swap(temp->number, temp->next->number);
          swap(temp->position, temp->next->position);
        }
        temp = temp->next;
      }
    }
    return 1;
    }
  int index() {
    Player *cu = head;
    for (int i = 0; i < size; i++) {
      cu->index = i;
      cu = cu->next;
    }
    return 0;
  }
  int locate(string name) {
    Player *temp = head;
    while(temp != NULL) {
      if (temp->name == name) return temp->index;
      temp = temp->next;
    }
    return -1;
  }
};

int main(int argc, char *argv[]) {
  if (argc < 1 || (argc != 3 && argc != 2)) {
    cout << "Invalid arguments" << endl;
    return 1;
  }
  ArgumentManager am(argc, argv);
  const string in = am.get("input");
  const string command = am.get("command");
  const string out = am.get("output");
  // 
  // string in = "input13.txt"; // local testing
  // string command = "command13.txt";
  // string out = "output.txt";

  ifstream ifs(in);
  ofstream ofs(out);

  Team psg;
  Player *player;
  string line, Fname, Lname, name, position, s_number;
  int number, lines = 0;

  while(!ifs.eof()) {
    getline(ifs, line);
    lines++;
  }
  psg.size = lines;
  ifs.close();
  ifs.open(in);
  for (int i = 0; i < lines; i++) {
    getline(ifs, name, ',');
    getline(ifs, s_number, ',');
    getline(ifs, position);
    stringstream ss_num(s_number);
    ss_num >> number;
    player = new Player(name, number, position);
    psg.add_end(player);
  }
  if (!psg.sort()) { cout << "No players!"; return 0; }
  psg.index();
  ifs.close();

  int requests = 0;
  ifstream ifsCom(command);
  while(!ifsCom.eof()) {
    getline(ifsCom, line);
    if (line.length() > 0) requests++;
  }
  ifsCom.close();
  string *requestList = new string[requests];
  ifsCom.open(command);
  for (int i = 0; i < requests; i++) {
    getline(ifsCom, requestList[i]);
  }
  for (int i = 0; i < requests; i++) {
    cout << requestList[i] << ": " << psg.locate(requestList[i]) << '\n';
    ofs << requestList[i] << ": " << psg.locate(requestList[i]) << '\n';
  }
  ofs.close();

  // cout << string(3, '\n');
  // psg.print();


  return 0;
}
