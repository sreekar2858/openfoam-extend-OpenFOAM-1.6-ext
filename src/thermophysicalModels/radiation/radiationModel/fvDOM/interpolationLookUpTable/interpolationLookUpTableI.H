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

template<class Type>
inline Foam::label
Foam::interpolationLookUpTable<Type>::findFieldIndex
(
    const word& fieldName
) const
{
    return fieldIndices_[fieldName];
}


template<class Type>
inline const Foam::List<Foam::dictionary>&
Foam::interpolationLookUpTable<Type>::output() const
{
    return output_;
}


template<class Type>
inline const Foam::List<Foam::dictionary>&
Foam::interpolationLookUpTable<Type>::entries() const
{
    return entries_;
}


template<class Type>
inline const Foam::List<Foam::scalar>&
Foam::interpolationLookUpTable<Type>::min() const
{
    return min_;
}


template<class Type>
inline const Foam::List<Foam::label>&
Foam::interpolationLookUpTable<Type>::dim() const
{
    return dim_;
}


template<class Type>
inline const Foam::List<Foam::scalar>&
Foam::interpolationLookUpTable<Type>::delta() const
{
    return delta_;
}


template<class Type>
inline const Foam::List<Foam::scalar>&
Foam::interpolationLookUpTable<Type>::max() const
{
    return max_;
}


template<class Type>
inline Foam::word Foam::interpolationLookUpTable<Type>::tableName() const
{
    return fileName_.name();
}


// ************************************************************************* //
