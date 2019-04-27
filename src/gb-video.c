#include "gb-impl.h"

BYTE getColour(BYTE colourNum, BYTE palette) {
    BYTE hi = 0;
    BYTE lo = 0;

    lo = colourNum * 2;
    hi = lo+1;

    // use the palette to get the colour
    BYTE colour = 0;
    colour = ((palette >> (hi)) & 0x1) << 1;
    colour |= ((palette >> (lo)) & 0x1);

    return colour;
}

void renderTiles(gb *cpu) {
    WORD tileData = 0;
    WORD backgroundMemory = 0;
    BYTE unsig = 1;

    BYTE lcd_control = readMemory(cpu, LCD_REG_CONTROL);

    BYTE scrollY = readMemory(cpu, SCROLLY);
    BYTE scrollX = readMemory(cpu, SCROLLX);
    BYTE windowY = readMemory(cpu, WINDOWY);
    BYTE windowX = readMemory(cpu, WINDOWX);

    if (windowX < 7) {
        windowX = 7;
    }
    windowX -= 7;

    BYTE currentLine = readMemory(cpu, LCD_SCANLINE_ADRR);
    BYTE usingWindow = 0;

    /*The window is enabled and visible?*/
    if ((lcd_control & 0x20) != 0 && windowY <= currentLine)
        usingWindow = 1;

    // tile area ?
    if ((lcd_control & 0x10) != 0)
        tileData = 0x8000;
    else {
        // This memory region uses signed bytes
        tileData = 0x8800;
        unsig = 0;
    }

    BYTE yPos = 0;

    // yPos is used to calculate which of 32 vertical tiles the
    // current scanline is drawing
    if (usingWindow == 0)
        yPos = scrollY + currentLine;
    else {
        yPos = currentLine - windowY;
    }

    // which line of the tile is being rendered ?
    WORD tileRow = (yPos / 8) * 32;

    BYTE palette = readMemory(cpu, 0xFF47);
    BYTE colorMap[4] = {getColour(0, palette), getColour(1, palette),
                        getColour(2, palette), getColour(3, palette)};

    // Now I have to render the line, pixel by pixel
    for (BYTE pixel = 0; pixel < 160; pixel++) {
        BYTE xPos = pixel + scrollX;

        if ((lcd_control & 0x08) != 0)
            backgroundMemory = 0x9C00;
        else
            backgroundMemory = 0x9800;

        // translate the current x pos to window space if necessary
        if (usingWindow == 1) {
            if (pixel >= windowX) {
                // This means I'm in the window
                xPos = pixel - windowX;
                if ((lcd_control & 0x40) != 0)
                    backgroundMemory = 0x9c00;
                else
                    backgroundMemory = 0x9800;
            }
        }

        // which of the 32 horizontal tiles does this xPos fall within?
        WORD tileCol = (xPos / 8);
        WORD tileNum;

        WORD tileAddrss = backgroundMemory + tileRow + tileCol;
        if (unsig == 1)
            tileNum = (BYTE)readMemory(cpu, tileAddrss);
        else {
            tileNum =
                ((SIGNED_WORD)readMemory(cpu, tileAddrss) + (SIGNED_WORD)128) &
                0xff;
        }

        // deduce where this tile identifier is in memory.
        WORD tileLocation = tileData + (tileNum * 16);

        BYTE line = yPos % 8;
        line *= 2; // each line takes two bytes
        BYTE data1 = readMemory(cpu, tileLocation + line);
        BYTE data2 = readMemory(cpu, tileLocation + line + 1);

        BYTE colourBit = xPos % 8;
        colourBit -= 7;
        colourBit *= -1;

        BYTE colourNum = (data2 >> (colourBit)) & 0x1;
        colourNum <<= 1;
        colourNum |= ((data1 >> (colourBit)) & 0x1);

        BYTE col = colorMap[colourNum];

        cpu->screenData[currentLine][pixel] = col;
    }
}

