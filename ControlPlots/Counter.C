{
  double Lumi = 2.197;

  TFile *_file0 = TFile::Open("HH4b_subjetBTagged_14Fev2016/Data_RunD_Moriond.root");

  TDirectory* hh4b = (TDirectory*) _file0->Get("hh4b;1");
  TH1D* cutflow = (TH1D*) hh4b->Get("cutflow;1");
  cout << cutflow->GetBinContent(7) << endl;

  double data = cutflow->GetBinContent(7);

  TFile *_file1 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT700to1000_Moriond.root");

  hh4b = (TDirectory*) _file1->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");
  
  double nevt_HT700to1000 = cutflow->GetBinContent(7);
  double nevt_HT700to1000_w = cutflow->GetBinContent(7)*6802000.*Lumi/15356448.;

  cout << "HT700to1000: " << nevt_HT700to1000 << " weighted = "<< nevt_HT700to1000_w << " weight = " << 6802000.*Lumi/15356448. << endl;


  TFile *_file2 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT1000to1500_Moriond.root");

  hh4b = (TDirectory*) _file2->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");
  
  double nevt_HT1000to1500 = cutflow->GetBinContent(7);
  double nevt_HT1000to1500_w = cutflow->GetBinContent(7)*1206000.*Lumi/4963895.;

  cout << "HT1000to1500: " << nevt_HT1000to1500 << " weighted = "<< nevt_HT1000to1500_w<< " weight = " << 1206000.*Lumi/4963895. << endl;


  TFile *_file3 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT1500to2000_Moriond.root");

  hh4b = (TDirectory*) _file3->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");
  
  double nevt_HT1500to2000 = cutflow->GetBinContent(7);
  double nevt_HT1500to2000_w = cutflow->GetBinContent(7)*120400.*Lumi/3868886;

  cout << "HT1500to2000: " << nevt_HT1500to2000 << " weighted = "<< nevt_HT1500to2000_w << " weight = " << 120400.*Lumi/3868886 << endl;

  TFile *_file4 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT2000toInf_Moriond.root");

  hh4b = (TDirectory*) _file4->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");
  
  double nevt_HT2000toInf = cutflow->GetBinContent(7);
  double nevt_HT2000toInf_w = cutflow->GetBinContent(7)*25250.*Lumi/1912529;

  cout << "HT2000toInf: " << nevt_HT2000toInf << " weighted = "<< nevt_HT2000toInf_w<< " weight = " << 25250.*Lumi/1912529 << endl;

  cout << "data = " << data << " QCD = " << nevt_HT700to1000_w +  nevt_HT1000to1500_w +  nevt_HT1500to2000_w + nevt_HT2000toInf_w << endl;

}
