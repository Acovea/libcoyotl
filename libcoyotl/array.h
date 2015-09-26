//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  array.h (libcoyotl)
//
//  Templatized array classes compatible with STL containers and
//  algorithms.
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

#if !defined(LIBCOYOTL_ARRAY_H)
#define LIBCOYOTL_ARRAY_H

// Microsoft Visual C++-specific pragmas
#if defined(_MSC_VER)
#pragma warning(disable : 4290 4101) // "exception specification ignored", "unused var"
#endif

#include <cstddef>   // for size_t
#include <algorithm> // for lexicographical_compare

#include "validator.h" // validation functions
#include "realutil.h"  // need min_of function

#if defined(LIBCOYOTL_BOUNDS_CHECKING)
#include <stdexcept>
#include <sstream>
#define LIBCOYOTL_ARRAY_EXCEPTIONS validation_error<size_t>
#define LIBCOYOTL_ARRAY_CHECK_INDEX(n) validate_less(n,m_size,LIBCOYOTL_LOCATION);
#else
#define LIBCOYOTL_ARRAY_EXCEPTIONS
#define LIBCOYOTL_ARRAY_CHECK_INDEX(n)
#endif

namespace libcoyotl
{
    //! A STL-compatible array class
    /*!
        This class defines a simple array with elements stored in contiguous
        allocated memory. The Standard C++ valarray is focused on numerical
        applications and largely incompatible with the STL. The std::vector
        includes dyanmic array features that simply aren't necessary for
        many applications.
    */
    template <typename Type>
    class array
    {
    public:
        //! Type of an array element
        typedef Type         value_type;

        //! type of a pointer to an element
        typedef Type *       pointer;

        //! Type of a constant pointer to an element
        typedef const Type * const_pointer;

        //! Type of a reference to an element
        typedef Type &       reference;

        //! Type of a constant reference to an element
        typedef const Type & const_reference;

        //! Difference type between two element pointers
        typedef ptrdiff_t    difference_type;

        //! Size type for indexing array elements
        typedef size_t       size_type;

        //! Iterator type
        typedef Type *       iterator;

        //! Constant iterator type
        typedef const Type * const_iterator;

        //! Reverse iterator type
        typedef Type *       reverse_iterator;

        //! Constant reverse iterator type
        typedef const Type * const_reverse_iterator;

        //! Default constructor
        /*!
            Constructs an array with <i>a_length</i> uninitialized elements.
            /param a_length number of elements in the array
        */
        array(size_t a_length);

        //! Initialization constructor
        /*!
            Constructs an array with specific number of elements initialized to
            given value.
            /param a_length number of elements in the array
            /param a_init_value initial value of all array elements
        */
        array(size_t a_length, const Type & a_init_value);

        //! Copy constructor
        /*!
            Creates a new array identical to an existing one.
            \param a_source - The a_source object
        */
        array(const array<Type> & a_source);

        //! Create from C-style array
        /*!
            Constructs a new array by copying the elements of the specified
            C-style array.
            /param a_length number of elements in the array
            /param a_carray pointer to an array of with a_length elements
        */
        array(size_t a_length, const Type * a_carray);

        //! Virtual destructor
        /*!
            A virtual destructor. By default, it does nothing; this is
            a placeholder that identifies this class as a potential base,
            ensuring that objects of a derived class will have their
            destructors called if they are destroyed through a base-class
            pointer.
        */
        virtual ~array() throw();

        //! Assignment operator
        /*!
            Assigns an existing object the state of another.
            \param a_source - The source object
        */
        array & operator = (const array<Type> & a_source) throw();

        //! Assign value to all elements
        /*!
            Assigns a given value to all elements in an array.
            \param a_value - Value to be assigned
            \return A reference to the target array
        */
        array & operator = (const Type & a_value) throw();

        //! Assign from C-style array
        /*!
            Assign elements from a c-style array, assuming that <i>c_array</i>
            contains at least the number of elements in the target array.
            \param a_carray - A pointer to a C-style array
        */
        array & operator = (const Type * a_carray) throw();

        //! Conversion to C-style array
        /*!
            Returns a pointer to the internal C-style array encapsulated by
            this array. The returned pointer is constant, so no elements can
            be change via this function.
            \return A const pointer to the underlying C-style array
        */
        const Type * c_array() const throw();

        //! Element access
        /*!
            Returns a reference to a specific element in an array.
            \param n - Index of an element
            \return A reference to the element at index <i>n</i>
        */
        Type & operator [] (size_t n) throw(LIBCOYOTL_ARRAY_EXCEPTIONS);

