#pragma once
#include "CalibratorImp.h"

namespace Engine
{
	namespace Calibrations
	{

		class   ApexCalibrator0 :
			public CCalibratorImp
		{
		public:
			ApexCalibrator0(void);
			~ApexCalibrator0(void);

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass) ;
			double GetFrequencyFromCubicEquation(double p, double q, double r, double mass);
		};
	}
}