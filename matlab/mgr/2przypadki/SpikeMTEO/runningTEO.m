
function out = runningTEO(rawSignal,k)
%%
% calcs the function x(n)^2 - x(n-1)*x(n+1)
%
% this is the standard energy operator (TEO)
% some people like to invent new names for old concepts and call this "NEO -> nonlinear energy operator"
%
% urut/aprl07
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
if nargin==1
    k=1;
end

out = rawSignal.^2 - [rawSignal(1+k:end);zeros(1,k)'].*[zeros(1,k)';rawSignal(1:end-k)];

