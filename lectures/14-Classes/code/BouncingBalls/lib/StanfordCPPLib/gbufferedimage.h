/*
 * File: gbufferedimage.h
 * ----------------------
 * This file exports the GBufferedImage class for per-pixel graphics.
 *
 * author: Marty Stepp
 * version: 2014/08/04
 * since: 2014/08/04
 */

#ifndef _gbufferedimage_h
#define _gbufferedimage_h

#include "grid.h"
#include "gobjects.h"
#include "gtypes.h"

/*
 * This class implements a 2D region of colored pixels that can be read/set
 * individually, not unlike the <code>BufferedImage</code> class in Java.
 * The color of each pixel in a <code>GBufferedImage</code> is represented
 * as a 32-bit integer as described by the <code>GWindow</code> function
 * <code>convertRGBToColor</code></a>, where:
 *
 * - bits 0-7 are unused;
 * - bits 8-15 represent the redness of the color, from 0 (none) through 255 (full);
 * - bits 16-23 represent the greenness of the color, from 0 (none) through 255 (full);
 * - and bits 24-31 represent the blueness of the color, from 0 (none) through 255 (full).
 *
 * For example, the integer <code>0xff00cc</code> is a purple color, while
 * <code>0x770000</code> is a dark red.
 * A <code>GBufferedImage</code> will also let you represent colors as hex strings
 * such as <code>"#ff00cc"</code> instead of as integers.
 * String colors are always converted to integer colors internally by calling the
 * <code>GWindow</code> function <code>convertColorToRGB</code>.
 * Therefore some common color names like "black" can be passed successfully
 * in lieu of the usual hex format; see that function for more details.
 *
 * Though the x, y, width, and height parameters to the constructor and several
 * methods are received as type <code>double</code> for maximum compatibility
 * with other classes in this library, they should be thought of as
 * integer coordinates.  Any real numbers passed will be internally truncated
 * into integers by discarding any fractional component (by type-casting from
 * <code>double</code> to <code>int</code>).
 *
 * Note that per-pixel graphics operations using the Stanford C++ library are
 * relatively slow.  A call to the <code>fill</code> method is relatively
 * efficient, and a call to <code>getRGB</code> is also efficient since pixels'
 * colors are cached locally.  But calling <code>setRGB</code> repeatedly over
 * a large range of pixels is likely to yield poor performance.
 * This is due to the fact that the graphics are implemented using a background
 * Java process to which all graphical commands are forwarded.
 * The <code>GBufferedImage</code> class is not performant enough to be used
 * for rapidly advancing animations or extremely complex graphical effects.
 * It also does not provide any drawing primitives other than filling
 * individual pixels and rectangular regions.
 * If you want to draw shapes and lines, use other classes from this library
 * such as GRect, GLine, and so on.
</p>

<p class="since">
    Available since: 2014/08/04 version of C++ library
</p>
 */
class GBufferedImage : public GObject {
public:
    /*
     * Constructs an image with the specified location, size, and optional
     * background color.
     * If no location is passed, the default of (x=0, y=0) is used.
     * If no background color is passed, the default of black (0x0) is used.
     * Throws an error if the given width/height ranges are negative.
     * Throws an error if the given rgb value is invalid or out of range.
     */
    GBufferedImage(double width, double height);
    GBufferedImage(double x, double y, double width, double height,
                   int rgbBackground = 0x000000);
    GBufferedImage(double x, double y, double width, double height,
                   std::string rgbBackground);

    /* Prototypes for the virtual methods */
    virtual GRectangle getBounds() const;
    virtual std::string getType() const;
    virtual std::string toString() const;

    /* unique GBufferedImage behavior */

    /*
     * Sets the color of every pixel in the image to the given color value.
     * Throws an error if the given rgb value is not a valid color.
     */
    void fill(int rgb);
    void fill(std::string rgb);

    /*
     * Sets the color of every pixel in the given rectangular range of the image
     * to the given color value.
     * Specifically, the pixels in the rectangular range (x, y) through
     * (x + width - 1, y + height - 1) become filled with the given color.
     * Throws an error if the given x/y/width/height range goes outside the bounds
     * of the image.
     * Throws an error if the given rgb value is not a valid color.
     */
    void fillRegion(double x, double y, double width, double height, int rgb);
    void fillRegion(double x, double y, double width, double height,
                    std::string rgb);

    /*
     * Returns the height of the image in pixels.
     */
    double getHeight() const;

    /*
     * Returns the color of the pixel at the given x/y coordinates of the image
     * as an integer such as 0xff00cc.
     * Throws an error if the given x/y values are out of bounds.
     */
    int getRGB(double x, double y) const;

    /*
     * Returns the color of the pixel at the given x/y coordinates of the image
     * as a string such as "#ff00cc".
     * The string that is returned comes from the <code>GWindow</code> function
     * <code>convertRGBToColor</code>; see documentation of that function.
     * Throws an error if the given x/y values are out of bounds.
     */
    std::string getRGBString(double x, double y) const;

    /*
     * Returns the width of the image in pixels.
     */
    double getWidth() const;

    /*
     * Sets the color of the pixel at the given x/y coordinates of the image
     * to the given value.
     * Implementation/performance note: Each call to this method produces a
     * call to the Java graphical back-end.  Calling this method many times
     * in a tight loop can lead to poor performance.  If you need to fill a
     * large rectangular region, consider calling fill or fillRegion instead.
     * Throws an error if the given x/y values are out of bounds.
     * Throws an error if the given rgb value is not a valid color.
     */
    void setRGB(double x, double y, int rgb);
    void setRGB(double x, double y, std::string rgb);

private:
    double m_width;
    double m_height;
    Grid<int> m_pixels;

    /*
     * Throws an error if the given rgb value is not a valid color.
     */
    void checkColor(std::string member, int rgb) const;

    /*
     * Throws an error if the given x/y values are out of bounds.
     */
    void checkIndex(std::string member, double x, double y) const;

    /*
     * Initializes private member variables; called by all constructors.
     */
    void init(double x, double y, double width, double height, int rgb);
};

#endif