void renderSprites(gb *cpu) {
    BYTE ysize = 8;
    BYTE currentLine = readMemory(cpu, 0xFF44);
    BYTE lcd_control = readMemory(cpu, LCD_REG_CONTROL);
    if ((lcd_control & 0x4) != 0)
        ysize = 16;

    /*Explore all the sprite table*/
    /*Each sprite is formed by 4 bytes:
     * 0 : y pos - 16
     * 1 : x pos - 8
     * 2 : data location in memory
     * 3 : several flags
     */
    for (BYTE index = 0; index < 40 * 4; index += 4) {
        BYTE yPos = readMemory(cpu, 0xFE00 + index) - 16;

        if ((currentLine < yPos) || (currentLine >= (yPos + ysize)))
            continue;

        BYTE xPos = readMemory(cpu, 0xFE00 + index + 1) - 8;

        if (xPos > 160)
            continue;

        BYTE tileLocation = readMemory(cpu, 0xFE00 + index + 2);
        BYTE attributes = readMemory(cpu, 0xFE00 + index + 3);

        BYTE yFlip = attributes & 0x40;
        BYTE xFlip = attributes & 0x20;

        // does this sprite intercept with the scanline?
        BYTE line = currentLine - yPos;

        // read the sprite in backwards in the y axis
        if (yFlip != 0) {
            line -= ysize;
            line *= -1;
        }

        line *= 2; // same as for tiles
        WORD dataAddress = (0x8000 + (tileLocation * 16)) + line;
        BYTE data1 = readMemory(cpu, dataAddress);
        BYTE data2 = readMemory(cpu, dataAddress + 1);

        // its easier to read in from right to left as pixel 0 is
        // bit 7 in the colour data, pixel 1 is bit 6 etc...
        for (SIGNED_BYTE tilePixel = 7; tilePixel >= 0; tilePixel--) {
            /*Should do some refactoring for avoiding this signed pixel*/
            SIGNED_BYTE colourbit = tilePixel;
            // read the sprite in backwards for the x axis
            if (xFlip != 0) {
                colourbit -= 7;
                colourbit *= -1;
            }

            BYTE colourNum = (data2 >> (colourbit)) & 0x1;
            colourNum <<= 1;
            colourNum |= ((data1 >> (colourbit)) & 0x1);

            /*Must ignore the alpha color*/
            if (colourNum == 0)
                continue;

            WORD colourAddress;
            if ((attributes & 0x10) != 0)
                colourAddress = 0xFF49;
            else
                colourAddress = 0xFF48;

            BYTE palette = readMemory(cpu, colourAddress);
            BYTE col = getColour(colourNum, palette);

            SIGNED_BYTE xPix = 0 - tilePixel;
            xPix += 7;
            BYTE pixel = xPos + (BYTE)xPix;

            if (pixel > 160 || currentLine > 144)
                continue;

            // check if pixel is hidden behind background
            if ((attributes & 0x80) != 0 &&
                cpu->screenData[currentLine][pixel] != 0) {
                continue;
            }
            /*I can draw the pixel*/
            cpu->screenData[currentLine][pixel] = col;
        }
    }
}

void drawScanline(gb *cpu) {
    BYTE control = readMemory(cpu, LCD_REG_CONTROL);
    if ((control & 0x1) != 0)
        renderTiles(cpu);

    if ((control & 0x2) != 0)
        renderSprites(cpu);
}

void updateLCD(gb *cpu) {
    BYTE status = readMemory(cpu, LCD_REG_STATUS);
    BYTE lcd_control = readMemory(cpu, LCD_REG_CONTROL);

    /*LCD is disabled*/
    if ((lcd_control & 0x80) == 0) {
        // set the mode to 1 during lcd disabled and reset scanline
        cpu->clockScanline = 456;
        cpu->memory[0xFF44] = 0;
        status &= 252;
        status |= 0x1;
        writeMemory(cpu, LCD_REG_STATUS, status);
        return;
    }

    BYTE currentline = readMemory(cpu, LCD_SCANLINE_ADRR);
    BYTE mode = status & 0x3;

    BYTE nextMode = 0;
    BYTE reqInt = 0;

    // in vblank so set mode to 1
    if (currentline >= 144) {
        nextMode = 1;
        status &= ~(0x3);
        status |= 0x1;
        reqInt = status & 0x10;
    } else {
        // mode 2
        if (cpu->clockScanline >= 376) {
            nextMode = 2;
            status &= ~(0x3);
            status |= 0x2;
            reqInt = status & 0x20;
        }
        // mode 3
        else if (cpu->clockScanline >= 204) {
            nextMode = 3;
            status &= ~(0x3);
            status |= 0x3;
        }
        // mode 0
        else {
            nextMode = 0;
            status &= ~(0x3);
            reqInt = status & 0x8;
        }
    }

    if ((reqInt != 0) && (mode != nextMode))
        raiseInterrupt(cpu, 1);

    // check the conincidence flag
    if (readMemory(cpu, 0xFF44) == readMemory(cpu, 0xFF45)) {
        status |= 0x4;
        if ((status & 0x40) != 0)
            raiseInterrupt(cpu, 1);
    } else {
        status &= ~(0x4);
    }
    writeMemory(cpu, LCD_REG_STATUS, status);
}

void handleGraphic(gb *cpu, BYTE cycles) {
    updateLCD(cpu);
    BYTE lcd_control = readMemory(cpu, LCD_REG_CONTROL);

    if ((lcd_control & 0x80) != 0) {
        cpu->clockScanline -= cycles;
    } else
        return;

    if (cpu->clockScanline <= 0) {
        cpu->memory[LCD_SCANLINE_ADRR]++;
        BYTE currentline = readMemory(cpu, LCD_SCANLINE_ADRR);
        cpu->clockScanline = 456;

        /*V-blank interrupt*/
        if (currentline == 144)
            raiseInterrupt(cpu, 0);

        else if (currentline > 153)
            cpu->memory[LCD_SCANLINE_ADRR] = 0;

        else if (currentline < 144)
            drawScanline(cpu);
    }
}

BYTE getPixelColor(gb *cpu, BYTE x, BYTE y) {
    BYTE col = cpu->screenData[y][x];
    BYTE color = 0;
    switch (col) {
    case 0:
        color = BLACK_COL;
        break;
    case 1:
        color = GRAY_COL;
        break;
    case 2:
        color = LIGHTGRAY_COL;
        break;
    case 3:
        color = WHITE_COL;
        break;
    }
    return color;
}
