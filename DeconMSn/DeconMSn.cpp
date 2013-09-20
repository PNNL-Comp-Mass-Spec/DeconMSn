// This is the main project file for VC++ application project 
// generated using an Application Wizard.


// Written by  Anoop Mayampurath 
// for the Department of Energy (PNNL, Richland, WA)
// Copyright 2006, Battelle Memorial Institute
// E-mail: anoop.mayampurath@pnl.gov
// Website: http://ncrr.pnl.gov/software
// -------------------------------------------------------------------------------
// 
// Licensed under the Apache License, Version 2.0; you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0


#include "stdafx.h"
#include <stdio.h>
#include <time.h>

#using <mscorlib.dll>
#using <system.dll>
#using <System.Xml.dll>

using namespace System;
using namespace System::Reflection ; 
using namespace System::IO ; 
using namespace System::Xml ; 
using namespace std;


int _tmain( int argc, char *argv[] )
{
	System::String *commandLine;
	
	int elapTicks;
    double elapMilli, elapSeconds, elapMinutes;
    clock_t Begin, End;             //initialize Begin and End for the timer

	void PrintUsage() ;

	System::IO::Path *ioPath ; 
	System::String *strAppFolder ; 
	System::String *strSVMParamFilePath ; 
	System::String *strDllFileAndPath ; 
	
	strAppFolder = ioPath->GetDirectoryName(System::Reflection::Assembly::GetExecutingAssembly()->Location) ; 
	strSVMParamFilePath = System::IO::Path::Combine(strAppFolder, "svm_params.xml") ; 
	
	int beginIndex;	

	if (argc == 1)
	{
		PrintUsage();		
		return 0;
	}

	//default options
	int IValue = 25; //ion count - resetting it to 25 
	int FValue = 1;
	int LValue = 1000000;
	int CValue = 0;
	double BValue = 200;	
	double TValue = 5000;
	bool bln_just_log = false;
	bool bln_write_composite_dta = false ; 
	int value = 65 ; 
	System::String *stringIvalue ;
	System::String *stringFvalue ;
	System::String *stringLvalue ;
	System::String *stringBvalue ;
	System::String *stringTvalue ;
	System::String *stringCvalue ;
	System::String *stringFileName ; 	
	System::String *stringOutputFileFormat ;
	System::String *stringSpectraFormat;
	System::String *stringParamFile ; 

	Decon2LS::clsProcRunner *obj_proc_runner;
	Decon2LS::HornTransform::clsHornTransformParameters *obj_transform_parameters;
	Decon2LS::DTAGeneration::clsDTAGenerationParameters *obj_dta_generation_parameters;
	Decon2LS::Peaks::clsPeakProcessorParameters *obj_peak_parameters;
	Decon2LS::DTAGeneration::OUTPUT_TYPE output_file_type = Decon2LS::DTAGeneration::OUTPUT_TYPE::DTA ;
		
	obj_proc_runner = new Decon2LS::clsProcRunner();
	obj_transform_parameters = new Decon2LS::HornTransform::clsHornTransformParameters();
	obj_peak_parameters = new Decon2LS::Peaks::clsPeakProcessorParameters();
	obj_dta_generation_parameters = new Decon2LS::DTAGeneration::clsDTAGenerationParameters() ;
	


	bool error = false ; 
	obj_dta_generation_parameters->set_SVMParamFile(strSVMParamFilePath) ; 
	
	Begin = clock() ;
	
	cout<<"Starting clock ticket. Begin = " << Begin << " ticks.\n";

	int argvIndex = 1;

	// Check if param file is loaded first
	if (argc > 1)
	{
		for (argvIndex = 1 ; argvIndex <argc-1 ; argvIndex++)
		{
			commandLine = argv[argvIndex] ; 
			char ch = commandLine->get_Chars(1) ; 
			if (ch == 'P')
			{
				cout<<"Reading Parameter File"<<std::endl ; 
				beginIndex = commandLine->IndexOf('P') ; 
				stringParamFile = commandLine->Remove(0, beginIndex + 1) ; 
				
				System::Xml::XmlTextReader *rdr =  new System::Xml::XmlTextReader(stringParamFile) ; 
				//Read each node in the tree.
				while (rdr->Read())
				{
					switch (rdr->NodeType)
					{
						case XmlNodeType::Element:							
							if (System::String::Compare(rdr->Name, S"PeakParameters") == 0 )
							{
								obj_peak_parameters->LoadV1PeakParameters(rdr) ; 
							}
							else if (System::String::Compare(rdr->Name, S"HornTransformParameters") == 0)
							{
								obj_transform_parameters->LoadV1HornTransformParameters(rdr) ;
							}							
							else if (System::String::Compare(rdr->Name, S"DTAGenerationParameters") == 0)
							{
								obj_dta_generation_parameters->LoadV1DTAGenerationParameters(rdr) ; 
							}
							break;
						default:
							break ; 
					}
				}

				if (rdr != 0)
					rdr->Close() ; 
			}
		}
	}

	if (argc > 1)
	{
		for (argvIndex = 1; argvIndex < argc-1; argvIndex++)
		{
			commandLine = argv[argvIndex];
			if (!error)
			{
				switch(commandLine->get_Chars(1))
				{
					case 'I':	beginIndex = commandLine->IndexOf('I');	
								stringIvalue = commandLine->Remove(0, beginIndex+1);
								IValue = System::Convert::ToInt32(stringIvalue, 10);
								obj_dta_generation_parameters->set_MinIonCount(IValue) ; 
								break;	
					case 'F':   beginIndex = commandLine->IndexOf('F');	
								stringFvalue = commandLine->Remove(0, beginIndex+1);
								FValue = System::Convert::ToInt32(stringFvalue, 10);
								obj_dta_generation_parameters->set_MinScan(FValue) ; 
								break;
					case 'L':	beginIndex = commandLine->IndexOf('L');	
								stringLvalue = commandLine->Remove(0, beginIndex+1);
								LValue = System::Convert::ToInt32(stringLvalue, 10);	
								obj_dta_generation_parameters->set_MaxScan(LValue) ; 
								break;
					case 'B':	beginIndex = commandLine->IndexOf('B');	
								stringBvalue = commandLine->Remove(0, beginIndex+1);
								BValue = System::Convert::ToDouble(stringBvalue);
								obj_dta_generation_parameters->set_MinMass(BValue) ; 
								break;
					case 'T':	beginIndex = commandLine->IndexOf('T');	
								stringTvalue = commandLine->Remove(0, beginIndex+1);
								TValue = System::Convert::ToDouble(stringTvalue);
								obj_dta_generation_parameters->set_MaxMass(TValue) ;
								break;				
					case 'C':	beginIndex = commandLine->IndexOf('C');
								stringCvalue = commandLine->Remove(0, beginIndex+1);
								CValue = System::Convert::ToInt16(stringCvalue);
								obj_dta_generation_parameters->set_ConsiderChargeValue(CValue) ; 
								break;
					case 'S':	beginIndex = commandLine->IndexOf('S');
								stringSpectraFormat = commandLine->Remove(0, beginIndex+1);							
								if (System::String::Compare(stringSpectraFormat, "ETD") == 0){
									obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::ETD);
								}
								else if (System::String::Compare(stringSpectraFormat, "CID") == 0){
									obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::CID);
								}
								else if (System::String::Compare(stringSpectraFormat, "HCD") == 0){
									obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::HCD);
								}
								else {
									obj_dta_generation_parameters->set_SpectraType(Decon2LS::DTAGeneration::SPECTRA_TYPE::ALL);
								}

					case 'X':	beginIndex = commandLine->IndexOf('X');
								stringOutputFileFormat = commandLine->Remove(0, beginIndex+1);							
								if (System::String::Compare(stringOutputFileFormat, "MGF") == 0)
									obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::MGF) ;														
								else if (System::String::Compare(stringOutputFileFormat, "LOG") == 0)
									obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::LOG) ;														
								else if (System::String::Compare(stringOutputFileFormat, "CDTA") == 0)
									obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::CDTA) ;														
								else if (System::String::Compare(stringOutputFileFormat, "MZXML") == 0)
									obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::MZXML) ;														
								else if (System::String::Compare(stringOutputFileFormat, "DTA") == 0)
									obj_dta_generation_parameters->set_OutputType(Decon2LS::DTAGeneration::OUTPUT_TYPE::DTA) ; 
								else
								{
									PrintUsage() ; 
									error = true ; 
								}
								break ; 
					case 'D':	beginIndex = commandLine->IndexOf('D') ; 
								stringFileName = commandLine->Remove(0, beginIndex+1) ;														
								obj_proc_runner->OutputPathForDTACreation = stringFileName ; 
								break;									
					case 'G':	beginIndex = commandLine->IndexOf('G');	
								break ; 
					case 'M':	beginIndex = commandLine->IndexOf('M');	
								break ; 		
					//case 'S':	beginIndex = commandLine->IndexOf('S');	
					//			break ; 	
					case 'P':	beginIndex = commandLine->IndexOf('P') ; 
								break ; 
					default :	PrintUsage();
								error = true ; 
				}
			}
			else
			{
				return 0 ; 
			}			
		}
		
		commandLine = argv[argvIndex];
		obj_proc_runner->FileName = commandLine ; 							
		
	}

	if (error) //Anoop 05/08 
	{
		return 0 ; 
	}

	cout<<"Processing File"<<std::endl ;	
		
	obj_proc_runner->HornTransformParameters  = obj_transform_parameters;
	obj_proc_runner->PeakProcessorParameters = obj_peak_parameters;
	obj_proc_runner->DTAGenerationParameters = obj_dta_generation_parameters ; 
	
	obj_proc_runner->CreateDTAFile() ; 

	//obj_dta_generation_parameters->__dtor() ; 
	//obj_peak_parameters->__dtor() ; 
	//obj_transform_parameters->__dtor() ; 
	//obj_proc_runner->__dtor() ; 
	End = clock() ; 
	cout<<"Stopping clock ticks. End = " << End << " ticks.\n";

	elapTicks = End - Begin;        //the number of ticks from Begin to End
    elapMilli = (CLK_TCK * elapTicks)/1000;     //milliseconds from Begin to End
    elapSeconds = elapMilli/1000;   //seconds from Begin to End
    elapMinutes = elapSeconds/60;   //minutes from Begin to End


	cout<<"\nDone. Finished processing in " << elapSeconds << " seconds.\n";
	
	return 0;
}



