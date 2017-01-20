

#include <iostream>
#include <cfloat> // for DBL_MAX
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
using namespace std;

void toonShade(GBufferedImage & img);
Vector<int> getColorPalette();
int getClosestColor(Vector<int> & palette, int original);
double getColorDistance(int color1, int color2);
void putImageInWindow(GWindow & gw, GBufferedImage & img, string title);
void showPalette(Vector<int> &palette);

bool openImageFromFilename(GBufferedImage& img, string filename);

int main() {
    setConsoleFont("Courier-24");
    cout << "Welcome to Toon Shader!" << endl;

    // load the image
    GBufferedImage img;
    string fileName = getLine("Enter name of image file to open (or blank to quit): ");
    openImageFromFilename(img, fileName);
    GWindow originalWindow;
    putImageInWindow(originalWindow, img, "Original");

    // copy the image and apply filter
    GBufferedImage filtered;
    filtered.fromGrid(img.toGrid());
    toonShade(filtered);
    GWindow filteredWindow;
    putImageInWindow(filteredWindow, filtered, "Filtered");

    return 0; // success!
}

/* Function: Toon Shade
 * ----------------------------------
 * This function takes in a picture and a palette and recolors
 * each pixel (to be the closest color from the palette).
 */
void toonShade(GBufferedImage & img) {
    Vector<int> palette = getColorPalette();
    showPalette(palette);
    Grid<int> pixels = img.toGrid();
    for (int r = 0; r < pixels.numRows(); r++) {
        for (int c = 0; c < pixels.numCols(); c++) {
            pixels[r][c] = getClosestColor(palette,pixels[r][c]);
        }
    }
    img.fromGrid(pixels);
}

/* Function: Get Closest Color
 * ----------------------------------
 * This function returns the color from the palette that is
 * closest to the original
 */
int getClosestColor(Vector<int> & palette, int pixel) {
    double minDist = DBL_MAX; // highest possible value
    int best; // the best color
    for (int color : palette) {
        double dist = getColorDistance(color, pixel);
        if (dist < minDist) {
            minDist = dist;
            best = color;
        }
    }
    return best;
}

/* Function: Get Color Distance
 * ----------------------------------
 * This function returns the L2 norm (euclidean distance) between
 * the two colors passed in.
 */
double getColorDistance(int color1, int color2) {
    int r1, g1, b1, r2, g2, b2;
    GBufferedImage::getRedGreenBlue(color1,	r1, g1, b1);
    GBufferedImage::getRedGreenBlue(color2,	r2, g2, b2);
    int diffRed = r2 - r1;
    int diffBlue = b2 - b1;
    int diffGreen = g2 - g1;
    return sqrt(diffRed * diffRed + diffBlue * diffBlue + diffGreen * diffGreen);
}

/* Function: Get Toon Colors
 * ----------------------------------
 * This function returns the eight colors in the palette that we
 * will be using.
 * You can find lots of palettes at http://www.colourlovers.com
 */
Vector<int> getColorPalette() {
    // good example for mlk2.png:
    // #50514f,#f25f5c,#ffe066,#247ba0,#70c1b3
    // also good:
    // #655643,#80BCA3,#F6F7BD,#E6AC27,#BF4D28,#655643,#80BCA3,#F6F7BD
    // hope:
    // #04182B,#5A8C8C,#F2D99D,#738585,#AB1111,#04182B,#5A8C8C,#F2D99D

    Vector<int> colors;

    string colorSt = getLine("Please enter a list of comma-separated "
                             "hexadecimal colors (e.g., #80BCA3,#F6F7BD): ");
    Vector<string>colorsStrVec = stringSplit(colorSt,",");
    for (string color : colorsStrVec) {
        colors.add(convertColorToRGB(color));
    }
    return colors;
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

/* Function: Put Image in Window
 * ----------------------------------
 * Makes the window contain exactly the image. Changes the window size
 * to be correct and does the magic needed to make sure there isn't a
 * race condition on the Stanford libraries.
 */
void putImageInWindow(GWindow & gw, GBufferedImage & img, string title) {
    gw.setTitle(title);
    gw.setVisible(true);
    gw.requestFocus();
    gw.add(&img,0,0);
    gw.setCanvasSize(img.getWidth(), img.getHeight());
}

void showPalette(Vector<int> &palette) {
    GWindow paletteWin;
    const int STRIP_WIDTH = 100;
    int width = palette.size() * STRIP_WIDTH;
    int height = 100;
    GBufferedImage paletteImg(width,height);
    for (int i=0; i < palette.size(); i++) {
        int color = palette[i];
        paletteImg.fillRegion(i*STRIP_WIDTH,0,STRIP_WIDTH,100,color);
    }

    putImageInWindow(paletteWin, paletteImg, "Palette");
}

