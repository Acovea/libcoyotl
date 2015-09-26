//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  command_line.h (libcoyotl)
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

#if !defined(LIBCOYOTL_COMMAND_LINE_H)
#define LIBCOYOTL_COMMAND_LINE_H

// Standard C++
#include <string>
#include <vector>
#include <set>

namespace libcoyotl
{
    using std::string;
    using std::vector;
    using std::set;

    // a very simple command-line parser
    class command_line
    {
    public:
        struct option
        {
            string m_name;
            string m_value;
            
            option(const string & a_name)
              : m_name(a_name), m_value("")
            {
                // nada
            }
        };
        
        // create a command line parser
        command_line(int argc, char * argv[], const set<string> & bool_opts);
        
        // retrieve a list of options
        const vector<option> & get_options() const
        {
            return m_options;
        }
        
        // retrieve a list of input values
        const vector<string> & get_inputs() const
        {
            return m_inputs;
        }
        
    private:
        // the set of option names, with associated values
        vector<option> m_options;
        
        // the set of inputs -- command line arguments not associated with an option
        vector<string> m_inputs;
        
        // a list of boolean options, which have no values
        const std::set<std::string> & m_bool_opts;
    };

}

#endif
