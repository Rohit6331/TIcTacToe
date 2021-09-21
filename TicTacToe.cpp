#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <limits>

class TicTacToe {
	int finish ;
	int DIM ;
	int vec[3][3] = {} ;
	int remainingcells ;
	
	struct Move {
		int x = 0 ;
		int y = 0 ;
 	} ;
	
	// Input Pattern for Human understanding :)
	void dispayinfo() {
		std::cout << "\nChoose the position from below....\n" ;
		int t = 0 ;
		for(int i=0; i<3; i++) {
			std::cout << "-------------\n" ;
			std::cout << "|" ;

			for(int j=0; j<3; j++) {
				std::cout << " " << t++ << " |" ;
			}
			
			std::cout << "\n" ;
		}
		
		std::cout << "-------------\n" ;
	}
	
	// to print the Tic Tac Toe board 
	void printgrid() {
		
		for(int i=0; i<3; i++) {
			std::cout << "-------------\n" ;
			std::cout << "|" ;

			for(int j=0; j<3; j++) {
				if(vec[i][j] == 0) std::cout << "   " << "|" ;
				else if(vec[i][j] == 1) std::cout << " X " << "|" ;
				else std::cout << " O " << "|" ;
			}
			
			std::cout << "\n" ;
		}
		
		std::cout << "-------------\n" ;
	}
	
	// to get the x and y coordinates of the cell
	void xy(int& i, int& j, int n) {
		i = n/3 , j = n%3 ;
	}
	
	// Check for winner
	void check() {
		
		// For rows
		for(int i=0; i<3; i++) {
			bool flag = true ;
			int count = 0 ;
			int val = vec[i][0] ;
			for(int j=0; j<DIM; j++) {
				if(vec[i][j] == 0 || val != vec[i][j]) flag = false ;
				else count += vec[i][j] ;
			}
			
			if(flag) {
				finish = count/3 ;
				return ;
			}
		}
		
		// For columns
		for(int j=0; j<3; j++) {
			bool flag = true ;
			int count = 0 ;
			int val = vec[0][j] ;
			for(int i=0; i<DIM; i++) {
				if(vec[i][j] == 0 || val != vec[i][j]) flag = false ;
				else count += vec[i][j] ;
			}
			
			if(flag) {
				finish = count/3 ;
				return ;
			}
		}
		
		// For diagonals
		bool flag = true ;
		int count = 0 ;
		int val = vec[0][0] ;
		for(int i=0; i<DIM; i++) {
			if(vec[i][i] == 0 || vec[i][i] != val) flag = false ;
			else count += vec[i][i] ;
		}
		
		if(flag) {
			finish = count/3 ;
			return ;
		}
		
		flag = true ;
		count = 0 ;
		val = vec[0][2] ;
		for(int i=0; i<DIM; i++) {
			if(vec[i][DIM-1-i] == 0 || vec[i][2-i] != val) flag = false ;
			else count += vec[i][DIM-1-i] ;
		}
		
		if(flag) {
			finish = count/3 ;
			return ;
		}
		
		// Check for draw
		if(remainingcells == 0) {
			finish = 0 ;
			return ;
		}
	}
	
	// FUNCTIONS FOR AI MOVE GENERATOR
	
	Move minimax() {
		int score = std::numeric_limits<int>::max() ;
		Move move ;
		int level = 0 ;
		
		for(int i=0; i<DIM; i++) {
			for(int j=0; j<DIM; j++) {
				if(vec[i][j] == 0) {
					vec[i][j] = 2 ;
					remainingcells-- ;
					
					int temp = maxSearch(level, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) ;
					
					if(temp < score) {
						score = temp ;
						move.x = i ;
						move.y = j ;
					}
					
					vec[i][j] = 0 ;
					remainingcells++ ;
				}
			}
		}
		
		return move ;
	}
	
