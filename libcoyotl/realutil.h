//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  realutil.h (libcoyotl)
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

#if !defined(LIBCOYOTL_REALUTIL_H)
#define LIBCOYOTL_REALUTIL_H

#include <cstddef>
#include <cmath>
#include <limits>

namespace libcoyotl
{
    //! Round to nearest value
    /*!
        Rounds a value to nearest integer, rounding to even for
        exact fractions of 0.5.
    */
    template <typename T>
    T round_nearest(T x)
    {
        T result, fraction, dummy;

        fraction = fabs(modf(x,&result));

        if (fraction == T(0.0))
            return result;

        if (fraction == T(0.5))
        {
            if (modf(result / T(2.0), &dummy) != T(0.0))
            {
                if (x < T(0.0))
                    result -= T(1.0);
                else
                    result += T(1.0);
            }
        }
        else
        {
            if (fraction > T(0.5))
            {
                if (x < T(0.0))
                    result -= T(1.0);
                else
                    result += T(1.0);
            }
        }

        return result;
    }

    // Set number of significant digits in a floating-point value
    /*!
        Returns the given value rounded for the number of specified decimal
        digits of precision.
        \param x - Original value to be rounded
        \param n - Number of significant digits
        \return The value <i>x</i> rounded to <i>n</i> digits of precision
    */
    template <typename T>
    T sigdig(T x, unsigned short n)
    {
        T scale_factor, result;

        // is asking for no digits, or more digits than in double, simply return x
        if ((n == 0) || (n > std::numeric_limits<T>::digits10))
            result = x;
        else
        {
            // find a factor of ten such that all significant digits will
            //    be in the integer part of the double
            scale_factor = pow(T(10.0),T((int)n - 1 - (int)floor(log10(fabs(x)))));

            // scale up, round, and scale down
            result = round_nearest(x * scale_factor) / scale_factor;
        }

        return result;
    }

    //! Approximately equality
    /*!
        Determines if one value is approximately equal to another. This is primarily
        intended for floating-point types, where two computed values may not be
        precisely equal in terms of encoded floating-point bits, even though "hand"
        calculations would produce equal results.
        \param a - First operand
        \param b - Second operand
        \param tolerance - The size of the range used to determine equivalence. By
            default, this value is 1. To be considered equal to <i>b</i>, <i>a</i>
            must fall in the range (b - (tolerance * &epsilon;)) - (b + (tolerance * &epsilon;)),
            where &epsilon; is the minimum possible diffeence between two floating-point
            values of the given type.
        \return true if <i>a</i> falls in the range of equivalence with <i>b</i>; false otherwise
    */
    template <typename T>
    bool are_equal(T a, T b, T tolerance = T(1.0))
    {
        // find the range of tolerance
        T adjustment = tolerance * std::numeric_limits<T>::epsilon();

        // set high and low bounds on a's value
        T low = b - adjustment;
        T hi  = b + adjustment;

        // compare a to range
        return ((a >= low) && (a <= hi));
    }

    // Lowest common multiple
    /*!
        Calculates the lowest common multiple for two values.
    */
    unsigned long lcm(unsigned long x, unsigned long y);

    // Greatest common denominator
    /*!
        Calculates the greatest common denominator for two values.
    */
    unsigned long gcd(unsigned long x, unsigned long y);

    //! Generic absolute value template function
    /*!
        Calculates the absolute value for any numeric type.
    */
    template <class T> inline T abs_val(T value)
    {
        return (value < 0 ? (-value) : value);
    }

    //! Absolute value function, specialization
    /*!
        Specialization of template function for <i>unsigned long</i> values.
    */
    inline unsigned long abs_val(unsigned long value)
    {
        return value;
    }

    //! Absolute value function, specialization
    /*!
        Specialization of template function for <i>unsigned int</i> values.
    */
    inline unsigned int abs_val(unsigned int value)
    {
        return value;
    }

    //! Absolute value function, specialization
    /*!
        Specialization of template function for <i>unsigned short</i> values.
    */
    inline unsigned short abs_val(unsigned short value)
    {
        return value;
    }

    //! Absolute value function, specialization
    /*!
        Specialization of template function for <i>unsigned char</i> values.
    */
    inline unsigned char abs_val(unsigned char value)
    {
        return value;
    }

    //! Minimum value function template
    /*!
        Returns the lesser of two values.
    */
    template <class T> inline T min_of(T x1,T x2)
    {
        return (x1 < x2 ? x1 : x2);
    }

    //! Maximum value function template
    /*!
        Returns the greater of two values.
    */
    template <class T> inline T max_of(T x1,T x2)
    {
        return (x1 > x2 ? x1 : x2);
    }

    //! Hyperbolic arcsine 
    /*!
        Calculates sinh<sup>-1</sup>.
    */
    inline double asinh(const double& x)
    {
        return log(x + sqrt(x * x + 1.0));
    }

    //! Hyperbolic arccosine 
    /*!
        Calculates cosh<sup>-1</sup>.
    */
    inline double acosh(const double& x)
    {
        return log(x + sqrt(x * x - 1.0));
    }

    //! Hyperbolic arctangent 
    /*!
        Calculates tanh<sup>-1</sup>.
    */
    inline double atanh(const double& x)
    {
        return log((1.0 + x) / (1.0 - x)) / 2.0;
    }
    
} // end namespace libcoyotl

#endif
