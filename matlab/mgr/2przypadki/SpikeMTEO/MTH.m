function [TE,DTh] = MTH(MTEO,ks,L,Fs)
%% Multi-Scale Thresholding
%% Inputs:
% MTEO : MTEO signal outputs from MTEO function
% ks : levels of MTEO
% L : is the factor that multiplies [cost of comission]/[cost of omission].
% For most practical purposes -0.2 <= L <= 0.2. Larger L --> omissions
% likely, smaller L --> false positives likely. For unsupervised
% detection, the suggested value of L is close to 0.  
% Fs : Sampling frequency
%% Outputs :
% TE and DTh : Detected Muaps 

%% Algorithm is based on the following paper :
% H. Sedghamiz and Daniele Santonocito,'Unsupervised Detection and
% Classification of Motor Unit Action Potentials in Intramuscular 
% Electromyography Signals', The 5th IEEE International Conference on
% E-Health and Bioengineering - EHB 2015, At Iasi-Romania.
%% Author: 
% Hooman Sedghamiz
% June 2015, Linkoping University
% Please cite the paper if any of the methods were helpfull

[N,M] = size(MTEO);
ks = ks.*2;

%define detection parameter
Lmax = -551.0520;       %log(Lcom/Lom), where the ratio is the maximum 
L = L * Lmax;

for i = 1:N
    
    %take only coefficients that are independent (W(i) apart) for median
    %standard deviation
    
    Sigmaj = median(abs(MTEO(i,1:round(ks(i)):end) - mean(MTEO(i,:))))/0.6745;
    Thj = Sigmaj * sqrt(2 * log(M));     %hard threshold
    index = (abs(MTEO(i,:)) > Thj);
    index = MTEO(i,index);
    
    if ~isempty(index)
    
    Mj = mean(abs(index));       %mean of the signal coefficients
    PS = length(index)/M;                %prior of spikes
    PN = 1 - PS;                         %prior of noise
    DTh = Mj/2 + Sigmaj^2/Mj * (L + log(PN/PS));   %decision threshold
    DTh = abs(DTh) * (DTh >= 0);         %make DTh>=0
    TE = resolve_peaks(MTEO(i,:),DTh,Fs);
    else
        
        Mj = Thj;
        %assume at least one spike
        PS = 1/M;
        PN = 1 - PS;
        DTh = Mj/2 + Sigmaj^2/Mj * (L + log(PN/PS));    %decision threshold
        DTh = abs(DTh)* (DTh >= 0);                     %make DTh>=0
        ind  = (abs(MTEO(i,:)) > DTh);
        ind = MTEO(i,ind);
        if isempty(ind)
            %do nothing ct=[0];
            TE = [];
        else
            % This function resolves too close peaks
             TE = resolve_peaks(MTEO(i,:),DTh,Fs);
        end                
    end        
end

%%% to enhance performance discard detections more than 700Hz period
if ~isempty(TE)
 if (length(TE)/(size(MTEO,2)/(Fs))) > 500 ||...
        (length(TE)/(size(MTEO,2)/(Fs))) < 1
   TE = []; 
   DTh = [];
   return;
 end
end

  

end

