//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  kissrng.cpp (libcoyotl)
//
//  A multiply with carry psudeorandom number generator, as suggested
//  by George Marsaglia in Januray 2003. The original message can be
//  found at:
//
//  http://forums.wolfram.com/mathgroup/archive/2003/Jan/msg00355.html
//
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

#include "kissrng.h"
using namespace libcoyotl;

//--------------------------------------------------------------------------
//  Default constructor, reading seed from/dev/urandom or the time.
kissrng::kissrng()
  : prng()
{
    init_helper();
}

//--------------------------------------------------------------------------
//  Constructor
kissrng::kissrng(uint32_t seed)
  : prng(seed)
{
    init_helper();
}

//--------------------------------------------------------------------------
//  Initializes the generator with "seed"
void kissrng::init(uint32_t seed)
{
    prng::init(seed);
    init_helper();
}
//--------------------------------------------------------------------------
//  Initializes the generator with "seed"
void kissrng::init_helper()
{
    // Use Knuth's algorithms to set initial values from seed
    static const uint32_t K = 1812433253UL;
    m_c = K * (m_seed ^ (m_seed >> 30)) + 1;
    m_x = K * (m_c ^ (m_c >> 30)) + 2;
    m_y = K * (m_x ^ (m_x >> 30)) + 3;
    m_z = K * (m_y ^ (m_y >> 30)) + 5;
}

//--------------------------------------------------------------------------
//   Obtain the next 32-bit integer in the psuedo-random sequence
uint32_t kissrng::get_rand()
{
    static const uint64_t A = 698769069ULL;
    
    m_x = 69069 * m_x + 12345;
    m_y ^= ( m_y << 13);
    m_y ^= ( m_y >> 17);
    m_y ^= ( m_y <<  5);
    
    uint64_t temp = A * m_z + m_c;
    m_c = (temp >> 32);

    return m_x + m_y + (m_z = temp);
}
