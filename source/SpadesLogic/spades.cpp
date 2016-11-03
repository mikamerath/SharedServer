#include"card.cpp"
#include"game.hpp"
#include"player.hpp"
#include<random>
#include<algorithm>
#include<vector>
//#include<unistd.h>

class Spades :public Game{
	public: 
		void initializeDeck();
		void deal(int);
		void printPlayerHands();
		void start();
		void getBids();
		void beginRound(int);
		void startTrick();
		bool validMove(std::vector<Card>, int, Suit&, int);
		void getTrickWinner(std::vector<Card>, int&);
		int getNextPlayer(int);
		void score();
		void recordMove(std::vector<Card>);
		Spades(std::vector<Player>);
		~Spades(){}
	private:
		int starter;
		bool spadesBroken;
};

int Spades::getNextPlayer(int plId){
	if(plId == 3){
		return 0;
	}
	else {
		return ++plId;
	}
}

int next(int plId){
	if(plId == 3){
		return 0;
	}
	else {
		return ++plId;
	}
}

void printBoard(std::vector<Card> trick, std::vector<Card> hand, int turn){
 int posZero = turn;
 int posOne = next(turn);
 int posTwo = next(posOne);
 int posThree = next(posTwo);
 std::cout << "..........................................Player "<< posTwo << "...........................\n";
 std::cout << ".............................................................................\n";
 std::cout << ".Player "<< posOne << "....................................................................\n";
 std::cout << ".............................................................................\n";
 std::cout << ".............................................................................\n";
  for(auto c : trick){
 	c.tableprint();
  }
 std::cout << ".............................................................................\n";
 std::cout << ".............................................................................\n";
 std::cout << "....................................................................player "<<posThree<< ".\n";
 std::cout << ".............................................................................\n";
 std::cout << "..................Player "<< turn << "...................................................\n";
 if(trick.size() == 4){
	//sleep(3);
 }
}

Spades::Spades(std::vector<Player> p){
	players = p;
	start();
}

void Spades::getBids(){
	for(auto&& p : players){
		p.setBid(p.requestBid()); // could we just have requestBid update the players' bid and then have a getter?
	}
}

void Spades::recordMove(std::vector<Card> m){
	//essentially update field, then setup and send message to clients.
	m.at(0).print();
}

void Spades::getTrickWinner(std::vector<Card> trick, int& tw){



//holy hell it cannot possibly be as difficult as it feels to determine the winner of this thing.
	auto prevTw = tw;
	auto currentPlayer = tw;
	auto winningCard = trick.at(0);
	for(int i = 1; i < 4; i++){
		currentPlayer = getNextPlayer(currentPlayer);//look at next player
		if(trick.at(i).getSuit() == winningCard.getSuit()){//same suit? 
			if(trick.at(i).getValue() > winningCard.getValue()){//compare value
				winningCard = trick.at(i);//replace if greater value
				tw = currentPlayer;
			}
		}
		else if(trick.at(i).getSuit() == SPADES){
			if(winningCard.getSuit() == SPADES){
				if(trick.at(i).getValue() > winningCard.getValue()){
					winningCard = trick.at(i);
					tw = currentPlayer;
				}
			}
			else{
				winningCard = trick.at(i);
				tw = currentPlayer;
			}
		}
	}
}

bool Spades::validMove(std::vector<Card> tr, int pl, Suit &ls, int currentTurn){ //I'd like this to make sure of two things, one: validity of the move, and two: the winner of the trick(thus far).
	auto h = players.at(pl).getHand();
	if (tr.at(0).getSuit() == tr.back().getSuit() && tr.at(0).getValue() == tr.back().getValue()){ // If this is the first card played in the trick
		tr.at(0).print();
		std::cout << " equals ";
		tr.back().print();
		if (tr.back().getSuit() == SPADES){ //If it's spades, spades has to be broken first 
			if (spadesBroken == true){
				ls = SPADES;
				return true;
			}
			else{ //If spades isn't broken, you can only play spades if that is all you have. (For the first move.)
				for (auto c : h){
					if (c.getSuit() != SPADES){
						return false;
					}
				}
			}
		}
		else{ //It is the first move, and the lead suit is not spades
			ls = (Suit)tr.back().getSuit();
			tr.back().print();
			std::cout << "was led." << std::endl;
		}
	}
	if (tr.back().getSuit() == ls){
		return true;
	}
	//first thing, check the hand, if the player has any card of lead suit, he can't make the move he is trying to.
	for (auto c : h){
		if (c.getSuit() == ls){
			return false;
		}
	}
	//at this point, two things are true, the card played was NOT of the suit led, and the player does NOT have any cards of the led suit.
	if (tr.back().getSuit() == SPADES){
		spadesBroken = true;
	}
	return true;
}

void Spades::score(){
	for(auto p : players){
		auto bid = p.getBid();
		auto tricks = p.getTricksWon();
		auto bag = p.getBags();
		if(bid == tricks){
			p.setScore(bid * 10);
		}
		else if(bid < tricks){
			int sc = bid * 10;
			for(bid; bid < tricks; bid++){
				sc++;
			}
			p.setScore(sc);
		}
		else if(bid > tricks){
			p.setScore(0);
		}
		std::cout << "p.getId() + p.getScore() " << p.getId() << ":" << p.getScore() << std::endl;
	}
}

