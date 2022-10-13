function [data, info, status] = read_sc123(filename)
% [data, info, status] = read_sc123(filename)
%
% Get three channels of data from a MUtools database data file.  Assumes all three
%   channels are stored in little Endian (e.g., PC) format as int16 values.
%
% filename: (String) Name of the data file.  The file extension(s) can
%            be omitted, or any of the following extensions are
%            accepted: '.sc1', '.sc2', '.sc3' or '.sc*'.
%            If the file is not in the MATLAB path, then specify the
%            file name using the complete path name.
%
% data(N,3):    Data array of .sc1, .sc2, .sc3 data files, respectively.
%               Returned as type int16 for MATLAB versions that support
%               int16 (version 5.3+).  Else, returned as regular MATLAB
%               double.
% info:         Data record information structure.  Only member "rate"
%               is returned.
% status:       1 ==> OK.  0 ==> error.

% This work is licensed under the Creative Commons
% Attribution-NonCommercial-ShareAlike 2.5 License. To view a copy of
% this license, visit http://creativecommons.org/licenses/by-nc-sa/2.5/
% or send a letter to Creative Commons, 543 Howard Street, 5th Floor,
% San Francisco, California, 94105, USA.

% Initialize
data = []; info = []; status = 0;  % Initialize status to error.
if nargin ~= 1  % Be sure that required input argument has been supplied.
  errordlg('Must have one argument exactly.', 'EMGlab read_sc123');
  return;
end
% Strip any valid file name extension from the file name.
switch filename(max(end-3,1):end)
  case {'.sc1', '.sc2', '.sc3', '.sc*'}, filename = filename(1:end-4);
end

% Read the three MUtools EMG files.
for i = 1:3
  DataName = [filename '.sc' int2str(i)];
  fid = fopen(DataName, 'rb', 'ieee-le');  % Little endian.
  if fid<0  % Be sure file opened correctly.
    errordlg(['Can''t open file ' DataName '.'], 'EMGlab read_sc123');
    return;
  end
  % Perform the actual read, sensitive to the MATLAB version.
  try,          A = fread(fid, '*int16');  % Newer MATLAB.
    catch, try, A = int16( fread(fid, 'int16') );   % 5.3.
    catch,      A = fread(fid, 'int16');            % 5.2.
  end, end
  fclose(fid);
  if i>1 & length(A)~=size(data,1)
    errordlg([DataName ' not same length.'], 'EMGlab read_sc123');
    return;
  end
  data = [data A];
end

status = 1;  % If get this far, then no problems were encountered.
info.rate = 51200;
return
