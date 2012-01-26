// Written by Navdeep Jaitly and Anoop Mayampurath for the Department of Energy (PNNL, Richland, WA)
// Copyright 2006, Battelle Memorial Institute
// E-mail: navdeep.jaitly@pnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
// 
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once
#using <mscorlib.dll>
#include "clsPeakProcessor.h" 
#include "clsTransformResults.h" 
#include "clsHornTRansformParameters.h" 
#include "clsRawData.h" 
#include "clsDTAGenerationParameters.h"
namespace Decon2LS
{
	public __value enum enmProcessState {IDLE = 0, RUNNING, COMPLETE, ERROR}; 
	
	public __gc class clsProcRunner
	{
		int mint_percent_done ; 
		int mint_current_scan ; 
		enmProcessState menm_state ; 
		System::String *mstr_file_name ; 
		System::String *mstr_output_path_for_dta_creation ; 
		Decon2LS::Readers::FileType menm_file_type ;
		Decon2LS::Peaks::clsPeakProcessorParameters *mobj_peak_parameters ; 
		Decon2LS::HornTransform::clsHornTransformParameters *mobj_transform_parameters ; 
		Decon2LS::Readers::clsRawDataPreprocessOptions *mobj_fticr_preprocess_parameters ; 
		Decon2LS::Results::clsTransformResults *mobj_results ; 
		Decon2LS::DTAGeneration::clsDTAGenerationParameters *mobj_dta_generation_parameters ;		

		Decon2LS::Results::clsTransformResults* CreateTransformResults(System::String *file_name, 
			Decon2LS::Readers::FileType file_type, Decon2LS::Peaks::clsPeakProcessorParameters *peak_parameters, 
			Decon2LS::HornTransform::clsHornTransformParameters *transform_parameters, 
			Decon2LS::Readers::clsRawDataPreprocessOptions *fticr_preprocess_parameters, 
			bool save_peaks, bool transform) ;
	public:
		clsProcRunner(void);
		~clsProcRunner(void);
		void Reset()
		{
			mint_percent_done = 0 ; 
			mint_current_scan = 0 ; 
			menm_state = IDLE ; 
		}
		
		void CreateTransformResultWithPeaksOnly() ; 
		void CreateTransformResultWithNoPeaks() ; 
		void CreateTransformResults() ; 
		void MemoryTest() ; 
		void CreateDTAFile() ; 

		__property int get_CurrentScanNum()
		{
			if (menm_state == IDLE)
				return  0 ;
			return  mint_current_scan ;
		}

		__property int get_PercentDone()
		{
			if (menm_state == IDLE)
				return  0 ;
			else if (menm_state == RUNNING)
				return  mint_percent_done ;
			else
				return 100 ; 
		}
		__property int get_ProcessState()
		{
			return menm_state ; 
		}
		__property System::String* get_FileName()
		{
			return mstr_file_name ; 
		}
		__property void set_FileName(System::String* file_name)
		{
			mstr_file_name = file_name ; 
		}		
		__property Decon2LS::Readers::FileType get_FileType()
		{
			return menm_file_type ; 
		}
		__property void set_FileType(Decon2LS::Readers::FileType file_type)
		{
			menm_file_type = file_type ; 
		}
		__property System::String* get_OutputPathForDTACreation()
		{
			return mstr_output_path_for_dta_creation ; 
		}
		__property void set_OutputPathForDTACreation(System::String* path)
		{
			mstr_output_path_for_dta_creation = path ; 
		}
		__property int get_trial()
		{
			return 1 ;
		}
		__property Decon2LS::Peaks::clsPeakProcessorParameters* get_PeakProcessorParameters()
		{
			return mobj_peak_parameters ; 
		}
		__property void set_PeakProcessorParameters(Decon2LS::Peaks::clsPeakProcessorParameters *peak_parameters)
		{
			mobj_peak_parameters = peak_parameters ; 
		}
		__property Decon2LS::HornTransform::clsHornTransformParameters* get_HornTransformParameters()
		{
			return mobj_transform_parameters ; 
		}
		__property void set_HornTransformParameters(Decon2LS::HornTransform::clsHornTransformParameters *transform_parameters)
		{
			mobj_transform_parameters = transform_parameters ; 
		}
		__property Decon2LS::Results::clsTransformResults* get_HornTransformResults()
		{
			return mobj_results ; 
		}
		__property Decon2LS::DTAGeneration::clsDTAGenerationParameters* get_DTAGenerationParameters()
		{
			return mobj_dta_generation_parameters ;
		}
		__property void  set_DTAGenerationParameters(Decon2LS::DTAGeneration::clsDTAGenerationParameters *dta_generation_parameters)
		{
			mobj_dta_generation_parameters  = dta_generation_parameters;
		}
		__property Decon2LS::Readers::clsRawDataPreprocessOptions* get_FTICRPreprocessOptions()
		{
			return mobj_fticr_preprocess_parameters ;
		}	
		__property void  set_FTICRPreprocessOptions(Decon2LS::Readers::clsRawDataPreprocessOptions *parameters)
		{
			mobj_fticr_preprocess_parameters = parameters ;
		}
		
	};
}