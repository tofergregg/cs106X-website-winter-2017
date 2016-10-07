/*
 * CS 106B, Chris Piech
 * I had this need to program. And then while getting ready for lecture 4 I realized
 * there was no published AI solver for Bananagrams:
 * https://en.wikipedia.org/wiki/Bananagrams
 * So here you have it. The (as far as I know) first computer bananagram agent.
 *
 * When reading this I suggest:
 *  0. Check out main
 *  1. Check out the game setup
 *  2. Check out getFirstWord
 *  3. Check out playWordOnBoard
 *
 * All the best,
 * Chris Piech (piech@cs.stanford.edu)
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include "console.h"
#include "timer.h"
#include "hashset.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"
#include "vector.h"
#include "grid.h"
#include "filelib.h"
#include "gwindow.h"
#include "gobjects.h"
#include "simpio.h"

using namespace std;

// How many tiles each player draws at the start
const int NUM_START_TILES = 21;
// How big to make the virtual grid that I populate
const int MAX_BOARD_SIZE = NUM_START_TILES * 2;
// Bananagrams is a complex game. Limit how deep we go
const int MAX_WORDS_PER_SPOT = 300000;
// How big should the tiles be in visualization
const int TILE_SIZE = 50;
// Some constants to store directions
const int LEFT_RIGHT = 0;
// Some constants to store directions
const int UP_DOWN = 1;

/**
 * Struct: Spot
 * This is the one C++ thing I used that we haven't seen.
 * It basically packages a row, col and direction into 
 * a single, simple, variable type called Spot. I'll cover
 * this on Friday.
 */
struct Spot {
    int r;
    int c;
    int dir;
};

/**
 * Struct: Utilities
 * This variable type packages the reverseMap and the tile
 * letterScores into one variable for shorter parameter 
 * lists.
 */
struct Utils {
    Map<string, Set<string>> anagramMap;
    Map<char, int> letterScores;
};

// Artificial Intelligence Part
string getWordToPlay(Utils & utils, string & tiles, string seed);
string playWordOnBoard(Utils & utils, string & tiles, Grid<char> & board);
string checkForWord(Utils & utils, string & tiles);
int getHeuristic(Utils & utils, string str, string seed);
Vector<Spot> getSpots(Grid<char> & board, int spacing);

// First Word Functions
string getFirstWord(Utils & utils, string & tiles);
void placeFirstWordOnBoard(Grid<char> & board, string& word);

// Helper Functions
string sortLetters(string s);
void removeTiles(string & tiles, string playedWord);
int countLetters(string & str);
void orientWord(Grid<char> & board, Spot spot, string word);

// Game Setup
string setUpUtils(Utils & utils);
string loadLetters();
void populateAnagramMap(Lexicon &lexicon, Map<string, Set<string> > &anagram);
string selectRandomTiles(string & pile, int num);
Grid<char> makeBoard();

// Board Visualization
Grid<char> getTrimmedBoard(Grid<char> & board);
void visualizeBoard(Grid<char> & board);
void outputTrimmedBoard(Grid<char> & board);

/* Main
 * Selects 21 random tiles and plays them in a grid. It doesn't
 * work perfectly but plays all tiles about 90% of the time...
 * This is just the start..
 */
int main() {
    // Remove this to add some randomness. Keep for debugging.
    setRandomSeed(0);

    // 0. Setup the game
    Utils utils;
    string allTiles = setUpUtils(utils);
    string playerTiles = selectRandomTiles(allTiles, 21);
    Grid<char> board = makeBoard();

    cout << "Original Tiles: " << playerTiles << endl;
    getLine("Press enter to run:");

    // 1. Play the first word
    string first = getFirstWord(utils, playerTiles);
    placeFirstWordOnBoard(board, first);
    outputTrimmedBoard(board);
    removeTiles(playerTiles, first);
    cout << "remaining tiles: " << playerTiles << endl;

    // 2. Play the remaining words
    while(true) {
        if(playWordOnBoard(utils, playerTiles, board) == "") break;
        outputTrimmedBoard(board);
        cout << "remaining tiles: " << playerTiles << endl;
    }

    // 3. Show the user
    visualizeBoard(board);
    cout << "Thanks for playing" << endl;
    return 0;
}

