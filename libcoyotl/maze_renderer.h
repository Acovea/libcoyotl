//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  maze_renderer.h (libcoyotl)
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

#if !defined(LIBCOYOTL_MAZERENDERER_H)
#define LIBCOYOTL_MAZERENDERER_H

#include "maze.h"

namespace libcoyotl
{
    //! Renders a <i>maze</i> object
    /*!
        A <i>maze_renderer</i> creates an image of a maze as a black-and-white
        PNG (Portable Network Graphics) file. This class requires libpng and zlib.
    */
    class maze_renderer
    {
    public:
        //! Renders a maze to a PNG file with a specific cell size.
        /*!
            Renders a maze object to a PNG file, using a specified cell size.
            \param a_source - The maze to be rendered
            \param a_filename - The name of the file to be created
            \param a_grid_size - The dimension (in pixels) of a rendered cell (always square)
        */
        static void render(const libcoyotl::maze & a_source, const std::string & a_filename, size_t a_grid_size);

    private:
        // A type for handling mage images
        class image
        {
        public:
            // constructor
            image(const maze & source, size_t grid_size);

            // destructor
            ~image();

            // properties
            unsigned char ** get_bits() const
            {
                return m_bits;
            }

            int get_width() const
            {
                return m_width;
            }

            int get_height() const
            {
                return m_height;
            }

        private:
            // maze width
            int  m_width;

            // naze height
            int  m_height;

            // bits representing the maze
            unsigned char ** m_bits;
        };
    };
}

#endif
