function [locs] = MTEO_S(sig,Fs,C,init) 
%%% Function for Spike detection
% This is designed to filter out shallow peaks out of Action potentials
% with the help of Multi-dimensional TK operator. The function has several
% subroutins and uses template and label matching in order to cluster the
% action potentials in the signal. 
%% Inputs :
% Sig: EMG signal Vector
% Fs : Sampling Frequency (e.g. 2000 Hz)
% C : Threshold for the Spike Detection, determines the sensitivity of the
% algorithm
% basket if their correlation score goes higher than this value
% init : Flag for filtering, leave it empty if you have no idea what this
% is
%% Output:
% Index :Index of MUAPs clustered
% loc : location of the MUAPs in the signal

%% Algorithm is based on the following paper :
% H. Sedghamiz and Daniele Santonocito,'Unsupervised Detection and
% Classification of Motor Unit Action Potentials in Intramuscular 
% Electromyography Signals', The 5th IEEE International Conference on
% E-Health and Bioengineering - EHB 2015, At Iasi-Romania.
%% Author: 
% Hooman Sedghamiz
% June 2015, Linkoping University
% Please cite the paper if any of the methods were helpfull
%% Begin
%Input Handling
  if nargin < 4 
     init = 1;                           % flag for computing filters or not
   if nargin < 3 
      C = 0.1;                           % Default 0.6*STD(0.8-1.2)
   end
  end

%% Initialzie and highpass filter
% Detrends and band-pass filters the signal
if init
  [sig,Fs] = initialize(sig,Fs,1);
end

%% upsampling for better accuracy in Classification

upsample_flag = 0;
if (Fs < 10000) && (Fs > 4000)
   sig = resample(sig,5,1); % upsample by a factor of 3 
   Fs = 5*Fs;
   upsample_flag = 5;
elseif (Fs > 10000) && (Fs < 15000)
   sig = resample(sig,2,1); % upsample by a factor of 2 
   Fs = 2*Fs;
   upsample_flag = 2;
elseif Fs <= 3000
   sig = resample(sig,8,1);
   Fs = 8*Fs;
   upsample_flag = 8;
end


%% MTEO
ks = [2;3;5];                        % Scales for MTEO (or 1,3,5) detection
if upsample_flag
 ks = ks.*2;                        
end
 
%% First Stage Spike detection
sig_TEO = MTEO(sig, ks);               % Compute MTEO
[locs,~] = MTH(sig_TEO,ks,C,Fs);