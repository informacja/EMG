function [data, info, status] = read_wfdb(Rname)
%
% [data, info, status] = read_wfdb(Rname)
%
% Reads a Waveform Database (WFDB) data record.  Specification of this
% format is provided in the "WFDF Applications Guide" by George B.
% Moody (available at http:\\www\physionet.org) --- see the descriptions
% of "header" and "signal".
%
% Rname: (string) Record name, with or without the '.hea' or '.dat' extension.
%
% data:     Data matrix, one signal per column.
%           Returned as type int16 for MATLAB versions that support
%           int16 (version 5.3+).  Else, returned as regular MATLAB
%           double.
% info:     Data record information structure.  At minimum, returns
%           member "rate" with the sampling rate (Hz).
% status:   1 ==> OK.  0 ==> error.

% Check the input.
data = []; info = []; status = 1;  % Initialize status to OK.
if nargin ~= 1  % Be sure that required input argument has been supplied.
  errordlg(['Must have one argument exactly.'], 'EMGlab read_wfdb');
  return;
end
% If record name has the ".hea" or ".dat" extension, strip it.
if strcmp('.hea', Rname(max(1,end-3):end)), Rname = Rname(1:end-4); end
if strcmp('.dat', Rname(max(1,end-3):end)), Rname = Rname(1:end-4); end

% Read the header file into info.
[info FF] = e_readWFDBhea(Rname);
if FF ~= -2, status = 0; return; end

% Read the binary data files.
if info.Rsigs == 0, return; end  % No data to read.
% Build vector; one element per file indicating number of signals/file.
Scount = [1];  % First file, first signal.
for I = 2:info.Rsigs
  if strcmp(info.S(I).Name, info.S(I-1).Name)
    Scount(end) = Scount(end) + 1;  % Another signal in same file.
  else
    Scount = [Scount 1];            % New file.
  end
end
% Now, read from each file.
Sig = 1;  % Signal to get is set to one.
while Sig<=info.Rsigs
  [d FF] = e_readWFDBdat(info.S(Sig), Scount(1), fileparts(Rname));
  if FF<0, status = 0; return; end  % Some form of data file read error.
  data(1:length(d),Sig:Sig+Scount(1)-1) = d;
  Sig = Sig + Scount(1);          % Next signal to get.
  Scount = Scount(2:end);         % Eliminate first element in Scount.
end
  
return

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%% function e_readWFDBhea() %%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [WFDBinfo, Flag] = e_readWFDBhea(Rname)
% Returns WFDBinfo structure, completely filled out.
% Flag: -2 ==> OK; -1==>Failed opening file; 0==>Failed at Record Line;
%       1+ ==> Failed at corresponding Signal Line.
% Rname: (string) Record name, with or without the '.hea' filename extension.

Flag = -2;  % Default to "OK."
% Append '.hea' to the file name, if omited.
if length(Rname)<=4, Rname = [Rname '.hea']; end
if length(Rname)>4 & ~strcmp(Rname(end-3:end), '.hea'), Rname = [Rname '.hea']; end

% Try to open the WFDB header file.
AbsName = e_find_file(Rname);  % Find full path name.
fid = fopen(AbsName, 'rb');
if fid<0, Flag = -1; WFDBinfo = []; return; end

% Loop through the record line, signal line(s) and comment/info lines.
Nsig = -1; % Used as a flag.  Set initially to -1 to
           %  indicate that the record line has not yet been
           %  encountered.  After the record line has been read, Nsig
           %  lists the number of remaining signal lines.  Note that
           %  comment lines prior to the last required signal line are
           %  stored as comments.  Thereafter, stored as info
           %  strings.  (WFDB distinction.)
Ncomment = 0;  % Number of comment lines.  Init to zero.
Ninfo    = 0;  % Number of info    lines.  Init to zero.
WFDBinfo = [];
WFDBinfo.Com = [];  WFDBinfo.Iline = [];  % Initialize.

str = fgetl(fid);  % Get first line of text from file.
while ischar(str)
  [TempStr Count] = sscanf(str, '%s', Inf);  % Count non-white strings.
  if Count>0  % Skip null lines or lines with just white space.
    if str(1)=='#'  % Comment line or info string.
        if Nsig==0  % Info string.
          Ninfo = Ninfo + 1;        WFDBinfo.Iline{Ninfo} = str;
        else       % Comment line.
          Ncomment = Ncomment + 1;  WFDBinfo.Com{Ncomment} = str;
        end
    else  % Record line or signal line.
        if Nsig<0  % Record line.
          [WFDBinfo FF] = get_rec(str, WFDBinfo);
          if FF>0, Flag = 0; fclose(fid); return, end
          Nsig = WFDBinfo.Rsigs;
        else  % Signal line.
          if Nsig>0  % Fails if there are too many signal lines.
            [WFDBinfo FF] = get_sig(str, WFDBinfo);
            if FF>0, Flag = WFDBinfo.Rsigs - Nsig + 1; fclose(fid); return; end
            Nsig = Nsig - 1;
          end
        end
    end
  end  % length(str).
  str = fgetl(fid);  % Next line for next pass.
