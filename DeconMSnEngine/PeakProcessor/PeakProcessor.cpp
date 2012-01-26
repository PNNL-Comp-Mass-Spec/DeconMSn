// Written by Navdeep Jaitly for the Department of Energy (PNNL, Richland, WA)
// Copyright 2006, Battelle Memorial Institute
// E-mail: navdeep.jaitly@pnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
// 
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0

// PeakProcessor.cpp: implementation of the PeakProcessor class.
//
//////////////////////////////////////////////////////////////////////
#include "PeakProcessor.h"
#include <fstream>
#include <algorithm> 
#include <iostream>


namespace Engine
{
	namespace PeakProcessing
	{
		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////

		PeakProcessor::PeakProcessor()
		{
			mdbl_mz_tolerance_attention_list = 5.0 ; 
			mbln_chk_attention_list = false ; 
			SetPeakFitType(QUADRATIC) ; 
			mobj_peak_data = new PeakData() ; 
			mbln_centroided_data = false ; 
			menm_profile_type = PROFILE ; 

		}

		PeakProcessor::~PeakProcessor()
		{
			delete mobj_peak_data ; 
		}


		void PeakProcessor::ApplyMovingAverageFilter(std::vector<double> *vect_mz, std::vector<double> *vect_intensity, int num_points){
			mobj_peak_statistician.MovingAverageFilter(*vect_mz, *vect_intensity, num_points);

		}

		void PeakProcessor::LoadAttentionList(char *file_name)
		{
			const int BUFFER_SIZE = 512 ;
			std::fstream input_file(file_name, std::ios::binary) ; 

			char tolerance_str [BUFFER_SIZE] ;
			mmap_attention_list.clear() ; 

			while (!input_file.eof())
			{
				input_file.getline(tolerance_str, BUFFER_SIZE, '\n') ; 
				char *ptr = strstr(tolerance_str, "Tolerance=") ; 
				if (ptr != NULL)
				{
					double tolernce = atof(ptr+1) ; 
					this->mdbl_mz_tolerance_attention_list = tolernce ;
				}
				else
				{
					double mz_val_attention_list ; 
					mz_val_attention_list = atof(tolerance_str) ; 
					if (mz_val_attention_list != 0)
						this->mmap_attention_list.insert(std::pair<double, int>(mz_val_attention_list,1)) ; 
				}
			}
			input_file.close() ; 
		}



		void PeakProcessor::SetSignal2NoiseThreshold(double s2n)
		{
			this->mdbl_signal_2_noise_threshold = s2n ;
			if (mbln_thresholded_data)
			{
				if (mdbl_signal_2_noise_threshold != 0)
					mdbl_background_intensity = mdbl_peak_intensity_threshold / mdbl_signal_2_noise_threshold ;
				else
					mdbl_background_intensity = 1 ; 
			}
		}		
	
		void PeakProcessor::SetPeakIntensityThreshold(double threshold) 
		{
			this->mdbl_peak_intensity_threshold = threshold ; 
			if (mbln_thresholded_data)
			{
				if (mdbl_signal_2_noise_threshold != 0)
					mdbl_background_intensity = threshold / mdbl_signal_2_noise_threshold ;
				else if (threshold != 0)
					mdbl_background_intensity = threshold ; 
				else
					mdbl_background_intensity = 1 ; 
			}
		}
		void PeakProcessor::SetAttentionListTolerance(double mz_tol)
		{
			this->mdbl_mz_tolerance_attention_list = mz_tol ; 
		}

		void PeakProcessor::SetPeakFitType(PEAK_FIT_TYPE type)
		{
			this->menm_peak_fit_type = type ; 
			mobj_peak_fit.SetOptions(type) ; 
		}

		void PeakProcessor::SetPeaksProfileType(bool profile)
		{
			if(profile)
				menm_profile_type = PROFILE;			
			else
				menm_profile_type = CENTROIDED;
		}

		void PeakProcessor::SetCheckAttentionList(bool set)
		{
			this->mbln_chk_attention_list = set ;
		}

