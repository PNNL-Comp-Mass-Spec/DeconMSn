
#include ".\apexcalibratorix.h"

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibratorIX::ApexCalibratorIX(void)
		{
		}

		ApexCalibratorIX::~ApexCalibratorIX(void)
		{
		}
		CalibrationType ApexCalibratorIX::GetCalibrationType() 
		{
			return BRUKER_CALMET  ; 
		}
		void ApexCalibratorIX::GetMassFromFreq(double freq, double &mass)
		{
			if(freq != 0)
				mass = (-mdbl_calib_const_a - sqrt((mdbl_calib_const_a * mdbl_calib_const_a ) - 4 * (mdbl_calib_const_b - freq) * mdbl_calib_const_c)) / (2 * (mdbl_calib_const_b - freq)) ; 
			else
				mass = MAX_MASS ; 
		}

		double ApexCalibratorIX::Mass2Freq(double mass)
		{
			// Reverse the Freq2Mass equation and solve for frequency.
			mass = Helpers::absolute(mass) ; 
			if (mass != 0)
				mass = mdbl_calib_const_a / mass + mdbl_calib_const_c / (mass * mass) + mdbl_calib_const_b ; 
			return mass ; 
		}
	}
}