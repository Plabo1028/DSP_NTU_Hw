import sys
import string
import os
import time
import csv

try:
    in_file = open(sys.argv[1], "rb")
    out_file = open(sys.argv[2],"w")

except:
    sys.exit("ERROR. Did you make a mistake in the spelling")

text = in_file.read()
Row = text.split('\n')

i = 0

AnDict = dict()

for Level1 in Row:

	i = i+1
	temp1=[]
	temp2=[]

	data1=Level1.split(' ')
	#print data1 #['\xa4@', '\xa3\xb8\xa3\xbd/\xa3\xb8\xa3\xbf/\xa3\xb8\xa1\xc5']
	temp1 = data1[0] #chinese Word
	#print temp1 #the first chinese Word

	data2 = data1[1].split('/')
	#print data2 #['\xa3\xb8\xa3\xbd', '\xa3\xb8\xa3\xbf', '\xa3\xb8\xa1\xc5'] same as data1[1]
	#time.sleep(2)
	for level2 in data2:
		temp2=[level2[z:z+2] for z in range(0, len(level2), 2)]
		#print i
		if temp2[0] in AnDict:
			if temp1 not in AnDict.get(temp2[0]):
				AnDict[temp2[0]].append(temp1)
		else:
			AnDict[temp2[0]] = [temp1]
		
		#print AnDict
		#print ("\n")
		#print '{0} {1} {2}\n' .format(i,temp1,temp2[0]) # just have the first ChuIn which is we want
	if i == 13009:
		break

	#time.sleep(0.01)

t1=AnDict.items()
tempList=[]
for d1 in t1:
	tempList.append(d1[0])
	
	count = 0
	for d2 in d1[1]:
		tempList.append(d2)
	writer = csv.writer(out_file, delimiter=" ", lineterminator="\n")
	writer.writerow(tempList)
	tempList=[]
	for d2 in d1[1]:
		tempList.append(d2)

		tempList.append(d2)
		writer = csv.writer(out_file, delimiter=" ", lineterminator="\n")
		writer.writerow(tempList)
		tempList=[]

 
in_file.close()
out_file.close()