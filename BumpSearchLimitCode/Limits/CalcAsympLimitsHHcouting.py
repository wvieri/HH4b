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

channels=["HHcounting"]

fullToys=False

for chan in channels:
    print "chan =",chan

    masses =[1000.0,1500.0,2000.0,2500.0]
    bins=[0,1,"01",2,3,"23",4,5,"45"]

    for bin in bins:
      for mass in masses:
            print "mass =",mass
            datacard="datacards/Xvv.mX"+str(mass)+"_" + chan + "_8TeV_channel"+str(bin)+".txt"
	    command="combine "+datacard+" -M Asymptotic -v2 -m "+str(mass) + " -n "+chan+str(bin)+" --rMax 1000 --rMin 0.01 &>Xvv.mX"+str(mass)+"_" + chan + "_Asymptotic_8TeV_channel"+str(bin)+".out"
	    print command
            os.system(command)
	    command="mv higgsCombine"+chan+str(bin)+".Asymptotic.mH"+str(int(mass))+".root Limits/Xvv.mX"+str(mass)+"_" + chan + "_Asymptotic_8TeV_channel"+str(bin)+".root"
	    print command
            os.system(command)