void PrintUsage()
{	
	cout<<endl<< "DeconMSn usage : DeconMSn [options] filename"<<endl<<endl;
	cout<<"[options] are" <<endl<<endl;
	cout<<"\t -Istring : string is the minimum Number of ions peaks for a scan to be considered [35]" << endl;
	cout<<"\t -Fstring : string is the first Scan to be considered [1]" << endl;
	cout<<"\t -Lstring : string is the last Scan to be considered [1000000]" << endl;
	cout<<"\t -Bstring : string is the minimum setting for Mass Range [200]" <<endl;
	cout<<"\t -Tstring : string is the maximum setting for Mass Range [5000]" <<endl;
	cout<<"\t -Cstring : string is the charge to be considered [NULL]" <<endl;
	cout<<"\t -Pstring : string is the parameter XML file name to be used for processing [default options are set]" <<endl; 
	cout<<"\t -Dstring : string is the output directory[default - set to same directory as input file]" <<endl;
	cout<<"\t -Sstring : string is the type of spectra to process, options are"<<endl;
	cout<<"\t \t ALL : to process all spectra present in the raw file (default)"<<endl;
	cout<<"\t \t CID : to process only CID spectra present in the raw file"<<endl;
	cout<<"\t \t ETD : to process only ETD spectra present in the raw file"<<endl;
	cout<<"\t \t HCD : to process only HCD spectra present in the raw file"<<endl;
	cout<<"\t -Xstring : string is output file format, options are"<<endl;
	cout<<"\t \t DTA  : Creates .dta files along with a log file (_log.txt) and profile file (_profile.txt)[default option]"<<endl ; 
	cout<<"\t \t LOG  : Creates only log file (_log.txt) and profile file (_profile.txt)"<<endl; 
	cout<<"\t \t MGF  : Creates .mgf file along with log file(_log.txt) and profile file (_profile.txt)"<<endl; 
	cout<<"\t \t CDTA : Creates .dta files, log file(_log.txt), a composite dta file (_dta.txt) and profile file (_profile.txt)"<<endl; 		
	cout<<"filename : input file [mzXML or RAW]"<<endl; 
}