        //! Element access, constant array
        /*!
            Returns a specific element in an array.
            \param n - Index of an element
            \return A copy of the element at index <i>n</i>
        */
        Type operator [] (size_t n) const throw(LIBCOYOTL_ARRAY_EXCEPTIONS);

        //! Appending arrays
        /*!
            Appends the <i>a_other</i> array to the target, extending the length
            of the target by the length of <i>a_other</i>.
            \param a_array - Array to be appended to the target
        */
        void append(const array<Type> & a_array);

        //! Obtain beginning-of-sequence iterator
        /*!
            Returns an iterator to the first elements of the array.
            \return An iterator pointing to the first element in the array
        */
        iterator begin() throw();

        //! Obtain beginning-of-sequence iterator, constant array
        /*!
            Returns a const iterator to the first element of the array.
            \return A const iterator pointing to the first element in the array
        */
        const_iterator begin() const throw();

        //! Obtain end-of-sequence iterator
        /*!
            Returns an iterator to the first element beyond the end of the array.
            \return An iterator pointing to the first element beyond the end of the array
        */
        iterator end() throw();

        //! Obtain end-of-sequence iterator, constant array
        /*!
            Returns a const iterator to the first element beyond the end of the array.
            \return A const iterator pointing to the first element beyond the end of the array
        */
        const_iterator end() const throw();

        //! Obtain beginning-of-sequence reverse iterator
        /*!
            Returns a reverse iterator to the first element beyond the end of the array.
            \return An iterator pointing to the first element beyond the end of the array
        */
        iterator rbegin() throw();

        //! Obtain beginning-of-sequence reverse iterator, constant array
        /*!
            Returns a reverse iterator to the first element beyond the end of the array.
            \return An iterator pointing to the first element beyond the end of the array
        */
        const_iterator rbegin() const throw();

        //! Obtain end-of-sequence reverse iterator
        /*!
            Returns a reverse iterator to the first element of the array.
            \return A const reverse iterator pointing to the first element in the array
        */
        iterator rend() throw();

        //! Obtain end-of-sequence reverse iterator, constant array
        /*!
            Returns a const reverse iterator to the first element of the array.
            \return A const reverse iterator pointing to the first element in the array
        */
        const_iterator rend() const throw();

        //! Equals operator
        /*!
            Compares corresponding elements of the target array to the argument array,
            checking for equality.
            \param a_comparand - Comparand array
            \return <i>true</i> all corresponding elements are equal, <i>false</i> otherwise.
        */
        bool operator == (const array<Type> & a_comparand) const throw();

        //! Inequality operator
        /*!
            Compares corresponding elements of the target array to the argument array,
            checking for inequality.
            \param a_comparand - Comparand array
            \return <i>true</i> if any elements of the target are not equal to corresponding elements in the comparand; <i>false</i> otherwise.
        */
        bool operator != (const array<Type> & a_comparand) const throw();

        //! Less-than operator
        /*!
            Compares corresponding elements of the target array and the comparand array,
            checking that all target elements are less than comparand elements.
            \param a_comparand - Comparand array
            \return <i>true</i> if all elements of the target are less than corresponding elements in the comparand; <i>false</i> otherwise.
        */
        bool operator <  (const array<Type> & a_comparand) const throw();

        //! Less-than-or-equal-to operator
        /*!
            Compares corresponding elements of the target array and the comparand array,
            checking that all target elements are less than or equal to comparand elements.
            \param a_comparand - Comparand array
            \return <i>true</i> if all elements of the target are less than or equal to corresponding elements in the comparand; <i>false</i> otherwise.
        */
        bool operator <= (const array<Type> & a_comparand) const throw();

        //! Greater-than operator
        /*!
            Compares corresponding elements of the target array and the comparand array,
            checking that all target elements are greater than comparand elements.
            \param a_comparand - Comparand array
            \return <i>true</i> if all elements of the target are greater than corresponding elements in the comparand; <i>false</i> otherwise.
        */
        bool operator >  (const array<Type> & a_comparand) const throw();

        //! Greater-than-or-equal-to operator
        /*!
            Compares corresponding elements of the target array and the comparand array,
            checking that all target elements are greater than or equal to comparand elements.
            \param a_comparand - Comparand array
            \return <i>true</i> if all elements of the target are greater than or equal to corresponding elements in the comparand; <i>false</i> otherwise.
        */
        bool operator >= (const array<Type> & a_comparand) const throw();

