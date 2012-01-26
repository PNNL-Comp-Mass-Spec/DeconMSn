#pragma once
#include "CalibratorImp.h"

namespace Engine
{
	namespace Calibrations
	{

		class   ApexCalibratorVIII : public CCalibratorImp
		{
		public:

			ApexCalibratorVIII(void);
			~ApexCalibratorVIII(void);

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass) ;
		};
	}
}