// Written by Bryson Gibbons for the Department of Energy (PNNL, Richland, WA)
// Copyright 2017, Battelle Memorial Institute
// E-mail: bryson.gibbons@pnnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
//
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#include ".\DTAScanTypeGeneration.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace Engine
{
	namespace DTAProcessing
	{
		DTAScanTypeGeneration::DTAScanTypeGeneration(void)
		{
			mobj_raw_data_dta = NULL;
		}

		DTAScanTypeGeneration::~DTAScanTypeGeneration(void)
		{
			//delete mobj_raw_data_dta; // we just have a copy of it, and DTAGeneration controls it
		}

		void DTAScanTypeGeneration::GenerateScanTypeFile()
		{
			int min = mobj_raw_data_dta->GetFirstScanNum();
			int max = mobj_raw_data_dta->GetLastScanNum();

			mfile_dta_scanType << "ScanNumber\tScanTypeName\tScanType\tScanStartTime" << endl;

			for (int scan = min; scan <= max; scan++)
			{
				bool isFT = mobj_raw_data_dta->IsFTScan(scan);
				int actType = mobj_raw_data_dta->GetSpectrumType(scan);
				int msLevel = mobj_raw_data_dta->GetMSLevel(scan);
				double time = mobj_raw_data_dta->GetScanTime(scan);

				string scanTypeName = "MS";
				if (isFT)
				{
					scanTypeName = "HMS";
				}

				if (msLevel > 1)
				{
					scanTypeName += "n";

					switch (actType)
					{
					case 2:
						//ETD, or ETciD or EThcD
						scanTypeName = "ETD-" + scanTypeName;
						break;
					case 3:
						//HCD
						scanTypeName = "HCD-" + scanTypeName;
						break;
					case 1:
						// CID
						scanTypeName = "CID-" + scanTypeName;
						break;
					default:
						// We don't handle it, don't make assumptions
						break;
					}
				}

				mfile_dta_scanType << scan << "\t" << scanTypeName << "\t" << msLevel << "\t" << time << endl;
			}
		}
	}
}