        //! Exchanges the corresponding elements of two arrays
        /*!
            Exchanges the corresponding elements of two arrays; used by various
            Standard C++ algorithms.
            \param a_source - Another array
        */
        void swap(array<Type> & a_source) throw();
        
        //! Number of elements
        /*!
            Returns the number of elements in an array.
            Required by Standard C++ algorithms and container definitions.
            \return Number of elements in target array
        */
        size_t size() const throw();

        //! Maximum container size
        /*!
            Returns the maximum size of the container, which is the same as the <i>size()</i>.
            Required by Standard C++ algorithms and container definitions.
            \return Number of elements in the target array
        */
        size_t max_size() const throw();

        //! Empty container check
        /*!
            Always false, as an array is never "empty".
            Required by Standard C++ algorithms and container definitions.
            \return Always false
        */
        bool empty() const throw();

    protected:
        //! Underlying allocated array
        Type * m_array;

        //! Length of the array
        size_t m_size;

    private:
        // assign a single a_value to all elements
        void assign_value(const Type & a_value) throw();

        // copy elements from a c-style array
        void copy_carray(const Type * a_carray) throw();

        // copy elements from another array
        void copy_array(const array<Type> & a_source) throw();
    };

    // assign a single a_value to all elements
    template <typename Type>
    void array<Type>::assign_value(const Type & a_value) throw()
    {
        Type * element_ptr = m_array;

        for (size_t n = 0; n < m_size; ++n)
        {
            *element_ptr = a_value;
            ++element_ptr;
        }
    }

    // copy elements from a c-style array
    template <typename Type>
    void array<Type>::copy_carray(const Type * a_carray) throw()
    {
        // use pointers for speed
        Type * target_ptr = m_array;
        const Type * carray_ptr  = a_carray;

        for (size_t n = 0; n < m_size; ++n)
        {
            *target_ptr = *carray_ptr;
            ++target_ptr;
            ++carray_ptr;
        }
    }

    // copy elements from another array
    template <typename Type>
    void array<Type>::copy_array(const array<Type> & a_source) throw()
    {
        // find minimum a_length between the two arrays
        size_t copy_length = min_of(m_size,a_source.m_size);

        // use pointers for speed
        Type * target_ptr = m_array;
        const Type * source_ptr = a_source.m_array;

        for (size_t n = 0; n < copy_length; ++n)
        {
            *target_ptr = *source_ptr;
            ++target_ptr;
            ++source_ptr;
        }
    }

    // default constructor
    template <typename Type>
    array<Type>::array(size_t a_length)
      : m_array(NULL),
        m_size(a_length)
    {
        // enforce lower limit on a_length
        enforce_lower_limit(m_size,size_t(1));

        // allocate array
        m_array = new Type [m_size];
    }

    // a_value constructor
    template <typename Type>
    array<Type>::array(size_t a_length, const Type & a_init_value)
      : m_array(NULL),
        m_size(a_length)
    {
        // enforce lower limit on a_length
        enforce_lower_limit(m_size,size_t(1));

        // allocate array
        m_array = new Type [m_size];

        // assign values
        assign_value(a_init_value);
    }

    // copy constructor
    template <typename Type>
    array<Type>::array(const array<Type> & a_source)
      : m_array(NULL),
        m_size(a_source.m_size)
    {
        // allocate array
        m_array = new Type [m_size];

        // copy a_source array
        copy_array(a_source);
    }

    // construct from C-style array
    template <typename Type>
    array<Type>::array(size_t a_length, const Type * a_carray)
      : m_array(NULL),
        m_size(a_length)
    {
        // validate a_source
        validate_not(a_carray,(const Type *)NULL,LIBCOYOTL_LOCATION);

        // enforce lower limit on a_length
        enforce_lower_limit(m_size,size_t(1));

        // allocate array
        m_array = new Type [m_size];

        // copy elements of c array
        copy_carray(a_carray);
    }

    // destructor
    template <typename Type>
    array<Type>::~array() throw()
    {
        // clean up resources
        delete [] m_array;
        m_array  = NULL;
        m_size = 0;
    }

    // assignment operator
    template <typename Type>
    array<Type> & array<Type>::operator = (const array<Type> & a_source) throw()
    {
        copy_array(a_source);
        return *this;
    }

    // assign all operator
    template <typename Type>
    array<Type> & array<Type>::operator = (const Type & a_value) throw()
    {
        assign_value(a_value);
        return *this;
    }

    // assign from C-style array
    template <typename Type>
    array<Type> & array<Type>::operator = (const Type * a_source) throw()
    {
        copy_carray(a_source);
        return *this;
    }

