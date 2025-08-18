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

    Card(string r, string s, int v) : suit(s), rank(r), value(v) {}
};

//The object constructor to build the entire deck
class Deck {
public:
    vector<Card> cards; //the array to hold the deck of cards

    // a function to build a card and the add it to the deck until all 52 are made
    Deck() {
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11}; // Ace is 11

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards.push_back(Card(ranks[j], suits[i], values[j]));
            }
        }
        shuffle();
    }

    //a function to mix the order of the cards in the deck 
    void shuffle() {
        srand(time(0));
        for (int i = 0; i < cards.size(); i++) { // a for loop that loops as many time as the cards array is big
            int r = rand() % cards.size();       // 'r' is = to a random number modulus the cards array size
            swap(cards[i], cards[r]);            // swaps the index of cards[current loop value] and cards[new random number]
        }
    }

    //a function to get the top card after its been shuffle and place that into a Player's hand
    Card deal() {
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }
};

class Player {
public:
    vector<Card> hand;
    int score;

    Player() : score(0) {}

    void addCard(Card card) {
        hand.push_back(card);
        score += card.value;
        if (score > 21) {
            for (auto c : hand) {
                if (c.rank == "Ace" && c.value == 11) {
                    c.value = 1; // Change Ace from 11 to 1
                    score -= 10;
                    break;
                }
            }
        }
    }

    void showHand() {
        for (auto card : hand) {
            cout << card.rank << " of " << card.suit << endl;
        }
        cout << "Score: " << score << endl;
    }
};

int main() {
    Deck deck;
    Player player, dealer;

    // the first card dealings
    player.addCard(deck.deal());
    player.addCard(deck.deal());
    
    dealer.addCard(deck.deal());
    dealer.addCard(deck.deal());

    cout << "Your hand:" << endl;
    player.showHand();
    cout << "\nDealer's hand:" << endl;
    cout << dealer.hand[0].rank << " of " << dealer.hand[0].suit << endl; // Show one dealer card

    // Player's turn
    char choice;
    do {
        cout << "Do you want to hit (h) or stand (s)? ";
        cin >> choice;
        if (choice == 'h') {
            player.addCard(deck.deal());
            cout << "Your hand:" << endl;
            player.showHand();
            if (player.score > 21) {
                cout << "You bust! Dealer wins." << endl;
                return 0;
            }
        }
    } while (choice != 's');

    // Dealer's turn
    cout << "\nDealer's turn:" << endl;
    while (dealer.score < 17) {
        dealer.addCard(deck.deal());
    }
    dealer.showHand();

    // Determine winner
    if (dealer.score > 21 || player.score > dealer.score) {
        cout << "You win!" << endl;
    } else if (player.score < dealer.score) {
        cout << "Dealer wins!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
