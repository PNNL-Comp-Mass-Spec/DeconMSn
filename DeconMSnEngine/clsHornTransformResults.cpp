// Written by Navdeep Jaitly for the Department of Energy (PNNL, Richland, WA)
// Copyright 2006, Battelle Memorial Institute
// E-mail: navdeep.jaitly@pnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
// 
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0

#using <mscorlib.dll>
#include "clsHornTransformResults.h"
#include <exception>

namespace Decon2LS
{
	namespace HornTransform
	{
		clsHornTransformResults::clsHornTransformResults(void)
		{
		}

		clsHornTransformResults::~clsHornTransformResults(void)
		{
			delete marr_isotope_peak_indices ; 
		}




	}
}