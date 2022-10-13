function [Ann, status, Fvar] = eaf_load_ann(Fname)
% [Ann, status, Fvar] = eaf_load_xxx(Fname)
%
% eaf_load_xxx() is a subprogram to eaf_load that is used to specifically
% load annotations from an EMGlab ".xxx" annotation file into
% the EMGlab annotation structure.  The function inputs and outputs
% are standardized so that different annotation formats can be facilitated
% by different functions with names of the form: eaf_load_xxx, where
% xxx generally denotes the filename extension of the annotation file.
% See eaf_load() for complete definitions of Fname, Ann, status and Fvar.
% If output variable Fvar is unused, then it should be set to [].
%
% At a minimum, Ann must return the fields Ann.time and Ann.unit,
% as defined in the EMGlab annotation structure.  Be sure to close any
% files that were opened, even if errors occur.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%% Format: EMGlab ann File
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ".ann" file is ASCII with two columns: times in seconds and spike ID
% numbers.  This file type is intended as a temporary, simple file type
% and may not be supported in future EMGlab releases.  Instead, EMGlab
% annotation file (EAF) format will be supported.

Fvar = [];  % Unused output variable, but must be supplied.
Ann = [];

if ~exist(Fname, 'file')
  status = (['File "' Fname '" not found']); 
  return; 
end

fid = fopen (Fname, 'rt');
if fid<0; 
  status = (['Problem opening ', Fname]); 
  return; 
end;

[data, n] = fscanf (fid, '%g');
if n==0 | 2*round(n/2)~=n; 
  status = ([' Problem reading ', Fname]);
  return;
end;

Ann.time = data(1:2:end);
Ann.unit = data(2:2:end);
Ann.chan = ones(length(Ann.time),1);
Ann.instance = [1:length(Ann.time)]';
status = '';
