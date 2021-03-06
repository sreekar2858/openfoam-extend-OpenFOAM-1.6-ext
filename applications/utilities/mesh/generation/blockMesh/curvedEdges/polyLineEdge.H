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
    Foam::polyLineEdge

Description
    A curvedEdge defined in terms of a series of straight line segments.

SourceFiles
    polyLineEdge.C

\*---------------------------------------------------------------------------*/

#ifndef polyLineEdge_H
#define polyLineEdge_H

#include "curvedEdge.H"
#include "polyLine.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                        Class polyLineEdge Declaration
\*---------------------------------------------------------------------------*/

class polyLineEdge
:
    public curvedEdge,
    public polyLine
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        polyLineEdge(const polyLineEdge&);

        //- Disallow default bitwise assignment
        void operator=(const polyLineEdge&);


public:

    // Static data members
    TypeName("polyLine");


    // Constructors

        //- Construct from components
        polyLineEdge
        (
            const pointField&,
            const label start,
            const label end,
            const pointField& otherPoints
        );

        //- Construct from Istream
        polyLineEdge(const pointField&, Istream&);


        //- Destructor
        virtual ~polyLineEdge();


    // Member Functions

        //- Return the point position corresponding to the curve parameter
        //  0 <= lambda <= 1
        point position(const scalar lambda) const;

        //- Return the length of the curve
        scalar length() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
