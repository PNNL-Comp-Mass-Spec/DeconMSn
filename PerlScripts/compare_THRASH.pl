#use strict ; 
my $dta_folder_new = "C:\\data\\Raw_Data\\DTA_new\\" ; 
my $dta_folder_old = "C:\\data\\Raw_Data\\DTA_old\\" ; 

my @files_old = <$dta_folder_old*.dta> ; 
my @files_new = <$dta_folder_new*.dta> ; 

my $num_files_old = @files_old ;
my $num_files_new = @files_new ; 

printf "Found $num_files_old files using original DTACreator\n" ; 
printf "Found $num_files_new files using new DTACreator\n" ; 

my $out_file_name = "C:\\PNL\\Proteomics\\DtaCreator\\validate\\test_out.txt";

my %file_hash ; 

for (my $file_num_old = 0 ; $file_num_old < @files_old ; $file_num_old++)
{
	my $current_file_old  = substr($files_old[$file_num_old], length($dta_folder_old), length($files_old[$file_num_old]) - length($dta_folder_old)-4) ; 
	$file_hash{$current_file_old}= 1 ; 
}


my $exists_count = 0 ; 
my $not_exists_count = 0 ; 
open(OUTFILE, ">$out_file_name") || die "Could not open output file\n";

for (my $file_num_new = 0 ; $file_num_new < @files_new ; $file_num_new++)
{
	my $current_file_new  = substr($files_new[$file_num_new], length($dta_folder_new), length($files_new[$file_num_new]) - length($dta_folder_new)-4) ; 
	if (exists ($file_hash{$current_file_new}))
	{
		$file_hash{$current_file_new} = 0 ; 
		$exists_count  = $exists_count + 1; 
	}
	else
	{	
		$not_exists_count = $not_exists_count + 1 ;
		print OUTFILE "$current_file_new \n" ;  
	}
}



printf "Found $exists_count in both versions \n" ; 
printf "Found $not_exists_count missing in old \n" ; 

