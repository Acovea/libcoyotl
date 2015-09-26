//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  mwc1038.cpp (libcoyotl)
//
//  A multiply with carry psudeorandom number generator, as suggested
//  by George Marsaglia in Januray 2003. The original message can be
//  found at:
//
//  http://forums.wolfram.com/mathgroup/archive/2003/Jan/msg00355.html
//
//---------------------------------------------------------------------
//
//  COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
//
//  This notice applies *only* to this specific expression of this
//  algorithm, and does not imply ownership or invention of the
//  implemented algorithm.
//  
//  If you modify this file, you may insert additional notices
//  immediately following this sentence.
//  
//  Copyright 2001-2004 Scott Robert Ladd.
//  All rights reserved, except as noted herein.
//
//  This computer program source file is supplied "AS IS". Scott Robert
//  Ladd (hereinafter referred to as "Author") disclaims all warranties,
//  expressed or implied, including, without limitation, the warranties
//  of merchantability and of fitness for any purpose. The Author
//  assumes no liability for direct, indirect, incidental, special,
//  exemplary, or consequential damages, which may result from the use
//  of this software, even if advised of the possibility of such damage.
//  
//  The Author hereby grants anyone permission to use, copy, modify, and
//  distribute this source code, or portions hereof, for any purpose,
//  without fee, subject to the following restrictions:
//  
//      1. The origin of this source code must not be misrepresented.
//  
//      2. Altered versions must be plainly marked as such and must not
//         be misrepresented as being the original source.
//  
//      3. This Copyright notice may not be removed or altered from any
//         source or altered source distribution.
//  
//  The Author specifically permits (without fee) and encourages the use
//  of this source code for entertainment, education, or decoration. If
//  you use this source code in a product, acknowledgment is not required
//  but would be appreciated.
//  
//  Acknowledgement:
//      This license is based on the wonderful simple license that
//      accompanies libpng.
//
//-----------------------------------------------------------------------
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//-----------------------------------------------------------------------

#if !defined(LIBCOYOTL_MWC1038_H)
#define LIBCOYOTL_MWC1038_H

#include "prng.h"

namespace libcoyotl
{
    //! Implements MWC1038, a peudorandom number generator
    /*!
        The mwc1038 class encapsulates a multiply-with-carry algorithm
        for psuedorandom number generation, as suggested by George 
        Marsaglia in a posting found here:
        
        http://forums.wolfram.com/mathgroup/archive/2003/Jan/msg00355.html
    */
    class mwc1038 : public prng
    {
    private:
        // Period parameters
        static const size_t N = 1038;

        // Working storage
        uint32_t m_q[N];
        uint32_t m_carry;
        int      m_index;

    public:
        //! Default constructor, reading seed from/dev/urandom or the time.
        /*!
            The constructor initializes the prng seed from either the time
            or some stochastic source such as /dev/random or /dev/urandom.
        */
        mwc1038();

        //! Default constructor, with optional seed.
        /*!
            The constructor uses an explicit value for the seed.
            \param seed - Seed value used to "start" or seed the generator
        */
        mwc1038(uint32_t seed);

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
