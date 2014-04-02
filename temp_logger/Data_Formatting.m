T = datenum(2014,4,1,10,35,0:5:500000); % don't know what the exact end date is, so just make a bunch
T = T(:,1:32483); % then take only the first n
ts = timeseries(data,T,'Name','Temperature Log Data');
plot(ts)
datetick('x','HH:00')