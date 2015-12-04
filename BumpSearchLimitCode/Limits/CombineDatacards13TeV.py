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

for chan in channels:

    if "q" in chan:
       masses =[m*100/2 for m in range(2*10,2*40+1)]
       masses = [1000,2000]
    else:
       masses =[m*100/2 for m in range(2*10,2*29+1)]
       masses = [1000,2000]

    for mass in masses:
        print "mass = ",mass

        bin0="CMS_jj_VVHP=datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_CMS_jj_VVHP.txt "
        bin1="CMS_jj_VVLP=datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_CMS_jj_VVLP.txt "
        bin3="CMS_jj_qVHP=datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_CMS_jj_qVHP.txt "
        bin4="CMS_jj_qVLP=datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_CMS_jj_qVLP.txt "
        
        bin01="datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_CMS_jj_VV.txt "
        bin34="datacards/CMS_jj_"+chan+"_"+str(mass)+"_13TeV_CMS_jj_qV.txt "

        comb01 = "combineCards.py " + bin0 + bin1 + " >" + bin01
        comb34 = "combineCards.py " + bin3 + bin4 + " >" + bin34

        if "q" in chan:
            print comb34
            os.system( comb34  )
	else:
            print comb01
            os.system( comb01  )
