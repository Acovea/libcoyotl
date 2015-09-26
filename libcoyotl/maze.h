//---------------------------------------------------------------------
//  Algorithmic Conjurings @ http://www.coyotegulch.com
//
//  maze.h (libcoyotl)
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

#if !defined(LIBCOYOTL_MAZE_H)
#define LIBCOYOTL_MAZE_H

#include <string>
#include <iostream>
#include <cstddef>

namespace libcoyotl
{
    //! Defines the data structure of a maze
    /*!
        A maze object contains the definition of a rectangular maze, including
        dimensions, wall placement, and entrance and exit locations. The maze
        class does not include intrinsic support for rendering images or
        genetic algorithms; instead, it contains a generated set of
        tables used by algorithms implementing those features. As such, the
        class implements a variety of interrogation functions meant to provide
        read-only access to internal data.
    */
    class maze
    {
    public:
        //! The state of a wall
        enum wall
        {
            WALL_OPEN,      //!> Wall is open
            WALL_CLOSED,    //!> Wall is closed
            WALL_SOLID      //!> Walls is solid and can never be open (outside boundary)
        };

        //! Wall identifiers for the four cardinal directions
        enum direction
        {
            DIR_NORTH,      //!> North (up)
            DIR_EAST,       //!> East  (right)
            DIR_SOUTH,      //!> South (down)
            DIR_WEST        //!> West  (left)
        };

        //! A row-column position in the maze
        /*!
            A simple structure defining a row-column coordinate in a maze.
        */
        struct position
        {
            //! Row coordinate
            size_t m_row;

            //! Column coordinate
            size_t m_col;
        };

        //! A cell in a 2D maze grid
        /*!
            Each cell knows the state of its four walls. A cell references its
            walls by pointer; that way, two adjoining cells share the same pointer
            to the wall that they share.
        */
        struct cell
        {
            //! Pointers to four walls, indexed by <i>wall</i> values.
            wall * m_walls[4];

            //! Constructor
            /*!
                Creates a new cell. The wall references are initially NULL (they
                do not point to any walls).
            */
            cell();

            //! Copy constructor
            /*!
                Creates a new cell with the same state as an existing one.
                \param a_source - The object to be copied.
            */
            cell(const cell & a_source);

            //! Assignment operator
            /*!
                Assigns the state of one cell to another.
                \param  a_source - The object to be copied.
                \return A reference to the target object.
            */
            cell & operator = (const cell & a_source);

            //! Destructor
            /*!
                Destroys an existing cell; does nothing in this class, but
                might be required for a derived cell type.
            */
            virtual ~cell();
        };

        //! Pluggable object to randomize a maze
        /*!
            Since several different algorithms can carve mazes with different
            characteristics, <i>architect</i> implements a polymorphic
            class, thus divorcing the carving algorithm from the data it
            generates. The abstract architect class is tightly bound to the
            maze data structures, and I defined it within the scope of <i>maze</i>,
            as a friend; it implements protected static methods that access the
            internal data of a maze.
        */
        class architect
        {
        public:
            //! Creates a floor plan for a maze
            /*!
                This method "draws" in the given <i>maze</i> object, creating
                the floor plan.
                \param a_target - The <i>maze</i> that will be "architected".
            */
            virtual void create_floor_plan(maze & a_target) = 0;

        protected:
            //! Get cell map for a maze
            /*!
                Retrieves the two-dimensional maze containing the cells for a maze.
                This function provides direct read-write access to the cell data.
                \param a_target - The target maze
                \return A two-dimensional pointer to the cell grid
            */
            static cell ** get_cells(maze & a_target)
            {
                return a_target.m_cells;
            }
        };

    private:
        //! This is a friend so derived types can access maze elements
        friend class architect;

    public:
        //! Constructor
        /*!
            Creates a new maze with the specified dimensions and a floor plan
            defined by the given architect.
            \param a_width - Width, in cells, of the new maze
            \param a_height - Height, in cells, of the new maze
            \param a_architect - Architect to design a floorplan
            \return A new <i>maze</i> object
        */
        static maze generate(size_t a_width, size_t a_height, architect & a_architect);

        //! A "named constructor" to load a maze from an istream
        /*!
            Loads a maze from a binary file created using <i>maze::save</i>.
            \param a_source - Input stream containing the binary maze
            \return A new <i>maze</i> object
        */
        static maze load(std::istream & a_source);

        //! Copy constructor
        /*!
            Creates a new maze with a state matching an existing maze.
            \param a_source - Source object
        */
        maze(const maze & a_source);

        //! Assignment operator
        /*!
            Sets the state of a new maze to match the state of an existing maze.
            \param a_source - Source object
        */
        maze & operator = (const maze & a_source);

        //! Destructor
        /*!
            Destroys a maze objet and releases all of its resources.
        */
        virtual ~maze();

        //! Store a maze to a stream
        /*!
            Saves a maze to an output stream in binary format. This stream
            can later be used to reconstitute the maze via the <i>load</i>
            named constructor.
            \param a_receiver - Output stream to hold the binary maze object
        */
        void save(std::ostream & a_receiver);

        //! Return the width of the maze
        /*!
            Returns the width of a maze.
            \return Width of the maze
        */
        size_t get_width() const
        {
            return m_width;
        }

        //! Return the height of the maze
        /*!
            Returns the height of a maze.
            \return Height of the maze
        */
        size_t get_height() const
        {
            return m_height;
        }

        //! Get the entrance cell position
        /*!
            Returns the position of the entrance cell for a maze.
            \return Coordinates of the entrance cell of the maze
        */
        position get_entrance_cell_position() const
        {
            return m_entrance;
        }

        //! Get the exit cell position
        /*!
            Returns the position of the exit cell for a maze.
            \return Coordinates of the exit cell of the maze
        */
        position get_exit_cell_position() const
        {
            return m_exit;
        }

        //! Get cell data
        /*!
            Returns data for a specific cell in a maze.
            \param a_col - Column of the requested cell
            \param a_row - Row of the requested cell
            \return Cell data
        */
        cell get_cell(size_t a_col, size_t a_row) const;

    protected:
        //! Constructor without an architect (for use by load)
        /*!
            This constructor sets parameters, and then calls <i>construct</i>
            to allocate memory and assign default walls.
            \param a_width - Width, in cells, of the new maze
            \param a_height - Height, in cells, of the new maze
            \sa maze::generate
        */
        maze(size_t a_width, size_t a_height);

        //! Allocates memory and sets intial values for a maze
        /*!
            This constructor creates the raw maze, with all walls solid or closed.
            It is used by the named constructor <i>generate</i>
        */
        void construct();

        //! Utility method to delete all data buffers
        /*!
            Releases resources allocated to a maze.
        */
        void release();

        //! Deep copy utility
        /*!
            Performs a deep copy of one maze to another.
            \param a_source - Source object
        */
        void deep_copy(const maze & a_source);

        //! Utility method to read a maze
        /*!
            Read a maze's data from a binary stream.
            \param a_source - Input stream containing the binary maze
        */
        void read(std::istream & a_source);

    protected:
        //! Width of the maze in cells
        size_t m_width; 

        //! Height of the maze in cells
        size_t m_height;

        //! Position of the entrance cell
        position m_entrance;    

        //! Position of the exit cell
        position m_exit;        

        //! The cell data
        cell ** m_cells;        
    };

} // end namespace

#endif
