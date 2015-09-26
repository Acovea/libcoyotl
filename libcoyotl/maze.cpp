//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  maze.cpp (libcoyotl)
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

// module header
#include "maze.h"
using namespace libcoyotl;

// standard headers
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
using namespace std;

// a "named constructor"
maze maze::generate(size_t width, size_t height, architect & architect)
{
    if ((width < 2) || (height < 2))
        throw invalid_argument("maze height and width must both be greater than 1");

    // create a maze object
    maze new_maze(width,height);

    // generate a random maze through the architect
    architect.create_floor_plan(new_maze);

    // return the new maze
    return new_maze;
}

// a "named constructor" to load a maze from an istream
maze maze::load(istream & source)
{
    // ensure that this is a valid stream opened in binary mode
    if (!source)
        throw invalid_argument("Invalid input stream");

    // read dimensions
    size_t width = 0;
    size_t height = 0;

    source.read((char *)&width, sizeof(size_t));
    source.read((char *)&height,sizeof(size_t));

    // create maze
    maze new_maze(width,height);

    // read data into maze
    new_maze.read(source);

    return new_maze;
}

// constructor
maze::maze(size_t width, size_t height) :
    m_width(width),
    m_height(height),
    m_cells(NULL)
{
    construct();
}

void maze::construct()
{
    size_t row, col;

    // allocate cell array columns
    m_cells = new cell * [m_width];

    // allocate cells and walls
    for (col = 0; col < m_width; ++col)
    {
        // allocate a row
        m_cells[col] = new cell[m_height];

        // allocate top and left walls
        for (row = 0; row < m_height; ++row)
        {
            // allocate the west wall
            m_cells[col][row].m_walls[DIR_WEST] = new wall;

            if (col == 0)
            {
                // this is the outside edge of the maze
                *m_cells[col][row].m_walls[DIR_WEST] = WALL_SOLID;
            }
            else
            {
                // an inner wall
                *m_cells[col][row].m_walls[DIR_WEST] = WALL_CLOSED;

                // assign wall pointer to adjoining cell
                m_cells[col - 1][row].m_walls[DIR_EAST] = m_cells[col][row].m_walls[DIR_WEST];
            }

            // allocate north wall
            m_cells[col][row].m_walls[DIR_NORTH] = new wall;

            if (row == 0)
            {
                // this is the outside edge of the maze
                *m_cells[col][row].m_walls[DIR_NORTH] = WALL_SOLID;
            }
            else
            {
                // an inner wall
                *m_cells[col][row].m_walls[DIR_NORTH] = WALL_CLOSED;

                // assign wall pointer to adjoining cell
                m_cells[col][row - 1].m_walls[DIR_SOUTH] = m_cells[col][row].m_walls[DIR_NORTH];
            }
        }

        // row should == m_height now... so do south edge
        m_cells[col][row - 1].m_walls[DIR_SOUTH] = new wall;
        *m_cells[col][row - 1].m_walls[DIR_SOUTH] = WALL_SOLID;
    }

    // do east edge
    --col;

    for (row = 0; row < m_height; ++row)
    {
        m_cells[col][row].m_walls[DIR_EAST] = new wall;
        *m_cells[col][row].m_walls[DIR_EAST] = WALL_SOLID;
    }
}

void maze::release()
{
    // position variables
    size_t row, col;

    // delete horizontal walls
    for (col = 0; col < m_width; ++col)
    {
        for (row = 0; row < m_height; ++row)
        {
            delete m_cells[col][row].m_walls[DIR_NORTH];
            m_cells[col][row].m_walls[DIR_NORTH] = NULL;
        }

        --row;
        delete m_cells[col][row].m_walls[DIR_SOUTH];
        m_cells[col][row].m_walls[DIR_SOUTH] = NULL;
    }

    // write vertical walls
    for (row = 0; row < m_height; ++row)
    {
        for (col = 0; col < m_width; ++col)
        {
            delete m_cells[col][row].m_walls[DIR_WEST];
            m_cells[col][row].m_walls[DIR_WEST] = NULL;
        }

        --col;
        delete m_cells[col][row].m_walls[DIR_EAST];
        m_cells[col][row].m_walls[DIR_EAST] = NULL;
    }

    // delete cells
    for (col = 0; col < m_width; ++col)
    {
        delete [] m_cells[col];
        m_cells[col] = NULL;
    }

    delete [] m_cells;
    m_cells = NULL;
}

void maze::deep_copy(const maze & source)
{
    // iteration variables
    size_t row, col;

    // allocate cells and walls
    for (col = 0; col < m_width; ++col)
    {
        // allocate top and left walls
        for (row = 0; row < m_height; ++row)
        {
            *m_cells[col][row].m_walls[DIR_WEST]  = *source.m_cells[col][row].m_walls[DIR_WEST];
            *m_cells[col][row].m_walls[DIR_NORTH] = *source.m_cells[col][row].m_walls[DIR_NORTH];
        }

        // row should equal m_height now... so do south edge
        --row;
        *m_cells[col][row].m_walls[DIR_SOUTH] = *source.m_cells[col][row].m_walls[DIR_SOUTH];
    }

    // do east edge
    --col;

    for (row = 0; row < m_height; ++row)
        *m_cells[col][row].m_walls[DIR_EAST] = *source.m_cells[col][row].m_walls[DIR_EAST];
}

