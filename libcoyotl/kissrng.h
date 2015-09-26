//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  kissrng.cpp (libcoyotl)
//
//  The popular "Keep It Simple Stupid" psuedorandom number generator.
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

#if !defined(LIBCOYOTL_KISSRNG_H)
#define LIBCOYOTL_KISSRNG_H

#include "prng.h"

namespace libcoyotl
{
    //! Implements KISS, a peudorandom number generator
    /*!
        The popular "Keep It Simple Stupid" psuedorandom number generator.
        It has a period of around 2^125, which is shorter than most other
        algorithms, but certainly adequate for many applications.
    */
    class kissrng : public prng
    {
    private:
        uint32_t m_x;
        uint32_t m_y;
        uint32_t m_z;
        uint32_t m_c;

    public:
        //! Default constructor, reading seed from/dev/urandom or the time.
        /*!
            The constructor initializes the prng seed from either the time
            or some stochastic source such as /dev/random or /dev/urandom.
        */
        kissrng();

        //! Default constructor, with optional seed.
        /*!
            The constructor uses an explicit value for the seed.
            \param seed - Seed value used to "start" or seed the generator
        */
        kissrng(uint32_t seed);

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
