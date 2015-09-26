//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  command_line.cpp (libcoyotl)
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

#include "command_line.h"
using namespace libcoyotl;

command_line::command_line(int argc, char * argv[], const set<string> & bool_opts)
  : m_options(),
    m_inputs(),
    m_bool_opts(bool_opts)
{
	bool option_active = false;
	vector<option>::iterator active_option;

	for (int i = 1; i < argc; ++i)
	{
        // is it an option?
		if ((strlen(argv[i]) > 1) && (argv[i][0] == '-'))
		{
            // store new key
            string opt_key = string(&argv[i][1]);
			m_options.push_back(option(opt_key));
            
            // active option is now last in list
			active_option = m_options.end();
			--active_option;
            
            // check option list to see if we're looking for an argument
			option_active = (m_bool_opts.find(opt_key) == m_bool_opts.end());
		}
		else
		{
			if (option_active)
				active_option->m_value = string(argv[i]);
			else
				m_inputs.push_back(string(argv[i]));

			option_active = false;
		}
	}
}

