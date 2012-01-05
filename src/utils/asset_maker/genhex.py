#!/usr/env python
import argparse
import os
import math
from PIL import Image, ImageDraw

class Hex:
    
    def __init__(self, size):
        self.s = size
        radians = math.radians(30)
        self.h = int(round(math.sin(radians) * size))
        self.r = int(round(math.cos(radians) * size))
        self.rect_height = size + 2 * self.h
        self.rect_width = 2 * self.r

    def genImage(self, imagePath, backgroundColor, lineColor):
        im = Image.new("RGB", (self.rect_width, self.rect_height), backgroundColor)
        draw = ImageDraw.Draw(im)
        draw.polygon((0,self.h) + (self.rect_width/2,0) + (self.rect_width-1, self.h) + (self.rect_width-1, self.s + self.h - 1) + (self.rect_width/2, self.rect_height-1) + (0, self.s + self.h - 1), outline=lineColor)
        del draw
        im.save(imagePath)        
    
    def __str__(self):
        return "H:%f R:%f A:%f B:%f" % (self.h, self.r, self.rect_height, self.rect_width)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='This tool is used to generate hex sprites.')
    parser.add_argument('-f','--file', help='Output image file', required=True)
    parser.add_argument('-s','--size', help='Hexagon side size in pixels', type=int, required=True)
    parser.add_argument('-b','--bg', help='Background color', nargs=3, metavar=('R', 'G', 'B'), default=[128, 0, 128])
    parser.add_argument('-c', '--color', help='Line color', nargs=3, metavar=('R', 'G', 'B'), default=[125, 125, 125])

    args = parser.parse_args()
    filePath = os.path.abspath(args.file)
    size = args.size
    backgroundColor = tuple(args.bg)
    lineColor = tuple(args.color)

    hx = Hex(size)
    hx.genImage(filePath, backgroundColor, lineColor)
