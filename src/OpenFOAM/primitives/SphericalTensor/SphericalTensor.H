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
    Foam::SphericalTensor

Description
    Templated 3D SphericalTensor derived from VectorSpace adding construction
    from 1 component, element access using th ii() member function and the
    inner-product (dot-product) and outer-product operators.

SourceFiles
    SphericalTensorI.H

\*---------------------------------------------------------------------------*/

#ifndef SphericalTensor_H
#define SphericalTensor_H

#include "VectorSpace.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class SphericalTensor Declaration
\*---------------------------------------------------------------------------*/

template<class Cmpt>
class SphericalTensor
:
    public VectorSpace<SphericalTensor<Cmpt>, Cmpt, 1>
{

public:

    //- Equivalent type of labels used for valid component indexing
    typedef SphericalTensor<label> labelType;


    // Member constants

        enum
        {
            rank = 2 // Rank of SphericalTensor is 2
        };


    // Static data members

        static const char* const typeName;
        static const char* componentNames[];
        static const SphericalTensor zero;
        static const SphericalTensor one;
        static const SphericalTensor max;
        static const SphericalTensor min;
        static const SphericalTensor I;
        static const SphericalTensor oneThirdI;
        static const SphericalTensor twoThirdsI;


    //- Component labeling enumeration
    enum components { II };


    // Constructors

        //- Construct null
        inline SphericalTensor();

        //- Construct given VectorSpace
        inline SphericalTensor
        (
            const VectorSpace<SphericalTensor<Cmpt>, Cmpt, 1>&
        );

        //- Construct given the component
        inline SphericalTensor(const Cmpt& tii);

        //- Construct from Istream
        inline SphericalTensor(Istream&);


    // Member Functions

        // Access

            inline const Cmpt& ii() const;
            inline Cmpt& ii();


        //- Transpose
        inline const SphericalTensor<Cmpt>& T() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Include inline implementations
#include "SphericalTensorI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
