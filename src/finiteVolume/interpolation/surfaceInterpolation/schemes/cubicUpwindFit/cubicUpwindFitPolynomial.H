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
    Foam::cubicUpwindFitPolynomial

Description
    Cubic polynomial for upwind biased interpolation fitting.

    Can be used with the UpwindFit scheme to create a cubic surface
    interpolation scheme

\*---------------------------------------------------------------------------*/

#ifndef cubicUpwindFitPolynomial_H
#define cubicUpwindFitPolynomial_H

#include "vector.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                 Class cubicUpwindFitPolynomial Declaration
\*---------------------------------------------------------------------------*/

class cubicUpwindFitPolynomial
{
public:

    // Member functions

        static label nTerms(const direction dim)
        {
            return
            (
                dim == 1 ? 4 :
                dim == 2 ? 8 :
                dim == 3 ? 14 : 0
            );
        }

        static void addCoeffs
        (
            scalar* coeffs,
            const vector& d,
            const scalar weight,
            const direction dim
        )
        {
            register label curIdx = 0;

            coeffs[curIdx++] = weight;
            coeffs[curIdx++] = weight*d.x();
            coeffs[curIdx++] = weight*sqr(d.x());
            coeffs[curIdx++] = weight*pow(d.x(),3);

            if (dim >= 2)
            {
                coeffs[curIdx++] = weight*d.y();
                coeffs[curIdx++] = weight*d.x()*d.y();
                coeffs[curIdx++] = weight*sqr(d.y());
                coeffs[curIdx++] = weight*d.x()*sqr(d.y());
            }
            if (dim == 3)
            {
                coeffs[curIdx++] = weight*d.z();
                coeffs[curIdx++] = weight*d.x()*d.z();
                coeffs[curIdx++] = weight*d.y()*d.z();
                coeffs[curIdx++] = weight*sqr(d.z());
                coeffs[curIdx++] = weight*d.x()*d.y()*d.z();
                coeffs[curIdx++] = weight*d.x()*sqr(d.z());
            }
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
