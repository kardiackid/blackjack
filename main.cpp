include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

struct Card {       //Declares struct with members that will hold point value, suit, and card rank
    string value;
    string suit;
    int point;
};

struct Blackjack {      //Declares struct with members that will hold values related to the player and dealer hands as well as the deck.
    int dealertotal,
        playertotal,    //Total is to hold the sum of the player and dealers hands.
        position;       //Position is to hold hold the position in a deck as it is incremented through dealing cards and summing the hands.
    bool stand;         //Stand is a boolean to determine if the player or dealer has stopped drawing cards.
};

const int valueSize = 13, //Int corresponding to the number of ranks in a single deck of cards.
          suitSize = 4,   //Int corresponding to the number of suits in a deck of cards.
          numDecks = 6,   //Int that determines how many decks will be created.
          deckMax = 312,  //Determines the number of elements that the deck array will be able to hold.
          handSize = 11;  //Max number of elements allowed in the player and dealer hand arrays.

string values[valueSize] = {"Ace", "2", "3", "4","5", "6", "7","8","9", "10", "Jack", "Queen", "King" },    //array of strings holding card ranks to be passed to an array of structures when creating the decks.
       suits[suitSize] = {"Diamonds","Hearts","Spades","Clubs"};                                            //array of strings holding card suits also to be passed to an array of structures when creating the decks.

int points[valueSize] = {11,2,3,4,5,6,7,8,9,10,10,10,10};                                                   //array of ints holding points values for cards.

Card deck[deckMax], playerHand[handSize], dealerHand[handSize]; //Declaring arrays that will structure members from the Card struct. One for the deck, players hand, and dealers hand with corresponding sizes
Blackjack dealer, player, shoe;                                 //Declaring Blackjack structure for the dealer, player, and deck/shoe

void createDeck();
void shuffleDeck();
void printDeck();
void dealDealerCard();
void dealPlayerCard();
void showDealerHand();
void showPlayerHand();
void game();

int main ()
{
    int gameOver = 1;

    do
    {
        game();
        {
            cout << "\nWould you like to continue? Press: 1 for Yes, Press: 2 for No: ";
            cin >> gameOver;
            cout << "\n\n";
            while(gameOver != 1 && gameOver != 2)
            {
                cout << "\n!!Not a valid menu option!! Please enter a valid number: ";
                cin >> gameOver;
            }
        }
    }while (gameOver == 1);


}

void createDeck()
{
    int k = 0;
    int p;

    for(p = 0; p < numDecks; p++)
    {
        for(int i = 0; i < valueSize; i++)
        {
            for(int j = 0; j < suitSize; j++)
            {
                deck[k].value = values[i];
                deck[k].suit = suits[j];
                deck[k].point = points[i];
                k++;
            }
        }
    }
}

void shuffleDeck()
{
    srand(time(0));

    for(int counter = 0; counter < deckMax; counter++)
    {
        int r = rand() % deckMax;
        Card temp = deck[counter];
        deck[counter] = deck[r];
        deck[r] = temp;
    }
}

void printDeck()
{
    for (int x = 0; x < deckMax; x++)
    {
        cout << deck[x].value << " of " << deck[x].suit << " Point Value: " << deck[x].point << endl;
    }
}

void dealDealerCard()
{
    dealerHand[dealer.position] = deck[shoe.position];
    shoe.position++;
    dealer.position++;
}

void dealPlayerCard()
{
    playerHand[player.position] = deck[shoe.position];
    shoe.position++;
    player.position++;
}

void showDealerHand()
{
    int c;
    dealer.dealertotal = 0;
    cout << "\nDealer Hand: ";

    for(c = 0; c < dealer.position; c++)
    {
        dealer.dealertotal += dealerHand[c].point;
        cout << dealerHand[c].value << " of " << dealerHand[c].suit << " ** ";
    }
    cout << "Total: " << dealer.dealertotal << " \n";
}

void showPlayerHand()
{
    int b;
    player.playertotal = 0;
    cout << "\nPlayer Hand: ";

    for(b = 0; b < player.position; b++)
    {
        player.playertotal += playerHand[b].point;
        cout << playerHand[b].value << " of " << playerHand[b].suit <<  " ** ";
    }
    cout << "Total: " << player.playertotal << " \n";
}

