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

#include "sampledSurface.H"
#include "polyMesh.H"
#include "demandDrivenData.H"


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(sampledSurface, 0);
    defineRunTimeSelectionTable(sampledSurface, word);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::sampledSurface::clearGeom() const
{
    deleteDemandDrivenData(SfPtr_);
    deleteDemandDrivenData(magSfPtr_);
    deleteDemandDrivenData(CfPtr_);
    area_ = -1;
}


void Foam::sampledSurface::makeSf() const
{
    // It is an error to recalculate if the pointer is already set
    if (SfPtr_)
    {
        FatalErrorIn("Foam::sampledSurface::makeSf()")
            << "face area vectors already exist"
            << abort(FatalError);
    }

    const faceList& theFaces = faces();
    SfPtr_ = new vectorField(theFaces.size());

    vectorField& values = *SfPtr_;
    forAll(theFaces, faceI)
    {
        values[faceI] = theFaces[faceI].normal(points());
    }
}


void Foam::sampledSurface::makeMagSf() const
{
    // It is an error to recalculate if the pointer is already set
    if (magSfPtr_)
    {
        FatalErrorIn("Foam::sampledSurface::makeMagSf()")
            << "mag face areas already exist"
            << abort(FatalError);
    }

    const faceList& theFaces = faces();
    magSfPtr_ = new scalarField(theFaces.size());

    scalarField& values = *magSfPtr_;
    forAll(theFaces, faceI)
    {
        values[faceI] = theFaces[faceI].mag(points());
    }
}


void Foam::sampledSurface::makeCf() const
{
    // It is an error to recalculate if the pointer is already set
    if (CfPtr_)
    {
        FatalErrorIn("Foam::sampledSurface::makeCf()")
            << "face centres already exist"
            << abort(FatalError);
    }

    const faceList& theFaces = faces();
    CfPtr_ = new vectorField(theFaces.size());

    vectorField& values = *CfPtr_;
    forAll(theFaces, faceI)
    {
        values[faceI] = theFaces[faceI].centre(points());
    }
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //


Foam::autoPtr<Foam::sampledSurface>
Foam::sampledSurface::New
(
    const word& name,
    const polyMesh& mesh,
    const dictionary& dict
)
{
    word sampleType(dict.lookup("type"));
    if (debug)
    {
        Info<< "Selecting sampledType " << sampleType << endl;
    }

    wordConstructorTable::iterator cstrIter =
        wordConstructorTablePtr_->find(sampleType);

    if (cstrIter == wordConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "sampledSurface::New"
            "(const word&, const polyMesh&, const dictionary&)"
        )   << "Unknown sample type " << sampleType
            << endl << endl
            << "Valid sample types : " << endl
            << wordConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<sampledSurface>(cstrIter()(name, mesh, dict));
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::sampledSurface::sampledSurface
(
    const word& name,
    const polyMesh& mesh
)
:
    name_(name),
    mesh_(mesh),
    interpolate_(false),
    SfPtr_(NULL),
    magSfPtr_(NULL),
    CfPtr_(NULL),
    area_(-1)
{}


// Construct from dictionary
Foam::sampledSurface::sampledSurface
(
    const word& name,
    const polyMesh& mesh,
    const dictionary& dict
)
:
    name_(name),
    mesh_(mesh),
    interpolate_(dict.lookupOrDefault("interpolate", false)),
    SfPtr_(NULL),
    magSfPtr_(NULL),
    CfPtr_(NULL),
    area_(-1)
{
    dict.readIfPresent("name", name_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::sampledSurface::~sampledSurface()
{
    clearGeom();
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const Foam::vectorField& Foam::sampledSurface::Sf() const
{
    if (!SfPtr_)
    {
        makeSf();
    }

    return *SfPtr_;
}


const Foam::scalarField& Foam::sampledSurface::magSf() const
{
    if (!magSfPtr_)
    {
        makeMagSf();
    }

    return *magSfPtr_;
}


const Foam::vectorField& Foam::sampledSurface::Cf() const
{
    if (!CfPtr_)
    {
        makeCf();
    }

    return *CfPtr_;
}


Foam::scalar Foam::sampledSurface::area() const
{
    if (area_ < 0)
    {
        area_ = sum(magSf());
        reduce(area_, sumOp<scalar>());
    }

    return area_;
}


// do not project scalar - just copy values
Foam::tmp<Foam::Field<Foam::scalar> >
Foam::sampledSurface::project(const Field<scalar>& field) const
{
    tmp<Field<scalar> > tRes(new Field<scalar>(faces().size()));
    Field<scalar>& res = tRes();

    forAll(faces(), faceI)
    {
        res[faceI] = field[faceI];
    }

    return tRes;
}


Foam::tmp<Foam::Field<Foam::scalar> >
Foam::sampledSurface::project(const Field<vector>& field) const
{
    tmp<Field<scalar> > tRes(new Field<scalar>(faces().size()));
    project(tRes(), field);
    return tRes;
}


Foam::tmp<Foam::Field<Foam::vector> >
Foam::sampledSurface::project(const Field<sphericalTensor>& field) const
{
    tmp<Field<vector> > tRes(new Field<vector>(faces().size()));
    project(tRes(), field);
    return tRes;
}


Foam::tmp<Foam::Field<Foam::vector> >
Foam::sampledSurface::project(const Field<symmTensor>& field) const
{
    tmp<Field<vector> > tRes(new Field<vector>(faces().size()));
    project(tRes(), field);
    return tRes;
}


Foam::tmp<Foam::Field<Foam::vector> >
Foam::sampledSurface::project(const Field<tensor>& field) const
{
    tmp<Field<vector> > tRes(new Field<vector>(faces().size()));
    project(tRes(), field);
    return tRes;
}


void Foam::sampledSurface::print(Ostream& os) const
{
    os << type();
}

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

Foam::Ostream& Foam::operator<<(Ostream &os, const sampledSurface& s)
{
    s.print(os);
    os.check("Ostream& operator<<(Ostream&, const sampledSurface&");
    return os;
}

// ************************************************************************* //
