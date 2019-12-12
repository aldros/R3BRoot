/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/
// ----------------------------------------------------------------
// -----                    R3BPspxPrecal2Cal                 -----
// -----            Created  20-03-2017 by I. Syndikus		  -----
// -----              Modified  Dec 2019  by M. Holl		  -----
// ----------------------------------------------------------------

#include <iostream>
#include <limits>

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TClonesArray.h"

#include "R3BEventHeader.h"
#include "R3BPspxCalData.h"
#include "R3BPspxCalPar.h"
#include "R3BPspxPrecal2Cal.h"
#include "R3BPspxPrecalData.h"

R3BPspxPrecal2Cal::R3BPspxPrecal2Cal()
    : fPrecalItems()
    , fCalItems()
{
}

R3BPspxPrecal2Cal::R3BPspxPrecal2Cal(const char* name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fPrecalItems()
    , fCalItems()
{
}

R3BPspxPrecal2Cal::~R3BPspxPrecal2Cal() {}

void R3BPspxPrecal2Cal::SetParameters(){

    LOG(INFO) << "In R3BPspxPrecal2Cal::SetParameters()" << FairLogger::endl;
    //--- Parameter Container ---
    Int_t nDet=fCalPar->GetNumDetectors();//Number of Detectors/Faces
    gain.resize(nDet);
    for(Int_t d=0; d<nDet; d++){
        Int_t nStrips=fCalPar->GetNumStrips().At(d);//Number of Strips
        gain[d].resize(nStrips);
        Int_t parOffset = d*nStrips*2 + (d+1)*3; // Position in parameter list. 2 parameters per strip + 3 "header" parameters per detector.
        for(Int_t s=0; s<nStrips; s++){
            TArrayF par = fCalPar->GetCalPar();//Array with the parameters
            gain[d][s]=par.At(parOffset+1);
            parOffset += 2; // move to next line in parameter file.
            LOG(INFO)<< "Det: " << d <<"\tstr: " << s << "\tgain: " << gain[d][s] << FairLogger::endl;
        }
    }
}

InitStatus R3BPspxPrecal2Cal::Init()
{
    /**
     * Initialize output data. Read input data and parameters.
     * The parameters get saved in dedicated arrays.
     * Print parameters, if verbosity is set to INFO.
     */

    FairRootManager* fMan = FairRootManager::Instance();
    fHeader = (R3BEventHeader*)fMan->GetObject("R3BEventHeader");
    // Figure out how many detectors were registered by the reader
    const char xy[2] = {'x','y'}; // orientation of detector face
    for(Int_t d = 0; ; d++){
        TClonesArray* tmp[2];

        for(Int_t f = 0; f<2; f++){
            tmp[f] = (TClonesArray*)fMan->GetObject(Form("Pspx%d_%dPrecal",d+1,xy[f])); // = branch name in TTree
        }
        if(tmp[0]==NULL&&tmp[1]==NULL){
            if (d==0)
            {
                printf("Couldn't get handle on PSPX precal items\n");
                return kFATAL;
            }
            break;
        }
        for(Int_t f = 0; f<2; f++){
            fPrecalItems.push_back(tmp[f]);
            fCalItems.push_back(new TClonesArray("R3BPspxCalData"));
            FairRootManager::Instance()->Register(Form("Pspx%d_%dCal",d+1,xy[f]), Form("Pspx%d_%d",d+1,xy[f]), fCalItems.back(), kTRUE);
        }
    }

    SetParameters();

    return kSUCCESS;
}

void R3BPspxPrecal2Cal::SetParContainers()
{
    /**
     * Initialize/Reads parameter file for conversion.
     */

    LOG(INFO) << "R3BPspxPrecal2Cal :: SetParContainers() ";

    fCalPar = (R3BPspxCalPar*)FairRuntimeDb::instance()->getContainer("R3BPspxCalPar");
    
    if (!fCalPar){
        LOG(ERROR) << "Could not get access to R3BPspxCalPar-Container." << FairLogger::endl;
        return;
    }

    fCalPar->printParams();
}

InitStatus R3BPspxPrecal2Cal::ReInit()
{
    /**
     * Initialize/Reads parameter file for conversion.
     */

    LOG(INFO) << " R3BPspxPrecal2Cal :: ReInit() ";

    fCalPar = (R3BPspxCalPar*)FairRuntimeDb::instance()->getContainer("R3BPspxCalPar");

    if (!fCalPar){
        LOG(ERROR) << "Could not get access to R3BPspxCalPar-Container." << FairLogger::endl;
        return kFATAL;
    }

    return kSUCCESS;
}

void R3BPspxPrecal2Cal::Exec(Option_t* option)
{
    /**
     * Does the conversion from Precal to Cal level. It is called for every event.
     * Applies (strip specific) gains to the energy entries of every strip. This is necessary
     * for energy calibration.
     */
    for (Int_t d = 0; d<fPrecalItems.size(); d++){
        if (!fPrecalItems[d]){
            printf("Cannot access PSPX%d_%d precal items\n",(d/2)+1,(d%2)+1);
            return;
        }
        if (fCalPar->GetNumStrips().At(d) == 0) continue;

        Int_t nPrecal = fPrecalItems[d]->GetEntries();
        // Calculating strip and energys
        for (Int_t i = 0; i < nPrecal; i++){

            R3BPspxPrecalData* precalData = (R3BPspxPrecalData*)fPrecalItems[d]->At(i);

            Int_t strip = precalData->GetStrip();
            Float_t energy = (precalData->GetEnergy1()+precalData->GetEnergy2()) * gain[d][strip-1];
            Float_t pos = (precalData->GetEnergy1()-precalData->GetEnergy2())/(precalData->GetEnergy1()+precalData->GetEnergy2());
            new ((*fCalItems[d])[fCalItems[d]->GetEntriesFast()])R3BPspxCalData(strip, energy, pos);
        }
    }
}

void R3BPspxPrecal2Cal::FinishEvent() {
    for(Int_t i = 0; i<fPrecalItems.size() ; i++){
        fPrecalItems[i]->Clear(); 
    }
    for(Int_t i = 0; i<fCalItems.size() ; i++){
        fCalItems[i]->Clear(); 
    }
}

void R3BPspxPrecal2Cal::FinishTask() {}

ClassImp(R3BPspxPrecal2Cal)