	int maxSearch(int level, int alpha, int beta) {
		check() ;
		if(finish == 1) {
			finish = -1 ;
			return 10 ;
		}
		else if(finish == 2) {
			finish = -1 ;
			return -10 ; 
		}
		else if(finish == 0) {
			finish = -1 ;
			return 0 ;
		}
		
		int score = std::numeric_limits<int>:: min() ;
		
		for(int i=0; i<DIM; i++) {
			for(int j=0; j<DIM; j++) {
				if(vec[i][j] == 0) {
					vec[i][j] = 1 ;
					remainingcells-- ;
					
					score = std::max(score, minSearch(level+1, alpha, beta)-level) ;
					alpha = std::max(alpha, score) ;
					
					vec[i][j] = 0 ;
					remainingcells++ ;
					
					if(beta <= alpha) return alpha ;
				}
			}
		}
		
		return score ;
	}
	
	int minSearch(int level, int alpha, int beta) {
		check() ;
		if(finish == 1) {
			finish = -1 ;
			return 10 ;
		}
		else if(finish == 2) {
			finish = -1 ;
			return -10 ; 
		}
		else if(finish == 0) {
			finish = -1 ;
			return 0 ;
		}
		
		int score = std::numeric_limits<int>:: max() ;
		
		for(int i=0; i<DIM; i++) {
			for(int j=0; j<DIM; j++) {
				if(vec[i][j] == 0) {
					vec[i][j] = 2 ;
					remainingcells-- ;
					
					score = std::min(score, maxSearch(level+1, alpha, beta)+level) ;
					alpha = std::min(alpha, score) ;
					
					vec[i][j] = 0 ;
					remainingcells++ ;
					
					if(beta <= alpha) return beta ;
				}
			}
		}
		
		return score ;
	}
	
	// FUNCTIONS FOR RANDOM MOVE GENERATOR
	
	std::set<std::pair<int, int> > getRemainingMoves() {	
		std::set<std::pair<int, int> > res ;
		
		for(int i=0; i<DIM; i++) {
			for(int j=0; j<DIM; j++) {
				if(vec[i][j] == 0) res.insert(std::make_pair(i, j)) ;
			}
		}
		
		return res ;
	}
	
	Move randomMoveGenerator() {
		std::set<std::pair<int, int> > remainingmoves = getRemainingMoves() ;
		std::pair<int, int> action ;
		
		std::random_device dev ;
		std::mt19937 rng(dev()) ;
		std::uniform_int_distribution<std::mt19937::result_type> dist9(0, 8) ;
		
		Move move ;
		
		while(1) {
			int i = dist9(rng) ;
			action = std::make_pair(i/DIM, i%DIM) ;
			
			if(remainingmoves.find(action) != remainingmoves.end()) {
				break ;
			}
		}
		
		move.x = action.first, move.y = action.second ;
		
		return move ;
	}
	
	// taking the human move
	
	void getHumanMove() {
		bool fail = true ;
		int x = -1, y = -1 ;
		
		do {
			std::cout << "Input your Action Position 0-8: " ;
			
			int t ; std::cin >> t ;
			int x, y ;
			xy(x, y, t) ;
			
			if(t>8) std::cout << "Not a valid move, try again!!\n" ;
			else {
				if(vec[x][y] == 0) {
					vec[x][y] = 1 ;
					fail = false ;
				}
				else {
					std::cout << "Position is preoccupied, try again!! \n" ;
				}
			}
			
			std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
		} while(fail) ;
		
		vec[x][y] = 1 ;
		remainingcells-- ;
	}
	
	public: 
	
	TicTacToe() : finish(-1), DIM(3), remainingcells(DIM*DIM) {} ;
	
	
	// Game between 2 Human
	void play() {
		system("cls") ;
		
		std::cout << "Lets begin!!\n" ;
		printgrid() ;
		dispayinfo() ;
		int n = 0 ;
		
		// Game loop
		while(1) {
			std::cout << "Input your Action Position 0-8: " ;
			int t ; std::cin >> t ;
			system("cls") ;
			
			int i, j ;
			xy(i, j, t) ;
			remainingcells-- ;
			
			if(t>8) {
				std::cout << "Not a valid move, try again!!\n" ;
				remainingcells++ ;
			}
			else if(!(n&1)) {
				if(vec[i][j] == 0) vec[i][j] = 1 ;
				else {
					std::cout << "Position is preoccupied, try again!! \n" ;
					remainingcells++ ;
				}
			}
			else {
				if(vec[i][j] == 0) vec[i][j] = 2 ;
				else {
					std::cout << "Position is preoccupied, try again!! \n" ;
					remainingcells++ ;
				}
			}
			
			printgrid() ;
			check() ;
			
			if(finish == 1) {
				std::cout << "Player1 wins!! \n" ;
				return ;
			}
			else if(finish == 2) {
				std::cout << "Player2 wins!! \n" ;
				return ;
			}
			else if(finish == 0) {
				std::cout << "The Game ends in a tie!!\n" ;
				return ;
			}
			
			dispayinfo() ;
			
			n++ ;
		}
		
	}
	
