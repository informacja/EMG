function [data, info, status] = read_generic (filename, info);
%	Function for reading generic binary data files.
%	Info can be a struct with fields 'rate', 'nchannels', 'byte_order',
%		and 'header' to specify the data format.
%	If Info is not present, then a dialog box will be presented.
%	If Info = 'saved', then the most recent info will be used.

	persistent saved_info

	if nargin<2; info=[]; end;
	if ischar(info);
		info = saved_info;
	end;
	
	if isempty(info);
		[info, status] = getparams (saved_info);
		if ~status; data = []; return; end;
	end;
	saved_info = info;

	switch info.byte_order;
		case 'PC';  format = 'ieee-le';
		case 'Mac'; format = 'ieee-be';
	end;

	fid = fopen (filename, 'r', format);
	if fid<=0; status = 0; data = []; end;
	fseek (fid, info.header, 'bof');
	try
		data = fread (fid, [info.nchannels, inf], '*int16')';
	catch
		data = fread (fid, [info.nchannels, inf], 'int16')';
	end;
	fclose (fid);
	status = 1;

function [params, status] = getparams (params);
	if isempty(params);
		params = struct(...
			'rate', 10000, ...
			'nchannels', 1, ...
			'byte_order', 'Mac', ...
			'header', 0);	
	end;
	[params, status] = gendialog (...
		'EMG file format', 7, 1, params, {...
 			2, 1, 'npopup', 'nchannels', '# of channels',  ...
				[1,2,3,4,5,6,7,8,9,10]; ...
			3, 1, 'spopup', 'byte_order',  'Byte order',  ...
				{'PC', 'Mac'}; ...
			4, 1, 'edit', 'rate',   'Sampling rate', 10000; ...
			6, 1, 'edit', 'header',   'Header bytes',  0});
