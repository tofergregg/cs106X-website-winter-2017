

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"
#include "math.h" //for sqrt and exp in the optional Gaussian kernel
#include "random.h"
#include "vector.h"
#include "hashmap.h"
#include "map.h"
using namespace std;

static const int RED = 0xFF0000;

struct Coord {
    int row;
    int col;
};

Vector<Coord> getSeam(Grid<double>& weight);
Grid<double> getPixelImportance(GBufferedImage & picture);
void removePath(GBufferedImage & picture, Vector<Coord> & path);
void showPath(GBufferedImage & picture, Vector<Coord> & path);
double pathCost(Grid<double>& weight, Vector<Coord> & path);
Grid<int> getWeightViz(Grid<double>&weight);

bool openImageFromFilename(GBufferedImage& img, string filename);
bool saveImageToFilename(const GBufferedImage &img, string filename);

void seamCarve(GBufferedImage & picture) {
    getLine("Press enter to find seam");
    cout << "Thinking..." << endl;

    // 1. Get the importance of each pixel
    Grid<double> weight = getPixelImportance(picture);
    picture.fromGrid(getWeightViz(weight));

    // 2. Find the path with least importance sum
    Vector<Coord> path = getSeam(weight);

    // 3. Show and Remove the path
    showPath(picture, path);
    getLine("Press enter to carve");
    removePath(picture, path);
}

Vector<Coord> getSeam(Map<string, Vector<Coord>>& cache, Grid<double>& weight, Coord curr) {
    string key = integerToString(curr.row) + "," + integerToString(curr.col);
    // base case
    if(cache.containsKey(key)) return cache[key];

    if(curr.row == weight.nRows - 1) {
        Vector<Coord> single;
        single.add(curr);
        return single;
    }

    // recursive case
    Vector<Coord> bestPath;
    double bestPathCost = -1;
    for(int dCol = -1; dCol <= +1; dCol++) {
        Coord next = {curr.row + 1, curr.col + dCol};
        if(!weight.inBounds(next.row, next.col)) continue;
        Vector<Coord> childPath = getSeam(cache, weight, next);
        double cost = pathCost(weight, childPath);
        if(bestPathCost == -1 || cost < bestPathCost) {
            bestPath = childPath;
            bestPathCost = cost;
        }
    }
    bestPath.insert(0, curr);
    cache[key] = bestPath;
    return bestPath;
}

Vector<Coord> getSeam(Grid<double>& weight) {
    Map<string, Vector<Coord>> cache;
    Vector<Coord> path;
    double bestCost = -1;
    for(int c = 0; c < weight.nCols; c++) {
        Coord start = {0, c};
        Vector<Coord> currPath = getSeam(cache, weight, start);
        double currCost = pathCost(weight, path);
        if(bestCost == -1 || currCost < bestCost) {
            path = currPath;
            bestCost = currCost;
        }
    }
    return path;
}

void showPath(GBufferedImage & picture, Vector<Coord> & path) {
    Grid<int> pixels = picture.toGrid();
    for(Coord p : path) {
        pixels[p.row][p.col] = RED;
    }
    picture.fromGrid(pixels);
}

void removePath(GBufferedImage & picture, Vector<Coord> & path) {
    Grid<int> pixels = picture.toGrid();
    Grid<int> newPixels(pixels.nRows, pixels.nCols - 1);

    for(Coord p : path) {
        for(int c = 0; c < p.col; c++) {
            newPixels[p.row][c] = pixels[p.row][c];
        }
        for(int c = p.col + 1; c < pixels.nCols; c++) {
            newPixels[p.row][c - 1] = pixels[p.row][c];
        }
    }
    picture.fromGrid(newPixels);
}

double pathCost(Grid<double> &weight, Vector<Coord> &path) {
    double cost = 0;
    for(Coord c : path) {
        cost += weight[c.row][c.col];
    }
    return cost;
}

double getColorDistance(int color1, int color2) {
    int r1,g1,b1,r2,g2,b2;
    GBufferedImage::getRedGreenBlue(color1,	r1, g1, b1);
    GBufferedImage::getRedGreenBlue(color2,	r2, g2, b2);
    double gray1 = 0.21 *r1 + 0.72 *g1 + 0.07 *b1;
    double gray2 = 0.21 *r2 + 0.72 *g2 + 0.07 *b2;
    double diff = gray2 - gray1;
    return diff * diff;
}


double getImportance(Grid<int>& pixels, int r, int c) {
    double sum = 0;
    double n = 0;
    for(int dc = -1; dc <= +1; dc++) {
        for(int dr = -1; dr <= +1; dr++) {
            if(dc == 0 && dr == 0) continue;
            if(!(dc == 0 || dr == 0)) continue;
            int currR = r + dr;
            int currC = c + dc;
            if(pixels.inBounds(currR, currC)) {
                sum += getColorDistance(pixels[r][c], pixels[currR][currC]);
                n++;
            }
        }
    }
    return sum / n;
}

Grid<double> getPixelImportance(GBufferedImage & picture) {
    Grid<int> pixels = picture.toGrid();
    Grid<double> importance(pixels.nRows, pixels.nCols);

    for(int r = 0; r < pixels.nRows; r++) {
        for(int c = 0; c < pixels.nCols; c++) {
            importance[r][c] = getImportance(pixels, r, c);
        }
    }
    return importance;
}

Grid<int> getWeightViz(Grid<double>&weight) {
    double max = -1;
    double min = -1;
    for(int r = 0; r < weight.nRows; r++) {
        for(int c = 0; c < weight.nCols; c++) {
            if(max == -1 || weight[r][c] > max) {
                max = weight[r][c];
            }
            if(min == -1 || weight[r][c] < min) {
                min = weight[r][c];
            }
        }
    }
    Grid<int> viz(weight.nRows, weight.nCols);
    for(int r = 0; r < weight.nRows; r++) {
        for(int c = 0; c < weight.nCols; c++) {
            double s = (weight[r][c] - min) / (max - min);
            viz[r][c] = 256 * 256 *  256 * s;
        }
    }
    return viz;
}


int main() {
    cout << "Welcome to Seam Carving!" << endl;
    GBufferedImage original, carved;
    string fileName = getLine("Enter name of image file to open (or blank to quit): ");
    openImageFromFilename(original, fileName);
    //openImageFromFilename(carved, fileName);
    GWindow gw;
    gw.requestFocus();
    gw.setTitle("Seam Carving");
    gw.setVisible(true);
    gw.add(&original,0,0);
    gw.setCanvasSize(original.getWidth(), original.getHeight());

    seamCarve(original);
    return 0;
}

/* Function: Open Image From FileName
 * ----------------------------------
 * This function returns true when the image file was successfully
 * opened and the 'img' object now contains that image, otherwise it
 * returns false.
 */
bool openImageFromFilename(GBufferedImage& img, string filename) {
    try { img.load(filename); }
    catch (...) { return false; }
    return true;
}
