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

#if !defined(LIBCOYOTL_CRCCALC_H)
#define LIBCOYOTL_CRCCALC_H

namespace libcoyotl
{
    //! 32-bit unsigned value for holding CRC value
    typedef unsigned long crc32_t;
    
    //! Calculate 32-bit CRC values from byte data
    /*!
        Calculates a 32-bit CRC value using the algorithm specified by 
        ISO 3309, and as used by the PNG graphics specification.
        \version 1.1.0
        \date    15 June 2002
    */
    class crc_calculator
    {
        // internal class for preclaculated table
        private:
            class crc_precalc  
            {
            public:
                // constructor
                crc_precalc();
            
                // return element of table
                crc32_t operator [] (int n) const
                {
                    return m_table[n];
                }
            
            protected:
                // table of precalculated values
                crc32_t m_table[256];
            };
        
        public:
            //! Constrctor
            /*!
                Constructs a new CRC value with a base value of 0xFFFFFFFF.
            */
            crc_calculator();
        
            //! Update CRC for a given data set
            /*!
                Updates the crc value from the bytes provided in <i>data</i>.
                Each time this function is called for a given crc_calculator,
                the 32-bit CRC value changes to reflect the new bytes.
                \param a_data - Array of bytes to be "added" to the CRC value
                \param a_length - Number of bytes in the <i>data</i> array
            */  
            void update(const unsigned char * a_data, size_t a_length);
        
            //! Get CRC value
            /*!
                Returns the current 32-bit CRC value. This value will change
                with subsequent calls to update.
                \return Current 32-bit CRC value
            */
            crc32_t get_crc32()
            {
                return m_crc ^ 0xFFFFFFFFL;
            }
        
        private:
            // precacluated table
            static crc_precalc s_table;
    
            // computed CRC value
            crc32_t m_crc;
    };
    
} // end namespace libcoyotl

#endif
