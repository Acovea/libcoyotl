//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  crccalc.h (libcoyotl)
//
//  Defines tools for calculating 32-bit cyclic-redundancy (CRC)
//  values from arrays of 8-bit byte data.
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
#include <cstddef>

// libcoyotl
#include "crccalc.h"
using namespace libcoyotl;

// initialize a CRC table of precalculated values
crc_calculator::crc_precalc::crc_precalc()
{
    for (crc32_t n = 0; n < 256; ++n)
    {
        crc32_t c = n; // c will be the constant for n

        // assumes 8-bit bytes
        for (int bit = 0; bit < 8; ++bit)
        {
            if (c & 1)
                c = 0xEDB88320L ^ (c >> 1);
            else
                c >>= 1;
        }

        m_table[n] = c;
    }
}

// static member initialization
crc_calculator::crc_precalc crc_calculator::s_table;

// constructor
crc_calculator::crc_calculator()
{
    // initialize CRC value
    m_crc = 0xFFFFFFFFL;
}

// update CRC value based on an array of bytes
void crc_calculator::update(const unsigned char * data, size_t len)
{
    if (data == NULL)
        return;

    for (size_t n = 0; n < len; ++n)
        m_crc = s_table[(m_crc ^ data[n]) & 0xFF] ^ (m_crc >> 8);
}