		void PeakProcessor::SetOptions(double s2n, double thresh, bool thresholded, PEAK_FIT_TYPE type)
		{
			mbln_thresholded_data = thresholded ; 			
			// signal to noise should ideally be set before PeakIntensityThreshold
			SetSignal2NoiseThreshold(s2n) ; 
			SetPeakIntensityThreshold(thresh) ; 
			SetPeakFitType(type) ; 			
		}


		int PeakProcessor::DiscoverPeaks (std::vector<double> *vect_mz, std::vector<double> *vect_intensity, double start_mz, double stop_mz) 
		{

			if(vect_intensity->size() < 1)
				return 0 ; 

			mobj_peak_data->Clear() ; 
			int num_data_pts = (int) (*vect_intensity).size() ; 
			int ilow ; 
			int ihigh ; 

			Peak peak  ;

			int start_index = mobj_pk_index.GetNearestBinary(*vect_mz, start_mz, 0, num_data_pts-1) ; 
			int stop_index = mobj_pk_index.GetNearestBinary(*vect_mz, stop_mz, start_index, num_data_pts-1) ; 
			if (start_index <= 0)
				start_index = 1 ; 
			if (stop_index >= (int)vect_mz->size() -2)
				stop_index = (int)vect_mz->size() - 2 ; 

			for (int index = start_index ; index <= stop_index ; index++)
			{
				double FWHM = -1 ;
				double current_intensity = (*vect_intensity)[index] ; 
				double last_intensity = (*vect_intensity)[index-1] ; 
				double next_intensity = (*vect_intensity)[index+1]  ; 
				double current_mz = (*vect_mz)[index] ; 
				
				if (menm_profile_type == CENTROIDED)
				{
					if (current_intensity >= mdbl_peak_intensity_threshold)
					{
						double mass_ = (*vect_mz)[index] ; 
						double SN = current_intensity / mdbl_peak_intensity_threshold ; 
						double FWHM = 0.6 ; 
						peak.Set(mass_, current_intensity, SN, mobj_peak_data->GetNumPeaks(), index, FWHM) ;	
						mobj_peak_data->AddPeak(peak) ; 
					}
				}	
				else if (menm_profile_type == PROFILE)
				{
					 if(current_intensity >= last_intensity && current_intensity >= next_intensity
							&& current_intensity >= this->mdbl_peak_intensity_threshold)
					{
						//See if the peak meets the conditions.
						//The peak data will be found at _transformData->begin()+i+1.
						double SN = 0 ; 
						
						if (!mbln_thresholded_data)
							SN = this->mobj_peak_statistician.FindSignalToNoise(current_intensity, (*vect_intensity), index);
						else
							SN = current_intensity / mdbl_background_intensity ; 

						// Run Full-Width Half-Max algorithm to try and squeak out a higher SN
						if(SN < this->mdbl_signal_2_noise_threshold)
						{
							double mass_ = (*vect_mz)[index] ; 
							FWHM = this->mobj_peak_statistician.FindFWHM((*vect_mz), (*vect_intensity), index, SN);
							if(FWHM > 0 && FWHM < 0.5)
							{
								ilow = mobj_pk_index.GetNearestBinary((*vect_mz), current_mz  - FWHM, 0, index);
								ihigh = mobj_pk_index.GetNearestBinary((*vect_mz), current_mz + FWHM, index, stop_index);

								double low_intensity = (*vect_intensity)[ilow] ; 
								double high_intensity = (*vect_intensity)[ihigh] ;

								double sum_intensity = low_intensity + high_intensity ; 
								if(sum_intensity)
									SN = (2.0 * current_intensity) / sum_intensity ;
								else
									SN = 10;
							}
						}
						// Found a peak, make sure it is in the attention list, if there is one.
						if(SN >= this->mdbl_signal_2_noise_threshold && ( !this->mbln_chk_attention_list || this->IsInAttentionList(current_mz))) 
						{
							// Find a more accurate m/z location of the peak.
							double fittedPeak = mobj_peak_fit.Fit(index, (*vect_mz), (*vect_intensity)); 
							if (FWHM == -1)
							{
								FWHM = this->mobj_peak_statistician.FindFWHM((*vect_mz), (*vect_intensity), index, SN);
							}

							if (FWHM > 0)
							{
								peak.Set(fittedPeak, current_intensity, SN, mobj_peak_data->GetNumPeaks(), index, FWHM) ;	
								mobj_peak_data->AddPeak(peak) ; 
							}
							// move beyond peaks have the same intensity.
							bool incremented = false ; 
							while( index < num_data_pts && (*vect_intensity)[index] == current_intensity)
							{
								incremented = true ; 
								index++ ;
							}
							if(index > 0 && index < num_data_pts 
								&& incremented)
								index-- ; 
						}
					}
				}
			}
			mobj_peak_data->mptr_vect_mzs = vect_mz ; 
			mobj_peak_data->mptr_vect_intensities = vect_intensity ; 

			return mobj_peak_data->GetNumPeaks() ; 
		}


