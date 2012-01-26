#pragma once
#include "CalibratorImp.h"
#include "../Utilities/helpers.h" 

namespace Engine
{
	namespace Calibrations
	{

		class   ApexCalibratorIII :public CCalibratorImp
		{
		public:
			ApexCalibratorIII(void);
			~ApexCalibratorIII(void);

			CalibrationType GetCalibrationType() ;
			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass) ;
			double GetFrequencyFromQuadraticEquation(double b, double c, double mass);
		};
	}
}