/*********************************************************************
 *                          SETUP                                    *
 *********************************************************************/

/* Make Board
 * Make a really large empty board. Make it so big that if we start in
 * the middle no combination of words could take us off the board.
 * Later when visualizing the board we can trim it.
 */
Grid<char> makeBoard() {
    Grid<char> board(MAX_BOARD_SIZE,MAX_BOARD_SIZE);
    for(int r = 0; r < MAX_BOARD_SIZE; r++){
        for(int c = 0; c < MAX_BOARD_SIZE; c++) {
            board[r][c] = ' ';
        }
    }
    return board;
}

/* Score Letter
 * If I submitted this code, I might lose a style bucket for this method.
 * There are a bunch of what we call "magic" numbers... numbers which are
 * constant but have no explained meaning. This function takes a character,
 * and how many times it shows up in the game and scores how hard it is
 * to play.
 */
int scoreLetter(char ch, int count) {
    if(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
        return 1;             // Oops magic numbers. Minus style point.
    }
    if(count <= 2) return 40; // Oops magic numbers. Minus style point.
    if(count <= 4) return 10; // Oops magic numbers. Minus style point.
    if(count <= 9) return 5;  // Oops magic numbers. Minus style point.
    return 3;                 // Oops magic numbers. Minus style point.
}

/* Load Letter Scores
 * This creates a mapping between each letter and how useful
 * I think it is to play that letter. In the world of AI we call
 * these scores "heuristics". For example I think its really good
 * to play an X, and not nearly as good to play an A. I base these
 * scores off of how frequent the letters show up in the game.
 */
void loadLetterScores(Map<char, int> & scores) {
    ifstream countStream;
    openFile(countStream, "banana-dist.txt");
    for(char ch = 'A'; ch <= 'Z'; ch++) {
        string countStr;
        getline(countStream, countStr);
        int count = stringToInteger(countStr);
        int letterScore = scoreLetter(ch, count);
        scores[ch] = letterScore;
    }
}

/* Set Up Utils
 * This function loads the scrabble dictionary, the map
 * of letter scores (the "scores" are made up by Chris and
 * are not part of the game rules) and the game tiles.
 */
string setUpUtils(Utils & utils) {
    cout << "Bananagrams" << endl;
    Lexicon english("scrabble-dictionary.txt");
    populateAnagramMap(english, utils.anagramMap);
    loadLetterScores(utils.letterScores);
    return loadLetters();
}

/* Load Letters
 * Bananagrams uses a carefully chosen count of tiles. I looked
 * up those counts and put them in the file banana-dist.txt. This
 * function reads that file and returns all the tiles as one long
 * string.
 */
string loadLetters() {
    string letters;
    ifstream countStream;
    openFile(countStream, "banana-dist.txt");
    for(char ch = 'A'; ch <= 'Z'; ch++) {
        string countStr;
        getline(countStream, countStr);
        int count = stringToInteger(countStr);
        for(int i = 0; i < count; i++) {
            letters += ch;
        }
    }
    return letters;
}

/* Populate Anagram Map
 * Just like in the example we saw in class. We keep a map of sortedLetters
 * to all the words that those letters can be re-arranged to spell.
 */
void populateAnagramMap(Lexicon &lexicon, Map<string, Set<string> > &anagram) {
    for(string word : lexicon) {
        word = toUpperCase(word);
        string sorted = sortLetters(word);
        anagram[sorted].add(word);
    }
}

/* Select Random Tiles
 * Given a pile of tiles, randomly select num of them without
 * replacement. Return the selected tiles.
 */
string selectRandomTiles(string & pile, int num) {
    string selected;
    for(int i = 0; i < num; i++) {
        int index = randomInteger(0, pile.length() - 1);
        char tile = pile[index];
        pile.erase(index, 1);
        selected += tile;
    }
    return selected;
}

