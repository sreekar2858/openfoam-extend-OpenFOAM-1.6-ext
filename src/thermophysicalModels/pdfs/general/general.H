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
    Foam::general

Description
    general pdf

SourceFiles
    generalI.H
    general.C
    generalIO.C

\*---------------------------------------------------------------------------*/

#ifndef general_H
#define general_H

#include "pdf.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class general Declaration
\*---------------------------------------------------------------------------*/

class general
:
    public pdf
{
    // Private data

        dictionary pdfDict_;

        typedef VectorSpace<Vector<scalar>, scalar, 2> pair;

        List<pair> xy_;

        label nEntries_;

        //- min and max values of the distribution
        scalar minValue_;
        scalar maxValue_;

        scalar range_;


public:

    //- Runtime type information
    TypeName("general");


    // Constructors

        //- Construct from components
        general
        (
            const dictionary& dict,
            Random& rndGen
        );


    // Destructor
    virtual ~general();


    // Member Functions

        //- Sample the pdf
        virtual scalar sample() const;

        //- Return the minimum value
        virtual scalar minValue() const;

        //- Return the maximum value
        virtual scalar maxValue() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