    // conversion to C-style array
    template <typename Type>
    inline const Type * array<Type>::c_array() const throw()
    {
        return m_array;
    }

    // element access
    template <typename Type>
    inline Type & array<Type>::operator [] (size_t n) throw(LIBCOYOTL_ARRAY_EXCEPTIONS)
    {
        LIBCOYOTL_ARRAY_CHECK_INDEX(n)
        return m_array[n];
    }

    template <typename Type>
    inline Type array<Type>::operator [] (size_t n) const throw(LIBCOYOTL_ARRAY_EXCEPTIONS)
    {
        LIBCOYOTL_ARRAY_CHECK_INDEX(n)
        return m_array[n];
    }

    // appending
    template <typename Type>
    void array<Type>::append(const array<Type> & other)
    {
        size_t new_size = m_size + other.m_size;
        Type * new_array = new Type[new_size];

        Type * target = new_array;
        Type * a_source = m_array;
        size_t n;

        // copy from this array
        for (n = 0; n < m_size; ++n)
        {
            *target = *a_source;
            ++target;
            ++a_source;
        }

        // copy from other array
        a_source = other.m_array;

        for (n = 0; n < other.m_size; ++n)
        {
            *target = *a_source;
            ++target;
            ++a_source;
        }

        // set this to use new array, destroying old one
        m_size = new_size;
        delete [] m_array;
        m_array = new_array;
    }

    // iterator functions
    template <typename Type>
    inline typename array<Type>::iterator array<Type>::begin() throw()
    {
        return &(m_array[0]);
    }

    template <typename Type>
    inline typename array<Type>::const_iterator array<Type>::begin() const throw()
    {
        return &(m_array[0]);
    }

    template <typename Type>
    inline typename array<Type>::iterator array<Type>::end() throw()
    {
        return &(m_array[m_size]);
    }

    template <typename Type>
    inline typename array<Type>::const_iterator array<Type>::end() const throw()
    {
        return &(m_array[m_size]);
    }

    template <typename Type>
    inline typename array<Type>::reverse_iterator array<Type>::rbegin() throw()
    {
        return end();
    }

    template <typename Type>
    inline typename array<Type>::const_reverse_iterator array<Type>::rbegin() const throw()
    {
        return end();
    }

    template <typename Type>
    inline typename array<Type>::reverse_iterator array<Type>::rend() throw()
    {
        return begin();
    }

    template <typename Type>
    inline typename array<Type>::const_reverse_iterator array<Type>::rend() const throw()
    {
        return begin();
    }

    // comparisons (required by std. container definition)
    template <typename Type>
    inline bool array<Type>::operator == (const array<Type> & a_array) const throw()
    {
        return equal(begin(),end(),a_array.begin());
    }

    template <typename Type>
    inline bool array<Type>::operator != (const array<Type> & a_array) const throw()
    {
        return !(*this == a_array);
    }

    template <typename Type>
    inline bool array<Type>::operator < (const array<Type> & a_array) const throw()
    {
        return lexicographical_compare(begin(),end(),a_array.begin(),a_array.end());
    }

    template <typename Type>
    inline bool array<Type>::operator > (const array<Type> & a_array) const throw()
    {
        return (a_array < *this);
    }

    template <typename Type>
    inline bool array<Type>::operator <= (const array<Type> & a_array) const throw()
    {
        return !(*this > a_array);
    }

    template <typename Type>
    inline bool array<Type>::operator >= (const array<Type> & a_array) const throw()
    {
        return !(*this < a_array);
    }

    // swap (required by std. container definition)
    template <typename Type>
    void array<Type>::swap(array<Type> & a_source) throw()
    {
        // in this case, both arrays must be the same a_length
        validate_equals(m_size,a_source.m_size,LIBCOYOTL_LOCATION);

        // use pointers for copy
        Type * target_ptr = m_array;
        Type * source_ptr = a_source.m_array;

        for (size_t n = 0; n < m_size; ++n)
        {
            Type temp   = *target_ptr;
            *target_ptr = *source_ptr;
            *source_ptr = temp;

            ++target_ptr;
            ++source_ptr;
        }
    }

    // number of elements
    template <typename Type>
    inline size_t array<Type>::size() const throw()
    {
        return m_size;
    }

    // max_size (required by std. container definition)
    template <typename Type>
    inline size_t array<Type>::max_size() const throw()
    {
        return m_size;
    }

    // empty (always false; required by std. container definition)
    template <typename Type>
    inline bool array<Type>::empty() const throw()
    {
        return false;
    }

};

#endif
