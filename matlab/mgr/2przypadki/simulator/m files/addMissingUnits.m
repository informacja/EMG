function ann=addMissingUnits(ann)
olddir=cd;
%Units that exist in the gst file
numOfChan=max(ann.chan);
gstUnits=unique(ann.unit);
firingDataDir=fullfile(cd,'temp','run000','patient','Firing-Data');
cd(firingDataDir);
numMU=load('AMU.dat');
generatedMU=numMU(2:end);
missingUnits=setxor(gstUnits,generatedMU);
for i=1:length(missingUnits)
	fileName=['FTMU',num2str(missingUnits(i)),'.dat'];
	unitFirings=load(fileName);
	unitFirings=unitFirings(2:end)/10000;
	ann1.unit=[];
	ann1.uncertainty=[];
	ann1.time=[];
	ann1.instance=[];
	ann1.chan=[];
	for c=1:numOfChan
		ann1.time=[ann1.time,unitFirings'];
		ann1.instance=[ann1.instance,1:length(unitFirings)];
		chan=[];
		chan(1:length(unitFirings))=c;
		ann1.chan=[ann1.chan,chan];
	end

	ann1.unit(1:numOfChan*length(unitFirings))=missingUnits(i);
	ann1.uncertainty(1:numOfChan*length(unitFirings))=1;
	
	
	
	ann.time=[ann.time',ann1.time];
	ann.time=ann.time';
	ann.unit=[ann.unit',ann1.unit];
	ann.unit=ann.unit';
	ann.chan=[ann.chan',ann1.chan];
	ann.chan=ann.chan';
	ann.uncertainty=[ann.uncertainty',ann1.uncertainty];
	ann.uncertainty=ann.uncertainty';
	ann.instance=[ann.instance,ann1.instance];
	
	
end
cd(olddir);

