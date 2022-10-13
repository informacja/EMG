function newElectrode(electrodeHandle)
userData=get(electrodeHandle,'UserData');

electrodeHandles=userData.electrodeHandles;
selectedValue=get(electrodeHandle,'Value');
if(selectedValue >length(userData.electrodes))
	selectedValue=length(userData.electrodes);
	electrode=userData.electrodes(selectedValue);
	electrodeNames=get(electrodeHandles.electrodeNameH,'String');
	indexCustoms=find(strncmp(lower(electrodeNames),'custom_',7));
    indexes=[];
   if(~isempty(indexCustoms))
	   for i=1:length(indexCustoms);
		   int=str2num(electrodeNames{indexCustoms(i)}(8:end));
		   if(~isempty(int))
			   indexes(end+1)=int;
		   end
	   end
	   indexes=sort(indexes);
	   currentElectrodeName=['Custom_',num2str(length(indexes)+1)];
	   for i=length(indexes):-1:1
		   if(indexes(i)-i>0)
			   currentElectrodeName=['Custom_',num2str(i)];
		   end
	   end
   else
	  currentElectrodeName='Custom_1';
   end
	%currentElectrodeName='Custom Electrode';
	enableName='on';
else
    electrode=userData.electrodes(selectedValue);
    currentElectrodeName=electrode.electrodeName;
	nameWithoutUScore=currentElectrodeName;
	posIndex=find(currentElectrodeName=='_');
	if(~isempty(posIndex))
		currentElectrodeName=currentElectrodeName(1:posIndex(end));
		nameWithoutUScore=currentElectrodeName(1:posIndex(end)-1);
	end
	
	electrodeNames=get(electrodeHandles.electrodeNameH,'String');
	indexCustoms=find(strncmp(lower(electrodeNames),lower(currentElectrodeName),length(currentElectrodeName)));
    indexes=[];
   if(~isempty(indexCustoms))
	   for i=1:length(indexCustoms);
		   int=str2num(electrodeNames{indexCustoms(i)}((length(currentElectrodeName)+1):end));
		   if(~isempty(int))
			   indexes(end+1)=int;
		   end
	   end
	   indexes=sort(indexes);
	   cElectrodeName=[nameWithoutUScore,'_',num2str(length(indexes)+1)];
	   for i=length(indexes):-1:1
		   if(indexes(i)-i>0)
			   cElectrodeName=[nameWithoutUScore,'_',num2str(i)];
		   end
	   end
	   currentElectrodeName=cElectrodeName;
   else
	  currentElectrodeName=[nameWithoutUScore,'_1'];
   end
	enableName='on';
end
simulatormfc=electrode.electrodeCFG;



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Get the screen size
screenSize=get(0,'ScreenSize');
screenHeight=screenSize(4);
screenWidth=screenSize(3);

%figure height and width
figureWidth=475;
figureHeight=500;
backGroundColor=[0.98,0.98,0.98];
%margin
margin=0.01;

%Main figure
f=figure(...
	'Name','Electrode',...
	'NumberTitle','off',...
	'MenuBar','none',...
	'Units','pix',...
	'Resize','off',...
	'CloseRequestFcn',@cancel,...
	'Color',backGroundColor,...
	'defaultaxesxtick', [], ...
	'defaultaxesytick', [], ...
	'defaultuicontrolcallback',@checkValue,...
	'pos',[(screenWidth-figureWidth)/2,(screenHeight-figureHeight)/2,figureWidth,figureHeight]);

preferences=[];
figureData= struct(...
	'simulatormfc',simulatormfc,...
	'preferences', preferences);

set(f,'UserData',figureData);
%----------------------------Main Panel ----------------------------------------

panelHeight=0.98;
generalRowHeight=panelHeight/22;
leftPanelMargin=0.05;
editBoxPosX=0.30;
textBoxWidth=0.35;
browseField=0.50;
editBoxWidth=0.35;
checkBoxPosX=0.05;
editBoxStartY=panelHeight+margin;

