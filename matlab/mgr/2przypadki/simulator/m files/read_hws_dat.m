function [data, info, status] = read_hws_dat(Fname)
%
%  [data, info, status] = read_hws_dat(Fname)
%
% Get the one channel of data, and accompanying header information,
% from a Hamilton-Wright--Stashuk simulator output data file.
% Assumes all data stored in little Endian (i.e., PC) format.  File
% format is specified in Hamilton-Wright and Stashuk documentation
% for their software.

% Fname: (String) Name of the data file (including file name extension)
%        If the file is not on the MATLAB path, then specify the
%        file name using the complete path name.
%
% data:  Column vector of data values.  Returned as type int16 for
%        MATLAB versions that support int16 (version 5.3+).  Else,
%        returned as regular MATLAB double.
% info:  Data record information structure.  The following members are
%        returned (see Hamilton-Wright and Stashuk documentation for
%        definitions: channel, HP_cutoff, LP_cutoff, scale
%        sampling_rate, number_of_samples, elapsed_time,
%        compression_threshold
% status:       1 ==> OK.  0 ==> error.

% Copyright (c) 2006. Edward A. Clancy, Kevin C. McGill and others.
% This work is licensed under the Aladdin free public license.
% For copying permissions see license.txt.
% email: emglab@emglab.stanford.edu

% Initialize
data = int16([]); info = []; status = 0;  % Initialize status to error.
if nargin ~= 1  % Be sure that required input argument has been supplied.
  errordlg('Must have one argument exactly.', 'EMGlab read_hws_dat');
  return;
end

% Open the file for reading.
fid = fopen(Fname, 'rb', 'ieee-le');  % Little endian.
%fid = fopen(Fname, 'rb', 'ieee-be');
if fid<0  % Be sure file opened correctly.
  errordlg(['Can''t open file ' Fname '.'], 'EMGlab read_hws_dat');
  return;
end

% Read the fixed-length binary header.
info.channel               = fread(fid, 1, 'int16');
info.HP_cutoff             = fread(fid, 1, 'int16');
info.LP_cutoff             = fread(fid, 1, 'int16');
info.scale                 = fread(fid, 1, 'int16');
info.sampling_rate         = fread(fid, 1, 'int32');
info.number_of_samples     = fread(fid, 1, 'int32');
info.elapsed_time          = fread(fid, 1, 'int32');
info.compression_threshold = fread(fid, 1, 'int16');
if isempty(info.compression_threshold)
  errordlg(['Bogus header: ' Fname '.'], 'EMGlab read_hws_dat');
  fclose(fid); return;
end

% Then, read the data; sensitive to the MATLAB version.
try,          data = fread(fid, '*int16');  % Newer MATLAB.
  catch, try, data = int16( fread(fid, 'int16') );   % 5.3.
  catch,      data = fread(fid, 'int16');            % 5.2.
end, end
fclose(fid);
if isempty(data)
  errordlg(['Empty data: ' Fname '.'], 'EMGlab read_hws_dat');
  fclose(fid); return;
end

status = 1;  % If get this far, then no problems were encountered.
return
