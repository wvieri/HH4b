{

  double Lumi = 3.0;

  TFile *_file0 = TFile::Open("HH4b_subjetBTagged_15ov2015/ControlPlotsSignal.root");

  TFile *_fileOut = TFile::Open("HH4b_subjetBTagged_15ov2015/MassPlotFineBins.root", "RECREATE");

  TH1F* TotalMass1GeV_QCD_HT700to1000 = (TH1F*) _file0->Get("TotalMass1GeV_3btagExactly_QCD_HT700to1000;1");
  TH1F* TotalMass1GeV_QCD_HT1000to1500 =(TH1F*)  _file0->Get("TotalMass1GeV_3btagExactly_QCD_HT1000to1500;1");
  TH1F* TotalMass1GeV_QCD_HT1500to2000 =(TH1F*)  _file0->Get("TotalMass1GeV_3btagExactly_QCD_HT1500to2000;1");
  TH1F* TotalMass1GeV_QCD_HT2000toInf =(TH1F*)  _file0->Get("TotalMass1GeV_3btagExactly_QCD_HT2000toInf;1");

  TotalMass1GeV_QCD_HT700to1000->Scale(6802000*Lumi/15356448);
  TotalMass1GeV_QCD_HT1000to1500->Scale(1206000*Lumi/4884057);
  TotalMass1GeV_QCD_HT1500to2000->Scale(120400*Lumi/3863167);
  TotalMass1GeV_QCD_HT2000toInf->Scale(25250*Lumi/1912529);

  TotalMass1GeV_QCD_HT2000toInf->Add(TotalMass1GeV_QCD_HT1500to2000);
  TotalMass1GeV_QCD_HT2000toInf->Add(TotalMass1GeV_QCD_HT1000to1500);
  TotalMass1GeV_QCD_HT2000toInf->Add(TotalMass1GeV_QCD_HT700to1000);

  TotalMass1GeV_QCD_HT2000toInf->Write("QCD_cat1");


  TH1F* TotalMass1GeV_QCD_HT700to1000 = (TH1F*) _file0->Get("TotalMass1GeV_4btag_QCD_HT700to1000;1");
  TH1F* TotalMass1GeV_QCD_HT1000to1500 =(TH1F*)  _file0->Get("TotalMass1GeV_4btag_QCD_HT1000to1500;1");
  TH1F* TotalMass1GeV_QCD_HT1500to2000 =(TH1F*)  _file0->Get("TotalMass1GeV_4btag_QCD_HT1500to2000;1");
  TH1F* TotalMass1GeV_QCD_HT2000toInf =(TH1F*)  _file0->Get("TotalMass1GeV_4btag_QCD_HT2000toInf;1");

  TotalMass1GeV_QCD_HT700to1000->Scale(6802000*Lumi/15356448);
  TotalMass1GeV_QCD_HT1000to1500->Scale(1206000*Lumi/4884057);
  TotalMass1GeV_QCD_HT1500to2000->Scale(120400*Lumi/3863167);
  TotalMass1GeV_QCD_HT2000toInf->Scale(25250*Lumi/1912529);

  TotalMass1GeV_QCD_HT2000toInf->Add(TotalMass1GeV_QCD_HT1500to2000);
  TotalMass1GeV_QCD_HT2000toInf->Add(TotalMass1GeV_QCD_HT1000to1500);
  TotalMass1GeV_QCD_HT2000toInf->Add(TotalMass1GeV_QCD_HT700to1000);

  TotalMass1GeV_QCD_HT2000toInf->Write("QCD_cat0");


  TH1F* TotalMass1GeV_Radion_m1000_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m1000_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1200_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m1200_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1400_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m1400_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1600_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m1600_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1800_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m1800_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m2000_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m2000_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m2500_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m2500_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m3500_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m3500_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m4000_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m4000_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m4500_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_3btagExactly_Radion_m4500_13TeV;1");


  TotalMass1GeV_Radion_m1000_13TeV->Write("Radion1000_cat1");
  TotalMass1GeV_Radion_m1200_13TeV->Write("Radion1200_cat1");
  TotalMass1GeV_Radion_m1400_13TeV->Write("Radion1400_cat1");
  TotalMass1GeV_Radion_m1600_13TeV->Write("Radion1600_cat1");
  TotalMass1GeV_Radion_m1800_13TeV->Write("Radion1800_cat1");
  TotalMass1GeV_Radion_m2000_13TeV->Write("Radion2000_cat1");
  TotalMass1GeV_Radion_m2500_13TeV->Write("Radion2500_cat1");
  TotalMass1GeV_Radion_m3500_13TeV->Write("Radion3500_cat1");
  TotalMass1GeV_Radion_m4000_13TeV->Write("Radion4000_cat1");
  TotalMass1GeV_Radion_m4500_13TeV->Write("Radion4500_cat1");



  TH1F* TotalMass1GeV_Radion_m1000_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m1000_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1200_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m1200_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1400_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m1400_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1600_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m1600_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m1800_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m1800_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m2000_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m2000_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m2500_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m2500_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m3500_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m3500_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m4000_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m4000_13TeV;1");
  TH1F* TotalMass1GeV_Radion_m4500_13TeV = (TH1F*)   _file0->Get("TotalMass1GeV_4btag_Radion_m4500_13TeV;1");


  TotalMass1GeV_Radion_m1000_13TeV->Write("Radion1000_cat0");
  TotalMass1GeV_Radion_m1200_13TeV->Write("Radion1200_cat0");
  TotalMass1GeV_Radion_m1400_13TeV->Write("Radion1400_cat0");
  TotalMass1GeV_Radion_m1600_13TeV->Write("Radion1600_cat0");
  TotalMass1GeV_Radion_m1800_13TeV->Write("Radion1800_cat0");
  TotalMass1GeV_Radion_m2000_13TeV->Write("Radion2000_cat0");
  TotalMass1GeV_Radion_m2500_13TeV->Write("Radion2500_cat0");
  TotalMass1GeV_Radion_m3500_13TeV->Write("Radion3500_cat0");
  TotalMass1GeV_Radion_m4000_13TeV->Write("Radion4000_cat0");
  TotalMass1GeV_Radion_m4500_13TeV->Write("Radion4500_cat0");




  _fileOut->Close();
  _file0->Close();

}
