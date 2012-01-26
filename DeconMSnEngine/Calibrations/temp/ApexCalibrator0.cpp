#include ".\apexcalibrator0.h"
#include <float.h>

namespace Engine
{
	namespace Calibrations
	{
		ApexCalibrator0::ApexCalibrator0(void)
		{
		}

		ApexCalibrator0::~ApexCalibrator0(void)
		{
		}

		void ApexCalibrator0::GetMassFromFreq(double freq, double &mass)
		{
			if (freq == 0)
			{
				mass = MAX_MASS ; 
				return ; 
			}
			mass =  mdbl_calib_const_a / freq + mdbl_calib_const_b / (freq * freq) + mdbl_calib_const_c / (freq * freq * freq) ; 
			return ; 
		}

		double ApexCalibrator0::Mass2Freq(double mass)
		{
			// Reverse the Freq2Mass equation and solve for frequency.
			mass = Helpers::absolute(mass) ; 
			double p, q, r; 
			p = -mdbl_calib_const_a / mass ; 
			q = -mdbl_calib_const_b / mass ; 
			r = -mdbl_calib_const_c / mass ; 
			return GetFrequencyFromCubicEquation(p, q, r, mass) ; 					
		}

		double ApexCalibrator0::GetFrequencyFromCubicEquation(double p, double q, double r, double mass)
		{
			// Solves the equation F^3 + p F^2 + q F + r = 0  and chooses root that 
			// is closes to mass. 
			if (mass == 0)
				mass = 1 ; 

			double roots[3] ; 
			int num_roots = Helpers::CubeRoots(p, q, r, roots) ; 

			int best = 0 ; 
			double best_delta = DBL_MAX ; 
			for (int i = 0 ; i < num_roots ; i++)
			{
				double this_mass ; 
				GetMassFromFreq(roots[i], this_mass); 
				double delta = Helpers::absolute(this_mass - mass) ; 
				if (delta  < best_delta)
				{
					best_delta = delta ;
					best = i ; 
				}
			}
			return roots[best] ; 
		}
	}
}