		double PeakProcessor::GetClosestPeakMzFast(double peakMz, Engine::PeakProcessing::Peak &selectedPeak){
			double min_score = 1.00727638;
			Engine::PeakProcessing::Peak thisPeak;
			double score;				

			selectedPeak.mdbl_mz = 0.0;

			try{
				int high = mobj_peak_data->mvect_peak_tops.size();
				int low = 0;
				int mid = (low + high)/2;
				bool peakFound = false;

				while (low <= high && !peakFound){
					mid = (low + high)/2;
					thisPeak = mobj_peak_data->mvect_peak_tops[mid];
					score = (peakMz - thisPeak.mdbl_mz) * (peakMz-thisPeak.mdbl_mz);
					if ( score <= min_score ){

						//we've found a peak that gives a score lower than what we expect.
						//Instead of redividing, maybe we proceed sequentially from here on
						//and stop when we get a score that's higher than our current score
						selectedPeak = thisPeak;
						min_score = score;
						peakFound = true;
						//keep going lower till the score improves, there is no point in going 
						//to the right

						while ( score<= min_score && (mid - 1) >= 0 ) {
							thisPeak = mobj_peak_data->mvect_peak_tops[mid-1];
							score = (peakMz - thisPeak.mdbl_mz) * (peakMz-thisPeak.mdbl_mz);
							if ( score < min_score ){
								selectedPeak = thisPeak;
								min_score = score;
								mid -= 1;
								peakFound = true;
							}
							else{
								break;
							}
						}
					}
					else if ( score > min_score){
						high = mid - 1;
					}
				}

			}
			catch( char*mesg){
			}

			return selectedPeak.mdbl_mz;
		}
		//This should be changed to be a binary search, especially for Decon2LS if it's using the same code
		//I am assuming that the peak list is sorted by mz?
		double PeakProcessor::GetClosestPeakMz(double peakMz, Engine::PeakProcessing::Peak &selectedPeak)
		{
			//looks through the peak list and finds the closest peak to peakMz
			double min_score  = 1.00727638; //enough for one charge away
			Engine::PeakProcessing::Peak finalPeak; 
			Engine::PeakProcessing::Peak thisPeak;
			finalPeak.mdbl_mz = 0.0 ; 
			double score;				
         
			try
			{
				int numberPeaks = mobj_peak_data->mvect_peak_tops.size();
				//this exhaustive evaluates all peaks to find the score that's the lowest possible score betwee
				//the given mz and the peak list mz values.
				for (int peakCount = 0; peakCount < numberPeaks; peakCount++)
				{
					thisPeak = mobj_peak_data->mvect_peak_tops[peakCount];
					score = (peakMz - thisPeak.mdbl_mz) * (peakMz-thisPeak.mdbl_mz);
					if (score < min_score)
					{
						min_score = score;
						finalPeak = mobj_peak_data->mvect_peak_tops[peakCount];
					}
				}			
				selectedPeak = finalPeak;
			}
			catch(char *mesg) 
			{
				finalPeak.mdbl_mz = 0.0 ; 
				selectedPeak.mdbl_mz = 0.0 ; 
				selectedPeak.mdbl_intensity = 0.0; 
			}
			
			return finalPeak.mdbl_mz;
		}

		
		int PeakProcessor::DiscoverPeaks (std::vector<double> *vect_mz, std::vector<double> *vect_intensity) 
		{
			if (vect_mz->size() == 0)
				return 0 ; 
			double min_mz = vect_mz->at(0) ; 
			int num_elements = vect_mz->size()-1 ; 
			double max_mz = vect_mz->at(num_elements) ; 
			return DiscoverPeaks (vect_mz, vect_intensity, min_mz, max_mz) ;  
		}

