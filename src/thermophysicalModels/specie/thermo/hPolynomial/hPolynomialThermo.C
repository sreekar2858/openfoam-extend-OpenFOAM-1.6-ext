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

#include "hPolynomialThermo.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
Foam::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
    Istream& is
)
:
    EquationOfState(is),
    Hf_(readScalar(is)),
    Sf_(readScalar(is)),
    cpPolynomial_("cpPolynomial", is),
    hPolynomial_(),
    sPolynomial_()
{
    Hf_ *= this->W();
    Sf_ *= this->W();
    cpPolynomial_ *= this->W();

    hPolynomial_ = cpPolynomial_.integrate();
    sPolynomial_ = cpPolynomial_.integrateMinus1();

    // Offset h poly so that it is relative to the enthalpy at Tstd
    hPolynomial_[0] += Hf_ - hPolynomial_.evaluate(specie::Tstd);

    // Offset s poly so that it is relative to the entropy at Tstd
    sPolynomial_[0] += Sf_ - sPolynomial_.evaluate(specie::Tstd);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const hPolynomialThermo<EquationOfState, PolySize>& pt
)
{
    os  << static_cast<const EquationOfState&>(pt) << tab
        << pt.Hf_/pt.W() << tab
        << pt.Sf_ << tab
        << "cpPolynomial" << tab << pt.cpPolynomial_/pt.W();

    os.check
    (
        "operator<<"
        "("
            "Ostream&, "
            "const hPolynomialThermo<EquationOfState, PolySize>&"
        ")"
    );

    return os;
}


// ************************************************************************* //