	// Game with the Computer generating random moves

	void playWithRandomMoves() {
		int turn = 0 ;
		bool exit = false ;
		system("cls") ;
		
		std::cout << "Lets begin!!\n" ;
		printgrid() ;
		dispayinfo() ;
		
		do {
			// human move
			if(turn == 0) {
				getHumanMove() ;
				system("cls") ;
				
				check() ;
				if(finish == 1) {
					printgrid() ;
					std::cout << "Human Wins!!\n" ;
					return ;
				}
			}
			else {
				system("cls") ;
				std::cout << "Computer Move: " ;
				
				Move move = randomMoveGenerator() ;
				std::cout << move.x*DIM + move.y << "\n" ;
				
				vec[move.x][move.y] = 2 ;
				remainingcells-- ;
				
				check() ;
				if(finish == 2) {
					printgrid() ;
					std::cout << "Computer Wins!!\n" ;
					return ;
				} 	
			}
			
			if(finish == 0) {
				printgrid() ;
				std::cout << "The Game ends in a tie!!\n" ;
				return ;
			}
			
			turn ^= 1 ;
			printgrid() ;
			dispayinfo() ;
			
		} while(!exit) ;
	}
	
	// Game with the Computer(AI)
	
	void playWithComputer() {
		int turn = 0 ;
		bool exit = false ;
		system("cls") ;
		
		std::cout << "Lets begin!!\n" ;
		
		printgrid() ;
		dispayinfo() ;
		
		do {
			// human move
			if(turn == 0) {
				getHumanMove() ;
				system("cls") ;
				
				check() ;
				if(finish == 1) {
					printgrid() ;
					std::cout << "Human Wins!!\n" ;
					exit = true ;
				}
			}
			else {
				system("cls") ;
				std::cout << "Computer Move: " ;
				Move aimove = minimax() ;
				finish = -1 ;
				
				std::cout << aimove.x*DIM + aimove.y << "\n" ;
				
				vec[aimove.x][aimove.y] = 2 ;
				remainingcells-- ;
				
				check() ;
				if(finish == 2) {
					printgrid() ;
					std::cout << "Computer Wins!!\n" ;
					return ;
				} 					
			}
			
			if(finish == 0) {
				printgrid() ;
				std::cout << "The Game ends in a tie!!\n" ;
				return ; 
			}
			
			turn ^= 1 ;
			printgrid() ;
			dispayinfo() ;
			
		} while(!exit) ;
		
	}
	
} ;

int main(){
	TicTacToe round ;
	
	system("cls") ;
	
	std::cout << "Welcome to game of Tic Tac Toe...\n"
	     << "Press 1 to play against your Friend\n" 
	     << "Press 2 to play against your Computer\n" ;
	
	bool exit = false ;
	
	do {
		std::cout << "Choose the mode: " ; 
		int mode ; std::cin >> mode ;
		
		switch(mode) {
			case 1: round.play() ;
					exit = true ;
					break ;
			
			case 2: system("cls") ;
					std::cout << "Choose your difficulty level\n"
					     << "1 for Easy\n" 
						 << "2 for Hard\n" 
						 << "difficulty: " ;
						 
					int difficulty ; std::cin >> difficulty ;
					
					if(difficulty == 2) round.playWithComputer() ;
					else round.playWithRandomMoves() ;
					
					exit = true ;
					break ;
					
			default: std::cout << "Invalid Input, try again...\n" ;

		}
		
	} while(!exit) ;

    return 0;
}
