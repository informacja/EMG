function [Ann, status, Fvar] = eaf_load_gst(Fname)
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
%%%%%%%%%% Format: Hamilton-Wright & Stashuk "Gold Standard" (.gst, .dco)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% H-W & S GST/DCO annotation files are binary files comprised of a
% 64-byte header followed by a sequence of 16-byte annotations.  Full
% specification can be found in the H-W & S software documentation
% ("Production of Simulated EMG Using a Physiological Model").
% A sampling rate of 31250 is assumed.

Fvar = [];  % Unused output variable, but must be supplied.
NM = 'eaf_load_gst';  % Name of this MATLAB function (short hand).
Ann = []; status = -1;  % Defaults in case of error return.
%Ann.samprate = 31250;  % Assumed.
samprate=31250;

% Open the annotation file, with error checking.
fid = fopen(Fname, 'rb', 'l');
if fid<0, errordlg(['Can''t open file "' Fname '".'], NM); return; end

% Check that file has a valid length: (length-64)/16 is integer.
fseek(fid, 0, 'eof');          % Moves to end of file.
BB = ftell(fid);               % File length, in bytes.
Nspike = round( (BB-64)/16 );  % Number of MU spikes in file.
if BB < 64  ||  (Nspike*16)+64 ~= BB
  errordlg('Bogus H-W & S GST/DCO file length', NM); fclose(fid); return
end

% Read the fixed-length binary header.
Ann.Name       = fread(fid, 60, '*uchar');
Ann.Num_Trains = fread(fid,  1,  'int16');
Ann.Num_MUPs   = fread(fid,  1,  'int16');

% Read spikes using three passes (less looping).  Ignore "firing time"
%   (redundant with "buffer offset"); "MUP number" (not needed).
fseek(fid, 64+ 4, 'bof');                     % Rewind: 1st buffer offset.
Ann.time = fread(fid, 'int32', 12);           % Read buffer offsets.
fseek(fid, 64+ 8, 'bof');                     % Rewind: 1st motor unit.
Ann.unit = fread(fid, 'int16', 14);           % Read motor units.
fseek(fid, 64+12, 'bof');                     % Rewind: 1st uncertainty.
Ann.uncertainty = fread(fid, 'float32', 12);  % Read uncertainties.

% Remove bogus first annotation, if it was supplied.
if length(Ann.time)>0 & Ann.time(1)==0 & Ann.unit(1)==0  % Bogus.
  Ann.time        = Ann.time(2:end);
  Ann.unit        = Ann.unit(2:end);
  Ann.uncertainty = Ann.uncertainty(2:end);
end

%Ann.time = Ann.time / Ann.samprate;  % Convert to seconds.
Ann.time = Ann.time / samprate;  % Convert to seconds.
Ann.chan = ones(length(Ann.time), 1);

% Close the annotation file.
fclose(fid);

status = 0;  return
