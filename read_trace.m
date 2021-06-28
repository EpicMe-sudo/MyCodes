function z=read_trace(filename)
fid = fopen(filename,'r');

trNum = 100;  %
trLen = 22000; %

fseek(fid,128,'bof');

for i=1:trNum
    z(:,i)=fread(fid, trLen,'double');
end

plot(z(:,1));
fclose(fid);

end