%%%%%%%%%%%%%%%%%%%%%%%%UICONTROLS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%----------------------ROW 1--------------------------------------------
editBoxY=2.5*generalRowHeight;
h=uicontrol(...
	'style','text',...
	'String','Electrode name:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);
defaultFontName= get(h,'FontName');
defaultFontSize= get(h,'FontSize');

%--------Set default font and Size--------------
set(f,...
	'defaultuicontrolFontName',defaultFontName,...
	'defaultuicontrolFontSize',defaultFontSize);
%---------------------------------------------

h=uicontrol(...
	'style','edit',...
	'Tag','electrodeName',...
	'Enable',enableName,...
	'Units','norm',...
	'horizontalAlignment','left',...
	'BackgroundColor',backGroundColor,...
	'String',currentElectrodeName,...
	'UserData',f,...
	'pos',[leftPanelMargin+textBoxWidth,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);

uicontrol(...
	'style','pushButton',...
	'Tag','configFile',...
	'Units','norm',...
	'String','Load Electrode...',...
	'Callback',@loadCFGFile,...
	'UserData',h,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);

%----------------------ROW 2--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Electrode type:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','popup',...
	'Tag','electrode_type',...
	'Units','norm',...
	'horizontalAlignment','left',...
	'BackgroundColor',backGroundColor,...
	'String','single-fibre|concentric|monopolar|bipolar',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField,editBoxStartY-editBoxY,browseField,generalRowHeight]);

%----------------------ROW 2--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Cannula radius (um):',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','edit',...
	'Tag','canPhysicalRadius',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
%----------------------ROW 3--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Cannula length(mm):',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','edit',...
	'Tag','cannula_length',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
%----------------------ROW 4--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Tip/cannula reference setup:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','popup',...
	'Tag','needleReferenceSetup',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','tip only|cannula only|tip versus cannula',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField,editBoxStartY-editBoxY,browseField,generalRowHeight]);
%----------------------ROW 5--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Minimum metric to seek needle to:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','edit',...
	'Tag','minimumMuscleMetricThreshold',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
%----------------------ROW 6--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','SNR (dB):',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','edit',...
	'Tag','signalToNoiseRatio',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
%----------------------ROW 7--------------------------------------------
editBoxY=editBoxY+3.5*generalRowHeight;

uicontrol(...
	'style','pushButton',...
	'Units','norm',...
	'String','Save As',...
	'Callback',@saveConfiguration,...
	'UserData',f,...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);


