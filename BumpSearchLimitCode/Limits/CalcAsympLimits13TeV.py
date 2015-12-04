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

channels=["RS1WW","RS1ZZ","WZ","qW","qZ","BulkWW","BulkZZ"]
channels=["RS1WW"]

fullToys=False

for chan in channels:
    print "chan =",chan

    if "q" in chan:
       masses =[m*100 for m in range(10,60+1)]
       bins=["CMS_jj_qVHP","CMS_jj_qVLP","CMS_jj_qV"]
    else:
       masses =[m*100 for m in range(10,40+1)]
       #bins=["CMS_jj_VVHP","CMS_jj_VVLP","CMS_jj_VV"]
       bins=["CMS_jj_VVHP"]
       #masses=[3900]

    if fullToys:
      points=[]
      for p in range(1,10):
    	points+=[float(p/10.)]
    	points+=[float(p/10.+0.05)]
    	points+=[float(p/1.)]
    	points+=[float(p/1.+0.5)]
    	points+=[float(p*10.)]
    	points+=[float(p*10.+5.)]
    else:
      points=[0.1]
   
    for bin in bins:

        for mass in masses:
          print "mass =",mass

          for point in points:

            outputname = "CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_limit"+str(int(point*10))+"_submit.src"
            logname = "CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_limit"+str(int(point*10))+"_submit.out"
            outputfile = open(outputname,'w')
            outputfile.write('#!/bin/bash\n')
            outputfile.write("cd ${CMSSW_BASE}/src/DijetCombineLimitCode; eval `scramv1 run -sh`\n")
	    if fullToys:
              outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --clsAcc 0 -T 100 -i 30 --singlePoint "+str(point)+" -s 10000"+str(int(point*100))+" --saveHybridResult --saveToys -m "+str(mass) + " -n "+chan+str(bin)+" &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_toy"+str(int(point*10))+"_fullCLs.out\n")
              outputfile.write("hadd -f grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root higgsCombine" + chan + str(bin)+".HybridNew.mH"+str(int(mass))+".10000*.root\n")
              outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --grid grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root -m "+str(mass) + " -n "+chan+str(bin)+" &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_obs_fullCLs.out\n")
              outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --grid grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root -m "+str(mass) + " -n "+chan+str(bin)+" --expectedFromGrid 0.5 &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_50_fullCLs.out\n")
	      outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --grid grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root -m "+str(mass) + " -n "+chan+str(bin)+" --expectedFromGrid 0.16 &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_16_fullCLs.out\n")
	      outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --grid grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root -m "+str(mass) + " -n "+chan+str(bin)+" --expectedFromGrid 0.84 &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_84_fullCLs.out\n")
	      outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --grid grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root -m "+str(mass) + " -n "+chan+str(bin)+" --expectedFromGrid 0.025 &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_025_fullCLs.out\n")
	      outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M HybridNew --frequentist --grid grid_mX"+str(mass)+"_" + chan + "_13TeV_"+bin+".root -m "+str(mass) + " -n "+chan+str(bin)+" --expectedFromGrid 0.975 &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_975_fullCLs.out\n")
            else:
                outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+".txt -M Asymptotic -v2 -m "+str(mass) + " -n "+chan+str(bin)+" --rMax 1000 --rMin 0.01 &>CMS_jj_"+chan+"_"+str(mass)+"_13TeV_"+bin+"_asymptoticCLs.out\n")
                outputfile.write("mv higgsCombine"+chan+str(bin)+".Asymptotic.mH"+str(int(mass))+".root Limits/CMS_jj_"+str(mass)+"_"+chan+"_13TeV_"+bin+"_asymptoticCLs.root")
            outputfile.close()
  
            command="rm "+logname
	    print command
            os.system(command)
	    if fullToys:
                command="""bsub -q 8nh -o """+logname+" source "+outputname
            else:
	        command="bsub -q 1nh -o "+logname+" source "+outputname
	    print command
            os.system(command)
	    #os.system("chmod 755 ./"+outputname+";./"+outputname)
