// Written by Bryson Gibbons for the Department of Energy (PNNL, Richland, WA)
// Copyright 2017, Battelle Memorial Institute
// E-mail: bryson.gibbons@pnnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
//
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

#include "../Readers/RawData.h"
#include <fstream>

namespace Engine
{
	namespace DTAProcessing
	{
		class DTAScanTypeGeneration
		{
		private:
		public:
			char mch_scanType_filename[256];
			std::ofstream mfile_dta_scanType;

			Engine::Readers::RawData *mobj_raw_data_dta;

			//! default constructor.
			DTAScanTypeGeneration(void);
			//! destructor.
			~DTAScanTypeGeneration(void);

			void GenerateScanTypeFile();
		};
	}
}