void game()
{
    int option = 0, hit = 0;
    player.stand = false;
    dealer.stand = false;
    shoe.position = 0;
    player.position = 0;
    dealer.position = 0;

    cout << "**Welcome to Kardiac Kid Casino's Game of Black Jack!!**\n";
    cout << "          Please choose and option below\n";
    cout << "          --->For game rules press: 1\n";
    cout << "          --->To start a game press: 2\n";
    cout << "          --->To leave press: 3\n";
    cout << "          Enter your choice: ";
    cin >> option;

    while(option != 1 && option != 2 && option != 3)
        {
            cout << "\n!!Not a valid menu option!! Please enter a valid number: ";
            cin >> option;
        }

    if (option == 1)
    {
        cout << "\nThe rules of BlackJack are as follows: \n";
        cout << "1. Each participant attempts to beat the dealer by getting a total as close to 21 as possible, without going over 21.\n\n";
        cout << "2. It is up to each individual player if an ace is worth 1 or 11. Face cards are 10 and any other card is worth its numerical value.\n\n";
        cout << "3. The dealer gives one card face up to each player in rotation clockwise, and then one card face up to himself.\n";
        cout << "   Another round of cards is then dealt face up to each player, but the dealer takes his second card face down.\n\n";
        cout << "4. Each player, in the same clockwise rotation, will be given the option to Stand(not take any additional cards),\n";
        cout << "   or to Hit(take additional cards to improve total). At any point the player chooses to stand the turn passes to the next player.\n\n";
        cout << "5. When the dealer has served every player, his face-down card is turned up. If the total is 17 or more, he must stand.\n";
        cout << "   If the total is 16 or under, he must take a card. He must continue to take cards until the total is 17 or more,\n";
        cout << "   at which point the dealer must stand. If the dealer has an ace, and counting it as 11 would bring his total to 17 or more (but not over 21),\n";
        cout << "   he must count the ace as 11 and stand. The dealer's decisions, then, are automatic on all plays, whereas the player always has the option of taking one or more cards.\n\n";
        cout << "6. If a player total is greater than the dealer without going over 21 they win. If the dealer's total is higher the house wins.\n";
    }
    else if(option == 2)
    {
        cout << "\nLets begin!!\n";
        createDeck();
        shuffleDeck();
//        shoe.position = 0;
//        player.position = 0;
//        dealer.position = 0;


        dealDealerCard();
        dealPlayerCard();
        dealDealerCard();
        dealPlayerCard();
        showPlayerHand();
        showDealerHand();

        if(dealer.dealertotal == 21)
        {
            cout << "\nBlackjack!! Dealer wins!!\n";
            return;
        }
        else if(player.playertotal == 21)
        {
            cout << "\nBlackjack!! Player Wins!!\n";
            return;
        }
        while(dealer.stand == false || player.stand == false)
        {
            if(player.stand == false)
            {
                cout << "\nPlayer, would you like to hit? Press: 1 for Yes, Press: 2 for No: ";
                cin >> hit;

                if (hit == 1)
                {
                    dealPlayerCard();
                    showPlayerHand();

                    if(player.playertotal > 21)
                    {
                        cout << "\nBust!! Player loses!!\n";
                        return;
                    }
                }

                if(hit == 2)
                {
                    cout << "\nPlayer stands.\n";
                    player.stand = true;
                }
            }
            if(dealer.dealertotal < 17 && player.stand == true)
            {
                dealDealerCard();
                showDealerHand();

                if (dealer.dealertotal > 21)
                {
                    cout << "\nBust!! Dealer Loses.\n";
                    return;
                }
            }
            else if(dealer.dealertotal >= 17)
            {
                dealer.stand = true;
            }
            if(player.playertotal == 21 && dealer.dealertotal == 21)
            {
                cout << "Push, both the player and the dealer reached 21. No Winner :(\n";
                return;
            }
            else if(player.playertotal == 21)
            {
                cout << "\nBlackjack!! Player Wins!!\n";
                return;
            }
            else if(dealer.dealertotal == 21)
            {
                cout << "\nBlackjack!! Dealer Wins!!\n";
                return;
            }
            if(player.stand == true && dealer.stand == true)
            {
                if(dealer.dealertotal < player.playertotal)
                {
                    cout << "\nPlayer Wins!!\n";
                    return;
                }
                else if (player.playertotal == dealer.dealertotal)
                {
                    cout << "\nTie!!\n";
                    return;
                }
                else if (dealer.dealertotal > player.playertotal)
                {
                    cout << "\nDealer Wins!!\n";shoe.position = 0;
        player.position = 0;
        dealer.position = 0;
                    return;
                }
            }
        }
    }
    else if(option == 3)
    {
        return;
    }
}
