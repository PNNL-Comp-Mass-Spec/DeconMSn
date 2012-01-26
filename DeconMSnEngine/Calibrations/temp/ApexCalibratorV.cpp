#include ".\apexcalibratorv.h"

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibratorV::ApexCalibratorV(void)
		{
		}

		ApexCalibratorV::~ApexCalibratorV(void)
		{
			int i = 0 ; 
		}

		CalibrationType ApexCalibratorV::GetCalibrationType() 
		{
			return F  ; 
		}

		int ApexCalibratorV::GetRawPointsApplyFFT(float *data_ptr, std::vector <double> *mzs, std::vector<double> *intensities)
		{
			return GetRawPointsApplyFFT(data_ptr, mzs, intensities, mint_num_points_in_scan) ; 
		}

		int ApexCalibratorV::GetRawPointsApplyFFT(float *data_ptr, std::vector <double> *mzs, std::vector<double> *intensities, int num_pts_used)
		{
			// no fft required here.
			if (num_pts_used > mint_num_points_in_scan)
				num_pts_used = mint_num_points_in_scan ; 

			int capacity = (int)mzs->capacity() ; 
			if (capacity < num_pts_used)
			{
				mzs->reserve(num_pts_used) ; 
				intensities->reserve(num_pts_used) ; 
			}
			double ms, it ; 
			float int_float ; 
			for (int i = 0 ; i < num_pts_used ; i++)
			{
				GetMassFromFreq(i, ms) ; 
				int_float = data_ptr[i] ; 
				it = (double) int_float ; 
				mzs->push_back(ms) ; 
				intensities->push_back(it) ; 
			}
			return num_pts_used ; 
		}

		void ApexCalibratorV::GetMassFromFreq(double freq, double &mass) 
		{
			mass = freq ; 
		}

		double ApexCalibratorV::Mass2Freq(double mass)
		{
			return mass ; 
		}
	}
}