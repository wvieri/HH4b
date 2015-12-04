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

fullToys=False

for chan in channels:
    print "chan =",chan

    if "q" in chan:
       masses =[m*100 for m in range(10,40+1)]
       bins=["CMS_jj_qVHP","CMS_jj_qVLP","CMS_jj_qV"]
    else:
       masses =[m*100 for m in range(10,29+1)]
       bins=["CMS_jj_VVHP","CMS_jj_VVLP","CMS_jj_VV"]

    for bin in bins:
        sig=[]
        pval=[]
        for mass in masses:
            print "mass =",mass
        
            outputname = "CMS_jj_"+chan+"_"+str(mass)+"_8TeV_"+bin+"_pvalue_submit.src"
	    outfile="Limits/CMS_jj_"+chan+"_"+str(mass)+"_8TeV_"+bin+"_pvalue.out"
            outputfile = open(outputname,'w')
            outputfile.write('#!/bin/bash\n')
            outputfile.write("cd ${CMSSW_BASE}/src/DijetCombineLimitCode; eval `scramv1 run -sh`\n")
	    if "CMS_jj_qV" in bin:
                freeze=" --freezeNuisances CMS_bkg_fit_slope3_CMS_jj_qVHP,CMS_bkg_fit_slope3_CMS_jj_qVLP"
	    if "CMS_jj_VV" in bin:
                freeze=" --freezeNuisances CMS_bkg_fit_slope3_CMS_jj_VVHP,CMS_bkg_fit_slope3_CMS_jj_VVLP"
	    if fullToys:
                outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_8TeV_"+bin+".txt -M HybridNew "+freeze+" --frequentist --fullBToys -T 3000 --fork 0 -m "+str(mass) + " -n "+chan+str(bin)+" --signif \n")
            else:
                outputfile.write("combine datacards/CMS_jj_"+chan+"_"+str(mass)+"_8TeV_"+bin+".txt -M ProfileLikelihood -v2 "+freeze+" -m "+str(mass) + " -n "+chan+str(bin)+" --signif \n")
            outputfile.close()
  
            command="rm "+outfile
	    print command
            os.system(command)
	    if fullToys:
                command="bsub -q 8nh -o "+outfile+" source "+outputname
            else:
	        command="bsub -q 1nh -o "+outfile+" source "+outputname
	    print command
            os.system(command)
