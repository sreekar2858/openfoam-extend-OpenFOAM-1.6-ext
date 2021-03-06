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

Info << nl << "Creating autocorrelation functions." << endl;

IOdictionary mdTransportProperitesDict
(
    IOobject
    (
        "mdTransportProperitesDict",
        mesh.time().system(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE,
        false
    )
);

const dictionary& autocorrelationFunctionDict
(
    mdTransportProperitesDict.subDict("autocorrelationFunctions")
);

//- Velocity autocorrelation function

Info << tab << "velocty" << endl;

const dictionary& velocityACFDict
(
    autocorrelationFunctionDict.subDict("velocity")
);

correlationFunction<vector> vacf
(
    mesh,
    velocityACFDict,
    molecules.size()
);

bool writeVacf(Switch(velocityACFDict.lookup("writeFile")));

//- Pressure autocorrelation function

Info << tab << "pressure" << endl;

const dictionary& pressureACFDict
(
    autocorrelationFunctionDict.subDict("pressure")
);

correlationFunction<vector> pacf
(
    mesh,
    pressureACFDict,
    1
);

bool writePacf(Switch(pressureACFDict.lookup("writeFile")));

//- Heat flux autocorrelation function

Info << tab << "heat flux" << endl;

const dictionary& heatFluxACFDict
(
    autocorrelationFunctionDict.subDict("heatFlux")
);

correlationFunction<vector> hfacf
(
    mesh,
    heatFluxACFDict,
    1
);

bool writeHFacf(Switch(heatFluxACFDict.lookup("writeFile")));
