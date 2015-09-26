//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  maze_recursive.h (libcoyotl)
//
//  Maze generation and exploration tools
//-----------------------------------------------------------------------
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

#if !defined(LIBCOYOTL_MAZE_RECURSIVE_H)
#define LIBCOYOTL_MAZE_RECURSIVE_H

#include "maze.h"
#include "prng.h"

namespace libcoyotl
{
    //! Implements a recursive, back-tracking maze architect
    /*!
        A concrete implementation of a maze architect, using a
        recursive, back-tracking algorithm.
    */
    class recursive_maze_architect : public libcoyotl::maze::architect
    {
    public:
        //! Constructor
        /*!
            Creates a new architect, initializing its random-number
            generator with the given seed.
            \param a_prng - a random number generator
        */
        recursive_maze_architect(prng & a_prng)
            : m_prng(a_prng) // initialize random number generator
        {
            // nada
        }


        //! Creates a floor plan for a maze
        /*!
            "Carves" a maze using a recursive backtracking algorithm
            \param a_target - The <i>maze</i> that will be "architected".
        */
        virtual void create_floor_plan(libcoyotl::maze & a_target);

    private:
        // random number generator
        prng & m_prng;
    };
}

#endif
