function [fileNames] = filesList(directory, filtr, optionalNum_retrunStringFromList)

if ~exist('optionalNum_retrunStringFromList','var')
 % third parameter does not exist, so default it to something
  optionalNum_retrunStringFromList = -1; 
end
 
% if nargin==0
%     directory = 'rect/';
%     filtr = '*.wav';
%     returnStringArray_defaultReturn_cells = 0;
% end

% function [fileNames] = filesList(varargin)
%   varargin = [directory, filtr, returnStringArray_defaultReturn_cells]

%  Defaults = {'rect', '*.wav', 0};
%  Defaults(1:nargin) = varargin

% to do get current file path from csv log file (last file)
% d = uigetdir(pwd, 'Select a folder');
% files = dir(fullfile(d, '*.jpg'));
% Display the names
% files.name

% if( returnStringArray_default_cells )
    
% Defaults:
% directory = 'rect/';
% filtr     = '*.wav';

Name = strcat(directory, filtr);
Files = dir( Name );

fileNames = cell(1,length(Files));
% stringNames = '';

for k=1:length(Files)
    fileNames{k} = strcat(directory, Files(k).name);
%     stringNames = strvcat(stringNames,Files(k).name);
end

if optionalNum_retrunStringFromList > -1
    fileNames = strcat(directory, string(fileNames( optionalNum_retrunStringFromList )) );
end

end