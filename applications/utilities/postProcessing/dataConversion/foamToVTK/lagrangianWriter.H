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
    Foam::lagrangianWriter

Description
    Write fields (internal).

SourceFiles
    lagrangianWriter.C
    lagrangianWriterTemplates.C

\*---------------------------------------------------------------------------*/

#ifndef lagrangianWriter_H
#define lagrangianWriter_H

#include "globalPointPatch.H"
#include "OFstream.H"
#include "Cloud.H"
#include "volFields.H"
#include "pointFields.H"
#include "vtkMesh.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class volPointInterpolation;

/*---------------------------------------------------------------------------*\
                           Class lagrangianWriter Declaration
\*---------------------------------------------------------------------------*/

class lagrangianWriter
{
    const vtkMesh& vMesh_;

    const bool binary_;

    const fileName fName_;

    const word cloudName_;

    std::ofstream os_;

    label nParcels_;


public:

    // Constructors

        //- Construct from components
        lagrangianWriter
        (
            const vtkMesh&,
            const bool binary,
            const fileName&,
            const word&,
            const bool dummyCloud
        );


    // Member Functions

        std::ofstream& os()
        {
            return os_;
        }

        void writeParcelHeader(const label nFields);

        //- Write IOField
        template<class Type>
        void writeIOField(const wordList&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "lagrangianWriterTemplates.C"
#endif


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
