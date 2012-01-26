#include ".\apexcalibratoriv.h"

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibratorIV::ApexCalibratorIV(void)
		{
		}

		ApexCalibratorIV::~ApexCalibratorIV(void)
		{
		}

		CalibrationType ApexCalibratorIV::GetCalibrationType() 
		{
			return AF_PLUS_B  ; 
		}
		void ApexCalibratorIV::GetMassFromFreq(double freq, double &mass)
		{
			mass = mdbl_calib_const_a * freq + mdbl_calib_const_b ; 
		}
		
		double ApexCalibratorIV::Mass2Freq(double mass)
		{
			// Reverse the Freq2Mass equation and solve for frequency.
			mass = Helpers::absolute(mass) ; 
			return (mass - mdbl_calib_const_b) / mdbl_calib_const_a ;
		}
	}
}