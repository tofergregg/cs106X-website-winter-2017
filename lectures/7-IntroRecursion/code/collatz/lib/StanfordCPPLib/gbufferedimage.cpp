/*
 * File: gbufferedimage.cpp
 * ------------------------
 * This file implements the gbufferedimage.h interface.
 * See that file for documentation of each member.
 *
 * author: Marty Stepp
 * version: 2014/08/04
 */

#include "gbufferedimage.h"
#include <iomanip>
#include "gwindow.h"
#include "platform.h"
using namespace std;

static Platform* pp = getPlatform();

GBufferedImage::GBufferedImage(double width, double height) {
    init(0, 0, width, height, 0x000000);
}

GBufferedImage::GBufferedImage(double x, double y, double width, double height,
                               int rgbBackground) {
    init(x, y, width, height, rgbBackground);
}

GBufferedImage::GBufferedImage(double x, double y, double width, double height,
                               std::string rgbBackground) {
    init(x, y, width, height, convertColorToRGB(rgbBackground));
}

GRectangle GBufferedImage::getBounds() const {
    return GRectangle(x, y, m_width, m_height);
}

string GBufferedImage::getType() const {
    return "GBufferedImage";
}

string GBufferedImage::toString() const {
    return "GBufferedImage()";
}

void GBufferedImage::fill(int rgb) {
    checkColor("fill", rgb);
    m_pixels.fill(rgb);
    pp->gbufferedimage_fill(this, rgb);
}

void GBufferedImage::fill(string rgb) {
    fill(convertColorToRGB(rgb));
}

void GBufferedImage::fillRegion(double x, double y, double width, double height, int rgb) {
    checkIndex("fillRegion", x, y);
    checkIndex("fillRegion", x + width - 1, y + height - 1);
    checkColor("fillRegion", rgb);
    for (int r = (int) y; r < y + height; r++) {
        for (int c = (int) x; c < x + width; c++) {
            m_pixels[r][c] = rgb;
        }
    }
    pp->gbufferedimage_fillRegion(this, x, y, width, height, rgb);
}

void GBufferedImage::fillRegion(double x, double y, double width, double height, std::string rgb) {
    fillRegion(x, y, width, height, convertColorToRGB(rgb));
}

double GBufferedImage::getHeight() const {
    return m_height;
}

int GBufferedImage::getRGB(double x, double y) const {
    checkIndex("getRGB", x, y);
    return m_pixels[(int) y][(int) x];
}

string GBufferedImage::getRGBString(double x, double y) const {
    return convertRGBToColor(getRGB(x, y));
}

double GBufferedImage::getWidth() const {
    return m_width;
}

void GBufferedImage::setRGB(double x, double y, int rgb) {
    checkIndex("setRGB", x, y);
    checkColor("setRGB", rgb);
    m_pixels[(int) y][(int) x] = rgb;
    pp->gbufferedimage_setRGB(this, x, y, rgb);
}

void GBufferedImage::setRGB(double x, double y, string rgb) {
    setRGB(x, y, convertColorToRGB(rgb));
}

void GBufferedImage::checkColor(std::string member, int rgb) const {
    if (rgb < 0x0 || rgb > 0xffffff) {
        error("GBufferedImage::" + member
              + ": color is outside of range 0x000000 through 0xffffff");
    }
}

void GBufferedImage::checkIndex(string member, double x, double y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        error("GBufferedImage::" + member
              + ": (x=" + integerToString((int) x)
              + ", y=" + integerToString((int) y)
              + " is out of valid range of (0, 0) through ("
              + integerToString((int) m_width) + ", "
              + integerToString((int) m_height) + ")");
    }
}

void GBufferedImage::init(double x, double y, double width, double height,
                          int rgb) {
    if (width < 0 || height < 0) {
        error("GBufferedImage::constructor: width/height cannot be negative");
    }
    checkColor("constructor", rgb);
    this->x = x;
    this->y = y;
    this->m_width = width;
    this->m_height = height;
    this->m_pixels.resize((int) this->m_height, (int) this->m_width);
    pp->gbufferedimage_constructor(this, x, y, width, height);

    if (x != 0 || y != 0) {
        setLocation(x, y);
    }
    if (rgb != 0) {
        if (rgb != 0x0) {
            fill(rgb);
        }
    }
}
