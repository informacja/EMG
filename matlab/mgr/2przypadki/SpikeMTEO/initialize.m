function [sig,Fs] = initialize(sig,Fs,Notch)
%% Algorithm is based on the following paper :
% H. Sedghamiz and Daniele Santonocito,'Unsupervised Detection and
% Classification of Motor Unit Action Potentials in Intramuscular 
% Electromyography Signals', The 5th IEEE International Conference on
% E-Health and Bioengineering - EHB 2015, At Iasi-Romania.
%% Author: 
% Hooman Sedghamiz
% June 2015, Linkoping University
% Please cite the paper if any of the methods were helpfull

if nargin < 3    
    Notch = 0;    
end
%% Initialzie
sig = detrend(sig(:));                 % Remove the baseline shift
sig = sig - mean(sig);                 % Remove mean
sig = sig/std(sig);                    % Normalize variance

%% Notch Filter
if Notch
d = designfilt('bandstopiir','FilterOrder',32, ...
               'HalfPowerFrequency1',59,'HalfPowerFrequency2',61, ...
               'DesignMethod','butter','SampleRate',Fs);
           
sig = filtfilt(d,sig);           
end

%% High-Pass Filter
 F_l = 50/(Fs/2);                      % Normalized cutoff frequency   
 F_h = 1000/(Fs/2);
% F_h = 500/(Fs/2);

Wn = [F_l F_h];
[z,p,k] = butter(4,Wn);               % Butterworth filter
[sos,G] = zp2sos(z,p,k);              % Convert to SOS form
sig = filtfilt(sos,G,sig(:));



%  F_l = 30/(Fs/2);                      % Normalized cutoff frequency   
% % F_h = 400/(Fs/2);
% [z,p,k] = butter(4,F_l,'high');        % Highpass
% [sos,G] = zp2sos(z,p,k);              % Convert to SOS form
% sig = filtfilt(sos,G,sig(:));






end