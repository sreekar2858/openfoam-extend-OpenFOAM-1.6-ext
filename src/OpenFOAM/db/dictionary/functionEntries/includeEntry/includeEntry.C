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

#include "includeEntry.H"
#include "dictionary.H"
#include "IFstream.H"
#include "addToMemberFunctionSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const Foam::word Foam::functionEntries::includeEntry::typeName
(
    Foam::functionEntries::includeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeEntry
int Foam::functionEntries::includeEntry::debug(0);

namespace Foam
{
namespace functionEntries
{
    addToMemberFunctionSelectionTable
    (
        functionEntry,
        includeEntry,
        execute,
        dictionaryIstream
    );

    addToMemberFunctionSelectionTable
    (
        functionEntry,
        includeEntry,
        execute,
        primitiveEntryIstream
    );
}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::fileName Foam::functionEntries::includeEntry::includeFileName
(
    Istream& is
)
{
    fileName fName(is);
    fName.expand();

    if (fName.size() && fName[0] != '/')
    {
        fName = fileName(is.name()).path()/fName;
    }

    return fName;
}


bool Foam::functionEntries::includeEntry::execute
(
    dictionary& parentDict,
    Istream& is
)
{
    IFstream fileStream(includeFileName(is));

    if (fileStream)
    {
        parentDict.read(fileStream);
        return true;
    }
    else
    {
        FatalIOErrorIn
        (
            "functionEntries::includeEntry::includeEntry"
            "(dictionary& parentDict,Istream& is)",
            is
        )   << "Cannot open include file " << fileStream.name()
            << " while reading dictionary " << parentDict.name()
            << exit(FatalIOError);

        return false;
    }
}

bool Foam::functionEntries::includeEntry::execute
(
    const dictionary& parentDict,
    primitiveEntry& entry,
    Istream& is
)
{
    IFstream fileStream(includeFileName(is));

    if (fileStream)
    {
        entry.read(parentDict, fileStream);
        return true;
    }
    else
    {
        FatalIOErrorIn
        (
            "functionEntries::includeEntry::includeEntry"
            "(dictionary& parentDict, primitiveEntry& entry, Istream& is)",
            is
        )   << "Cannot open include file " << fileStream.name()
            << " while reading dictionary " << parentDict.name()
            << exit(FatalIOError);

        return false;
    }
}

// ************************************************************************* //
