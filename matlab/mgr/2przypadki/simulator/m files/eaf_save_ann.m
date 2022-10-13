function status = eaf_save_ann(Fname, Ann, Vars)
% status = eaf_save_xxx(Fname, Ann, Vars)
%
% eaf_save_xxx() is a subprogram to eaf_save that is used to specifically
% save annotations to an EMGlab ".xxx" annotation file from
% the EMGlab annotation structure.  The function inputs and outputs
% are standardized so that different annotation formats can be facilitated
% by different functions with names of the form: eaf_save_xxx, where
% xxx generally denotes the filename extension of the annotation file.
% See eaf_save() for complete definitions of Fname, Ann, Vars and status.
% If input variable Vars is unused, it must still be included in the
% function prototype.
%
% At a minimum, Ann must include the fields Ann.time and Ann.unit,
% as defined in the EMGlab annotation structure.  Be sure to close any
% files that were opened, even if errors occur.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%% Format: EMGlab ann File
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ".ann" file is ASCII with two columns: times in seconds and spike ID
% numbers.  This file type is intended as a temporary, simple file type
% and may not be supported in future EMGlab releases.  Instead, EMGlab
% annotation file (EAF) format will be supported.

NM = 'eaf_save_ann';  % Name of this MATLAB function (short hand).
% Open the annotation file, with error checking.
fid = fopen(Fname, 'wb');
if fid<0, errordlg(['Can''t open file "' Fname '".'], NM); return; end

% Write the annotations.
fprintf (fid, '%g %d\r\n', [Ann.time'; Ann.unit']);  % Time in seconds.

% Close the annotation file.
fclose(fid);

status = 0;  return
