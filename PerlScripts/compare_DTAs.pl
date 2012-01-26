#use strict ; 
my $dta_folder_one = "C:\\data\\Dta\\Test\\" ; 
my $dta_folder_two = "C:\\data\\Dta\\Test\\LowRes\\" ; 

my @files_one = <$dta_folder_one*.dta> ; 
my @files_two = <$dta_folder_two*.dta> ; 

my $num_files_one = @files_one ;
my $num_files_two = @files_two ; 

printf "Found $num_files_one files in folder one (ignore ID)\n" ; 
printf "Found $num_files_two files in folder two (ID Charge One)\n" ; 

my $out_file_name = "C:\\development\\DeconMSn\\validate\\test_out.txt";

my %file_hash ; 

for (my $file_num_one = 0 ; $file_num_one < @files_one ; $file_num_one++)
{
	my $current_file_one  = substr($files_one[$file_num_one], length($dta_folder_one), length($files_one[$file_num_one]) - length($dta_folder_one)-4) ; 
	$file_hash{$current_file_one}= 1 ; 
}

my $exists_count = 0 ; 
my $not_exists_count = 0 ; 
open(OUTFILE, ">$out_file_name") || die "Could not open output file\n";

for (my $file_num_two = 0 ; $file_num_two < @files_two ; $file_num_two++)
{	my $current_file_two  = substr($files_two[$file_num_two], length($dta_folder_two), length($files_two[$file_num_two]) - length($dta_folder_two)-4) ; 
	if (exists ($file_hash{$current_file_two}))
	{
		$file_hash{$current_file_two} = 0 ; 
		$exists_count  = $exists_count + 1; 
	}
	else
	{	
		$not_exists_count = $not_exists_count + 1 ;
		print OUTFILE "$current_file_two \n" ;  
	}
}



printf "Found $exists_count in both versions \n" ; 
printf "Found $not_exists_count present in two and not in one \n" ; 

close(OUTFILE) ; 