		bool PeakProcessor::ConvertPeakListToSpectra(std::vector<double> *vect_mz, std::vector<double> *vect_intensity){
			vect_intensity->clear();
			vect_mz->clear();
			Peak peak;

			int numPeaks = mobj_peak_data->GetNumPeaks();
			for (int i = 0; i < numPeaks; i++){
				mobj_peak_data->GetPeak(i, peak);
				vect_intensity->push_back(peak.mdbl_intensity);
				vect_mz->push_back(peak.mdbl_mz);
			}
			


			return false;
		}

		bool PeakProcessor::DiscoverPeak(std::vector<double> &vect_mz, std::vector<double> &vect_intensity, double start_mz, double stop_mz, Peak &pk, bool find_fwhm = false, bool find_sn =false, bool fit_peak = false )
		{
			int start_index = mobj_pk_index.GetNearest(vect_mz, start_mz, 0) ; 
			int stop_index = mobj_pk_index.GetNearest(vect_mz, stop_mz, start_index) ; 

			pk.mdbl_mz = 0 ; 
			pk.mdbl_intensity = 0 ; 
			pk.mint_data_index = -1 ; 
			pk.mdbl_FWHM = 0 ; 
			pk.mdbl_SN = 0 ;

			double max_intensity = 0 ; 
			bool found = false ; 
			for (int i = start_index ; i < stop_index ; i++)
			{
				double intensity = vect_intensity[i] ; 
				if (intensity > max_intensity)
				{
					max_intensity = intensity ; 
					pk.mdbl_mz = vect_mz[i] ; 
					pk.mdbl_intensity = intensity ; 
					pk.mint_data_index = i ; 
					found = true ; 
				}
			}
			if (found)
			{
				if (find_fwhm)
					pk.mdbl_FWHM = mobj_peak_statistician.FindFWHM(vect_mz, vect_intensity, pk.mint_data_index) ; 
				if (find_sn)
					pk.mdbl_SN = mobj_peak_statistician.FindSignalToNoise(pk.mdbl_intensity, vect_intensity, pk.mint_data_index) ; 
				if (fit_peak)
					pk.mdbl_mz = mobj_peak_fit.Fit(pk.mint_data_index, vect_mz, vect_intensity); 

			}
			return found ; 
		}

		bool PeakProcessor::IsInAttentionList(double mz_val)
		{
			if (mmap_attention_list.empty())
				return false ; 
			std::map<double, int>::iterator closest_iterator = mmap_attention_list.lower_bound(mz_val - mdbl_mz_tolerance_attention_list) ; 
			if ((*closest_iterator).first <= mz_val + mdbl_mz_tolerance_attention_list)
				return true ; 
			return false ; 
		}


		void PeakProcessor::Clear()
		{
			mmap_attention_list.clear() ; 
			mobj_peak_data->Clear() ; 
		}
		void PeakProcessor::FilterPeakList(double tolerance)
		{
			mobj_peak_data->FilterList(tolerance) ; 
		}
		double PeakProcessor::GetFWHM (std::vector<double> &vect_mz, std::vector<double> &vect_intensity, int data_index, double SN)
		{
			return mobj_peak_statistician.FindFWHM(vect_mz, vect_intensity, data_index, SN) ; 
		}
		double PeakProcessor::GetFWHM (std::vector<double> &vect_mz, std::vector<double> &vect_intensity, double peak)
		{
			int index = mobj_pk_index.GetNearest(vect_mz, peak, 0) ;  
			return mobj_peak_statistician.FindFWHM(vect_mz, vect_intensity, index) ; 
		}

		double PeakProcessor::GetSN (std::vector<double> &vect_intensity, int data_index)
		{
			return mobj_peak_statistician.FindSignalToNoise(vect_intensity[data_index], vect_intensity, data_index) ; 
		}
		double PeakProcessor::GetSN (std::vector<double> &vect_mz, std::vector<double> &vect_intensity, double peak)
		{
			int index = mobj_pk_index.GetNearest(vect_mz, peak, 0) ;  
			return mobj_peak_statistician.FindSignalToNoise(vect_intensity[index], vect_intensity, index) ; 
		}

	}
}

