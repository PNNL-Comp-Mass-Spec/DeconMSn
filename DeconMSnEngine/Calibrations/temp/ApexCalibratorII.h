#pragma once
#include "CalibratorImp.h"

namespace Engine
{
	namespace Calibrations
	{
		class   ApexCalibratorII : public CCalibratorImp
		{
		public:

			double mdbl_intensity_normalizer ;  // don't know the exact purpose yet. initialize to 1.

			ApexCalibratorII(void);
			~ApexCalibratorII(void);

			CalibrationType GetCalibrationType() ;
			void SetIntensityNormalizer(double norm) ;
			double GetIntensityNormalizer() ;

			virtual void GetMassFromFreq(double freq, double &mass)  ; 
			virtual double Mass2Freq(double mass);
			double GetFrequencyFromQuadraticEquation(double b, double c, double mass);
		};
	}
}