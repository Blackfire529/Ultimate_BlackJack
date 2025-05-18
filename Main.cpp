#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// The object constructor to build a card 
class Card {
public:
    string suit;
    string rank;
    int value;

    Card(string r, string s, int v) : rank(r), suit(s), value(v) {}
};
