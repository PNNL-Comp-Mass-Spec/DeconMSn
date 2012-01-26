#pragma once
#include "CalibratorImp.h"
#include "../Utilities/Helpers.h" 

namespace Engine
{
	namespace Calibrations
	{
		class   ApexCalibratorVI :
			public CCalibratorImp
		{
		public:
			ApexCalibratorVI(void);
			~ApexCalibratorVI(void);

			CalibrationType GetCalibrationType() ;

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass);
		};
	}
}