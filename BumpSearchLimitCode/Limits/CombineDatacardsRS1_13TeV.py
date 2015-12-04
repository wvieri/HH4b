from ROOT import *
import ROOT
import array, math
import os

gROOT.Reset()
gROOT.SetStyle("Plain")
gStyle.SetOptStat(0)
gStyle.SetOptFit(0)
gStyle.SetTitleOffset(1.2,"Y")
gStyle.SetPadLeftMargin(0.18)
gStyle.SetPadBottomMargin(0.15)
gStyle.SetPadTopMargin(0.03)
gStyle.SetPadRightMargin(0.05)
gStyle.SetMarkerSize(1.5)
gStyle.SetHistLineWidth(1)
gStyle.SetStatFontSize(0.020)
gStyle.SetTitleSize(0.06, "XYZ")
gStyle.SetLabelSize(0.05, "XYZ")
gStyle.SetNdivisions(510, "XYZ")
gStyle.SetLegendBorderSize(0)

masses =[m*100 for m in range(10,40+1)]

theoryWW={}
for line in open("theory_RS1_WW_13TeV.txt").readlines():
   split=line.replace("\n","").split(" ")
   theoryWW[int(split[0])]=float(split[1])
theoryZZ={}
for line in open("theory_RS1_ZZ_13TeV.txt").readlines():
   split=line.replace("\n","").split(" ")
   theoryZZ[int(split[0])]=float(split[1])

for mass in masses:
        print "mass = ",mass

        fWW=open("datacards/CMS_jj_RS1WW_"+str(mass)+"_13TeV_CMS_jj_VVHP.txt").readlines()
	fZZ=open("datacards/CMS_jj_RS1WW_"+str(mass)+"_13TeV_CMS_jj_VVHP.txt").readlines()
	outfile="datacards/CMS_jj_RS1_"+str(mass)+"_13TeV_CMS_jj_VVHP.txt"
	print outfile
        f=open(outfile,"w")
	for l in range(len(fWW)):
	  if "rate" in fWW[l]:
	    line="rate                                     "
	    fWWsplit=fWW[l].split(" ")
	    fZZsplit=fZZ[l].replace("  "," ").replace("  "," ").replace("  "," ").replace("  "," ").replace("  "," ").replace("  "," ").split(" ")
	    count=0
	    for s in range(len(fWWsplit)):
	      try:
	        float(fWWsplit[s])
		number=True
	      except: number=False
	      if number:
	        numberWW=float(fWWsplit[s])
	        numberZZ=float(fZZsplit[count+1])
		if count==0:
		    number=numberWW*100.*theoryWW[mass]
		elif count==1:
		    number=numberZZ*100.*theoryZZ[mass]
		else:
		    number=numberWW
		count+=1
                line+="%.5e  " % number
	    line+="\n"
	    f.write(line)
	  else:
	    f.write(fWW[l])
