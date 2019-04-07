### Python Program to Get rid of formatting from Mathematica
### $python process.py Rman.txt >> fixedtextfile.txt

import sys

with open(sys.argv[1] ,"r") as f:
	content= f.readlines()
if sys.argv[1][:3] == "all":
	amount = sys.argv[1][3:]
else: amount = sys.argv[1]

amount = amount.split('a', 1)[-1]
amount=amount[:amount.find(".")]
int_amount = int(amount)
zeroline = "0 "

for i in range(1,int_amount):
	zeroline=zeroline+" 0 "


for stuff in content:
	stuff = stuff.replace('"{' , "")
	stuff = stuff.replace(',' , ' ')
	stuff = stuff.replace('}"' , "")
	stuff = stuff.replace('"BREAK"' , zeroline)
	stuff = stuff.rstrip()
	
	if len(stuff)!=0:
		print stuff
	
