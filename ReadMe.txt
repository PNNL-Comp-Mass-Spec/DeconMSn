--------------------
-- DeconMSn Overview
--------------------

DeconMSn creates spectrum files for tandem mass spectrometry data. DeconMSn
can read in Finnigan .RAW files provided that XRawFile2.dll v2.2 is installed
on the computer.  This file is installed with Xcalibur 2.2, but can also be
installed using MSFileReader v2.2, available at:
http://sjsupport.thermofinnigan.com/public/detail.asp?id=703

DeconMSn also supports the mzXML format.  You can use Proteowizard's MSConvert
tool to convert most vendor formats into the mzXML format:
http://proteowizard.sourceforge.net/downloads.shtml

For datasets with high resolution MS1 spectra, DeconMSn calculates the monoisotopic mass
of the parent ion for each MSn spectrum by applying a modified THRASH approach 
to the parent isotopic distribution. For datasets with low-resolution 
MS1 spectra, DeconMSn uses a support-vector machine based charge-detection 
algorithm to determine parent mass. However, this algorithm is not fully
tested and therefore you should process low resolution datasets using
Proteowizard's MSConvert tool.

Results can be saved as .DTA files, .MGF files, or _DTA.txt files.  These files
can then be used for peptide identifications using search engines such as 
SEQUEST, X!Tandem, MASCOT, or MSGF+

--------------------
-- Installation
--------------------

Double click the DeconMSnInstaller.msi file to install. The .exe gets installed in 
C:\Program Files\DeconMSn, unless otherwise specified during installation.  
Type DeconMSn.exe at the command line in the installer directory to see the 
basic method of usage of the program shown below.  

If the program reports an error when you run it, make sure that both 
of these runtimes are installed:
1) Microsoft Visual C++ 2003 runtime (required by Xerces 2.8)
	- http://www.microsoft.com/en-us/download/details.aspx?id=26
	- C:\Windows\System32\msvcr71.dll
	- C:\Windows\System32\msvcp71.dll
2) Microsoft Visual C++ 2010 SP1 runtime (required by DeconMSn)
	- http://www.microsoft.com/en-us/download/details.aspx?id=8328
	- C:\Windows\System32\msvcr100.dll
	- C:\Windows\System32\msvcp100.dll

--------------------
-- Syntax
--------------------

> DeconMSn.exe
	
	DeconMSn usage : DeconMSn [options] filename
	
	[options] are
	
	         -Istring : string is the minimum Number of ions peaks for a scan to be considered [35]
	         -Fstring : string is the first Scan to be considered [1]
	         -Lstring : string is the last Scan to be considered [1000000]
	         -Bstring : string is the minimum setting for Mass Range [200]
	         -Tstring : string is the maximum setting for Mass Range [5000]
	         -Cstring : string is the charge to be considered [NULL]
	         -Pstring : string is the parameter XML file name to be used for processing [default options are set]
	         -Dstring : string is the output directory[default - set to same directory as input file]
	         -Sstring : string is the type of spectra to process, options are
	                 ALL : to process all spectra present in the raw file (default)
	                 CID : to process only CID spectra present in the raw file
	                 ETD : to process only ETD spectra present in the raw file
	                 HCD : to process only HCD spectra present in the raw file
	         -Xstring : string is output file format, options are
	                 DTA  : Creates .dta files along with a log file (_log.txt) and profile file (_profile.txt)[default option]
	                 LOG  : Creates only log file (_log.txt) and profile file (_profile.txt)
	                 MGF  : Creates .mgf file along with log file(_log.txt) and profile file (_profile.txt)
	                 CDTA : Creates .dta files, log file(_log.txt), a composite dta file (_dta.txt), and profile file (_profile.txt)
			 -W      : instructs the program to create a _progress.txt file, updating the percent complete every 50 scans
	filename : input file [mzXML or RAW]	

Note that the switch parameters are case-sensitive (for example you must use -P an not -p)

Some examples

Process sample.RAW, create .dta files
> DeconMSn.exe C:\data\sample.RAW 

Process sample.RAW with scan range of 1000-1200 and mass range of 200-1000, create .dta files
> DeconMSn.exe -F1000 -L1200 -B200 -T1000 C:\data\sample.RAW 

Process sample.RAW using default options; create .MGF as result file
> DeconMSn.exe -XMGF C:\data\sample.RAW 

Process sample.RAW, use processing options specified by parameter file LTQ_FT_Normal.xml
> DeconMSn.exe -PLTQ_FT_Normal.xml C:\data\sample.RAW 


--------------------
-- Dependencies
--------------------

- DeconMSN assumes that the user has vendor specific libraries installed on the machine 
to analyze ThermoFinnigan data.  Alternatively, if the user converts the raw data into 
the .mzXML format, then DeconMSn can process the data without vendor specific libraries.

- When compiling the source code, the user must first install Xerces 
(http://xerces.apache.org/xerces-c/) and then modify the paths for header and library
in the solution to indicate any change in the Xerces installation folder (the default 
installation path given in DeconMSN is C:\xerces\)
	- Current version of this program is built with xerces 2.8.

-This program requires msvcr71.dll and msvcr100.dll, which are often already on your computer.
 The installer should install those DLLs if they're missing

-------------------------------------------------------------------------------
Written by Anoop Mayampurath and Navdeep Jaitly for the Department of Energy 
(PNNL, Richland, WA) in 2006-2007.
Copyright 2007, Battelle Memorial Institute.  All Rights Reserved.

E-mail: matthew.monroe@pnnl.gov or samuel.payne@pnnl.gov
Website: http://omics.pnl.gov or http://panomics.pnnl.gov
-------------------------------------------------------------------------------

Licensed under the Apache License, Version 2.0; you may not use this file 
except in compliance with the License.  You may obtain a copy of the License 
at http://www.apache.org/licenses/LICENSE-2.0
All publications that result from the use of this software should include the 
following acknowledgment statement:
 Portions of this research were supported by the NIH National Centre for 
 Research Resources and the National Institute of Allergy and Infectious 
 Diseases  (NIH/DHHS through interagency agreement Y1-AI-4894-01).  
 Experimental portions of this research were performed at the Environmental 
 and Molecular Sciences Laboratory (EMSL), a U. S. Department of Energy (DOE) 
 national scientific user facility located at Pacific Northwest National 
 Laboratory in Richland, Washington, USA.  PNNL is operated by Battelle 
 Memorial Institute for the U.S. Department of Energy under contract 
 DE-AC05-76RL0 1830.
 

Notice: This computer software was prepared by Battelle Memorial Institute, 
hereinafter the Contractor, under Contract No. DE-AC05-76RL0 1830 with the 
Department of Energy (DOE).  All rights in the computer software are reserved 
by DOE on behalf of the United States Government and the Contractor as provided
in the Contract.  NEITHER THE GOVERNMENT NOR THE CONTRACTOR MAKES ANY WARRANTY,
EXPRESS OR IMPLIED, OR ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE.  
This notice including this sentence must appear on any copies of this computer 
software.
