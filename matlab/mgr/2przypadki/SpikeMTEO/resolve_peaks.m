function TE = resolve_peaks(sig,DTh,Fs)
%% Resolves the spikes which are too close

%% Algorithm is based on the following paper :
% H. Sedghamiz and Daniele Santonocito,'Unsupervised Detection and
% Classification of Motor Unit Action Potentials in Intramuscular 
% Electromyography Signals', The 5th IEEE International Conference on
% E-Health and Bioengineering - EHB 2015, At Iasi-Romania.
%% Author: 
% Hooman Sedghamiz
% June 2015, Linkoping University
% Please cite the paper if any of the methods were helpfull

%% Script Begins here, Do not Change
 sig = abs(sig(:));
 min_pd = round(0.0015*Fs); %def 15 millisec min distance
 tmp = zeros(1,length(sig));
 ind = (sig > DTh);
 tmp(ind)=sig(ind);
 [~,TE] = findpeaks(tmp,'MinPeakDistance',min_pd);


end