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
    Foam::constInjector

Description
    Injector model with
    specified Constant values for the droplet diameter and spray cone angle

\*---------------------------------------------------------------------------*/

#ifndef constInjector_H
#define constInjector_H

#include "injectorModel.H"
#include "scalarList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
/*---------------------------------------------------------------------------*\
                           Class constInjector Declaration
\*---------------------------------------------------------------------------*/

class constInjector
:
    public injectorModel
{

private:

    // Private data

        dictionary specDict_;

        scalarList dropletNozzleDiameterRatio_;
        scalarList sprayAngle_;

public:

    //- Runtime type information
        TypeName("constInjector");


    // Constructors

        //- Construct from components
        constInjector
        (
            const dictionary& dict,
            spray& sm
        );


    // Destructor

        ~constInjector();


    // Member Functions

        //- Return the injected droplet diameter
        scalar d0(const label injector, const scalar time) const;

        //- Return the spray angle of the injector
        vector direction
        (
            const label injector, 
            const label hole,
            const scalar time,
            const scalar d
        ) const;

        scalar velocity
        (
            const label i,
            const scalar time
        ) const;
        
        scalar averageVelocity
        (
            const label i
        ) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
