#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Card {
public:
    string suit;
    string value;

    Card(string s, string v) : suit(s), value(v) {}

    int get_value() const {
        if (value == "Ace") {
            return 11;
        }
        else if (value == "Jack" || value == "Queen" || value == "King") {
            return 10;
        }
        else {
            return stoi(value);
        }
    }
};

class Deck {
public:
    vector<Card> cards;

    Deck() {
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

        for (const auto& suit : suits) {
            for (const auto& value : values) {
                cards.push_back(Card(suit, value));
            }
        }
    }

    void shuffle() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
    }

    Card deal_card() {
        Card top_card = cards.back();
        cards.pop_back();
        return top_card;
    }
};

class Hand {
public:
    vector<Card> cards;

    int calculate_value() {
        int total_value = 0;
        int num_aces = 0;

        for (const auto& card : cards) {
            total_value += card.get_value();
            if (card.value == "Ace") {
                num_aces++;
            }
        }

        while (total_value > 21 && num_aces > 0) {
            total_value -= 10;
            num_aces--;
        }

        return total_value;
    }
};

class Blackjack {
public:
    Deck deck;
    Hand player_hand;
    Hand dealer_hand;

    Blackjack() {
        deck = Deck();
        deck.shuffle();
        player_hand.cards.clear();
        dealer_hand.cards.clear();
    }

    void player_hits() {
        player_hand.cards.push_back(deck.deal_card());
    }

    void dealer_hits() {
        dealer_hand.cards.push_back(deck.deal_card());
    }

    void display_player_hand() {
        cout << "Your hand:" << endl;
        for (const auto& card : player_hand.cards) {
            cout << card.value << " of " << card.suit << endl;
        }
        cout << "Total: " << player_hand.calculate_value() << endl;
        cout << endl;
    }

    void display_dealer_hand() {
        cout << "Dealer's hand:" << endl;
        cout << dealer_hand.cards[0].value << " of " << dealer_hand.cards[0].suit << endl;
        cout << "Hidden card" << endl;
        cout << "Total: " << dealer_hand.cards[0].get_value() << endl;
        cout << endl;
    }

    void play_game() {
        char play_again;
        do {
            deck = Deck();
            deck.shuffle();

            player_hand.cards.clear();
            dealer_hand.cards.clear();

            // Împărțirea cărților pentru un joc nou
            player_hand.cards.push_back(deck.deal_card());
            dealer_hand.cards.push_back(deck.deal_card());
            player_hand.cards.push_back(deck.deal_card());
            dealer_hand.cards.push_back(deck.deal_card());

            cout << "Welcome to Blackjack!" << endl;
            display_player_hand();
            display_dealer_hand();

            char choice;
            cout << "Do you want to hit or stand? (h/s): ";
            cin >> choice;

            while (choice == 'h') {
                player_hits();
                display_player_hand();
                if (player_hand.calculate_value() > 21) {
                    cout << "\nBust! Dealer wins!" << endl;
                    break;
                }
                cout << "Do you want to hit or stand? (h/s): ";
                cin >> choice;
            }

            if (player_hand.calculate_value() <= 21) {
                while (dealer_hand.calculate_value() < 17) {
                    dealer_hits();
                }

                cout << "Dealer's hand:" << endl;
                for (const auto& card : dealer_hand.cards) {
                    cout << card.value << " of " << card.suit << endl;
                }
                cout << "Total: " << dealer_hand.calculate_value() << endl;

                if (dealer_hand.calculate_value() > 21 || dealer_hand.calculate_value() < player_hand.calculate_value()) {
                    cout << "\nPlayer wins!" << endl;
                }
                else if (dealer_hand.calculate_value() > player_hand.calculate_value()) {
                    cout << "\nDealer wins!" << endl;
                }
                else {
                    cout << "\nIt's a tie!" << endl;
                }
            }

            cout << "\nDo you want to play again? (y/n): ";
            cin >> play_again;

        } while (play_again == 'y' || play_again == 'Y');

        cout << "Thank you for playing! Goodbye!" << endl;
    }
};

int main() {
    Blackjack game;
    game.play_game();
    return 0;
}