void Spades::beginRound(int starter){//a more accurate title might be "playRound()" the round logic is this function
	Suit ledSuit = HEARTS;
	//player 0 starts the round
	std::vector<Card> trick;
	int trickWinner = 0;
	int turn = 0;
	while(s == PLAYING){
		//s = ROUND_OVER;
		
		for(int i = 0; i < 4; i++){
			
			trick.push_back(players.at(turn).requestMove().at(0));
			if(validMove(trick, turn, ledSuit, i)){
				std::vector<Card> m;
				m.push_back(trick.at(i));
			}
			else{
				bool vm = false;
				while(vm == false){
				std::cout << "Invalid Move!!!" << std::endl;
				std::cout << std::endl;
				//std::cout << "Trick: " << std::endl;
				auto sendBack = trick.back();
				trick.pop_back();
				//for(auto c : trick){
				//	c.print();
				//}
				players.at(turn).giveCard(sendBack);
				trick.push_back(players.at(turn).requestMove().at(0));
				vm = validMove(trick, turn, ledSuit, i);
				if(vm && i == 0){ledSuit = (Suit)trick.at(0).getSuit();}
				}
				
			//severe connection to client (you don't want to play with them anyway).
			}
			turn = getNextPlayer(turn);
			if(players.at(turn).getHand().empty()){
				s = ROUND_OVER;
			}
			printBoard(trick, players.at(turn).getHand(), turn);
			std::cout << std::endl;
			//std::cout << "Trick: " << std::endl;
			//for(auto c : trick){
			//	c.print();
			//}
		}
		getTrickWinner(trick, trickWinner);
		std::cout << "Player " << trickWinner << " won the trick." << std::endl;
		players.at(trickWinner).augTricksWon();
		std::cout << players.at(trickWinner).getId() << " has won " << players.at(trickWinner).getTricksWon() << " tricks." << std::endl;
		trick.clear();
		turn = trickWinner;
	}
	score();
	//initializeDeck();
	deal(52);
	s = BIDDING;
	getBids();
	s = PLAYING;
	spadesBroken = false;
	beginRound(getNextPlayer(starter));
	
	
	/*std::vector<Player> temp;//my goal with this loop is to reorder the players correctly.
	for(int j = 0; j < 4;j++){ 
		temp.push_back(players.at(i));
				i++;
				i%=4;
	}
	players = temp;
	while(s == PLAYING){//dependant on the state of the game.
		for(auto&& p: players){
			if(p.getHand().empty() == true){//request move will have to use pop_back();
				s = ROUND_OVER;
				return;
			}
			else{
				std::vector<Card> validMoves;
				auto&& h = p.getHand();
				for(auto&& c : h){
					if(c.suit == ledSuit){
						validMoves.push_back(c);
					}
				}
				auto move = p.requestMove();	
				if(validMoves.empty()){
					recordMove(move);
				}
				else{
					while(move.at(0).suit != ledSuit){
						std::vector<Card> v = p.getHand();
						v.push_back(move.at(0));
						p.setHand(v);
						move = p.requestMove();
					}
					recordMove(move);
				}
			}
		}
	}*/
}

void Spades::start(){
	initializeDeck();
	deal(52);
	starter = 0;
	s = BIDDING;
	getBids();
	s = PLAYING;
	spadesBroken = false;
	beginRound(0);
}

void Spades::initializeDeck(){
	for(int i = 0; i < 4; i++){
		for(int j = 1; j < 14; j++){
			if(i == 0){
				Card c(HEARTS, j);
				Spades::deck.push_back(c);
			}
			else if(i == 1){
				Card c(SPADES, j);
				Spades::deck.push_back(c);
			}
			else if(i == 2){
				Card c(CLUBS, j);
				Spades::deck.push_back(c);
			}
			else if(i == 3){
				Card c(DIAMONDS, j);
				Spades::deck.push_back(c);
			}
		}
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(Spades::deck.begin(), Spades::deck.end(),g);
}

void Spades::printPlayerHands(){
	if(players.empty()){
		//done
	}
	else{
		for(auto&& p: players){
			auto&& h = p.getHand();
			std::cout << "Player" << std::endl;
			for(auto && c : h){
				c.print();
			}
		}
	}
	
}

void Spades::deal(int fifty_two){
	if(players.empty() == true){
		for(int k = 0; k < 4; k++){
			Player p = Player("127.0.0.1", k);
			players.push_back(p);//in a perfect world, this will never happen.
		}
	}
	std::vector<Card> one;
	std::vector<Card> two;
	std::vector<Card> three;
	std::vector<Card> four;
	int i = 0;
	for(auto&& c : deck){
		if(i == 0){
			one.push_back(c);
		}
		else if(i == 1){
			two.push_back(c);
		}
		else if(i == 2){
			three.push_back(c);
		}
		else if(i == 3){
			four.push_back(c);
		}
		i++;
		i %= 4;
	}

	for(int j = 0; j < 4; j++){
		if(j == 0){
			players.at(j).setHand(one);
		}
		else if(j == 1){
			players.at(j).setHand(two);
		}
		else if(j == 2){
			players.at(j).setHand(three);
		}
		else if(j == 3){
			players.at(j).setHand(four);
		}
	}

	//construct and send some kind of an update message to all clients at this point
}

int main(){
	Player one("192.168.0.1", 0);
	Player two("192.168.0.2", 1);
	Player three("192.168.0.3", 2);
	Player four("192.168.0.4", 3);
	std::vector<Player> p;
	p.push_back(one);
	p.push_back(two);
	p.push_back(three);
	p.push_back(four);
	Spades mySpades(p);
	return 0;
}
