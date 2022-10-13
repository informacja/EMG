function [Ann, Fvar] = eaf_load(Fname, varargin)
%
% [Ann, status] = eaf_load(Fname [, option pairs])
% [Ann, status, Fvar] = eaf_load(Fname, [, option pairs])
%
% Fname: (String) Name of the annotation file (filename extension MUST be
%        included).  If the file is not in the MATLAB path, then specify
%        the file name using the complete path name.
% Option pairs:
% 'Format' format_string: Format specifier (case sensitive).  When absent,
%         eaf_load() determines the file format via the filename extension.
%         In particular, the filename extension IS the file format
%         specifier.  If the extension is denoted as "xxx", then eaf_load
%         looks for another function named "eaf_load_xxx" that
%         loads annotations into the EMGlab annotation structure Ann.  The
%         table below gives the names of pre-defined formats whose functions
%         are provided with EMGlab.  Examples of how to write an
%         eaf_load_xxx function can be found by looking at the functions
%         for these pre-defined formats.  A common set of input and output
%         arguments is used.
%              When Format is specified, the file name extension is
%         ignored and the function "eaf_load_'Format'" is used to load the
%         EMGlab annotation structure.
%
% Ann:    Returned annotation structure.  Required members (each returned
%         as a column vector) are:
%           unit:   Motor unit number (integer, stored as Matlab double),
%           time:  Absolute (since begin of data) firing time (seconds, double),
%           version: For EAF files, lists the annotation specification
%               version as a string.
%         Optional members (depends on the file format) are documented in
%           EMGlab documentation (see "EMGlab Annotation Structure within
%           MATLAB".
% status:  -1 ==> error, 0 ==> OK.
% Fvar:    Optional output variable holding freeform variables, if any
%          were supplied in the EAF.  If none, Fvar = [].  Else, Fvar
%          is a structure vector, one structure element per freeform
%          variable.  Each structure element has two fields.  Field
%          'nam' is a string holding a variable name.  Field 'val'
%          is a variable holding the corresponding variable value.
%          The class of val corresponds to the variable class.  Thus,
%          all freeform variables can be unpacked into the calling
%          function's workspace with:
%          for k=1:length(Fvar), eval([Fvar(k).nam ' = Fvar(k).val;']); end
%
% The table of pre-defined filename "Format"s and their corresponding
% implicit filename extensions follows.
%
% Format      Ext  Definition
% 'ann'      .ann  EMGlab simple ASCII format for time and unit number.
% 'eaf'      .eaf  "EMGlab annotation file" matching the standard set forth
%                  by this software (ASCII).
% 'tim'      .tim  MUtools software legacy format (binary, little endian).

% Copyright (c) 2006. Edward A. Clancy, Kevin C. McGill and others.
% This work is licensed under the Aladdin free public license.
% For copying permissions see license.txt.
% email: emglab@emglab.stanford.edu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Perform some simple checking of the command line arguments.
Ann = [];     % Null value assigned on premature error return.
status = -1;  % Default to error.  Alter as annotations are read.
Fvar = []; % Default to empty.
if nargin<1, error ('Annotation file name not specified.'); end

% Process command-line options.
Format = NaN;  % Not yet specified.
if mod(length(varargin), 2) == 1, 
    error ('Options must each be entered as pairs.'); 
end
for k = 1:2:length(varargin)
  switch lower(varargin{k})
    case 'format', Format = varargin{k+1};
    otherwise
      error (['Bad option: "' varargin{k}]); 
  end
end

% If file format is not specified, get it from the filename extension.
if isnan(Format)  % File format not specified.
  Index = find('.' == Fname);  % Find periods in file name, if any.
  if isempty(Index) | length(Fname)<Index(end)+1 % No '.' or text after '.'.
    error (['Filename lacks extension: ' Fname]);
  else  % One or more periods found in file name.
    Format = Fname(Index(end)+1:end);
  end
end

% Read the annotations, based on the format.
reader_name = ['eaf_load_', Format];
if exist(reader_name)~=2; error (['No reader found for file type ', Format, '.']); end;
eval(['[Ann, Fvar] = ', reader_name '(Fname);']);
