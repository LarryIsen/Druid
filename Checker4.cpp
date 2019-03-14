// This program is not finished, and won't run.  Please see accompanying "Checker pseudocode and notes.txt" document for where I was heading when I ran out of time.

#include <string>
#include <iostream>
using namespace std;
#include <cstdlib>

// Going to be a simple, abstract, numeric-based representation of a checkerboard.
// An 8x8 grid, where 0 represents an empty square, a 1 represents player 1, a 2 represents player 2,
// and a -1 represents a squrare that can't be moved to.
// Going to make it text input; graphics can always come later, once I have better tools.
// I don't have a lot of time to be clever, so I'm going to have to brute force most of this.
// Hence not using linked list, not using classes, putting everything in one file... not using anything remotely fancy.
// Also not going to check for a draw, just going to keep it going until one player is out of pieces and/or moves
// (i.e., if all their remaining pieces are on the far side of the board, since I can't find the rules of Simple Checkers anywhere).

int board[8][10];  // the board is 8x8, but the outer two columns are dummy columns used for error handling,
                   // so the "column" variable doesn't go out of range.
                   // It also helps in that now the columns are 1-8 rather than 0-7

int p1=12, p2=12 ; // Number of pieces each player has.
                   // Will decrement for captured pieces and for pieces that can no longer move.

//------------------------------------------

void initBoard(int board[8][10])
{
    int i,j ; // counters
    
    for (i=0;i<=7;i++)
        for (j=0;j<=9;j++)
            board[i][j]=-1; // Since half the board is going to be -1s, easier to just fill in the -1s at the start
    
    // If i is even (i mod 2 = 0, rows 0, 2, 4, 6), then the usable squares are j = 2, 4, 6, 8;
    // If i is odd (i mod 2 = 1, rows 1, 3, 5, 7), then the usable squares are j = 1, 3, 5, 7;
    
    for (i=0;i<=7;i++) // row
    {
        if (i<=2)
            for (j=1;j<=7;j=j+2)
                board[i][j+(i%2)] = 2 ; //opponent at the top
                
        if ((i>=3)&&(i<=4))
            for (j=1;j<=7;j=j+2)
                board[i][j+(i%2)] = 0 ; //empty squares
        
        if (i>=5)
            for (j=1;j<=7;j=j+2)
                board[i][j+(i%2)] = 1 ; //player at the bottom
    }
    
}

//------------------------------------------

void showBoard(int board[8][10])
{
    int i,j ; // counters
    
    for (i=0;i<=7;i++)
    {
        for (j=0;j<=9;j++)
            if (board[i][j]==-1)
                cout << ". ";
                else cout << board[i][j] << " ";
        cout << "\n";
    } 
}


//------------------------------------------

void playerTurn(int board[8][10], int win, int p1, int p2)
{
    int i,j ; // counters.  Might not need them, but I have them anyway.
    int row, column ; // separating them
    bool legal=false; // used to both indicate whether the square actually has a free checker in it, and whether the subsequent move is legal
    
    // ... okay, this is gonna be ugly.  Sanity checks are a luxury I don't have; I only have an hour and a half left as I type this.
    // Just going to assume that all data entered is in the proper range.
    // Also not testing for "if you can jump, then you must jump".
    
    while (!legal)
    {
        cout << "\nWhich piece do you want to move?  Enter row (1-8).\n";
        cin >> row;
        row--; // subtracting one, because the actual value of the row is 0-7, not 1-8 as instructed.
        cout << "\nEnter column. (1-8)\n";
        cout << column ;
        if (board[row][column]!=1) // does the selected space have an opponent's checker in it, is it empty, or is it a non-movable space?
            cout << "\nYou don't have a checker there.\n";
        else if ((row=0) || ((board[row-1][column-1]=1) && (board[row-1][column+1]=1))) // is the piece in the top row already, or is it blocked by the player's own checkers?
            cout << "\nThat piece cannot move.\n";
        else if ((board[row-1][column-1]=2) || (board[row-1][column+1]=2)) // does either space above have an opponent's checker in it?  If so, check whether it can be jumped.
		{
			if ((board[row-1][column-1]==2) && (row>2))
			{
				if ((board[row-2][column-2])==0);
				legal=true;
			}
			else if ((board[row-1][column+1]==2) && (row>2))
			{
				if ((board[row-2][column+2])==0);
				legal=true;
			}
				
		} // jump test


    }
        
        
        //
        //  The above isn't anywhere near done.  
        //
        
        
    //}
}

//------------------------------------------

void compTurn(int board[8][10], int win, int p1, int p2)
{
    int i,j ; // counters
}


//------------------------------------------

void gameLoop(int board[8][10])
{
    int win=0 ; // When either player wins, this will be set to 1 or 2 (for player or computer, respectively)
    
    while (!win) {
        playerTurn(board,win,p1,p2); // Player goes first, because... I say so.
        compTurn(board,win,p1,p2);
    }

    if (win==1)
        cout << "\n\nThe player wins!";
    else if (win==2)
        cout << "\n\nThe computer wins!";
    else cout << "\n\nYou broke something, dude.";
    showBoard(board);

}

//------------------------------------------

int main()
{
  initBoard(board);
  showBoard(board);
  gameLoop(board);
}
