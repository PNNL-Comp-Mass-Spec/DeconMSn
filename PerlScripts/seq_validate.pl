#use strict ; 
my $dta_folder = "C:\\data\\MassRefinement\\DTA_Creator\\" ;
my $out_folder = "C:\\data\\MassRefinement\\DTA_Creator\\" ;
my @files = <$dta_folder*.dta> ; 
my $num_dta_files = @files ;

my @files = <$out_folder*.out> ;
my $num_out_files = @files ;

printf "Found $num_dta_files DTA files\n" ; 
printf "Foung $num_out_files OUT files\n" ;

