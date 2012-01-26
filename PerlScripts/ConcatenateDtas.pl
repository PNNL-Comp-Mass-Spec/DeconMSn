my $decon_folder_dta = "C:\\data\\Dta\\Test\\TestLowRes2\\" ;
my @files = <$decon_folder_dta*.dta> ; 
my $num_files = @files ;
printf "Found $num_files files\n" ; 
my $out_file_name = "C:\\data\\Dta\\validate_results\\file_list.txt";

open(OUTFILE, ">$out_file_name") || die "Could not open output file\n";


for (my $file_num = 0 ; $file_num < @files ; $file_num++)
{
	my $current_file = substr($files[$file_num], length($dta_folder_dta), length($files[$file_num])) ; 
	print OUTFILE "$current_file \n" ;

}

print "Done\n" ;


