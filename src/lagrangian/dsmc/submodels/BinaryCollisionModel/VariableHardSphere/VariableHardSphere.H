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
    Foam::VariableHardSphere

Description
    Variable Hard Sphere BinaryCollision Model

\*---------------------------------------------------------------------------*/

#ifndef VariableHardSphere_H
#define VariableHardSphere_H

#include "BinaryCollisionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
/*---------------------------------------------------------------------------*\
                      Class VariableHardSphere Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class VariableHardSphere
:
    public BinaryCollisionModel<CloudType>
{
    // Private data

        //- Reference temperature
        const scalar Tref_;


public:

    //- Runtime type information
    TypeName("VariableHardSphere");


    // Constructors

        //- Construct from dictionary
        VariableHardSphere
        (
            const dictionary& dict,
            CloudType& cloud
        );


    // Destructor
    virtual ~VariableHardSphere();


    // Member Functions

        //- Return the collision cross section * relative velocity product
        virtual scalar sigmaTcR
        (
            label typeIdP,
            label typeIdQ,
            const vector& UP,
            const vector& UQ
        ) const;

        //- Apply collision
        virtual void collide
        (
            label typeIdP,
            label typeIdQ,
            vector& UP,
            vector& UQ,
            scalar& EiP,
            scalar& EiQ
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "VariableHardSphere.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
