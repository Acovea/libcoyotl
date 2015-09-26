//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  mwc256.cpp (libcoyotl)
//
//  A multiply with carry psudeorandom number generator, as suggested
//  by George Marsaglia.
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

#if !defined(LIBCOYOTL_MWC256_H)
#define LIBCOYOTL_MWC256_H

#include "prng.h"

namespace libcoyotl
{
    //! Implements MWC256, a peudorandom number generator
    /*!
        A multiply with carry psudeorandom number generator, as suggested
        by George Marsaglia.
    */
    class mwc256 : public prng
    {
    private:
        // Period parameters
        static const size_t N = 256;

        // Working storage
        uint32_t m_q[N];
        uint32_t m_carry;
        uint8_t  m_index;

    public:
        //! Default constructor, reading seed from/dev/urandom or the time.
        /*!
            The constructor initializes the prng seed from either the time
            or some stochastic source such as /dev/random or /dev/urandom.
        */
        mwc256();

        //! Default constructor, with optional seed.
        /*!
            The constructor uses an explicit value for the seed.
            \param seed - Seed value used to "start" or seed the generator
        */
        mwc256(uint32_t seed);

        //! Initializes the generator with "seed"
        /*!
            Resets the generator using the provided seed value.
            \param seed - Seed value used to "start" or seed the generator
        */
        virtual void init(uint32_t seed);

    private:
        //! Initializes the generator with "seed"
        /*!
            Initializes internal tables based on the current seed value.
            \param seed - Seed value used to "start" or seed the generator
        */
        void init_helper();

    public:
        //!  Get the next integer
        /*!
            Returns the next uint32_t in sequence.
            \return A pseudorandom uint32_t value
        */
        virtual uint32_t get_rand();
    };

} // end namespace libcoyotl

#endif
