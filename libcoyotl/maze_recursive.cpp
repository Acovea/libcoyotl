//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  maze_recursive.cpp (libcoyotl)
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

#include "maze_recursive.h"
using namespace libcoyotl;

#include <deque>

void recursive_maze_architect::create_floor_plan(maze & a_target)
{
    // permutations of directions
    static size_t dir_perms[24][4] =
    {
        { 0, 1, 2, 3 }, { 0, 1, 3, 2 }, { 0, 2, 1, 3 }, { 0, 2, 3, 1 }, { 0, 3, 1, 2 }, { 0, 3, 2, 1 },
        { 1, 0, 2, 3 }, { 1, 0, 3, 2 }, { 1, 2, 0, 3 }, { 1, 2, 3, 0 }, { 1, 3, 0, 2 }, { 1, 3, 2, 0 },
        { 2, 1, 0, 3 }, { 2, 1, 3, 0 }, { 2, 0, 1, 3 }, { 2, 0, 3, 1 }, { 2, 3, 1, 0 }, { 2, 3, 0, 1 },
        { 3, 1, 2, 0 }, { 3, 1, 0, 2 }, { 3, 2, 1, 0 }, { 3, 2, 0, 1 }, { 3, 0, 1, 2 }, { 3, 0, 2, 1 }
    };

    // record places we can go back to
    std::deque<maze::position> cell_stack;
    
    // obtain references to elements of target maze
    size_t          width     = a_target.get_width();
    size_t          height    = a_target.get_height();
    maze::position  entrance  = a_target.get_entrance_cell_position();
    maze::position  exit      = a_target.get_exit_cell_position();
    maze::cell **   cells     = get_cells(a_target);

    // record whether or not we've visisted a given cell
    bool ** visited = new bool * [width];

    for (size_t col = 0; col < width; ++col)
    {
        visited[col] = new bool[height];

        for (size_t row = 0; row < height; ++row)
            visited[col][row] = false;
    }

    // start in a random location along the edge
    switch (m_prng.get_rand_range(maze::DIR_NORTH,maze::DIR_WEST))
    {
    case maze::DIR_NORTH: // north edge
        // entrance
        entrance.m_col = m_prng.get_rand_index(width);
        entrance.m_row = 0;
        *cells[entrance.m_col][entrance.m_row].m_walls[maze::DIR_NORTH] = maze::WALL_OPEN;
        // exit
        exit.m_col = m_prng.get_rand_index(width);
        exit.m_row = height - 1;
        *cells[exit.m_col][exit.m_row].m_walls[maze::DIR_SOUTH] = maze::WALL_OPEN;
        break;
    case maze::DIR_EAST: // east edge
        // entrance
        entrance.m_col = width - 1;
        entrance.m_row = m_prng.get_rand_index(height);
        *cells[entrance.m_col][entrance.m_row].m_walls[maze::DIR_EAST] = maze::WALL_OPEN;
        // exit
        exit.m_col = 0;
        exit.m_row = m_prng.get_rand_index(height);
        *cells[exit.m_col][exit.m_row].m_walls[maze::DIR_WEST] = maze::WALL_OPEN;
        break;
    case maze::DIR_SOUTH: // south edge
        // entrance
        entrance.m_col = m_prng.get_rand_index(width);
        entrance.m_row = height - 1;
        *cells[entrance.m_col][entrance.m_row].m_walls[maze::DIR_SOUTH] = maze::WALL_OPEN;
        // exit
        exit.m_col = m_prng.get_rand_index(width);
        exit.m_row = 0;
        *cells[exit.m_col][exit.m_row].m_walls[maze::DIR_NORTH] = maze::WALL_OPEN;
        break;
    case maze::DIR_WEST: // west edge
        // entrance
        entrance.m_col = 0;
        entrance.m_row = m_prng.get_rand_index(height);
        *cells[entrance.m_col][entrance.m_row].m_walls[maze::DIR_WEST] = maze::WALL_OPEN;
        // exit
        exit.m_col = width - 1;
        exit.m_row = m_prng.get_rand_index(height);
        *cells[exit.m_col][exit.m_row].m_walls[maze::DIR_EAST] = maze::WALL_OPEN;
        break;
    }

    maze::position current_cell = entrance;

    // automatically visit the starting cell
    visited[current_cell.m_col][current_cell.m_row] = true;

    // start carving
    bool carving = true;

    while (carving)
    {
        bool backtrack = true;

        // pick a list of directions to search for "un-visited" cells
        size_t permutation = m_prng.get_rand_index(24);

        // look in each direction for a closed wall
        for (size_t dir = 0; dir < 4; ++dir)
        {
            // did we find someplace to move to?
            if  (*cells[current_cell.m_col][current_cell.m_row].m_walls[dir_perms[permutation][dir]] == maze::WALL_CLOSED)
            {
                // if so, move to the new cell
                maze::position next_cell = current_cell;

                // set coordinates of new cell based on direction moved
                switch (dir_perms[permutation][dir])
                {
                case maze::DIR_NORTH:
                    --next_cell.m_row;
                    break;
                case maze::DIR_EAST:
                    ++next_cell.m_col;
                    break;
                case maze::DIR_SOUTH:
                    ++next_cell.m_row;
                    break;
                case maze::DIR_WEST:
                    --next_cell.m_col;
                    break;
                }

                // if this cell has not been been visited...
                if (!visited[next_cell.m_col][next_cell.m_row])
                {
                    // open the wall
                    *cells[current_cell.m_col][current_cell.m_row].m_walls[dir_perms[permutation][dir]] = maze::WALL_OPEN;

                    // push current cell ono the stack
                    cell_stack.push_back(current_cell);

                    // make new cell the current_cell
                    current_cell = next_cell;

                    // mark cell as visited
                    visited[current_cell.m_col][current_cell.m_row] = true;

                    // no need to backtrack
                    backtrack = false;

                    // exit this loop
                    break;
                }
            }
        }

        // if we couldn't carve, 
        if (backtrack)
        {
            // when the stack is empty, we're done!
            if (cell_stack.size() == 0)
                carving = false;
            else 
            {
                // backtrack by popping a cell location from the stack
                current_cell = cell_stack.back();
                cell_stack.pop_back();
            }
        }
    }

    // delete buffer
    for (size_t col2 = 0; col2 < width; ++col2)
        delete [] visited[col2];

    delete [] visited;
}
