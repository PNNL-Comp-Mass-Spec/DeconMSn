#include ".\apexcalibratorvii.h"

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibratorVII::ApexCalibratorVII(void)
		{
		}

		ApexCalibratorVII::~ApexCalibratorVII(void)
		{
		}

		CalibrationType ApexCalibratorVII::GetCalibrationType() 
		{
			return A_OVER_F_PLUS_B_PLUS_CI  ; 
		}

		void ApexCalibratorVII::SetIntensityNormalizer(double norm)
		{
			mdbl_intensity_normalizer = norm ; 
		}

		double ApexCalibratorVII::GetIntensityNormalizer()
		{
			return mdbl_intensity_normalizer ; 
		}
		void ApexCalibratorVII::GetMassFromFreq(double freq, double &mass)
		{
			if(freq == 0)
			{	
				mass = MAX_MASS ;
				return ; 
			}
			if ( freq - mdbl_calib_const_b + mdbl_calib_const_c * mdbl_intensity_normalizer < 0 ) 
			{
				mass = mdbl_calib_const_a / freq ; 
				return ; 
			}
			
			mass = mdbl_calib_const_a / (freq + mdbl_calib_const_b + mdbl_calib_const_c * mdbl_intensity_normalizer) ; 
		}

		double ApexCalibratorVII::Mass2Freq(double mass)
		{
			if (mass == 0)
				mass = 1 ; 
			return mdbl_calib_const_a/mass - mdbl_calib_const_b - mdbl_calib_const_c * this->mdbl_intensity_normalizer ; 
		}
	}
}