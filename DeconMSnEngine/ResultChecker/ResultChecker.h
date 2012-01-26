#pragma once
#include <vector>
#include <map> 
#include <fstream> 
#include <string>
#include "../PeakProcessor/PeakProcessor.h" 
#include "../HornTransform/MassTransform.h" 
#include "../DeconEngineUtils.h"
#include "../Results/LCMSTransformResults.h"

namespace Engine
{
	namespace ResultChecker
	{
		class LCMSCheckResults
		{
			//! This class stores just those transform records which have been flagged as possible wrongly deisotoped
			/*! 
			Initial version, do not exactly know what this will look like. Winging it for the moment.
			*/		

			std::vector <Engine::HornTransform::IsotopeFitRecord> mvect_isotope_records ; 

			public:

				LCMSCheckResults() ; 
				~LCMSCheckResults() ; 

				void AddTransformsToCheck(std::vector<Engine::HornTransform::IsotopeFitRecord> &vect_isotope_record) ; 

				void WriteOutTransformsToCheck(char *filename)  ; 

				
				
		};
	}
}