end

fclose(fid);
if ~isfield(WFDBinfo, 'Rsigs'), Flag = 0; return, end  % No lines.
if Nsig~=0, Flag = WFDBinfo.Rsigs - Nsig + 1; end  % Too few sig lines.
 
return

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%% function get_rec()  %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Info, Flag] = get_rec(Line, Info)

% Convert the Record Line to entries in the information structure Info.

% Set defaults.
Flag = 0; % OK.
Info.Rname = [];   Info.Rsegs = 1;        Info.Rsigs = [];
Info.rate  = 250;  Info.Rcfr  = [];       Info.Rbcnt = 0;
Info.Rsps  = [];   Info.Rbtm  = '0:0:0';  Info.Rbdt  = [];

% Parse the line into distinct strings.
II = 0;
[TempStr count errmsg Inext] = sscanf(Line, '%s', 1);
while count>0
  II = II + 1;
  RecStr{II} = TempStr;
  Line = Line(Inext:end);  % Chop off most recent string.
  [TempStr count errmsg Inext] = sscanf(Line, '%s', 1);
end
% Return if the two required arguments are not supplied.
if length(RecStr)<2, Flag = 1+length(RecStr); return; end

% Record name and number of segments.
II = find( RecStr{1} == '/');  % Look for optional Number of Segments.
if isempty(II)
  Info.Rname = RecStr{1};
else
  Info.Rname = RecStr{1}(1:II-1);
  Info.Rsegs = sscanf(RecStr{1}(II+1:end), '%d', 1);
end

% Number of signals.
Info.Rsigs = sscanf(RecStr{2}, '%d', 1);

% Sampling frequency, counter frequency and base counter value.
if length(RecStr)<3, Info.Rcfr = Info.rate; return; end
II = find( RecStr{3} == '/');  % Look for optional counter frequency.
if isempty(II)
  Info.rate = sscanf(RecStr{3}, '%f', 1);
  Info.Rcfr = Info.rate;  % The default, since not specified.
else  % Counter frequency is specified.
  Info.rate = sscanf(RecStr{3}(1:II-1), '%f', 1);  % Sampling frequency.
  JJ = find( RecStr{3} == '(');  % Look for optional base counter value.
  if isempty(JJ)
    Info.Rcfr = sscanf(RecStr{3}(II+1:end), '%f', 1);  % Counter freq.
  else  % Base counter value is specified.
    KK = find( RecStr{3} == ')'); % Finds tail of base counter value.
    Info.Rbcnt = sscanf(RecStr{3}(JJ+1:KK-1), '%f', 1);
  end
end

% Number of samples per signal, base time and base date.
if length(RecStr)>3, Info.Rsps = sscanf(RecStr{4}, '%d', 1); end
if length(RecStr)>4, Info.Rbtm = RecStr{5}; end
if length(RecStr)>5, Info.Rbdt = RecStr{6}; end

return

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%% function get_sig()  %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Info, Flag] = get_sig(Line, Info)

% Convert the Signal Line to entries in the information structure Info.

% Set defaults.
Flag = 0; % OK.
I = 1;
if isfield(Info, 'S'), I = length(Info.S) + 1; end

% Defaults.  Note that SigName, SigUnits and SigDescript are cells.
% Defaults.
Info.S(I).Name = [];      Info.S(I).Format = [];
Info.S(I).Spf = 1;        Info.S(I).Skew = [];
Info.S(I).ByteOff = 0;    Info.S(I).ADCgain = 200;
Info.S(I).Baseline = [];  Info.S(I).Units = [];
Info.S(I).ADCres = [];    Info.S(I).ADCzero = 0;
Info.S(I).InitVal = [];   Info.S(I).Checksum = [];
Info.S(I).Block = [];     Info.S(I).Desc = [];

% Parse the line into distinct strings.
II = 0;
[TempStr count errmsg Inext] = sscanf(Line, '%s', 1);
while count>0
  II = II + 1;
  SigStr{II} = TempStr;
  Line = Line(Inext:end);  % Chop off most recent string.
  [TempStr count errmsg Inext] = sscanf(Line, '%s', 1);
end
% Return if the two required arguments are not supplied.
if length(SigStr)<2, Flag = 1+length(SigStr); return; end

% File Name.
Info.S(I).Name = SigStr{1};

