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
    pointConstraint

Description
    Accumulates point constraints through successive applications of the
    applyConstraint function.  After all the constraints have been entered the
    resulting transformation tensor is returned by the constraintTransformation
    function.

SourceFiles
    pointConstraintI.H

\*---------------------------------------------------------------------------*/

#ifndef pointConstraint_H
#define pointConstraint_H

#include "Tuple2.H"
#include "label.H"
#include "vector.H"
#include "tensor.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class pointConstraint Declaration
\*---------------------------------------------------------------------------*/

class pointConstraint
:
    public Tuple2<label, vector>
{

public:

    // Constructors

        //- Construct null
        inline pointConstraint();

        //- Construct from Istream
        inline pointConstraint(Istream&);


    // Member Functions

        //- Apply and accumulate the effect of the given constraint direction 
        inline void applyConstraint(const vector& cd);

        //- Return the accumulated constraint transformation tensor
        inline tensor constraintTransformation() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "pointConstraintI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
