#pragma once
#include "CalibratorImp.h"

namespace Engine
{
	namespace Calibrations
	{
		class   ApexCalibratorVII : public CCalibratorImp
		{
			double mdbl_intensity_normalizer ; 
		public:

			ApexCalibratorVII(void);
			~ApexCalibratorVII(void);

			CalibrationType GetCalibrationType() ;
			void SetIntensityNormalizer(double norm) ;
			double GetIntensityNormalizer() ; 

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass);
		};
	}
}