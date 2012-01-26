function out = PlotValidate ()
fid = fopen('test_out.txt') ;
line = fgets(fid);
histogram = [0 0 0 0];
count = 0;

while line ~= -1
    count = count+1;
    value = str2num(line);
    histogram(value+1) = histogram(value+1) +1;
    line = fgets(fid);
end
fclose(fid);
histogram(1) = histogram(1)/count * 100;
histogram(2) = histogram(2)/count * 100;
histogram(3) = histogram(3)/count * 100;
histogram(4) = count;

out = histogram;
return;