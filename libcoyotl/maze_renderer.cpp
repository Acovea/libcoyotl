//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  maze_renderer.cpp (libcoyotl)
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

#include "maze_renderer.h"
using namespace libcoyotl;

#include <stdexcept>
using namespace std;

#define PNG_SETJMP_NOT_SUPPORTED
#include "png.h"

// constructor
maze_renderer::image::image(const maze & source, size_t grid_size)
{
    if (grid_size < 2)
        throw invalid_argument("grid size must be 2 or greater");

    m_width  = static_cast<int>(grid_size * (source.get_width()  + 2));
    m_height = static_cast<int>(grid_size * (source.get_height() + 2));

    size_t alloc_width = (m_width + 7) / 8;

    size_t row, col;

    // allocate row pointers
    m_bits = new unsigned char * [m_height];
    
    // allocate and initialize rows
    for (row = 0; row < size_t(m_height); ++row)
    {
        m_bits[row] = new unsigned char [alloc_width];
        memset(m_bits[row],0xFF,alloc_width);
    }

    // now we set the bits we need to draw
    size_t x = 0, y = 0, x2 = 0, y2 = 0;
    size_t south_row = source.get_height() - 1;
    size_t east_col  = source.get_width() - 1;

    for (col = 0; col <= east_col; ++col)
    {
        maze::cell current_cell;

        x += grid_size;
        y  = 0;

        for (row = 0; row <= south_row; ++row)
        {
            y += grid_size;

            // get the current cell
            current_cell = source.get_cell(col,row);

            // draw west wall
            if (*current_cell.m_walls[maze::DIR_WEST] != maze::WALL_OPEN)
            {
                for (y2 = y; y2 < y + grid_size + 1; ++y2)
                    m_bits[y2][x / 8] &= ~(0x80 >> (x % 8));
            }

            // draw north wall
            if (*current_cell.m_walls[maze::DIR_NORTH] != maze::WALL_OPEN)
            {
                for (x2 = x; x2 < x + grid_size; ++x2)
                    m_bits[y][x2 / 8] &= ~(0x80 >> (x2 % 8));
            }

            // draw south wall when at bottom
            if (row == south_row)
            {
                if (*current_cell.m_walls[maze::DIR_SOUTH] != maze::WALL_OPEN)
                {
                    y2 = y + grid_size;

                    for (x2 = x; x2 < x + grid_size; ++x2)
                        m_bits[y2][x2 / 8] &= ~(0x80 >> (x2 % 8));
                }
            }

            // draw east wall
            if (col == east_col)
            {
                if (*current_cell.m_walls[maze::DIR_EAST] != maze::WALL_OPEN)
                {
                    x2 = x + grid_size;

                    // set bits for this wall segment
                    for (y2 = y; y2 < y + grid_size + 1; ++y2)
                        m_bits[y2][x2 / 8] &= ~(0x80 >> (x2 % 8));
                }
            }
        }
    }
}

// destructor
maze_renderer::image::~image()
{
    // delete image data
    for (int row = 0; row < m_height; ++row)
        delete [] m_bits[row];

    delete [] m_bits;
}

// create a PNG image of the maze in the specified file
void maze_renderer::render(const maze & source, const string & file_name, size_t grid_size)
{
    // libpng requires C-style file I/O
    FILE * file;

    // open the PNG output file
    file = fopen(file_name.c_str(), "wb");

    if (!file)
        throw runtime_error("unable to create PNG file");

    // create a maze image
    image maze_image(source,grid_size);

    // prepare the standard PNG structures
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
    {
        fclose(file);
        throw runtime_error("failure when calling png_create_write_struct");
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr)
    {
        fclose(file);
        png_destroy_write_struct(&png_ptr, (png_infopp) NULL);
        throw runtime_error("failure when calling png_create_write_struct");
    }

    // initialize the I/O
    png_init_io(png_ptr, file);
        
    // we're going to write a very simple 3x8 bit RGB image
    png_set_IHDR(png_ptr, info_ptr, maze_image.get_width(), maze_image.get_height(), 1, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    
    // write the file header information
    png_write_info(png_ptr, info_ptr);

    // write out the entire image data in one call
    png_write_image (png_ptr, maze_image.get_bits());
    
    // write the additional chunks to the PNG file (not really needed)
    png_write_end(png_ptr, info_ptr);
    
    // clean up after the write, and free any memory allocated
    png_destroy_write_struct(&png_ptr, &info_ptr);

    // close file
    fclose (file);
}

