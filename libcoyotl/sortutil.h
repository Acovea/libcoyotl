//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  sortutil.h
//
//  Generic tools for sorting C-type arrays of data.
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

#if !defined(LIBCOYOTL_SORTUTIL_H)
#define LIBCOYOTL_SORTUTIL_H

#include <stdexcept>

namespace libcoyotl
{

    //--------------------------------------------------
    // sort two items
    
    template<class  T>
    inline void sort_two(T & a, T & b)
    {
        if (a > b)
        {
            T t = a;
            a = b;
            b = t;
        }
    }
    
    //--------------------------------------------------
    // sort three items
    
    template<class  T>
    inline void sort_three(T & a, T & b, T & c)
    {
        sort_two(a,b);
        sort_two(a,c);
        sort_two(b,c);
    }
    
    //--------------------------------------------------
    // shell sort an array in ascending order
    
    template<class  T> void
    shell_sort(T * a, size_t n)
    {
        size_t inc, i, j;
        T t;
        
        // algorithm relies on one-based arrays
        --a;
        
        for (inc = 1; inc <= n / 9; inc = 3 * inc + 1) ;
        
        for ( ; inc > 0; inc /= 3)
        {
            for (i = inc + 1; i <= n; i += inc)
            {
                t = a[i];
                j = i;
                
                while ((j > inc) && (a[j - inc] > t))
                {
                    a[j] = a[j - inc];
                    j -= inc;
                }
                
                a[j] = t;
            }
        }
    }
    
    //--------------------------------------------------
    // shell sort an array in ascending order
    
    template<class  T>
    void shell_sort_descending(T * array, size_t n)
    {
        size_t increment, i, j;
        T t;
        
        // algorithm relies on one-based arrays
        --array;
        
        for (increment = 1; increment <= n / 9; increment = 3 * increment + 1) ;
        
        for ( ; increment > 0; increment /= 3)
        {
            for (i = increment + 1; i <= n; i += increment)
            {
                t = array[i];
                j = i;
                
                while ((j > increment) && (array[j - increment] < t))
                {
                    array[j] = array[j - increment];
                    j -= increment;
                }
                
                array[j] = t;
            }
        }
    }
    
    //--------------------------------------------------
    // Quick Sort an array in ascending order
    template <class T>
    void quick_sort(T * array, size_t n)
    {
        static const size_t STACK_SIZE = CHAR_BIT * sizeof(int);
        static const size_t THRESHOLD  = 7;

        size_t left_index  = 0;
        size_t right_index = n - 1;

        T temp, pivot;
        size_t scan_left, scan_right, middle, pivot_index, size_left, size_right;
        size_t stack_left[STACK_SIZE], stack_right[STACK_SIZE], stack_ptr = 0;
        
        while (true)
        {
            while (right_index > left_index)
            {
                if ((right_index - left_index) > THRESHOLD)
                {
                    // "median-of-three" partitioning
                    middle = (left_index + right_index) / 2;
                    
                    // three-sort left, middle, and right elements
                    if (array[left_index] > array[middle])
                    {
                        temp              = array[left_index];
                        array[left_index] = array[middle];
                        array[middle]     = temp;
                    }
                    
                    if (array[left_index] > array[right_index])
                    {
                        temp               = array[left_index];
                        array[left_index]  = array[right_index];
                        array[right_index] = temp;
                    }
                    
                    if (array[middle] > array[right_index])
                    {
                        temp               = array[middle];
                        array[middle]      = array[right_index];
                        array[right_index] = temp;
                    }
                    
                    pivot_index = right_index - 1;
                    
                    temp               = array[middle];
                    array[middle]      = array[pivot_index];
                    array[pivot_index] = temp;
                    
                    // set-up for partitioning
                    scan_left  = left_index  + 1;
                    scan_right = right_index - 2;
                }
                else
                {
                    pivot_index = right_index;
                    scan_left   = left_index;
                    scan_right  = right_index - 1;
                }
                
                pivot = array[pivot_index];
                
                while (true)
                {
                    // scan from left
                    while ((array[scan_left] < pivot) && (scan_left < right_index))
                        ++scan_left;
                    
                    // scan from right
                    while ((array[scan_right] > pivot) && (scan_right > left_index))
                        --scan_right;
                    
                    // if scans have met, exit inner loop
                    if (scan_left >= scan_right)
                        break;
                    
                    // exchange elements
                    temp              = array[scan_right];
                    array[scan_right] = array[scan_left];
                    array[scan_left]  = temp;
                    
                    if (scan_left < right_index)
                        ++scan_left;

                    if (scan_right > left_index)
                        --scan_right;
                }
                
                // exchange final element
                if (scan_left != pivot_index)
                {
                    temp               = array[pivot_index];
                    array[pivot_index] = array[scan_left];
                    array[scan_left]   = temp;
                }
                
                // place largest partition on stack
                size_left  = scan_left   - left_index;
                size_right = right_index - scan_left;
                
                if (size_left > size_right)
                {
                    if (size_left != 1)
                    {
                        ++stack_ptr;
                        
                        if (stack_ptr == STACK_SIZE)
                            throw std::runtime_error("stack overflow in quick_sort");
                        
                        stack_left[stack_ptr]  = left_index;
                        stack_right[stack_ptr] = scan_left - 1;
                    }
                    
                    if (size_right != 0)
                        left_index = scan_left + 1;
                    else
                        break;
                }
                else
                {
                    if (size_right != 1)
                    {
                        ++stack_ptr;
                        
                        if (stack_ptr == STACK_SIZE)
                            throw std::runtime_error("stack overflow in quick_sort");
                        
                        stack_left[stack_ptr]  = scan_left + 1;
                        stack_right[stack_ptr] = right_index;
                    }
                    
                    if (size_left != 0)
                        right_index = scan_left - 1;
                    else
                        break;
                }
            }
            
            // iterate with values from stack
            if (stack_ptr > 0)
            {
                left_index  = stack_left[stack_ptr];
                right_index = stack_right[stack_ptr];
                
                --stack_ptr;
            }
            else
                break;
        }
    }
            
} // end namespace libcoyotl

#endif

