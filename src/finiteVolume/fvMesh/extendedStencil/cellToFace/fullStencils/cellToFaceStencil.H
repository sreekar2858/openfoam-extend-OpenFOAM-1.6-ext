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
    Foam::cellToFaceStencil

Description
    baseclass for extended cell-to-facel stencils (face values from
    neighbouring cells)

SourceFiles
    faceStencil.C

\*---------------------------------------------------------------------------*/

#ifndef cellToFaceStencil_H
#define cellToFaceStencil_H

#include "globalIndex.H"
#include "boolList.H"
#include "HashSet.H"
#include "indirectPrimitivePatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class polyMesh;

/*---------------------------------------------------------------------------*\
                           Class cellToFaceStencil Declaration
\*---------------------------------------------------------------------------*/

class cellToFaceStencil
:
    public labelListList
{
    // Private data

        const polyMesh& mesh_;

        //- Global numbering for cells and boundary faces
        const globalIndex globalNumbering_;


    // Private Member Functions
//HJ
//HJ        //- Disallow default bitwise copy construct
//HJ        cellToFaceStencil(const cellToFaceStencil&);
//HJ
//HJ        //- Disallow default bitwise assignment
//HJ        void operator=(const cellToFaceStencil&);


protected:

        //- Merge two lists.
        static void merge
        (
            const label,
            const label,
            const labelList&,
            labelList&
        );

        //- Merge two lists.
        static void merge(const label, const labelList&, labelList&);

        //- Valid boundary faces (not empty and not coupled)
        void validBoundaryFaces(boolList& isValidBFace) const;

        //- Return patch of all coupled faces.
        autoPtr<indirectPrimitivePatch> allCoupledFacesPatch() const;

        //- Combine operator for labelLists
        class unionEqOp
        {
            public:
            void operator()( labelList& x, const labelList& y ) const;
        };

        //- Collect cell neighbours of faces in global numbering
        void insertFaceCells
        (
            const label exclude0,
            const label exclude1,
            const boolList& nonEmptyFace,
            const labelList& faceLabels,
            labelHashSet& globals
        ) const;

        //- Collect cell neighbours of faces in global numbering
        labelList calcFaceCells
        (
            const boolList& nonEmptyFace,
            const labelList& faceLabels,
            labelHashSet& globals
        ) const;


        //- Collect cell neighbours into extended stencil
        void calcFaceStencil
        (
            const labelListList& globalCellCells,
            labelListList& faceStencil
        ) const;


public:

    // Constructors

        //- Construct from mesh
        explicit cellToFaceStencil(const polyMesh&);


    // Member Functions

        const polyMesh& mesh() const
        {
            return mesh_;
        }

        //- Global numbering for cells and boundary faces
        const globalIndex& globalNumbering() const
        {
            return globalNumbering_;
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
