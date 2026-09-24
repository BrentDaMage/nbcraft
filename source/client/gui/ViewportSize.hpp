#pragma once

struct ViewportSize
{
    struct Size {
        Size(unsigned int width, unsigned int height)
            : width(width)
            , height(height)
        {
        }
        
        unsigned int width, height;
    };
    
    ViewportSize(unsigned int physicalWidth, unsigned int physicalHeight, unsigned int logicalWidth, unsigned int logicalHeight)
        : physical(physicalWidth, physicalHeight)
        , logical(logicalWidth, logicalHeight)
    {
    }
    
	// the resolution the game is rendered at
    Size physical;
    
	// the resolution the GUI is scaled at
    Size logical;
};