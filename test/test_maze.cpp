//---------------------------------------------------------------------
//  A Set of Tools for Exploring Mazes
//
//  test_maze.h (libcoyote)
//-----------------------------------------------------------------------
//
//  COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
//  
//  If you modify this file, you may insert additional notices
//  immediately following this sentence.
//  
//  Copyright 2001, 2004 Scott Robert Ladd.
//  All rights reserved, except as noted herein.
//  
//  This computer program source file is supplied "AS IS". Scott Robert
//  Ladd (hereinafter referred to as "Author") disclaims all warranties,
//  expressed or implied, including, without limitation, the warranties
//  of merchantability and of fitness for any purpose. The Author
//  assumes no liability for direct, indirect, incidental, special,
//  exemplary, or consequential damages, which may result from the use
//  of this software, even if advised of the possibility of such damage.
//  
//  The Author hereby grants anyone permission to use, copy, modify, and
//  distribute this source code, or portions hereof, for any purpose,
//  without fee, subject to the following restrictions:
//  
//      1. The origin of this source code must not be misrepresented.
//  
//      2. Altered versions must be plainly marked as such and must not
//         be misrepresented as being the original source.
//  
//      3. This Copyright notice may not be removed or altered from any
//         source or altered source distribution.
//  
//  The Author specifically permits (without fee) and encourages the use
//  of this source code for entertainment, education, or decoration. If
//  you use this source code in a product, acknowledgment is not required
//  but would be appreciated.
//  
//  Acknowledgement:
//      This license is based on the wonderful simple license that
//      accompanies libpng.
//
//-----------------------------------------------------------------------
//  For more information on this software package, please visit
//  Scott's web site, Coyote Gulch Productions, at:
//
//      http://www.coyotegulch.com
//-----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

#include "../libcoyotl/mwc1038.h"
#include "../libcoyotl/maze.h"
#include "../libcoyotl/maze_recursive.h"
#include "../libcoyotl/maze_renderer.h"
using namespace libcoyotl;

#if defined(_DEBUG)
ostream & operator << (ostream & target, const maze & source)
{
    static const string dir_names[4] = { " N", " E", " S", " W" };

    for (size_t col = 0; col < source.get_width(); ++col)
    {
        for (size_t row = 0; row < source.get_height(); ++row)
        {
            target << "[" << setw(2) << col << "," << setw(2) << row << "] walls =";

            maze::cell cell = source.get_cell(col,row);

            for (size_t dir = maze::DIR_NORTH; dir <= maze::DIR_WEST; ++dir)
                target << dir_names[dir] << (*cell.m_walls[dir]);

            target << endl;
        }
    }

    return target;
}
#endif

int main(int argc, char * argv[])
{
    cout << endl;

    // default arguments -- yes, I know this is very simple, but it's a test program, darn it...
    string image_name("maze.png");
    int width     =  997;
    int height    = 1001;
    int grid_size =   11;

    mwc1038 randomizer;
    string maze_data_name(image_name + ".maze");
    string restored_image_name("restored_");
    restored_image_name += image_name;

    try
    {
        // keep track of run time
        clock_t start = clock();

        // create an architect object
        recursive_maze_architect architect(randomizer);

        // create the maze
        cout << "generating a " << width << "-by-" << height << " maze" << endl;
        maze m1 = maze::generate(width,height,architect);

        // draw it to a PNG file
        cout << "writing maze image to " << image_name << " (grid size " << grid_size << ")" << endl;
        maze_renderer::render(m1,image_name,grid_size);

        // save maze data
        cout << "writing maze data to " << maze_data_name << endl;
        ofstream file_out(maze_data_name.c_str(),ios::binary | ios::out | ios::trunc);
        m1.save(file_out);
        file_out.close();

        // restore maze data from file
        cout << "reading maze data" << endl;
        ifstream file_in(maze_data_name.c_str(),ios::binary | ios::in);
        maze m2 = maze::load(file_in);
        file_in.close();

        // write restored image to PNG file
        cout << "writing restored maze image to " << restored_image_name << endl;
        maze_renderer::render(m2,restored_image_name,grid_size);

        // dump mazes for debugging
#if defined(_DEBUG)
        cout << endl
             << "Maze m1 dump:" << endl << m1 << endl
             << "Maze m2 dump:" << endl << m2 << endl;
#endif

        // done
        cout << "done in " << (double(clock() - start) / CLOCKS_PER_SEC) << " seconds" << endl;

    }
    catch (exception & ex)
    {
        cerr << "** EXCEPTION: " << ex.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "** UNKNOWN EXCEPTION **" << endl;
        return 2;
    }

    // outa here!
    return 0;
}
