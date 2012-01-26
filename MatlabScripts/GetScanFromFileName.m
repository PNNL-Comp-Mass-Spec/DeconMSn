function out = GetScanFromFileName(filename)
for i = 1:size(filename,2)
    ch = filename(i);
    if ch == '.'
        index_dot = i;
        second_index_dot = i+1;
        ch = filename(second_index_dot);
        while ch ~= '.'
            second_index_dot = second_index_dot +1;
            ch = filename(second_index_dot);
        end
        break;
    end
end

scan = filename(index_dot+1:second_index_dot-1);

scan_ch = strcat(scan);
out = str2num(scan_ch);
return
