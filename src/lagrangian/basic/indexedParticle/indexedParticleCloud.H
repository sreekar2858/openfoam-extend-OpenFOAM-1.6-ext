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
    Foam::indexedParticleCloud

Description
    A Cloud of particles carrying an additional index.

SourceFiles
    indexedParticleCloud.C

\*---------------------------------------------------------------------------*/

#ifndef indexedParticleCloud_H
#define indexedParticleCloud_H

#include "Cloud.H"
#include "indexedParticle.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                    Class indexedParticleCloud Declaration
\*---------------------------------------------------------------------------*/

class indexedParticleCloud
:
    public Cloud<indexedParticle>
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        indexedParticleCloud(const indexedParticleCloud&);

        //- Disallow default bitwise assignment
        void operator=(const indexedParticleCloud&);


public:

    // Constructors

        //- Construct given mesh
        indexedParticleCloud
        (
            const polyMesh&,
            const word& cloudName = "defaultCloud",
            bool readFields = true
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
