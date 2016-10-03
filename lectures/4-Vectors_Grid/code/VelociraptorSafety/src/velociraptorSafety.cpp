#include <iostream>
#include <string>
using namespace std;

#include "random.h"
#include "grid.h"

#include "gevents.h"
#include "gwindow.h"
#include "gobjects.h"


// for good style we use constants, not magic numbers.
static const int NUM_RAPTORS = 6;
static const int BOARD_DIMENSION = 8;
static const int NUM_ROWS = BOARD_DIMENSION;
static const int NUM_COLS = BOARD_DIMENSION;
static const double SQUARE_SIZE = 32;
static const double DELAY_MS = 100;
static const string TITLE = "Velociraptor Safety";
static const string FONT = "Helvetica-24-Bold";

// main helper methods.
void clearBoard(Grid<bool> &board, GWindow &window);
void placeRandomRaptors(Grid<bool> &board, GWindow &window);
void identifySafeLocations(Grid<bool> &board, GWindow &window);

// graphics helper methods.
void drawSquare(GWindow &window, int row, int col);
void drawRaptor(GWindow &window, int row, int col);
void drawSafe(GWindow &window, int row, int col);
void drawDanger(GWindow &window, int row, int col);

int main() {
    Grid<bool> board(NUM_ROWS, NUM_COLS);
    GWindow window;
    window.setWindowTitle(TITLE);
    window.setVisible(true);

    clearBoard(board, window);
    placeRandomRaptors(board, window);
    identifySafeLocations(board, window);

    cout << "All done!  It's safe to close both windows." << endl;
    return 0;
}

/**
 * Function: clearBoard
 * --------------------
 * Sets all elements in the board grid to be false.
 * Also draws the squares.
 */
void clearBoard(Grid<bool>& board, GWindow& window) {
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			board[row][col] = false;
            drawSquare(window, row, col);
		}
	}
}

/**
 * Function: placeRandomRaptors
 * --------------------
 * Sets exactly NUM_RAPTORS number of squares on the grid
 * to be true... reflecting the presence of raptors. Also
 * draws raptors.
 */
void placeRandomRaptors(Grid<bool>& board, GWindow& window) {
    int numPlaced = 0;
    while (numPlaced < NUM_RAPTORS) {
		int row = randomInteger(0, board.numRows() - 1);
		int col = randomInteger(0, board.numCols() - 1);
		if (!board[row][col]) {
			board[row][col] = true;
            drawRaptor(window, row, col);
            numPlaced++;
		}
	}
	
	cout << "Click the mouse anywhere in the window to see which locations are safe." << endl;
    waitForClick();
}

/**
 * Function: isDirectionSafe
 * --------------------
 * Checks if a line of cells starting from row col and moving in
 * the direction drow, dcol is safe from raptors.
 */
bool isDirectionSafe(Grid<bool>& board, int row, int col, int drow, int dcol) {
    if (drow == 0 && dcol == 0) return true;
    
    while (board.inBounds(row, col)) {
        if(board[row][col]) return false;
		row += drow;
        col += dcol;
	}
    
    return true;
}

/**
 * Function: isSafe
 * --------------------
 * Checks if a given row, col is safe from the raptors
 * on the board.
 */
bool isSafe(Grid<bool>& board, int row, int col) {
	for (int drow  = -1; drow  <= 1; drow++) {
		for (int dcol = -1; dcol <= 1; dcol++) {
            if (!isDirectionSafe(board, row, col, drow, dcol)) {
				return false;
            }
		}
    }
	return true;
}

/**
 * Function: identifySafeLocations
 * --------------------
 * Loops over every location on the board and determines
 * which ones are safe and which are not. Visualizes the
 * results so as to help save the users life.
 */
void identifySafeLocations(Grid<bool>& board, GWindow& window) {
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			if (!board[row][col]) {
                if (isSafe(board, row, col)) {
                    drawSafe(window, row, col);
				} else {
                    drawDanger(window, row, col);
				}
			}
		}
	}
}

/*************************************************************************
 *                Graphics Helper Methods                                *
 * You don't need to understand the following code, but I included it    *
 * in case you were curious. It includes concepts we haven't covered yet *
 * such as graphics and pointers. We will get there:)                    *
 *************************************************************************/

void drawSquare(GWindow& window, int row, int col) {
    string color = "blue";
    int ulx = (window.getWidth() - BOARD_DIMENSION * SQUARE_SIZE)/2 + col * SQUARE_SIZE;
    int uly = (window.getHeight() - BOARD_DIMENSION * SQUARE_SIZE)/2 + row * SQUARE_SIZE;
    window.setColor(color);
    window.drawRect(ulx, uly, SQUARE_SIZE, SQUARE_SIZE);
}

void markLocation(GWindow& window, string text, int row, int col, string color) {
    int cx = (window.getWidth() - BOARD_DIMENSION * SQUARE_SIZE)/2 + col * SQUARE_SIZE + SQUARE_SIZE/2;
    int cy = (window.getHeight() - BOARD_DIMENSION * SQUARE_SIZE)/2 + row * SQUARE_SIZE + SQUARE_SIZE/2;
    window.setColor(color);

    // for reasons I won't go into at this point, these need to be dynamically allocated
    GLabel *label = new GLabel(text);
    label->setFont(FONT);
    label->setColor(color);
    window.add(label, cx - label->getWidth()/2, cy + label->getFontAscent()/2);
    pause(DELAY_MS);
}

void drawRaptor(GWindow &window, int row, int col){
    markLocation(window, "R", row, col, "Black");
}

void drawSafe(GWindow &window, int row, int col){
    markLocation(window, "S", row, col, "Green");
}

void drawDanger(GWindow &window, int row, int col){
    markLocation(window, "X", row, col, "Red");
}


