//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  validator.h (libcoyotl)
//
//  Templatized validation and constraint enforcement functions.
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

#if !defined(LIBCOYOTL_VALIDATOR_H)
#define LIBCOYOTL_VALIDATOR_H

#include <sstream>
#include <stdexcept>
#include <typeinfo>

namespace libcoyotl
{
    using std::stringstream;
    using std::string;
    using std::runtime_error;

    //! Standard validation exception
    /*!
        This is the standard exception thrown for validation failures.
        By deriving from the Standard C++ exception <i>runtime_error</i>,
        validation error is caught by generic <i>catch (std::exception)
        </i> blocks or more specific exception handlers.
        \version 1.0.0
        \date    1 May 2002
    */
    template <typename Type>
    class validation_error : public runtime_error
    {
    private:
        static string build_error_string(const Type & object,
                                         const string & details)
        {
            stringstream message;

            message << "validation error: "
                    << typeid(object).name() << " " << object
                    << details;

            return message.str();
        }

    public:
        //! Constructor
        /*!
            Constructs a <i>validation_error</i> from an object and an optional
            detail string. The resulting error message -- retrieved
            via the <i>what()</i> method inherited from <i>
            runtime_error</i> -- contains the type of object, it's
            content, and the test of the detail string (if one is
            provided).
            \param object  The erroneous object that failed validation
            \param details A string providing detailed information
                           about the validation failure
        */
        validation_error(const Type & object,
                         const string & details = string())
            : runtime_error(build_error_string(object,details))
        {
            // nada
        }
    };

