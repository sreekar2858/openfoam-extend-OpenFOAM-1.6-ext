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
    Foam::LESmodels::SpalartAllmarasDDES

Description
    SpalartAllmaras DDES LES turbulence model for incompressible flows

    Reference:
    P.R. Spalart, S. Deck, S., M.L.Shur, K.D. Squires, M.Kh Strelets, and
    A. Travin. `A new version of detached-eddy simulation, resistant to
    ambiguous grid densities'. Theor. Comp. Fluid Dyn., 20:181-195, 2006.

SourceFiles
    SpalartAllmarasDDES.C

\*---------------------------------------------------------------------------*/

#ifndef SpalartAllmarasDDES_H
#define SpalartAllmarasDDES_H

#include "SpalartAllmaras.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace incompressible
{
namespace LESModels
{

/*---------------------------------------------------------------------------*\
                        Class SpalartAllmarasDDES Declaration
\*---------------------------------------------------------------------------*/

class SpalartAllmarasDDES
:
    public SpalartAllmaras
{
    // Private member functions

        tmp<volScalarField> fd(const volScalarField& S) const;

        tmp<volScalarField> rd
        (
            const volScalarField& visc,
            const volScalarField& S
        ) const;

        // Disallow default bitwise copy construct and assignment
        SpalartAllmarasDDES(const SpalartAllmarasDDES&);
        SpalartAllmarasDDES& operator=(const SpalartAllmarasDDES&);


protected:

    // Protected member functions

        //- Length scale
        virtual tmp<volScalarField> dTilda(const volScalarField& S) const;


public:

    //- Runtime type information
    TypeName("SpalartAllmarasDDES");


    // Constructors

        //- Construct from components
        SpalartAllmarasDDES
        (
            const volVectorField& U,
            const surfaceScalarField& phi,
            transportModel& transport
        );


    //- Destructor
    virtual ~SpalartAllmarasDDES()
    {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace LESModels
} // End namespace incompressible
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