h=uicontrol(...
	'style','pushButton',...
	'Units','norm',...
	'String','Create electrode',...
	'Callback',@createElectrode,...
	'UserData',electrodeHandle,...
	'pos',[leftPanelMargin+browseField/2+0.075,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
if(gcbo==electrodeHandle)
	%set(h,'String','OK','Callback',@createElectrode);
	set(h,'String','OK','Callback',@checkElectrode);
else
	%set(h,'String','OK','Callback',@saveElectrode);
	%set(h,'String','OK','Callback',@createElectrode);
	set(h,'String','OK','Callback',@checkElectrode);
end

uicontrol(...
	'style','pushButton',...
	'Tag','Exit',...
	'Units','norm',...
	'String','Cancel',...
	'Callback',@cancel,...
	'UserData',electrodeHandle,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
fillIn(f,f);
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%checkElectrode
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function checkElectrode(src,evnt)
f=gcbf;
electrodeHandle=get(gcbo,'UserData');
h=findobj(f,'Tag','electrodeName');
electrodeName='Electrode';
if(ishandle(h))
	electrodeName=get(h,'string');
	if (isempty(electrodeName))|(strcmp(lower(electrodeName),'custom...'))
		electrodeName='Electrode';
	end
end
strValues=get(electrodeHandle,'String');

index=0;
for i=1:length(strValues)-1;
 	temp=strValues(i,:);
	if(strcmp(lower(temp),lower(electrodeName)))
	 	index=i;
       break;
			
	end
 end
 if(index>0)
	 button = questdlg('The Electrode already exists!  Do you want to replace it?','Select Electrode To Save ','Yes','Cancel','Cancel');
	 if(strcmp(button,'Yes'))
		 saveElectrode(f,electrodeHandle,electrodeName,index)
	 end
 else
	 createElectrode(f,electrodeHandle,electrodeName);
 end
			
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%createElectrode
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function createElectrode(src,evnt)
function createElectrode(f,electrodeHandle,electrodeName)
%f=gcbf;
updateCFG(f,f);
figureUserData=get(f,'UserData');
simulatormfc=figureUserData.simulatormfc;
%electrodeHandle=get(gcbo,'UserData');
electrodeData=get(electrodeHandle,'UserData');
electrodeHandles=electrodeData.electrodeHandles;
electrodes=electrodeData.electrodes;
newelectrode=electrodes(end);
% h=findobj(f,'Tag','electrodeName');
% 
% electrodeName='Electrode';
% if(ishandle(h))
% 	electrodeName=get(h,'string');
% 	if (isempty(electrodeName))|(strcmp(lower(electrodeName),'custom...'))
% 		electrodeName='Electrode';
% 	end
% end
		
newelectrode.electrodeName=electrodeName;
newelectrode.electrodeCFG=simulatormfc;
electrodes(end+1)=newelectrode;
electrodeData.electrodes=electrodes;
set(electrodeHandle,'UserData',electrodeData);
strValues=get(electrodeHandle,'String');

for i=1:length(strValues)-1;
 	temp=strValues(i,:);
	str{i}=temp{1};
 end

str{end+1}=newelectrode.electrodeName;

% parentF=get(electrodeHandle,'Parent');
% h=findobj(parentF,'Tag','electrodeIndex');
% if(ishandle(h))
% set(h,'String',str);
% end
%str{end+1}='___________';
str{end+1}='Custom...';

set(electrodeHandle,'String',str);
set(electrodeHandle,'Value',length(str)-1);
value=get(electrodeHandles.electrodeNumH,'Value');
userData=get(electrodeHandles.electrodeNumH,'UserData');
userData.electrodeIndexArray(value)=length(str)-1;
set(electrodeHandles.electrodeNumH,'UserData',userData);

updateContractionElectrodes(electrodeHandles.electrodeNumH);


delete(f);


%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%saveElectrode
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function saveElectrode(src,evnt)
function saveElectrode(f,electrodeHandle,electrodeName,index)
%f=gcbf;
updateCFG(f,f);
figureUserData=get(f,'UserData');
simulatormfc=figureUserData.simulatormfc;
%electrodeHandle=get(gcbo,'UserData');
electrodeData=get(electrodeHandle,'UserData');
electrodeHandles=electrodeData.electrodeHandles;
electrodes=electrodeData.electrodes;
%value=get(electrodeHandle,'Value')
value=index;
newelectrode=electrodes(value);


% h=findobj(f,'Tag','electrodeName');
% electrodeName='Electrode';
% if(ishandle(h))
% 	electrodeName=get(h,'string');
% 	if (isempty(electrodeName))
% 		electrodeName='Electrode';
% 	end
% end
strValues=get(electrodeHandle,'String');
for i=1:length(strValues);
 	temp=strValues(i,:);
	str{i}=temp{1};
 end
str{value}=electrodeName;
set(electrodeHandle,'String',str);

newelectrode.electrodeName=electrodeName;
newelectrode.electrodeCFG=simulatormfc;
electrodes(value)=newelectrode;
electrodeData.electrodes=electrodes;
set(electrodeHandle,'UserData',electrodeData);
updateContractionElectrodes(electrodeHandles.electrodeNumH);
delete(f);


%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%FILLIN
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function fillIn(f,parentf)

figureUserData=get(parentf,'UserData');
% get the simulatormfc structure
simulatormfc=figureUserData.simulatormfc;
h=findobj(f,'style','edit');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=getfield(simulatormfc,field);
		value=value.value;
		set(h(i),'String',value);
	end
end
h=findobj(f,'style','checkbox');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=getfield(simulatormfc,field);
		value=str2num(value.value);
		if(~isempty(value))
			set(h(i),'Value',value);
		end
	end
end
h=findobj(f,'style','popupmenu');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=getfield(simulatormfc,field);
		value=str2num(value.value);
		if(~isempty(value))
			set(h(i),'Value',value);
		end
	end
end
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%LOADCFGFILE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function loadCFGFile(src,evnt,simulator)
if nargin<3
% get the callback figure
simulator=gcbf;
figureUserData=get(simulator,'UserData');
% get the simulatormfc structure
simulatormfc=figureUserData.simulatormfc;


%Get the file
[fileName,pathName,filterIndex] = uigetfile('.cfg');
fullFilePath=fullfile(pathName,fileName);
else
	%fullFilePath=fullfile(cd,'tempsimulator.cfg');
	figureUserData=get(simulator,'UserData');
    %get the simulatormfc structure
	fullFilePath=figureUserData.preferences.configFile;
    simulatormfc=figureUserData.simulatormfc;
end

%open the file
fid=fopen(fullFilePath);
if(fid~=-1)
	nameField=get(gcbo,'UserData');
	if(ishandle(nameField))
		[pathF,nameF,extF,versnF] =fileparts(fileName);
		set(nameField,'String',nameF);
	end
	tline=fgetl(fid);
	while tline~=-1
		[field,count,errmsg,nextIndex]=sscanf(tline,'%s',1);
		if(isfield(simulatormfc,field))
			tline=tline(nextIndex:end);
			[equalSign,count,errmsg,nextIndex]=sscanf(tline,'%s',1);
			value=tline(nextIndex:end);
			value=strtrim(value);
            %value=deblank(value);
			if(value(end)==';')
				value=value(1:end-1);
			end
			if (value(1)=='"')
				value=value(2:end-1);
				value=regexprep(value,'\\\','\\');
				fieldstruct=getfield(simulatormfc,field);
				fieldstruct.value=value;
				simulatormfc=setfield(simulatormfc,field,fieldstruct);
			else
				fieldstruct=getfield(simulatormfc,field);
				fieldstruct.value=value;
				simulatormfc=setfield(simulatormfc,field,fieldstruct);
			end
		end

		tline=fgetl(fid);
	end
	fclose(fid);
	figureUserData.simulatormfc=simulatormfc;
	set(simulator,'UserData',figureUserData);
	fillIn(simulator,simulator);

end
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Cancel
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function cancel(src,evnt)
f=gcbf;
h=findobj(f,'Tag','Exit');
if(ishandle(h))
electrodeHandle=get(h,'UserData');
userData=get(electrodeHandle,'UserData');
strValue=get(electrodeHandle,'String');
value=get(electrodeHandle,'Value');
str=strValue(value,:);
if(strcmp(str{1},'Custom...'))
	electrodeHandles=userData.electrodeHandles;
	currentElectrode=get(electrodeHandles.electrodeNumH,'Value');
	electrodeUserData=get(electrodeHandles.electrodeNumH,'UserData');
	set(electrodeHandle,'Value',electrodeUserData.electrodeIndexArray(currentElectrode));	
end
end
delete(gcbf);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%checkValue
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function checkValue(src,evnt)
simulator=get(gcbo,'UserData');
figureUserData=get(simulator,'UserData');
simulatormfc=figureUserData.simulatormfc;
field=get(gcbo,'Tag');
style=get(gcbo,'style');
if(isfield(simulatormfc,field))
	if(strcmp(style,'edit'))

		fieldStruct=getfield(simulatormfc,field);
		fieldStruct.value=get(gcbo,'String');
		if (isempty(fieldStruct.range))
		elseif(length(fieldStruct.range)<2)
			if(str2num(fieldStruct.value)< fieldStruct.range)
				message=['The value should be greater than ', num2str(fieldStruct.range),' !'];
				h=warndlg(message);
			end
		else
			if((str2num(fieldStruct.value)< fieldStruct.range(1))&(str2num(fieldStruct.value)>fieldStruct.range(2)))
				message=['The value should be between ', num2str(fieldStruct.range(1)),' and ',num2str(fieldStruct.range(2)),' !'];
				h=warndlg(message);
			end

		end


	end
end

%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%updateCFG
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function updateCFG(f,parentf)

figureUserData=get(parentf,'UserData');
% get the simulatormfc structure
simulatormfc=figureUserData.simulatormfc;
h=findobj(f,'style','edit');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=get(h(i),'String');
		fieldStruct=getfield(simulatormfc,field);
	    fieldStruct.value=value;
	    simulatormfc=setfield(simulatormfc,field,fieldStruct);
		
	end
end
h=findobj(f,'style','checkbox');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=get(h(i),'Value');
		fieldStruct=getfield(simulatormfc,field);
	    fieldStruct.value=num2str(value);
	    simulatormfc=setfield(simulatormfc,field,fieldStruct);
		
	end
end
h=findobj(f,'style','popupmenu');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=get(h(i),'Value');
		fieldStruct=getfield(simulatormfc,field);
	    fieldStruct.value=num2str(value);
	    simulatormfc=setfield(simulatormfc,field,fieldStruct);
		
	end
end
figureUserData.simulatormfc=simulatormfc;
set(parentf,'UserData',figureUserData);
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%saveConfiguration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function saveConfiguration(src,evnt)
f=gcbf;
updateCFG(f,f);
h=findobj(f,'Tag','electrodeName');

electrodeName='Electrode';
if(ishandle(h))
	electrodeName=get(h,'string');
	if (isempty(electrodeName))
		electrodeName='Electrode';
	end
end
electrodeName=fullfile(cd,'Electrodes',electrodeName);
[fileName,pathName,FilterIndex] = uiputfile('.cfg','Save the Electrode configuration',electrodeName);
cfgFile=fullfile(pathName,fileName);
if(fileName~=0)
	simulator=gcbf;
    figureUserData=get(gcbf,'UserData');
    simulatormfc=figureUserData.simulatormfc;
	newFileLine=[];
	fid=fopen('default.cfg','r');
	tline=fgetl(fid);

	while tline~=-1
		[field,count,errmsg,nextIndex]=sscanf(tline,'%s',1);
		if(isfield(simulatormfc,field))
			[equalSign,count,errmsg,nextIndex]=sscanf(tline,'%s',2);
			value=tline(nextIndex:end);
			value=strtrim(value);
            %value=deblank(value);
			tline=tline(1:nextIndex);

			if (value(1)=='"')
				s=getfield(simulatormfc,field);
				s=s.value;
				s=regexprep(s,'\\','\\\');
				tline=[tline,'"',s,'"',';'];
			else
				s=getfield(simulatormfc,field);
				s=s.value;
				tline=[tline,s,';'];
			end
		end

		newFileLine{end+1}=tline;
		tline=fgetl(fid);
	end


	fclose(fid);

	
	fid=fopen(cfgFile,'w');

	for i=1:length(newFileLine)
		fprintf(fid,'%s\n',newFileLine{i});

	end
	fclose(fid);
end
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%updateContractonEletrodes
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function updateContractionElectrodes(electrodeNumH)
userData=get(electrodeNumH,'UserData');
electrodeHandles=userData.electrodeHandles;
electrodeNameH=electrodeHandles.electrodeNameH;
strValues=get(electrodeNameH,'String');
electrodeIndexArray=userData.electrodeIndexArray;
parentF=get(electrodeNumH,'Parent');
h=findobj(parentF,'Tag','electrodeIndex');
if(ishandle(h))
for i=1:length(electrodeIndexArray)
	temp=strValues(electrodeIndexArray(i),:);
	str{i}=[num2str(i),'-',temp{1}];
end
set(h,'String',str);
end