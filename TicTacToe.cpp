#include<bits/stdc++.h>

using namespace std;

class TicTacToe {
	bool finish ;
	bool draw ;
	int vec[3][3] = {} ;
	
	// Input Pattern for Human understanding :)
	void dispayinfo() {
		int t = 0 ;
		for(int i=0; i<3; i++) {
			cout << "-------------\n" ;
			cout << "|" ;

			for(int j=0; j<3; j++) {
				cout << " " << t++ << " |" ;
			}
			
			cout << "\n" ;
		}
		
		cout << "-------------\n" ;
	}
	
	// to print the Tic Tac Toe board 
	void printgrid() {
		for(int i=0; i<3; i++) {
			cout << "-------------\n" ;
			cout << "|" ;

			for(int j=0; j<3; j++) {
				if(vec[i][j] == 0) cout << "   " << "|" ;
				else if(vec[i][j] == 1) cout << " X " << "|" ;
				else cout << " O " << "|" ;
			}
			
			cout << "\n" ;
		}
		
		cout << "-------------\n" ;
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
			for(int j=1; j<3; j++) {
				if(vec[i][j] == 0 || vec[i][j-1] != vec[i][j]) flag = false ;
			}
			
			if(flag) {
				finish = true ;
				return ;
			}
		}
		
		// For columns
		for(int j=0; j<3; j++) {
			bool flag = true ;
			for(int i=1; i<3; i++) {
				if(vec[i][j] == 0 || vec[i-1][j] != vec[i][j]) flag = false ;
			}
			
			if(flag) {
				finish = true ;
				return ;
			}
		}
		
		// For diagonals
		bool flag = true ;
		for(int i=1; i<3; i++) {
			int val = vec[0][0] ;
			for(int j=0; j<3; j++) {
				if(i == j) {
					if(vec[i][j] == 0 || vec[i][j] != val) flag = false ;
				}
			}
		}
		
		if(flag) {
			finish = true ;
			return ;
		}
		
		flag = true ;
		for(int i=1; i<3; i++) {
			int val = vec[0][2] ;
			for(int j=0; j<3; j++) {
				if(i + j == 2) {
					if(vec[i][j] == 0 || vec[i][j] != val) flag = false ;
				}
			}
		}
		
		if(flag) {
			finish = true ;
			return ;
		}
		
		// Check for draw
		flag = true ; 
		for(int i=0; i<3; i++) {
			for(int j=1; j<3; j++) {
				if(vec[i][j] == 0) flag = false ;
			}
		}
		
		if(flag) {
			draw = true ;
			return ;
		}
	}
	
	public: 
	
	TicTacToe() : finish(false), draw(false) {} ;
	
	
	// Game between 2 Human
	void play() {
		dispayinfo() ;
		
		cout << "Lets begin!!\n" ;
		printgrid() ;
		
		int n = 0 ;
		
		// Game loop
		while(1) {
			cout << "Input your Action Position 0-8: " ;
			int t ; cin >> t ;
			
			int i, j ;
			xy(i, j, t) ;
			
			if(t>8) cout << "Not a valid move, try again!!\n" ;
			else if(!(n&1)) {
				if(vec[i][j] == 0) vec[i][j] = 1 ;
				else cout << "Position is preoccupied, try again!! \n" ;
			}
			else {
				if(vec[i][j] == 0) vec[i][j] = 2 ;
				else cout << "Position is preoccupied, try again!! \n" ;
			}
			
			printgrid() ;
			check() ;
			
			if(draw) {
				cout << "The Game ends in a tie!!\n" ;
				return ;
			}
			
			if(finish) {
				if(n&1) cout << "Player2 wins!! \n" ;
				else cout << "Player1 wins!! \n" ;
				
				return ;
			}
			
			n++ ;
		}
		
	}
	
} ;

int main(){
	TicTacToe round ;
	
	round.play() ;

    return 0;
}
