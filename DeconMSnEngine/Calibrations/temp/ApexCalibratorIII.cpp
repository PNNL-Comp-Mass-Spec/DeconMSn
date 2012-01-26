#include ".\apexcalibratoriii.h"

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibratorIII::ApexCalibratorIII(void)
		{
		}

		ApexCalibratorIII::~ApexCalibratorIII(void)
		{
		}

		CalibrationType ApexCalibratorIII::GetCalibrationType() 
		{
			return A_OVER_F_PLUS_B_OVER_FSQ_PLUS_C ; 
		}

		void ApexCalibratorIII::GetMassFromFreq(double freq, double &mass)
		{
			if(freq == 0)
			{
				mass = MAX_MASS ; 
				return ;
			}
			mass = mdbl_calib_const_a / freq + mdbl_calib_const_b / (freq * freq) + mdbl_calib_const_c ; 
		}

		double ApexCalibratorIII::Mass2Freq(double mass)
		{
			// Reverse the Freq2Mass equation and solve for frequency.
			double a ; 
			mass = Helpers::absolute(mass) ; 
			a = (mass - mdbl_calib_const_c) ; 
			if (a == 0)
				a = 1 ; 
			return GetFrequencyFromQuadraticEquation(-1*mdbl_calib_const_a/a, -1*mdbl_calib_const_b/a, mass) ; 					
		}

		double ApexCalibratorIII::GetFrequencyFromQuadraticEquation(double b, double c, double mass)
		{
			double roots[2] ; 
			Helpers::SolveQuadraticEquation(b, c, roots) ; 					
			if (roots[0] < 0 && roots[1] < 0)
				// both are negative frequencies. return MAX_MASS 
				return 0 ; 
			// otherwise return the positive one, if one of them is negative.
			if (roots[0] < 0)
				return roots[1] ; 
			if (roots[1] < 0)
				return roots[0] ; 

			// otherwise, return the one that gives a mass value closer to the one return.
			double mass1 ; 
			GetMassFromFreq(roots[0], mass1) ; 
			double mass_delta1 = mass1 - mass ; 
			double mass2 ; 
			GetMassFromFreq(roots[1], mass2) ; 
			double mass_delta2 = mass2 - mass ; 
			if (Helpers::absolute(mass_delta1) < Helpers::absolute(mass_delta2))
				return roots[0] ; 
			return roots[1] ; 					
		}
	}
}