//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  mwc256.cpp (libcoyotl)
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

#include "mwc256.h"
using namespace libcoyotl;

//--------------------------------------------------------------------------
//  Default constructor, reading seed from/dev/urandom or the time.
mwc256::mwc256()
  : prng()
{
    init_helper();
}

//--------------------------------------------------------------------------
//  Constructor
mwc256::mwc256(uint32_t seed)
  : prng(seed)
{
    init_helper();
}

//--------------------------------------------------------------------------
//  Initializes the generator with "seed"
void mwc256::init(uint32_t seed)
{
    prng::init(seed);
    init_helper();
}
//--------------------------------------------------------------------------
//  Initializes the generator with "seed"
void mwc256::init_helper()
{
    // Save seed for historical purpose
    m_q[0] = m_seed;
    
    // Set the array using one of Knuth's generators
    for (int i = 1; i < N; ++i)
        m_q[i] = 1812433253UL * (m_q[i - 1] ^ (m_q[i - 1] >> 30)) + i;
       
    m_carry = m_q[N-1] % 61137367UL;
    m_index = N - 1;
}

//--------------------------------------------------------------------------
//   Obtain the next 32-bit integer in the psuedo-random sequence
uint32_t mwc256::get_rand()
{
    uint32_t result;
    
    static const uint64_t A = 1540315826ULL;
    
    uint64_t temp = A * m_q[++m_index]+ m_carry;
    m_carry = (temp >> 32);
    uint32_t x = temp + m_carry;
    
    if (x < m_carry)
    {
        ++x;
        ++m_carry;
    }
    
    return m_q[m_index] = x;
}