// read a maze's data from a stream
void maze::read(istream & source)
{
    // read entrance and exit positions
    source.read((char *)&m_entrance.m_col, sizeof(size_t));
    source.read((char *)&m_entrance.m_row, sizeof(size_t));
    source.read((char *)&m_exit.m_col,     sizeof(size_t));
    source.read((char *)&m_exit.m_row,     sizeof(size_t));

    // position variables
    size_t row, col;

    // input value used to reduce file size
    unsigned char byte = 0;

    // read horizontal walls
    for (col = 0; col < m_width; ++col)
    {
        for (row = 0; row < m_height; ++row)
        {
            source.read((char *)&byte,sizeof(byte));
            *m_cells[col][row].m_walls[DIR_NORTH] = (wall)byte;
        }

        --row;
        source.read((char *)&byte,sizeof(byte));
        *m_cells[col][row].m_walls[DIR_SOUTH] = (wall)byte;
    }

    // read vertical walls
    for (row = 0; row < m_height; ++row)
    {
        for (col = 0; col < m_width; ++col)
        {
            source.read((char *)&byte,sizeof(byte));
            *m_cells[col][row].m_walls[DIR_WEST] = (wall)byte;
        }

        --col;
        source.read((char *)&byte,sizeof(byte));
        *m_cells[col][row].m_walls[DIR_EAST] = (wall)byte;
    }
}

// copy constructor
maze::maze(const maze & source) :
    m_width(source.m_width),
    m_height(source.m_height),
    m_entrance(source.m_entrance),
    m_exit(source.m_exit),
    m_cells(NULL)
{
    construct();
    deep_copy(source);
}

// assignment operator
maze & maze::operator = (const maze & source)
{
    release();
    m_width    = source.m_width;
    m_height   = source.m_height;
    m_entrance = source.m_entrance;
    m_exit     = source.m_exit;
    construct();
    deep_copy(source);
    return *this;
}

// destructor
maze::~maze()
{
    release();
}

// get the cell state at a given position
maze::cell maze::get_cell(size_t col, size_t row) const
{
    if ((col >= m_width) || (row >= m_height))
        throw invalid_argument("invalid cell coordinates");

    return m_cells[col][row];
}

// store a maze to a stream
void maze::save(ostream & receiver)
{
    // verify output stream
    if (!receiver)
        throw invalid_argument("Invalid output stream");

    // write maze data
    receiver.write((const char *)&m_width, sizeof(size_t));
    receiver.write((const char *)&m_height,sizeof(size_t));

    // write entrance and exit positions
    receiver.write((const char *)&m_entrance.m_col, sizeof(size_t));
    receiver.write((const char *)&m_entrance.m_row, sizeof(size_t));
    receiver.write((const char *)&m_exit.m_col,     sizeof(size_t));
    receiver.write((const char *)&m_exit.m_row,     sizeof(size_t));

    // iteration variables
    size_t row, col;

    // output value used to reduce file size
    unsigned char byte = 0;

    // write horizontal walls
    for (col = 0; col < m_width; ++col)
    {
        for (row = 0; row < m_height; ++row)
        {
            byte = (unsigned char)(*m_cells[col][row].m_walls[DIR_NORTH]);
            receiver.write((const char *)&byte,sizeof(byte));
        }

        --row;
        byte = (unsigned char)(*m_cells[col][row].m_walls[DIR_SOUTH]);
        receiver.write((const char *)&byte,sizeof(byte));
    }

    // write vertical walls
    for (row = 0; row < m_height; ++row)
    {
        for (col = 0; col < m_width; ++col)
        {
            byte = (unsigned char)(*m_cells[col][row].m_walls[DIR_WEST]);
            receiver.write((const char *)&byte,sizeof(byte));
        }

        --col;
        byte = (unsigned char)(*m_cells[col][row].m_walls[DIR_EAST]);
        receiver.write((const char *)&byte,sizeof(byte));
    }
}

// constructor
maze::cell::cell()
{
    for (size_t i = 0; i < 4; ++i)
        m_walls[i] = NULL;
}

// destructor
maze::cell::cell(const cell & source)
{
    for (size_t i = 0; i < 4; ++i)
        m_walls[i] = source.m_walls[i];
}

// assignment operator
maze::cell & maze::cell::operator = (const cell & source)
{
    for (size_t i = 0; i < 4; ++i)
        m_walls[i] = source.m_walls[i];

    return *this;
}

// destructor
maze::cell::~cell()
{
    // nada
}
