// Written by Navdeep Jaitly for the Department of Energy (PNNL, Richland, WA)
// Copyright 2006, Battelle Memorial Institute
// E-mail: navdeep.jaitly@pnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
// 
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0

#pragma once
#include "clsElementIsotopes.h" 
#include "clsIsotopeFit.h"
#include "TheoreticalProfile/Averagine.h"
#using <System.Xml.dll>
using namespace System::Xml ; 

namespace Decon2LS
{
	namespace HornTransform
	{

		public __gc class clsAveragine: public System::ICloneable
		{
			Engine::TheoreticalProfile::Averagine *mobjAveragine ; 
			clsElementIsotopes *mobjElementIsotopes ; 
		public:
			clsAveragine(void);
			~clsAveragine(void);

			virtual Object* Clone()
			{
				return NULL ; 
			}

			__property double get_MonoMass()
			{
				return 0 ; 
			}

			__property double get_AverageMass()
			{
				return 0 ; 
			}
	
			__property clsElementIsotopes* get_ElementIsotopeComposition()
			{
				return mobjElementIsotopes ; 
			}

			__property void set_ElementIsotopeComposition(clsElementIsotopes *atomic_info)
			{
				if (atomic_info != mobjElementIsotopes)
				{
					mobjElementIsotopes->Assign(atomic_info) ; 
				}
				mobjAveragine->SetElementalIsotopeComposition(*mobjElementIsotopes->GetElementalIsotopeComposition()) ; 
			}

			System::String*  GenerateAveragineFormula(double averageMass, System::String *averagineFormula, 
				System::String *tagFormula) ; 
		};
	}
}
