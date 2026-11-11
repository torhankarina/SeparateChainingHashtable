//***************************************************************************
//
// Karina Torhan
// Z2111032
// CSCI 340 -OPE1 20268
// Assignment 09 Separate Chaining Hashtable
// Due Date: 11/17/26, 5:00 PM
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//***************************************************************************

#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// initialize the hash table with the requested number of buckets
HT::HT(const unsigned &hs) : hsize(hs), hTable(hs) {}

HT::~HT() {
  hTable.clear();
  pTable.clear();
}

void HT::insert(const Entry &e) {
  int i = hash(e.key);
  list<Entry> &bucket = hTable[i];

  auto it = find_if(bucket.begin(), bucket.end(), [&e](const Entry &item) {
    return item.key == e.key;
  });

  if (it != bucket.end()) {
    cout << " not inserted - duplicate key!!!\n";
    return;
  }

  // new records go at the front of their bucket
  bucket.push_front(e);
  pTable.push_back(&bucket.front());
  cout << " entry =  " << i << '\n';
}

void HT::search(const string &s) {
  int i = hash(s);
  list<Entry> &bucket = hTable[i];

  auto it = find_if(bucket.begin(), bucket.end(), [&s](const Entry &item) {
    return item.key == s;
  });

  if (it == bucket.end()) {
    cout << " not in table!!\n";
    return;
  }

  cout << " ==> number: " << right << setw(4) << it->num
       << " - item:" << left << setw(ITEM_SZ) << it->desc
       << right << '\n';
}

void HT::hTable_print() {
  cout << '\n';

  for (unsigned i = 0; i < hsize; ++i) {
    for (const Entry &e : hTable[i]) {
      cout << left << setw(4) << i << ':' << setw(6) << e.key
           << " - " << setw(6) << e.num << " -  "
           << setw(ITEM_SZ) << e.desc << '\n';
    }
  }
}

void HT::pTable_print() {
  // sort pointers without changing the hash table
  sort(pTable.begin(), pTable.end(), [](const Entry *a, const Entry *b) {
    return a->key < b->key;
  });

  for (const Entry *e : pTable) {
    cout << "   " << e->key << "  - " << right << setw(5) << e->num
         << "  -  " << left << setw(ITEM_SZ) << e->desc << '\n';
  }
}