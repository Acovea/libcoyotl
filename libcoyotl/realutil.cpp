//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.libcoyotl.com
//
//  realutil.cpp (libcoyotl)
//
//  A collection of useful functions for working with numbers.
//---------------------------------------------------------------------
//
//  Copyright 1990-2005 Scott Robert Ladd
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the
//      Free Software Foundation, Inc.
//      59 Temple Place - Suite 330
//      Boston, MA 02111-1307, USA.
//
//-----------------------------------------------------------------------
//
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//  
//-----------------------------------------------------------------------

// Standard C++ library
#include <cfloat>

// libcoyotl
#include "realutil.h"

using namespace libcoyotl;

// lowest common denominator
unsigned long libcoyotl::lcm(unsigned long x, unsigned long y)
{
    unsigned long s, l;

    if (x == y)
        return x;

    if (x < y)
    {
        s = x;
        l = y;
    }
    else
    {
        l = x;
        s = y;
    }

    return (l / gcd(s,l)) * s;
}

// greatest common multiple
unsigned long libcoyotl::gcd(unsigned long x, unsigned long y)
{
    unsigned long temp;

    while (y != 0ul)
    {
        temp = x % y;
        x = y;
        y = temp;
    }

    return x;
}


