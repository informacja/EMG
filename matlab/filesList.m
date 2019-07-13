function [fileNames] = filesList(directory, filtr, returnStringArray_default_cells)

% to do get current file path from csv log file (last file)
% d = uigetdir(pwd, 'Select a folder');
% files = dir(fullfile(d, '*.jpg'));
% Display the names
% files.name

% Defaults:
% directory = 'rect/';
% filtr     = '*.wav';

Name = strcat(directory, filtr);
Files = dir( Name );

fileNames = cell(1,length(Files));
stringNames = '';

for k=1:length(Files)
    fileNames{k} = Files(k).name;
    stringNames = strvcat(stringNames,Files(k).name)
end

if ( returnStringArray_default_cells )
    fileNames = stringNames;

end