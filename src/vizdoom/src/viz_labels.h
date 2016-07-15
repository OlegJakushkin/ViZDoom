/*
 Copyright (C) 2016 by Wojciech Jaśkowski, Michał Kempka, Grzegorz Runc, Jakub Toczek, Marek Wydmuch

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#ifndef __VIZ_LABELS_H__
#define __VIZ_LABELS_H__

//UNCOMMENT TO ENABLE LABELS BUFFER DEBUG WINDOW
//#define VIZ_LABELS_TEST 1

//UNCOMMENT TO ENABLE COLOR-BASED LABELS TEST
//#define VIZ_LABELS_COLORS 1

#include "basictypes.h"
#include "doomtype.h"
#include "actor.h"

#include "r_main.h"
#include "r_plane.h"
#include "r_draw.h"
#include "r_things.h"
#include "r_3dfloors.h"
#include "a_sharedglobal.h"
#include "g_level.h"

#include <vector>

#ifdef VIZ_LABELS_TEST
#include <SDL_video.h>
#endif

#define VIZ_MAX_LABELS 256
#define VIZ_MAX_LABEL_NAME_LEN 128

struct VIZToLabel{
    AActor* actor;
    bool psrpite;
    vissprite_t* vissprite;
    BYTE label;
};

struct VIZLabel{
    int id;
    char name[VIZ_MAX_LABEL_NAME_LEN];
    BYTE label;
};

class VIZLabelsBuffer{
public:

    VIZLabelsBuffer(unsigned int width, unsigned int height);
    ~VIZLabelsBuffer();

    BYTE *getBuffer();
    BYTE *getBufferPoint(unsigned int x, unsigned int y);
    void setPoint(unsigned int x, unsigned int y, BYTE label);
    void setPoint(unsigned int x, unsigned int y);
    unsigned int getBufferSize();
    unsigned int getBufferWidth();
    unsigned int getBufferHeight();
    void clearBuffer();
    void clearBuffer(BYTE color);
    void lock();
    void unlock();
    bool isLocked();
    void sizeUpdate();

    void addSprite(AActor *thing, vissprite_t* vis);
    void addPSprite(AActor *thing, vissprite_t* vis);
    BYTE getLabel(vissprite_t* vis);
    void setLabel(BYTE label);

    #ifdef VIZ_LABELS_TEST
        void testUpdate();
    #endif

private:

    BYTE *buffer;
    unsigned int bufferSize;
    unsigned int bufferWidth;
    unsigned int bufferHeight;

    int tX, tY;
    bool locked;

    BYTE labeled;
    BYTE nextLabel;
    BYTE currentLabel;
    std::vector<VIZToLabel> toLabel;

    #ifdef VIZ_LABELS_TEST
        SDL_Window* window;
        SDL_Surface* surface;
        SDL_Color colors[256];
    #endif
};

extern VIZLabelsBuffer* vizLabels;
#endif
