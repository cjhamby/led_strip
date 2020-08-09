/* 
 * palettes.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * a palette holds colors to be used together
*/

#include "colors.h"
#include "palettes.h"


/* IF YOU CHANGE A PALETTE SIZE 
 * YOU MUST ALSO CHANGE THE VALUES IN PALLETES.H
*/

long electricPalette[ELECTRIC_PALETTE_SIZE] = 
{
    YELLOW, 
    CORAL, 
    LIME, 
    SPRING_GREEN, 
    YELLOW_GREEN, 
    AQUA_MARINE, 
    PALE_GREEN
};

long coolPalette[COOL_PALETTE_SIZE] = 
{
    //MAROON, 
    BLUE, 
    NAVY, 
    INDIGO, 
    PURPLE, 
    MAGENTA, 
    //DARK_MAGENTA, 
    //DARK_ORCHID, 
    DARK_SLATE, 
    MIDNIGHT
};

long rainbowPalette[RAINBOW_PALETTE_SIZE] = 
{
    WHYTE, 
    YELLOW, 
    ORANGE, 
    PINK, 
    CORAL, 
    RED, 
    LIME, 
    GREEN, 
    CYAN, 
    TEAL, 
    NAVY,
    BLUE, 
    INDIGO, 
    PURPLE, 
    MAGENTA
};