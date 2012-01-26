#include ".\apexcalibratorvi.h"

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibratorVI::ApexCalibratorVI(void)
		{
		}

		ApexCalibratorVI::~ApexCalibratorVI(void)
		{
		}

		CalibrationType ApexCalibratorVI::GetCalibrationType() 
		{
			return A_OVER_F_PLUS_B  ; 
		}
		void ApexCalibratorVI::GetMassFromFreq(double freq, double &mass)
		{
			if(freq + mdbl_calib_const_b != 0)
				mass = mdbl_calib_const_a / (freq + mdbl_calib_const_b) ; 
			else if(freq - mdbl_calib_const_b <= 0)
				mass = mdbl_calib_const_a ; 
			else
				mass = 0 ;
			return ; 
		}

		double ApexCalibratorVI::Mass2Freq(double mass)
		{
			// Reverse the Freq2Mass equation and solve for frequency.
			mass = Helpers::absolute(mass) ; 
			return mdbl_calib_const_a/mass - mdbl_calib_const_b  ; 
		}

	}
}