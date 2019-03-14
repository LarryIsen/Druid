/*
 *  Jewel.h
 *  Jeweler
 *
 *  Created by Larry Isen on Sun Mar 22 2009.
 *  Copyright (c) 2009 Larry Isen. All rights reserved.
 *
 */

// #include <Carbon/Carbon.h> // Uncomment if running in XCode on MacOS
#include <cstdlib>
#include <stdio.h>

	const int numberOfRows=6;
	const int numberOfCols=6;

//Type Definitions
enum ColorType {
	red, blue, green, yellow, orange, purple, black, white
};

class CeJeweledPP {
	public:
		ColorType jewel[numberOfRows][numberOfCols]; //Temporarily making it public for debug purposes
		int totalScore; // ditto

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		
		ColorType NewJewel ()
		{
			int randall; // Random Number.  With a whimsical name.
			ColorType jewel;
			randall = rand()%8;					//Choose a random color for the jewel
			switch (randall)
			{
				case 0:		jewel=red; break;
				case 1:		jewel=blue; break;
				case 2:		jewel=green; break;
				case 3:		jewel=yellow; break;
				case 4:		jewel=orange; break;
				case 5:		jewel=purple; break;
				case 6:		jewel=black; break;
				case 7:		jewel=white; break;
			}
			return jewel;
		} // end NewJewel
		
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		CeJeweledPP SetUpBoard ()
			/*PRE: None
			  POST: returns an array of random jewels.
			*/
			{
				CeJeweledPP newBoard;
				for (int row=0;row<numberOfRows;row++) {		
					for (int col=0;col<numberOfCols;col++) {
					newBoard.jewel[row][col]=NewJewel();
					}  //end of for col
				} //end of for row
				return newBoard;
				totalScore=0;
			} // end of SetUpBoard()

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		void DisplayBoard (CeJeweledPP board)  // debug-only function
		{
				for (int row=0;row<numberOfRows;row++) {
					printf("row %d: ",row+1);
					for (int col=0;col<numberOfCols;col++) {
						switch (board.jewel[row][col])
						{
							case red:		printf("%dred ",col+1); break;
							case blue:		printf("%dblue ",col+1); break;
							case green:		printf("%dgreen ",col+1); break;
							case yellow:	printf("%dyellow ",col+1); break;
							case orange:	printf("%dorange ",col+1); break;
							case purple:	printf("%dpurple ",col+1); break;
							case black:		printf("%dblack ",col+1); break;
							case white:		printf("%dwhite ",col+1); break;
							default: printf("%d ERROR ", col);
						}
					}  //end of for col
					printf("\n");
				} //end of for row
				printf("\n");
			} // end of DisplayBoard()
			
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		CeJeweledPP SwapPieces (CeJeweledPP &board, int row1, int col1, int row2, int col2)
		{
			ColorType temp;
			temp=board.jewel[row1][col1]; // swap the pieces
			board.jewel[row1][col1]=board.jewel[row2][col2];
			board.jewel[row2][col2]=temp;
			int score=CheckForMatch(board,row1,col1,1); // check each new spot for matches, with the starting score multiplier set to 1
			score+=CheckForMatch(board,row2,col2,1);
			if (score==0) { //if there are no matches, swap the pieces back.
				temp=board.jewel[row1][col1];
				board.jewel[row1][col1]=board.jewel[row2][col2];
				board.jewel[row2][col2]=temp;
			} // endif
			totalScore+=score;
			return board;
		} // end of SwapPieces()

		
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		int CheckForMatch(CeJeweledPP &board, int row, int col, int multiplier)
		// Pre: row < maximum rows, col < maximum cols, multplier is an integer > 0
		// Post: returns score
		{
			ColorType center=board.jewel[row][col];
			int mark=0; /*marks which jewels are to be removed, using bits:
					bit 1 (1): two above center
					bit 2 (2): one above
					bit 3 (4): two left
					bit 4 (8): one left
					bit 5 (16): one right
					bit 6 (32): two right
					bit 7 (64): one below
					bit 8 (128): two below */
					
			int score=0;
			
			if (row > 1) {
				if ((center == board.jewel[row-1][col]) && (center == board.jewel[row-2][col])) {
					mark += 3;
					score = score + multiplier;
					if (row < 5) { 
						if((center == board.jewel[row+1][col])) {
							mark += 64;
							score = score + multiplier;
								if (row < 4) {
									if (center == board.jewel[row+2][col]) {
										mark += 128;
										score = score + multiplier;
									} // end if row+2
								} // end if row < 4
						} // end if row+1
					} // end if row < 5
				}
			} // endif two above center
			
			
			if ((row > 0) and (row < 5)) {
				if ((center == board.jewel[row-1][col]) && (center == board.jewel[row+1][col])) {
					mark += 66;
					score = score + multiplier;
					if (row < 4) {
						if (center == board.jewel[row+2][col]) {
							mark += 128;
							score = score + multiplier;
						} // endif row+2
					} // endif row < 4
				}
			} // endif one above, one below
			
			
			if (col > 1) {
				if ((center == board.jewel[row][col-1]) && (center == board.jewel[row][col-2])) {
					mark += 12;
					score = score + multiplier;
					if (col < 5) {
						if (center == board.jewel[row][col+1]) {
							mark += 16;
							score = score + multiplier;
							if (col < 4) {
								if (center == board.jewel[row][col+2]) {
									mark += 32;
									score = score + multiplier;
								} // endif col+2
							} // endif col < 4
						} // endif col+1
					} // endif col < 5	
				}
			} // endif two left of center
			
			if ((col > 0) and (col < 5)) {
				if ((center == board.jewel[row][col-1]) && (center == board.jewel[row][col+1])) {
					mark += 24;
					score = score + multiplier;
					if (col < 4) {
						if (center == board.jewel[row][col+2]) {
							mark += 32;
							score = score + multiplier;
						} // endif col+2
					} // endif col < 4
				}
			} // endif one left, one right
			
			if (col < numberOfCols-2) {
				if ((center == board.jewel[row][col+1]) && (center == board.jewel[row][col+2])) {
					if ((mark&16) == 0) {mark += 16;} //remove only if they weren't already marked for removal when checking the two to the left.
					if ((mark&32) == 0) {mark += 32;}
					score = score + multiplier;
				}
			} // endif two right of center
			
			
			if (row < numberOfRows-2) {
				if ((center == board.jewel[row+1][col]) && (center == board.jewel[row+2][col])) {
					if ((mark&64) == 0) {mark += 64;}  // remove only if they weren't already marked for removal when checking the two above.
					if ((mark&128) == 0) {mark += 128;}
					score = score + multiplier;
				}
			} // endif two below center
			
			
			
			if (mark&1) {board=RemoveJewel(board,row-2,col,multiplier);}
			if (mark&2) {board=RemoveJewel(board,row-1,col,multiplier);}
			if (mark&4) {board=RemoveJewel(board,row,col-2,multiplier);}
			if (mark&8) {board=RemoveJewel(board,row,col-1,multiplier);}
			if (mark) {board=RemoveJewel(board,row,col,multiplier);} // If any surrounding nodes have been marked for removal, then remove the center, too
			if (mark&16) {board=RemoveJewel(board,row,col+1,multiplier);}
			if (mark&32) {board=RemoveJewel(board,row,col+1,multiplier);}
			if (mark&64) {board=RemoveJewel(board,row+1,col,multiplier);}
			if (mark&128) {board=RemoveJewel(board,row+2,col,multiplier);}
			
			return score;
	
		} // end of CheckForMatch()
		
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		CeJeweledPP RemoveJewel(CeJeweledPP board, int row, int col, int multiplier)
		{
			int rowCount=0;
			for (rowCount=row;rowCount>0;rowCount--) {
				board.jewel[rowCount][col]=board.jewel[rowCount-1][col];
			}
			board.jewel[0][col]=NewJewel();
			
			for (rowCount=row;rowCount>=0;rowCount--) {
				totalScore=totalScore + CheckForMatch(board, rowCount, col, multiplier+1);
			}
			return board;
		} //End of RemoveJewel()
		
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		int ScoreValue()
		{
			return totalScore;
		}

} jewelBoard; // end of CeJeweledPP class definition
