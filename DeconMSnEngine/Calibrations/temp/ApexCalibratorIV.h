#pragma once
#include "CalibratorImp.h"
#include "../Utilities/Helpers.h"

namespace Engine
{
	namespace Calibrations
	{
		class   ApexCalibratorIV :
			public CCalibratorImp
		{
		public:

			ApexCalibratorIV(void);
			~ApexCalibratorIV(void);

			CalibrationType GetCalibrationType() ;

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass);
		};
	}
}