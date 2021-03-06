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

\*---------------------------------------------------------------------------*/

#include "meshRefinement.H"
#include "fvMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Add a T entry
template<class T> void meshRefinement::updateList
(
    const labelList& newToOld,
    const T& nullValue,
    List<T>& elems
)
{
    List<T> newElems(newToOld.size(), nullValue);

    forAll(newElems, i)
    {
        label oldI = newToOld[i];

        if (oldI >= 0)
        {
            newElems[i] = elems[oldI];
        }
    }

    elems.transfer(newElems);
}


// Compare two lists over all boundary faces
template<class T>
void meshRefinement::testSyncBoundaryFaceList
(
    const scalar tol,
    const string& msg,
    const UList<T>& faceData,
    const UList<T>& syncedFaceData
) const
{
    label nBFaces = mesh_.nFaces() - mesh_.nInternalFaces();

    if (faceData.size() != nBFaces || syncedFaceData.size() != nBFaces)
    {
        FatalErrorIn
        (
            "meshRefinement::testSyncBoundaryFaceList"
            "(const scalar, const string&, const List<T>&, const List<T>&)"
        )   << "Boundary faces:" << nBFaces
            << " faceData:" << faceData.size()
            << " syncedFaceData:" << syncedFaceData.size()
            << abort(FatalError);
    }

    const polyBoundaryMesh& patches = mesh_.boundaryMesh();

    forAll(patches, patchI)
    {
        const polyPatch& pp = patches[patchI];

        label bFaceI = pp.start() - mesh_.nInternalFaces();

        forAll(pp, i)
        {
            const T& data = faceData[bFaceI];
            const T& syncData = syncedFaceData[bFaceI];

            if (mag(data - syncData) > tol)
            {
                label faceI = pp.start()+i;

                FatalErrorIn("testSyncFaces")
                    << msg
                    << "patchFace:" << i
                    << " face:" << faceI
                    << " fc:" << mesh_.faceCentres()[faceI]
                    << " patch:" << pp.name()
                    << " faceData:" << data
                    << " syncedFaceData:" << syncData
                    << " diff:" << mag(data - syncData)
                    << abort(FatalError);
            }

            bFaceI++;
        }
    }
}


//template <class T, class Mesh>
template<class GeoField>
void meshRefinement::addPatchFields(fvMesh& mesh, const word& patchFieldType)
{
    HashTable<const GeoField*> flds
    (
        mesh.objectRegistry::lookupClass<GeoField>()
    );

    for
    (
        typename HashTable<const GeoField*>::const_iterator iter = flds.begin();
        iter != flds.end();
        ++iter
    )
    {
        const GeoField& fld = *iter();

        typename GeoField::GeometricBoundaryField& bfld =
            const_cast<typename GeoField::GeometricBoundaryField&>
            (
                fld.boundaryField()
            );

        label sz = bfld.size();
        bfld.setSize(sz+1);
        bfld.set
        (
            sz,
            GeoField::PatchFieldType::New
            (
                patchFieldType,
                mesh.boundary()[sz],
                fld.dimensionedInternalField()
            )
        );
    }
}


// Reorder patch field
template<class GeoField>
void meshRefinement::reorderPatchFields(fvMesh& mesh, const labelList& oldToNew)
{
    HashTable<const GeoField*> flds
    (
        mesh.objectRegistry::lookupClass<GeoField>()
    );

    for
    (
        typename HashTable<const GeoField*>::const_iterator iter = flds.begin();
        iter != flds.end();
        ++iter
    )
    {
        const GeoField& fld = *iter();

        typename GeoField::GeometricBoundaryField& bfld =
            const_cast<typename GeoField::GeometricBoundaryField&>
            (
                fld.boundaryField()
            );

        bfld.reorder(oldToNew);
    }
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
