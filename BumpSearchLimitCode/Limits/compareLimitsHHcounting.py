from ROOT import *

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

if __name__ == '__main__':
 for suffix in ["","-tau21","-medium"]:
  f1=TFile.Open("brazilianFlag_HH-3btags"+suffix+".root")
  f2=TFile.Open("brazilianFlag_HH-4btags"+suffix+".root")
  f3=TFile.Open("brazilianFlag_HH-34btags"+suffix+".root")

  c1=f1.Get("c1")
  print [a for a in c1.GetListOfPrimitives()]
  l1=c1.GetListOfPrimitives()[-2]
  l1.GetListOfPrimitives().Remove(l1.GetListOfPrimitives()[0])
  l1.GetListOfPrimitives().Remove(l1.GetListOfPrimitives()[0])
  l1.GetListOfPrimitives().Remove(l1.GetListOfPrimitives()[0])
  #l1.GetListOfPrimitives().Remove(l1.GetListOfPrimitives()[0])
  #l1.GetListOfPrimitives().Remove(l1.GetListOfPrimitives()[0])
  c1.GetListOfPrimitives().Remove(c1.GetListOfPrimitives()[2])
  c1.GetListOfPrimitives().Remove(c1.GetListOfPrimitives()[2])
  c1.GetListOfPrimitives().Remove(c1.GetListOfPrimitives()[2])
  c1.GetListOfPrimitives().Remove(c1.GetListOfPrimitives()[2])
  c1.Draw()
  mg=c1.GetListOfPrimitives()[1]
  #mg.Draw("same")
  #l1.Draw("same")
  l1.AddEntry(mg.GetListOfGraphs()[0],"3 l sj b-tags","l")

  c2=f2.Get("c1")
  print [a for a in c2.GetListOfPrimitives()]
  g2=c2.GetListOfPrimitives()[4]
  g2.SetLineColor(4)
  g2.SetLineStyle(1)
  mg.Add(g2,"L")
  l1.AddEntry(g2,"4 l sj b-tags","l")

  c3=f3.Get("c1")
  print [a for a in c3.GetListOfPrimitives()]
  g3=c3.GetListOfPrimitives()[4]
  g3.SetLineColor(4)
  g3.SetLineStyle(3)
  mg.Add(g3,"L")
  l1.AddEntry(g3,"3+4 l sj b-tags","l")
  
  c1.SaveAs("compare_limits_HH"+suffix+".pdf")
