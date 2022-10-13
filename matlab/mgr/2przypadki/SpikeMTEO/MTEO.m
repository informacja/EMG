function [runTEO,tmp] = MTEO(rawSignal, ks)
%% Implements the MTEO detector according to 
%Note this is from => urut/april07
%% Inputs:
% rawSignal: raw signal
% ks : levels of MTEO
%% Algorithm is based on the following paper :
% H. Sedghamiz and Daniele Santonocito,'Unsupervised Detection and
% Classification of Motor Unit Action Potentials in Intramuscular 
% Electromyography Signals', The 5th IEEE International Conference on
% E-Health and Bioengineering - EHB 2015, At Iasi-Romania.
%% Author: 
% Hooman Sedghamiz
% June 2015, Linkoping University
% Please cite the paper if any of the methods were helpfull
L = length(ks);
rawSignal = rawSignal(:);
tmp=zeros(L,length(rawSignal));
v = zeros(L,1);
for i=1:length(ks)
    tmp(i,:) = runningTEO(rawSignal, ks(i));
    v(i) = var(tmp(i,:));

    %apply the window
    win = hamming( 4*ks(i)+1, 'symmetric');
    tmp(i,:) = filtfilt( win,1,tmp(i,:))./(v(i)^2); %def was v unsquared
    
end

%runTEO= sum(tmp); %runTEO + tmp./v(i);
runTEO = max(tmp);
