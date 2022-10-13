function status = hws_mk_hea(Fname, PCorMAC)

% Make WFDB header for a Hamilton-Wright and Stashuk simulation data file.
% The file has a 22 byte header section, followed by two-byte shorts
% which contain single-channel data.  The short format can be 16 or 61,
% depending on whether a PC or Mac wrote the data, respectively.
%
% Fname:   Header file name, complete path, with filename extension.
% PCorMAC: 'PC' ==> Data are format 16, 'MAC' ==> Data are format 61.
%          Not case sensitive.
%
% status: Set to null if no error.  Else, will contain the error message.
%

status = [];  % Default to no error.
if nargin ~= 2, error('Requires two input arguments.'); end
[pathstr, name] = fileparts(Fname);
switch lower(PCorMAC)  % Determine the format.
  case 'pc',  Format = '16';
  case 'mac', Format = '61';
  otherwise, status = ['Bogus PCorMAC "' PCorMAC '"']; return
end

fid = fopen(Fname, 'w');  % Open the header file.
if fid < 0, status = 'Unable to open file.'; end

fprintf(fid, '%s 1 31250\r\n', name);        % Write record line.
fprintf(fid, '%s.dat %s+22', name, Format);  % Write signal line.

fclose(fid);  % Close the header file.

return