/*********************************************************************
 *                       FIRST WORD                                  *
 *********************************************************************/

/* Get First Word
 * Chose a first word to play given your tiles. All of the logic here
 * is deffered to the function getWordToPlay which can take a seed (aka
 * a letter to play off). At the start there is no seed.
 */
string getFirstWord(Utils & utils, string & tiles) {
    return getWordToPlay(utils, tiles, "");
}

/* Place First Word on Board
 * Put it right in the middle. If we make the board at least 2N x 2N
 * where N is the number of tiles to play this should always be safe.
 */
void placeFirstWordOnBoard(Grid<char> &board, string& first){
    for(int i = 0; i < first.size(); i++) {
        int col = MAX_BOARD_SIZE/2 + i;
        board[MAX_BOARD_SIZE/2][col] = first[i];
    }
}

/*********************************************************************
 *                       A.I. PART                                   *
 *********************************************************************/

/* Get Word To Play
 * This function is the heart of the AI. It tries to find the best word
 * it can possibly play using a set of tiles and building off of a
 * seed (which is often the empty string or a single character). It
 * wants to call checkForWord with every possible combination of letters
 * in tiles. To try every combination of letters I use a Queue called
 * pipeline. In pipeline I keep all the combinations of tiles I have used
 * so far. At first I just put the seed in the pipeline. Then each step
 * through the pipeline I pull out the next combination of letters to
 * check... and then
 *    1. I check if I can make a better word using those letters
 *    2. I enqueue two extra combinations.
 *        2a. One with the next tile
 *        2b. One without the next tile
 * If you think it through this will eventually try every combination
 * of tiles. This is a *very* advanced use of queues and I don't expect
 * everyone in CS106B to get it just by reading the code. But please do ask
 * if you want to know more.
 */
string getWordToPlay(Utils & utils, string & tiles, string seed) {
    string best = "";
    int bestScore = 0;
    // A collection of things to try
    Queue<string> pipeline;

    // Initially we are going to start with the seed
    pipeline.enqueue(seed);
    int done = 0;
    while(!pipeline.isEmpty()) {
        // Get the next combination of tiles to try.
        string soFar = pipeline.dequeue();

        // How great would it be if we could make a word?
        int score = getHeuristic(utils, soFar, seed);
        if(score > bestScore) { // Very
            string word = checkForWord(utils, soFar);
            // We found a word thats better than previous best
            if(word != "") {
                bestScore = score;
                best = word;
                cout << best  << endl;
            }
        }

        // What is the next tile to include or exclude?
        int index = soFar.length() - seed.length();
        if(index < tiles.length()) {
            // Try including it (will be dequeued later)
            string a = soFar + tiles[index];
            pipeline.enqueue(a);
            // Try excluding it (will be dequeued later)
            string b = soFar + '-';
            pipeline.enqueue(b);
        }

        // Sometimes you have searched deep enough...
        if(++done == MAX_WORDS_PER_SPOT) break;
    }
    return best;
}

/* Play Word On Board
 * First find all spots where you could potentially play all of your tiles
 * in terms of spacing. Then for each of those spots find the best word you
 * could play in terms of actual english words. Finally play your best move!
 */
string playWordOnBoard(Utils & utils, string & tiles, Grid<char> & board) {
    Spot bestSpot;
    string best = "";
    int bestScore = 0;

    // Check each spot
    Vector<Spot> playableSpots = getSpots(board, tiles.size());
    for(Spot spot : playableSpots) {
        string seed = charToString(board[spot.r][spot.c]);
        string word = getWordToPlay(utils, tiles, seed);
        if(word != "") {
            int score = getHeuristic(utils, word, seed);
            if(score > bestScore) {
                bestSpot = spot;
                bestScore = score;
                best = word;
            }
        }
    }

    // Play your best move
    if(best != "") {
        string seed = charToString(board[bestSpot.r][bestSpot.c]);
        string used = best;
        used.erase(used.find(seed), 1);
        removeTiles(tiles, used);
        orientWord(board, bestSpot, best);
    }
    return best;
}

