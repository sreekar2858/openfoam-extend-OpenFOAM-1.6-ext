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
    Foam::interpolationCellPointFace

Description
    Foam::interpolationCellPointFace

\*---------------------------------------------------------------------------*/

#ifndef interpolationCellPointFace_H
#define interpolationCellPointFace_H

#include "interpolation.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class interpolationCellPointFace Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class interpolationCellPointFace
:
    public interpolation<Type>
{
    // Private data

        //- Interpolated volfield
        const GeometricField<Type, pointPatchField, pointMesh> psip_;

        //- Linearly interpolated volfield
        const GeometricField<Type, fvsPatchField, surfaceMesh> psis_;

        bool findTet
        (
            const vector& position,
            const label nFace,
            vector tetPoints[],
            label tetLabelCandidate[],
            label tetPointLabels[],
            scalar phi[],
            scalar phiCandidate[],
            label& closestFace,
            scalar& minDistance
        ) const;

        bool findTriangle
        (
            const vector& position,
            const label nFace,
            label tetPointLabels[],
            scalar phi[]
        ) const;


public:

    //- Runtime type information
    TypeName("cellPointFace");


    // Constructors

        //- Construct from components
        interpolationCellPointFace
        (
            const GeometricField<Type, fvPatchField, volMesh>& psi
        );


    // Member Functions

        //- Interpolate field to the given point in the given cell
        Type interpolate
        (
            const vector& position, 
            const label nCell,
            const label facei = -1
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "interpolationCellPointFace.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