    //! Validates that an object has a specific value.
    /*!
        If value is not equal to <i>constraint</i>, as defined by the appropriate
        == operator, this function throws a <i>validation_error</i>.
        \param object     Object to be tested against <i>constraint</i>
        \param constraint Expected value of object
        \param message    Additional text to be included in a
                          <i>validation_error</i>
    */
    template <typename Type>
    void validate_equals(const Type & object,
                         const Type & constraint,
                         const string & message = string())
    {
        if (object != constraint)
        {
            stringstream details;
            details << " must equal " << constraint << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates that an object does not have a specific value.
    /*!
        If value equals the <i>constraint</i>, as defined by the appropriate
        == operator, this function throws a <i>validation_error</i>.
        \param object     Object to be tested against <i>constraint</i>
        \param constraint Value that object should not equal
        \param message    Additional text to be included in a
                          <i>validation_error</i>
    */
    template <typename Type>
    void validate_not(const Type & object,
                      const Type & constraint,
                      const string & message = string())
    {
        if (object == constraint)
        {
            stringstream details;
            details << " must not equal " << constraint << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates that an object is less than <i>constraint</i>.
    /*!
        If value is greater than or equal to <i>constraint</i> (using the >=
        operator), this function throws a <i>validation_error</i>.
        \param object       Object to be tested
        \param constraint   Object must be < than this value
        \param message      Additional text to be included in a
                            <i>validation_error</i>
    */
    template <typename Type>
    void validate_less(const Type & object,
                      const Type & constraint,
                      const string & message = string())
    {
        if (object >= constraint)
        {
            stringstream details;
            details << " must be less than " << constraint << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates that an object is less than or equal to <i>constraint</i>.
    /*!
        If value is greater than or equal to <i>constraint</i> (using the >=
        operator), this function throws a <i>validation_error</i>.
        \param object       Object to be tested
        \param constraint   Object must be < than this value
        \param message      Additional text to be included in a
                            <i>validation_error</i>
    */
    template <typename Type>
    void validate_less_eq(const Type & object,
                          const Type & constraint,
                          const string & message = string())
    {
        if (object > constraint)
        {
            stringstream details;
            details << " must be less than " << constraint << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates that an object is greater than <i>constraint</i>.
    /*!
        If value is less than or equal to <i>constraint</i> (using the <=
        operator), this function throws a <i>validation_error</i>.
        \param object       Object to be tested
        \param constraint   Object must be > than this value
        \param message      Additional text to be included in a
                            validation_error
    */
    template <typename Type>
    void validate_greater(const Type & object,
                      const Type & constraint,
                      const string & message = string())
    {
        if (object <= constraint)
        {
            stringstream details;
            details << " must be greater than " << constraint << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates that an object is greater than or equal to <i>constraint</i>.
    /*!
        If value is less than or equal to <i>constraint</i> (using the <=
        operator), this function throws a <i>validation_error</i>.
        \param object       Object to be tested
        \param constraint   Object must be > than this value
        \param message      Additional text to be included in a
                            validation_error
    */
    template <typename Type>
    void validate_greater_eq(const Type & object,
                      const Type & constraint,
                      const string & message = string())
    {
        if (object < constraint)
        {
            stringstream details;
            details << " must be greater than " << constraint << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates that an object has a value in a specified range.
    /*!
        If value is less than <i>low_bound</i> (using the < operator) or greater
        than <i>high_bound</i> (using the > operator), this function throws a
        <i>validation_error</i>. The function does not verify that <i>low_bound</i> is
        less than <i>high_bound</i>.
        \param object       Object to be tested
        \param low_bound    Low boundary (inclusive) on value of object
        \param high_bound   High boundary (inclusive) on value of object
        \param message      Additional text to be included in a
                            <i>validation_error</i>
    */
    template <typename Type>
    void validate_range(const Type & object,
                        const Type & low_bound,
                        const Type & high_bound,
                        const string & message = string())
    {
        if ((object < low_bound) || (object > high_bound))
        {
            stringstream details;
            details << " must be between " << low_bound << " and "
                    << high_bound << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Validates an object with a given predicate.
    /*!
        If <i>predicate(object)</i> is <i>false</i> -- indicating an invalid object in
        the context defined by <i>predicate</i> -- this function throws a
        <i>validation_error</i>.
        \param object    Object to be tested against the <i>predicate</i>
        \param predicate A function or functor returning <i>true</i>
                         for valid objects and <i>false</i> for an
                         invalid object
        \param message   Additional text to be included in a
                         <i>validation_error</i>
    */
    template <typename Type, typename Predicate>
    void validate_with(const Type & object,
                       const Predicate & constraint,
                       const string & message = string())
    {
        if (!constraint(object))
        {
            stringstream details;
            details << " failed test " << typeid(constraint).name() << " " << message;
            throw validation_error<Type>(object,details.str());
        }
    }

    //! Enforce a lower limit on the value of an object.
    /*!
        If object's value is less than <i>low_value</i>, as per the < operator,
        object will be set equal to <i>low_value</i>.
        \param object    Object to undergo enforcement
        \param low_value Lower limit on the value of <i>object</i>
    */
    template <typename Type>
    void enforce_lower_limit(Type & object,
                             const Type & low_value)
    {
        if (object < low_value)
            object = low_value;
    }

    //! Enforce an upper limit on the value of an object.
    /*!
        If object's value is greater than <i>high_value</i>, as per the >
        operator, object will be set equal <i>to high_value</i>.
        \param object     Object to undergo enforcement
        \param high_value Upper limit on the value of <i>object</i>
    */
    template <typename Type>
    void enforce_upper_limit(Type & object,
                            const Type & high_value)
    {
        if (object > high_value)
            object = high_value;
    }

    //! Enforce an range limit on the value of an object.
    /*!
        If object's value is less than <i>low_value</i>, as per the < operator,
        object will be set equal to <i>low_value</i>. If object's value is
        greater than <i>high_value</i>, as per the > operator, object will
        be set equal to <i>high_value</i>.
        \param object     Object to undergo enforcement
        \param low_value  Lower limit on the value of <i>object</i>
        \param high_value Upper limit on the value of <i>object</i>
    */
    template <typename Type>
    void enforce_range(Type & object,
                       const Type & low_value,
                       const Type & high_value)
    {
        if (object < low_value)
            object = low_value;
        else if (object > high_value)
            object = high_value;
    }

    //! Utility function to create a location string.
    /*!
        This function formats a string from a given file name and 
        line number. If C++ incorporates parts of C99, this function
        could be extended to support the <i>__func__</i> macro that names
        the current function.
        \param filename The name of a file, usually the Standard C <i>__FILE__</i> macro
        \param line_no  A line number in the file, usually the Standard C <i>__LINE__</i> macro
        \sa LIBCOYOTL_LOCATION
    */
    inline string build_location_string(const char * filename, long line_no)
    {
        stringstream text;
        text << "in " << filename << ", line " << line_no;
        return text.str();
    }
}

// These macros allow validation to be included on a per-compile basis, based on the settings
// of the DEBUG and NDEBUG preprocessor macros.
#if defined(_DEBUG) && !defined(NDEBUG)
#define LIBCOYOTL_VALIDATE_EQUALS(object,constraint,details) libcoyotl::validate_equals(object,constraint,details)
#define LIBCOYOTL_VALIDATE_NOT(object,constraint,details) libcoyotl::validate_not(object,constraint,details)
#define LIBCOYOTL_VALIDATE_LESS(object,constraint,details) libcoyotl::validate_less(object,constraint,details)
#define LIBCOYOTL_VALIDATE_LESS_EQ(object,constraint,details) libcoyotl::validate_less_eq(object,constraint,details)
#define LIBCOYOTL_VALIDATE_GREATER(object,constraint,details) libcoyotl::validate_greater(object,constraint,details)
#define LIBCOYOTL_VALIDATE_GREATER_EQ(object,constraint,details) libcoyotl::validate_greater_eq(object,constraint,details)
#define LIBCOYOTL_VALIDATE_RANGE(object,low_bound,high_bound,details) libcoyotl::validate_range(object,low_bound,high_bound,details)
#define LIBCOYOTL_VALIDATE_WITH(object,constraint,details) libcoyotl::validate_with(object,constraint,details)
#define LIBCOYOTL_LOCATION libcoyotl::build_location_string(__FILE__,__LINE__)
#else
#define LIBCOYOTL_VALIDATE_EQUALS(object,constraint,details)
#define LIBCOYOTL_VALIDATE_NOT(object,constraint,details)
#define LIBCOYOTL_VALIDATE_LESS(object,constraint,details)
#define LIBCOYOTL_VALIDATE_LESS_EQ(object,constraint,details)
#define LIBCOYOTL_VALIDATE_GREATER(object,constraint,details)
#define LIBCOYOTL_VALIDATE_GREATER_EQ(object,constraint,details)
#define LIBCOYOTL_VALIDATE_RANGE(object,low_bound,high_bound,details)
#define LIBCOYOTL_VALIDATE_WITH(object,constraint,details)
#define LIBCOYOTL_LOCATION std::string()
#endif

#endif