/* Check For Word
 * This is that same funcition that we wrote in class for the
 * anagrams problem! It uses the anagramMap which maps from
 * sortedLetters to a set of all words you can make with those
 * letters. Its super fast. Returns a word if found. Empty string
 * otherwise.
 */
string checkForWord(Utils & utils, string & tiles) {
    string base = "";
    for(int i = 0; i < tiles.size(); i++) {
        if(tiles[i] != '-') base += tiles[i];
    }
    base = toUpperCase(base);
    string baseSorted = sortLetters(base);
    if(utils.anagramMap.containsKey(baseSorted)) {
        return utils.anagramMap[baseSorted].first();
    }
    return "";
}

/* Get Heuristic
 * How awesome would it be if we played this word?
 */
int getHeuristic(Utils & utils, string str, string seed) {
    int score = 0;
    for(int i = seed.length(); i < str.length(); i++) {
        if(str[i] != '-') {
            char ch = str[i];
            score += utils.letterScores[ch];
        }
    }
    return score;
}

/* Check Left Right Spacing
 * Would there be enough spacing to place all of our letters at this spot
 * left-to-right regardless of how it latches on. This hasn't been
 * thoroughly tested.
 */
bool checkLeftRightSpacing(Grid<char> & board, int r, int c, int spacing) {
    for(int dRow = -1; dRow <= +1; dRow++) {
        for(int dCol = -spacing; dCol <= +spacing; dCol++) {
            int currCol = c + dCol;
            int currRow = r + dRow;
            if(board[currRow][currCol] != ' ' && currCol != c) return false;
            if(board[currRow][currCol] && currCol == c && abs(dCol) == spacing) return false;
        }
    }
    return true;
}

/* Check Up Down Spacing
 * Would there be enough spacing to place all of our letters at this spot
 * up-to-down regardless of how it latches on. This hasn't been
 * thoroughly tested.
 */
bool checkUpDownSpacing(Grid<char> & board, int r, int c, int spacing) {
    for(int dCol = -1; dCol <= +1; dCol++) {
        for(int dRow = -spacing; dRow <= +spacing; dRow++) {
            int currRow = r + dRow;
            int currCol = c + dCol;
            if(board[currRow][currCol] != ' ' && currRow != r) return false;
            if(board[currRow][currCol] && currRow == r && abs(dRow) == spacing) return false;
        }
    }
    return true;
}

/* Get Spots
 * Find all board locations (with direction) where you could safely play
 * any word without worrying about running into another word.
 */
Vector<Spot> getSpots(Grid<char> & board, int spacing) {
    Vector<Spot> spots;
    for(int r = 0; r < board.numRows(); r++) {
        for(int c = 0; c < board.numCols(); c++) {
            if(board[r][c] != ' ') {
                if(checkLeftRightSpacing(board, r, c, spacing)) {
                    Spot found = {r,c,LEFT_RIGHT};
                    spots.add(found);
                }
                if(checkUpDownSpacing(board, r, c, spacing)) {
                    Spot found = {r,c,UP_DOWN};
                    spots.add(found);
                }
            }
        }
    }
    return spots;
}



/*********************************************************************
 *                     HELPER FUNCTIONS                              *
 *********************************************************************/

/* Sort Letters
 * Returns a canonical version of the given word
 * with its letters arranged in alphabetical order.
 * For example, sortLetters("banana") returns "aaabnn".
 * This code was provided by the instructor as-is; we didn't write it in class.
 */
string sortLetters(string s) {
    sort(s.begin(), s.end());   // sort function comes from C++ STL libraries
    return s;
}

/* Remove Tiles
 * Assumes that tiles is a string of tiles that you can play
 * and that you just played the string playedWord. Removes each
 * of the letters in playedWord from tiles.
 */
