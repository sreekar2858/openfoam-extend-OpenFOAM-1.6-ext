/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::splitCell

Description
    Description of cell after splitting. Contains cellLabel and pointers
    to cells it it split in. See directedRefinement.

SourceFiles
    splitCell.C

\*---------------------------------------------------------------------------*/

#ifndef splitCell_H
#define splitCell_H

#include "label.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes

/*---------------------------------------------------------------------------*\
                           Class splitCell Declaration
\*---------------------------------------------------------------------------*/

class splitCell
{
    // Private data

        //- Unsplit cell label. Only uptodate if this cell is 'live'
        //  (i.e. no master or slave)
        label cellI_;

        //- Parent splitCell or null
        splitCell* parent_;

        //- Cells replacing this or null
        splitCell* master_;

        splitCell* slave_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        splitCell(const splitCell&);

        //- Disallow default bitwise assignment
        void operator=(const splitCell&);


public:

    // Constructors

        //- Construct from cell number and parent
        splitCell(const label cellI, splitCell* parent);


    // Destructor

        ~splitCell();


    // Member Functions

        // Access

            label cellLabel() const
            {
                return cellI_;
            }

            label& cellLabel()
            {
                return cellI_;
            }

            splitCell* parent() const
            {
                return parent_;
            }

            splitCell*& parent()
            {
                return parent_;
            }

            splitCell* master() const
            {
                return master_;
            }

            splitCell*& master()
            {
                return master_;
            }

            splitCell* slave() const
            {
                return slave_;
            }

            splitCell*& slave()
            {
                return slave_;
            }

            //- Check if this is master cell of split
            bool isMaster() const;

            //- Check if this is unrefined (i.e. has no master or slave)
            bool isUnrefined() const;

            //- Returns other half of split cell. I.e. slave if this is master.
            splitCell* getOther() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
