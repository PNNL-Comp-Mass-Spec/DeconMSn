# source ("C:\\development\\DeconMsn\\RScripts\\plotDelM.R") 
rm(list = ls()) 
par(pch = 20, pty = "m", bg = "lightgray", type = "n")
plot.new()
fht_data = read.csv("C:/data/Dta/test.csv")  
ij = which((fht_data[,10]>0.1) & (fht_data[, 20]>=1))
fht_data_filtered =  fht_data[ij, ] 
plot(fht_data_filtered[,15], fht_data_filtered[,6], xlab = "delM", ylab = "Xcorr", main = "DeconMSn", col = "blue")


