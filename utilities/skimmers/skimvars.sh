echo "Use this script with the header generated by MakeSelector"

grep -Eo 'fReader, "\w+' $1 > listofvars.txt #get variables
sed -i -e 's/fReader, \"//g' listofvars.txt
sed -i -e 'g/p4/d' listofvars.txt

cp listofvars.txt first.txt
cp listofvars.txt mid.txt
cp listofvars.txt last.txt

cp listofvars.txt outvars.txt
cp listofvars.txt inpoint.txt

sed -i -e 's/^/out_/g' listofvars.txt #add out at beginning of each variables
sed -i -e 's/$/,/g' listofvars.txt #add , to separate vars

#Output variables
paste -d ' ' - - - - - < listofvars.txt > vars.txt #compact in one line each 5 lines
sed -i -e 's/^/Float_t /g' vars.txt #add Float_t ad the beginning of each line
sed -i -e 's/,$/;/g' vars.txt #replace , at the end of line with ;
sed -i -e '$ s/, $/;/g' vars.txt #replace , at the end of file with ;

#Output branches
sed -i -e 's/^/outTree->Branch("/g' first.txt && sed -i -e 's/$/", /g' first.txt
sed -i -e 's/^/\&out_/g' mid.txt && sed -i -e 's/$/, /g' mid.txt
sed -i -e 's/^/\"/g' last.txt && sed -i -e 's/$/\/F\");/g' last.txt  

paste first.txt mid.txt last.txt > branches.txt

#Variables
sed -i -e 's/^/out_/g' outvars.txt  && sed -i -e 's/$/ = /g' outvars.txt
sed -i -e 's/^/(Float_t)(*/g' inpoint.txt  && sed -i -e 's/$/);/g' inpoint.txt

paste outvars.txt inpoint.txt > assign.txt

#Cleaning
rm first.txt
rm mid.txt
rm last.txt
rm listofvars.txt
rm outvars.txt
rm inpoint.txt