% Format, Samps/frame, skew and byte offset.
% Grab Format, which is required (and listed first).
[Info.S(I).Format count errmsg Inext] = sscanf(SigStr{2}, '%d', 1);
% Now, process any optional specifications bound to Format.
SigStr{2} = SigStr{2}(Inext:end);  % Remove Format.
while ~isempty(SigStr{2})
  Sep = SigStr{2}(1);           % Copy the separator character.
  SigStr{2} = SigStr{2}(2:end); % Remove the separator.
  switch Sep
    case 'x', [Info.S(I).Spf     count errmsg Inext] = sscanf(SigStr{2}, '%d', 1);
    case ':', [Info.S(I).Skew    count errmsg Inext] = sscanf(SigStr{2}, '%d', 1);
    case '+', [Info.S(I).ByteOff count errmsg Inext] = sscanf(SigStr{2}, '%d', 1);
  end
  SigStr{2} = SigStr{2}(Inext:end);  % Remove optional specification.
end

% ADC gain, Baseline and Units.
if length(SigStr)>2
  % Grab ADCgain.
  [Info.S(I).ADCgain count errmsg Inext] = sscanf(SigStr{3}, '%f', 1);
  SigStr{3} = SigStr{3}(Inext:end);  % Remove ADCgain.
  % If Baseline is supplied, it must be next.
  if ~isempty(SigStr{3}) & SigStr{3}(1)=='('
    SigStr{3} = SigStr{3}(2:end);  % Remove '('.
    [Info.S(I).Baseline count errmsg Inext] = sscanf(SigStr{3}, '%d', 1);
    SigStr{3} = SigStr{3}(Inext+1:end);  % Remove through/including ')'.
  end
  % If Units is supplied, it must be last.
  if ~isempty(SigStr{3}) & SigStr{3}(1)=='/'
    Info.S(I).Units = sscanf(SigStr{3}(2:end), '%s', 1);
  end
end

% Remaining optional parameters.
if length(SigStr)>3, Info.S(I).ADCres   = sscanf(SigStr{4}, '%d', 1); end
if length(SigStr)>4, Info.S(I).ADCzero  = sscanf(SigStr{5}, '%d', 1); end
if length(SigStr)>5, Info.S(I).InitVal  = sscanf(SigStr{6}, '%d', 1);
else,                Info.S(I).InitVal  = Info.S(I).ADCzero;
end
if length(SigStr)>6, Info.S(I).Checksum = sscanf(SigStr{7}, '%d', 1); end
if length(SigStr)>7, Info.S(I).Block    = sscanf(SigStr{8}, '%d', 1); end
Info.S(I).Desc = sprintf('record %s, signal %d', Info.S(I).Name, I-1);
if length(SigStr)>8
  Info.S(I).Desc = SigStr{9};
  for k=10:length(SigStr)  % Re-assemble description.
    Info.S(I).Desc = [Info.S(I).Desc ' ' SigStr{k}];
  end
end

return

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%% function e_readWFDBdat() %%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Data, Flag] = e_readWFDBdat(Sig, N, supplied_path)
% Read binary data from a WFDB data file.
%
% [Data Flag] = e_readWFDBdat(Sig, N)
%
% Sig:  Signal line information structure for first signal in this file.
% N:    Number of signals in this file.
% Data: Data matrix, one signal per row.  Returned as int16 for MATLAB
%       versions that support int16 (version 5.3+).  Else, returned as
%       regular MATLAB double.
% Flag: -2 ==> OK; -1==>Failed opening file; 0==>Failed reading file.

% Check the input.
if nargin<2, error('Need two command-line arguments'); end
Flag = 0;  % Set "OK" as default.

% Use Sig.Format to set endianess for fopen().
switch Sig.Format
  case {16}, EndianFlag = 'l';
  case {61}, EndianFlag = 'b';
  otherwise
    fclose(fid);
    errordlg('Illegal WFDB format (1)', 'EMGlab read_wfdb');
    return;
end

% Try to open the WFDB data file.
AbsName = e_find_file(Sig.Name, 0, supplied_path);  % Find full path name.
fid = fopen(AbsName, 'rb', EndianFlag);
if fid<0, Flag = -1; Data = []; return; end
DirInfo = dir(AbsName);  % Get directory listing information.
if round( (DirInfo.bytes-Sig.ByteOff)/N ) * N ~= DirInfo.bytes-Sig.ByteOff
  fclose(fid);
  errordlg(['Data file "' AbsName '": Bogus number of bytes (minus header).'], 'EMGlab read_wfdb');
  return;
end
% Skip header, if any.
if isfield(Sig, 'ByteOff') & ~isempty(Sig.ByteOff)
  fseek(fid, Sig.ByteOff, 'bof');
end

% Read data, based on the signal file format and MATLAB version.
switch Sig.Format
  case {16, 61}  % Note: '*int16' not available in MATLAB 5.2.
    try,          Data = fread(fid, [N Inf], '*int16')';  % Newer MATLAB.
      catch, try, Data = int16( fread(fid, [N Inf], 'int16')' );   % 5.3.
      catch,      Data = fread(fid, [N Inf], 'int16')';            % 5.2.
    end, end
  otherwise
    fclose(fid);
    errordlg('Illegal WFDB format (2)', 'EMGlab read_wfdb');
    return;
end  

fclose(fid);
return
