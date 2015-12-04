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

channels=["WW","ZZ","WZ","qW","qZ"]
channels=["qW","WW"]

fullToys=True

for chan in channels:
    if "q" in chan:
       masses =[1000.0, 1100.0, 1200.0, 1300.0, 1400.0, 1500.0, 1600.0, 1700.0, 1800.0, 1900.0, 2000.0, 2100.0, 2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 2900.0, 3000.0, 3100.0, 3200.0, 3300.0, 3400.0, 3500.0, 3600.0, 3700.0, 3800.0, 3900.0, 4000.0]
       bins=[3,4,"34"]
       masses =[1000.0,1500.0,2000.0,2500.0,3000.0,3900.0]
       bins=[3]
    else:
       masses =[1000.0, 1100.0, 1200.0, 1300.0, 1400.0, 1500.0, 1600.0, 1700.0, 1800.0, 1900.0, 2000.0, 2100.0, 2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 2900.0]
       bins=[0,1,"01"]
       masses =[1000.0,1500.0,2000.0,2500.0,2800.0]
       bins=[0]

    for bin in bins:
        for mass in masses:
	      full_limit_obs=-1
	      asym_limit_obs=-1
	      full_limit_exp=-1
	      asym_limit_exp=-1
	      asym_limit_exp1up=-1
	      asym_limit_exp1down=-1
              file_obs=file("Xvv.mX"+str(mass)+"_" + chan + "_Full_8TeV_channel"+str(bin)+"_obs.out")
	      for l in file_obs.readlines():
	           if "Limit: r < " in l:
		       full_limit_obs=" ".join(l.split(" ")[3:6]).strip("\n")

              file_obs=file("Xvv.mX"+str(mass)+"_" + chan + "_Full_8TeV_channel"+str(bin)+"_50.out")
	      for l in file_obs.readlines():
	           if "Limit: r < " in l:
		       full_limit_exp=" ".join(l.split(" ")[3:6]).strip("\n")

              file_obs=file("Xvv.mX"+str(mass)+"_" + chan + "_Asymptotic_8TeV_channel"+str(bin)+".out")
	      for l in file_obs.readlines():
	           if "Observed Limit: r < " in l:
		       asym_limit_obs=l.split(" ")[4].strip("\n")
	           if "Expected 50.0%: r < " in l:
		       asym_limit_exp=l.split(" ")[4].strip("\n")
	           if "Expected 16.0%: r < " in l:
		       asym_limit_exp1down=l.split(" ")[4].strip("\n")
	           if "Expected 84.0%: r < " in l:
		       asym_limit_exp1up=l.split(" ")[4].strip("\n")
              asym_limit_exp1down=str(float(asym_limit_exp)-float(asym_limit_exp1down))
              asym_limit_exp1up=str(float(asym_limit_exp1up)-float(asym_limit_exp))

              print "chan =",chan,", mass =",mass
              print "obs full CLs = ",full_limit_obs,", obs asymptotic CLs = ",asym_limit_obs
              print "exp full CLs = ",full_limit_exp,", exp asymptotic CLs = ",asym_limit_exp," -",asym_limit_exp1down," +",asym_limit_exp1up
 