void removeTiles(string & tiles, string playedWord) {
    playedWord = toUpperCase(playedWord);
    for(int i = 0; i < playedWord.size(); i++) {
        if(playedWord[i] == '-') continue;
        int tileIndex = tiles.find(playedWord[i]);
        tiles.erase(tileIndex, 1);
    }
}

/* Count Letters
 * Given a string that is composed of letters and dashes,
 * eg: AB--C--D--
 * Count how many letters the are. Above would return 4.
 */
int countLetters(string & str) {
    int count = 0;
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != '-') {
            count++;
        }
    }
    return count;
}

/* Orient Word
 * You found a spot, and you know what word you want to play
 * in that spot. This method places the word on the grid.
 */
void orientWord(Grid<char> & board, Spot spot, string word) {
    char seed = board[spot.r][spot.c];
    int index = word.find(seed);
    if(spot.dir == LEFT_RIGHT) {
        int startCol = spot.c - index;
        for(int i = 0; i < word.size(); i++) {
            int c = i + startCol;
            board[spot.r][c] = word[i];
        }
    }
    if(spot.dir == UP_DOWN) {
        int startRow = spot.r - index;
        for(int i = 0; i < word.size(); i++) {
            int r = i + startRow;
            board[r][spot.c] = word[i];
        }
    }
}

/*********************************************************************
 *                   BOARD VISUALIZATION                             *
 *********************************************************************/

/* Visualize Board
 * Draw a board of characters onto the screen. First trims it so
 * that there isn't a lot of empty white space.
 */
void visualizeBoard(Grid<char> & board) {
    Grid<char> trimmed = getTrimmedBoard(board);
    int width = TILE_SIZE * trimmed.numCols();
    int height = TILE_SIZE * trimmed.numRows();
    GWindow gw(width, height);
    for(int r = 0; r < trimmed.numRows(); r++) {
        for(int c = 0; c < trimmed.numCols(); c++) {
            if(trimmed[r][c] != ' ') {
                int x = TILE_SIZE * c;
                int y = TILE_SIZE * r;
                GRect * rect = new GRect(x, y, TILE_SIZE, TILE_SIZE);
                rect->setColor("#4E3520");
                rect->setFillColor("#EBCD9F");
                rect->setFilled(true);

                string tile = charToString(trimmed[r][c]);
                GLabel * label = new GLabel(tile);
                label->setFont("SansSerif-24");
                int labelX = x + (TILE_SIZE - label->getWidth())/2;
                int labelY = y + (TILE_SIZE + label->getFontAscent())/2;

                gw.add(rect);
                gw.add(label, labelX, labelY);
            }
        }
    }
}

/* Output Trimmed Board
 * Cout a board of characters onto the console. First trims it so
 * that there isn't a lot of empty white space.
 */
void outputTrimmedBoard(Grid<char> & board) {
    Grid<char> trimmed = getTrimmedBoard(board);

    cout << "----------" << endl;
    for(int r = 0; r < trimmed.numRows(); r++) {
        for(int c = 0; c < trimmed.numCols(); c++) {
            cout << trimmed[r][c];
        }
        cout << endl;
    }
    cout << "----------" << endl;
}

/* Get Trimmed Board
 * Trims a board of characters so that there isn't
 * a lot of empty white space.
 */
Grid<char> getTrimmedBoard(Grid<char> & board) {
    int minC = board.numCols() - 1;
    int maxC = 0;
    int minR = board.numRows() - 1;
    int maxR = 0;
    for(int r = 0; r < board.numRows(); r++) {
        for(int c = 0; c < board.numCols(); c++) {
            if(board[r][c] != ' ') {
                minC = min(minC, c);
                minR = min(minR, r);
                maxC = max(maxC, c);
                maxR = max(maxR, r);
            }
        }
    }
    Grid<char> trimmed(maxR - minR + 1, maxC - minC + 1);
    for(int r = 0; r < trimmed.numRows(); r++) {
        for(int c = 0; c < trimmed.numCols(); c++) {
            trimmed[r][c] = board[minR + r][minC + c];
        }
    }
    return trimmed;
}

