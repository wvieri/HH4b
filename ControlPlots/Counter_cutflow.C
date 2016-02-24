{
  double Lumi = 2.197;

  TFile *_file0 = TFile::Open("HH4b_subjetBTagged_14Fev2016/Data_RunD_Moriond.root");

  TDirectory* hh4b = (TDirectory*) _file0->Get("hh4b;1");
  TH1D* cutflow_data = (TH1D*) hh4b->Get("cutflow;1");

  TH1D* sum = new TH1D();

  TFile *_file1 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT700to1000_Moriond.root");

  hh4b = (TDirectory*) _file1->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");
  
  cutflow->Scale(6802000.*Lumi/15356448.);

  cutflow->Copy(*sum);


  TFile *_file2 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT1000to1500_Moriond.root");

  hh4b = (TDirectory*) _file2->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");

  cutflow->Scale(1206000.*Lumi/4963895.);
  
  sum->Add(cutflow);


  TFile *_file3 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT1500to2000_Moriond.root");

  hh4b = (TDirectory*) _file3->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");
  
  cutflow->Scale(120400.*Lumi/3868886);
  
  sum->Add(cutflow);


  TFile *_file4 = TFile::Open("HH4b_subjetBTagged_14Fev2016/QCD_HT2000toInf_Moriond.root");

  hh4b = (TDirectory*) _file4->Get("hh4b;1");
  cutflow = (TH1D*) hh4b->Get("cutflow;1");

  cutflow->Scale(25250.*Lumi/1912529);
  
  sum->Add(cutflow);
 

  sum->Draw();

}
