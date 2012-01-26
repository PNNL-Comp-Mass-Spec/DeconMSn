#pragma once
#include "CalibratorImp.h"

namespace Engine
{
	namespace Calibrations
	{
		class   ApexCalibratorI : public CCalibratorImp
		{
		public:
			ApexCalibratorI(void);
			~ApexCalibratorI(void);

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass);
			double GetFrequencyFromQuadraticEquation(double b, double c, double mass) ; 
		};
	}
}