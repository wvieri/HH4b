import ROOT as rt
from ROOT import *

withAcceptance=False
unblind=False
number_of_mc_events=20000.

gROOT.Reset()
gROOT.SetStyle("Plain")
gStyle.SetOptStat(0)
gStyle.SetOptFit(0)
gStyle.SetTitleOffset(1.2,"Y")
gStyle.SetPadLeftMargin(0.18)
gStyle.SetPadBottomMargin(0.15)
gStyle.SetPadTopMargin(0.08)
gStyle.SetPadRightMargin(0.05)
gStyle.SetMarkerSize(0.5)
gStyle.SetHistLineWidth(1)
gStyle.SetStatFontSize(0.020)
gStyle.SetTitleSize(0.06, "XYZ")
gStyle.SetLabelSize(0.05, "XYZ")
gStyle.SetNdivisions(510, "XYZ")
gStyle.SetLegendBorderSize(0)

def Plot(files, label, obs):

    radmasses = []
    for f in files:
        radmasses.append(float(f.replace("Xvv.mX","").split("_")[0])/1000.)
    #print radmasses

    efficiencies={}
    for mass in radmasses:
	efficiencies[mass]=0.001*number_of_mc_events/19800.0
        # W-tagging scale factor
        if "qW" in label.split("_")[0] or "qZ" in label.split("_")[0]:
            efficiencies[mass]*=0.89
        else:
            efficiencies[mass]*=0.89*0.89

    fChain = []
    for onefile in files:
        #print onefile
        fileIN = rt.TFile.Open(onefile)
        fChain.append(fileIN.Get("limit;1"))  

        rt.gROOT.ProcessLine("struct limit_t {Double_t limit;};")
        from ROOT import limit_t
        limit_branch = limit_t()

        for j in range(0,len(fChain)):
            chain = fChain[j]
            print j, chain
            chain.SetBranchAddress("limit", rt.AddressOf(limit_branch,'limit'))

    rad = []
    for j in range(0,len(fChain)):
        chain = fChain[j]
        thisrad = []
        for  i in range(0,6):
            chain.GetTree().GetEntry(i)
            thisrad.append(limit_branch.limit)
            #print "limit = %f" %limit_branch.limit
        #print thisrad
        rad.append(thisrad)


    # we do a plot r*MR
    mg = rt.TMultiGraph()
    mg.SetTitle("X -> HH")
    c1 = rt.TCanvas("c1","A Simple Graph Example",200,10,600,600)
    x = []
    yobs = []
    y2up = []
    y1up = []
    y1down = []
    y2down = []
    ymean = []

    for j in range(0,len(fChain)):
        y2up.append(rad[j][0]*efficiencies[radmasses[j]])
        y1up.append(rad[j][1]*efficiencies[radmasses[j]])
        ymean.append(rad[j][2]*efficiencies[radmasses[j]])
	print "expected limits at",radmasses[j],"GeV : median:",rad[j][2]*efficiencies[radmasses[j]]
	print "expected limits at",radmasses[j],"GeV : -2s:",rad[j][4]*efficiencies[radmasses[j]],"-1s:",rad[j][3]*efficiencies[radmasses[j]],"+1s:",rad[j][1]*efficiencies[radmasses[j]],"+2s:",rad[j][0]*efficiencies[radmasses[j]]
        y1down.append(rad[j][3]*efficiencies[radmasses[j]])
        y2down.append(rad[j][4]*efficiencies[radmasses[j]])
        yobs.append(rad[j][5]*efficiencies[radmasses[j]])

    grobs = rt.TGraphErrors(1)
    grobs.SetMarkerStyle(rt.kFullDotLarge)
    grobs.SetLineColor(rt.kRed)
    grobs.SetLineWidth(3)
    gr2up = rt.TGraphErrors(1)
    gr2up.SetMarkerColor(0)
    gr1up = rt.TGraphErrors(1)
    gr1up.SetMarkerColor(0)
    grmean = rt.TGraphErrors(1)
    grmean.SetLineColor(1)
    grmean.SetLineWidth(2)
    grmean.SetLineStyle(3)
    gr1down = rt.TGraphErrors(1)
    gr1down.SetMarkerColor(0)
    gr2down = rt.TGraphErrors(1)
    gr2down.SetMarkerColor(0)
  
    for j in range(0,len(fChain)):
        grobs.SetPoint(j, radmasses[j], yobs[j])
        gr2up.SetPoint(j, radmasses[j], y2up[j])
        gr1up.SetPoint(j, radmasses[j], y1up[j])
        grmean.SetPoint(j, radmasses[j], ymean[j])
        gr1down.SetPoint(j, radmasses[j], y1down[j])    
        gr2down.SetPoint(j, radmasses[j], y2down[j])
        #print " observed %f %f" %(radmasses[j],yobs[j])
    
    mg.Add(gr2up)#.Draw("same")
    mg.Add(gr1up)#.Draw("same")
    mg.Add(grmean,"L")#.Draw("same,AC*")
    mg.Add(gr1down)#.Draw("same,AC*")
    mg.Add(gr2down)#.Draw("same,AC*")
    if obs: mg.Add(grobs,"L,P")#.Draw("AC*")
 
    c1.SetLogy(1)
    mg.SetTitle("")
    mg.Draw("AP")
    mg.GetXaxis().SetTitle("Resonance mass (TeV)")
    if withAcceptance:
        mg.GetYaxis().SetTitle("#sigma #times BR(X #rightarrow HH #rightarrow 4b) #times A (pb)")
    else:
        mg.GetYaxis().SetTitle("#sigma #times BR(X #rightarrow HH #rightarrow 4b) (pb)")
    mg.GetYaxis().SetTitleSize(0.06)
    mg.GetXaxis().SetTitleSize(0.06)
    mg.GetXaxis().SetLabelSize(0.045)
    mg.GetYaxis().SetLabelSize(0.045)
    mg.GetYaxis().SetRangeUser(0.0004,0.4)
    mg.GetYaxis().SetTitleOffset(1.4)
    mg.GetYaxis().CenterTitle(True)
    mg.GetXaxis().SetTitleOffset(1.1)
    mg.GetXaxis().CenterTitle(True)
    mg.GetXaxis().SetNdivisions(508)

    if "qW" in label.split("_")[0] or "qZ" in label.split("_")[0]:
        mg.GetXaxis().SetLimits(0.9,4.1)
    elif "WZ" in label.split("_")[0]:
        mg.GetXaxis().SetLimits(0.9,2.1)
    else:
        mg.GetXaxis().SetLimits(0.9,3.1)

    # histo to shade
    n=len(fChain)

    grgreen = rt.TGraph(2*n)
    for i in range(0,n):
        grgreen.SetPoint(i,radmasses[i],y2up[i])
        grgreen.SetPoint(n+i,radmasses[n-i-1],y2down[n-i-1])

    grgreen.SetFillColor(rt.kGreen)
    grgreen.Draw("f") 


    gryellow = rt.TGraph(2*n)
    for i in range(0,n):
        gryellow.SetPoint(i,radmasses[i],y1up[i])
        gryellow.SetPoint(n+i,radmasses[n-i-1],y1down[n-i-1])

    gryellow.SetFillColor(rt.kYellow)
    gryellow.Draw("f,same") 

    grmean.Draw("L")
    if obs: grobs.Draw("L,P,E")


    
    gtheoryRadion = rt.TGraphErrors(1)
    gtheoryRadion.SetLineColor(rt.kBlue)
    gtheoryRadion.SetLineWidth(3)
    ftheory=open("HH_crosssections_total.txt")
    j=0
    glogtheoryRadion = rt.TGraphErrors(1)
    for lines in ftheory.readlines():
     for line in lines.split("\r"):
      if "Radion" in line:
        split=line.split(":")
        print split[1]
        gtheoryRadion.SetPoint(j, float(split[0][-4:])/1000., float(split[1]))
        glogtheoryRadion.SetPoint(j, float(split[0][-4:])/1000., log(float(split[1])))
	j+=1
    mg.Add(gtheoryRadion,"L")
    gtheoryRadion.Draw("L")
    if "HH" in label.split("_")[0]:
        ltheoryRadion="Radion #rightarrow HH"
    
    crossing=0
    for mass in range(int(radmasses[0]*1000.),int(radmasses[-1]*1000.)):
        if exp(glogtheoryRadion.Eval(mass/1000.))>grmean.Eval(mass/1000.) and crossing>=0:
	    print label,"exp crossing",mass
	    crossing=-1
        if exp(glogtheoryRadion.Eval(mass/1000.))<grmean.Eval(mass/1000.) and crossing<=0:
	    print label,"exp crossing",mass
	    crossing=1
    crossing=0
    for mass in range(int(radmasses[0]*1000.),int(radmasses[-1]*1000.)):
        if exp(glogtheoryRadion.Eval(mass/1000.))>grobs.Eval(mass/1000.) and crossing>=0:
	    print label,"obs crossing",mass
	    crossing=-1
        if exp(glogtheoryRadion.Eval(mass/1000.))<grobs.Eval(mass/1000.) and crossing<=0:
	    print label,"obs crossing",mass
	    crossing=1


            
    
    gtheoryBrane = rt.TGraphErrors(1)
    gtheoryBrane.SetLineColor(28)
    gtheoryBrane.SetLineWidth(3)
    ftheory=open("HH_crosssections_total.txt")
    j=0
    glogtheoryBrane = rt.TGraphErrors(1)
    for lines in ftheory.readlines():
     for line in lines.split("\r"):
      if "BraneGraviton" in line:
        split=line.split(":")
        print split[1]
        gtheoryBrane.SetPoint(j, float(split[0][-4:])/1000., float(split[1]))
        glogtheoryBrane.SetPoint(j, float(split[0][-4:])/1000., log(float(split[1])))
	j+=1
    mg.Add(gtheoryBrane,"L")
    gtheoryBrane.Draw("L")
    if "HH" in label.split("_")[0]:
        ltheoryBrane="Brane G #rightarrow HH"
    
    crossing=0
    for mass in range(int(radmasses[0]*1000.),int(radmasses[-1]*1000.)):
        if exp(glogtheoryBrane.Eval(mass/1000.))>grmean.Eval(mass/1000.) and crossing>=0:
	    print label,"exp crossing",mass
	    crossing=-1
        if exp(glogtheoryBrane.Eval(mass/1000.))<grmean.Eval(mass/1000.) and crossing<=0:
	    print label,"exp crossing",mass
	    crossing=1
    crossing=0
    for mass in range(int(radmasses[0]*1000.),int(radmasses[-1]*1000.)):
        if exp(glogtheoryBrane.Eval(mass/1000.))>grobs.Eval(mass/1000.) and crossing>=0:
	    print label,"obs crossing",mass
	    crossing=-1
        if exp(glogtheoryBrane.Eval(mass/1000.))<grobs.Eval(mass/1000.) and crossing<=0:
	    print label,"obs crossing",mass
	    crossing=1
    


    gtheoryBulk = rt.TGraphErrors(1)
    gtheoryBulk.SetLineColor(6)
    gtheoryBulk.SetLineWidth(3)
    ftheory=open("HH_crosssections_total.txt")
    j=0
    glogtheoryBulk = rt.TGraphErrors(1)
    for lines in ftheory.readlines():
     for line in lines.split("\r"):
      if "BulkGraviton" in line:
        split=line.split(":")
        print split[1]
        gtheoryBulk.SetPoint(j, float(split[0][-4:])/1000., float(split[1]))
        glogtheoryBulk.SetPoint(j, float(split[0][-4:])/1000., log(float(split[1])))
	j+=1
    mg.Add(gtheoryBulk,"L")
    gtheoryBulk.Draw("L")
    if "HH" in label.split("_")[0]:
        ltheoryBulk="Bulk G #rightarrow HH"
    
    crossing=0
    for mass in range(int(radmasses[0]*1000.),int(radmasses[-1]*1000.)):
        if exp(glogtheoryBulk.Eval(mass/1000.))>grmean.Eval(mass/1000.) and crossing>=0:
	    print label,"exp crossing",mass
	    crossing=-1
        if exp(glogtheoryBulk.Eval(mass/1000.))<grmean.Eval(mass/1000.) and crossing<=0:
	    print label,"exp crossing",mass
	    crossing=1
    crossing=0
    for mass in range(int(radmasses[0]*1000.),int(radmasses[-1]*1000.)):
        if exp(glogtheoryBulk.Eval(mass/1000.))>grobs.Eval(mass/1000.) and crossing>=0:
	    print label,"obs crossing",mass
	    crossing=-1
        if exp(glogtheoryBulk.Eval(mass/1000.))<grobs.Eval(mass/1000.) and crossing<=0:
	    print label,"obs crossing",mass
	    crossing=1
    

            
    
    leg = rt.TLegend(0.60,0.65,0.95,0.89)
    leg.SetFillColor(rt.kWhite)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)
    leg.SetBorderSize(0)

    if obs: leg.AddEntry(grobs, "Observed", "L,P")
    leg.AddEntry(grmean, "Expected", "L")
    leg.AddEntry(gryellow, "#pm 1 #sigma Expected", "f")
    leg.AddEntry(grgreen, "#pm 2 #sigma Expected", "f")
    leg.AddEntry(gtheoryRadion, ltheoryRadion, "L")
    leg.AddEntry(gtheoryBrane, ltheoryBrane, "L")
    leg.AddEntry(gtheoryBulk, ltheoryBulk, "L")

    leg.Draw()

    banner = TLatex(0.22,0.93,"CMS Preliminary, 19.8 fb^{-1}, #sqrt{s} = 8TeV");
    banner.SetNDC()
    banner.SetTextSize(0.045)
    banner.Draw();  

    if withAcceptance:
        c1.SaveAs("brazilianFlag_acc_%s.root" %label)
        c1.SaveAs("brazilianFlag_acc_%s.pdf" %label)
    else:
        c1.SaveAs("brazilianFlag_%s.root" %label)
        c1.SaveAs("brazilianFlag_%s.pdf" %label)


if __name__ == '__main__':
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel0.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel0.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel0.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel0.root"],
          "HH-3btags", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel1.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel1.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel1.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel1.root"],
          "HH-4btags", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel01.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel01.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel01.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel01.root"],
          "HH-34btags", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel2.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel2.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel2.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel2.root"],
          "HH-3btags-tau21", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel3.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel3.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel3.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel3.root"],
          "HH-4btags-tau21", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel23.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel23.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel23.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel23.root"],
          "HH-34btags-tau21", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel4.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel4.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel4.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel4.root"],
          "HH-3btags-medium", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel5.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel5.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel5.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel5.root"],
          "HH-4btags-medium", unblind)
    Plot(["Xvv.mX1000.0_HHcounting_Asymptotic_8TeV_channel45.root",
          "Xvv.mX1500.0_HHcounting_Asymptotic_8TeV_channel45.root",
          "Xvv.mX2000.0_HHcounting_Asymptotic_8TeV_channel45.root",
          "Xvv.mX2500.0_HHcounting_Asymptotic_8TeV_channel45.root"],
          "HH-34btags-medium", unblind)
