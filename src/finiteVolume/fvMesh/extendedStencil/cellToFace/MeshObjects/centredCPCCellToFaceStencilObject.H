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
    Foam::centredCPCCellToFaceStencilObject

Description

SourceFiles

\*---------------------------------------------------------------------------*/

#ifndef centredCPCCellToFaceStencilObject_H
#define centredCPCCellToFaceStencilObject_H

#include "extendedCentredCellToFaceStencil.H"
#include "CPCCellToFaceStencil.H"
#include "MeshObject.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
              Class centredCPCCellToFaceStencilObject Declaration
\*---------------------------------------------------------------------------*/

class centredCPCCellToFaceStencilObject
:
    public MeshObject<fvMesh, centredCPCCellToFaceStencilObject>,
    public extendedCentredCellToFaceStencil
{

public:

    TypeName("centredCFCCellToFaceStencil");

    // Constructors

        //- Construct from uncompacted face stencil
        explicit centredCPCCellToFaceStencilObject
        (
            const fvMesh& mesh
        )
        :
            MeshObject<fvMesh, centredCPCCellToFaceStencilObject>(mesh),
            extendedCentredCellToFaceStencil(CPCCellToFaceStencil(mesh))
        {
            if (extendedCellToFaceStencil::debug)
            {
                Info<< "Generated centred stencil " << type()
                    << nl << endl;
                writeStencilStats(Info, stencil(), map());
            }
        }


    // Destructor

        virtual ~centredCPCCellToFaceStencilObject()
        {}


    // Member functions

        //- Delete the stencil when the mesh moves
        virtual bool movePoints() const
        {
            deleteObject();
            return true;
        }

        //- Delete the stencil when mesh updates
        virtual bool updateMesh(const mapPolyMesh&) const
        {
            deleteObject();
            return true;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
