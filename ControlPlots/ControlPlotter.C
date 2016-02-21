int nbins; 
double minBin = 0, maxBin = 0, width = 0;
string histo_title;
string xaxis_title;
string yaxis_title;
string plotName, plotNameFake;
string variable, variable1;
TCut cut;
TCut cut0;
//TCut generalCut =  "evweight_w_btagSF";
//TCut generalCut =  "(HJets_MassPruned[0] > 105) * (HJets_MassPruned[1] > 105) * ((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>-0.01) * ((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1]) < 2.05) * (SelectedEventminv_leading2hjets > 1000)";

TCut generalCut =  "";//(HJets_MassPruned[0] > 105) * (HJets_MassPruned[1] > 105) * (HJets_MassPruned[0] < 135) * (HJets_MassPruned[1] < 135) * (SelectedEventminv_leading2hjets > 1000)";
//TCut generalCut =  "(SelectedEventminv_leading2hjets > 1000)";

TH1F* numRecVertex1 = new TH1F();
TH2F* numRecVertex2 = new TH2F();
TFile *f1, *f2, *fWrite;

bool bDATA = false;

TCanvas* Canvas  = new TCanvas("Canvas", "",  500, 500);

TTree* R2S;

void PlottiPlotta();
void setParams(TH1F* f, string xtitle, string ytitle, int Color, int Style, int Width);

void ControlPlotter(){

  string directory("HH4b_subjetBTagged_14Fev2016/"); 

  string s_file = directory + "ControlPlotsSignal.root"; 
  //string s_file = "ControlPlotsNoReg_X270.root"; 
  fWrite  = new TFile(s_file.data(), "RECREATE");

  const int ntrees = 19;

  string s[ntrees] = {
    "Data_RunD_Moriond.root",
    //   "hh4bTree_TT_TuneCUETP8M1_13TeV-powheg-pythia8.root",
    "QCD_HT700to1000_Moriond.root", 
    "QCD_HT1000to1500_Moriond.root", 
    "QCD_HT1500to2000_Moriond.root", 
    "QCD_HT2000toInf_Moriond.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1000_13TeV-madgraph_Moriond.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1200_13TeV-madgraph_Moriond.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1400_13TeV-madgraph_Moriond.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1600_13TeV-madgraph_Moriond.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1800_13TeV-madgraph_Moriond.root",//10 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-2000_13TeV-madgraph_Moriond.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-2500_13TeV-madgraph_Moriond.root", 
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1000_13TeV-madgraph_Moriond.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1200_13TeV-madgraph_Moriond.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1400_13TeV-madgraph_Moriond.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1600_13TeV-madgraph_Moriond.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1800_13TeV-madgraph_Moriond.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-2000_13TeV-madgraph_Moriond.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-2500_13TeV-madgraph_Moriond.root" //19
  };

  string sampleName[ntrees] = {
    "Data",
    //   "TTbar",
    "QCD_HT700to1000", 
    "QCD_HT1000to1500", 
    "QCD_HT1500to2000", 
    "QCD_HT2000toInf", 
    "Radion_m1000_13TeV",
    "Radion_m1200_13TeV",
    "Radion_m1400_13TeV",
    "Radion_m1600_13TeV",
    "Radion_m1800_13TeV",
    "Radion_m2000_13TeV",
    "Radion_m2500_13TeV",
    "Graviton_m1000_13TeV",
    "Graviton_m1200_13TeV",
    "Graviton_m1400_13TeV",
    "Graviton_m1600_13TeV",
    "Graviton_m1800_13TeV",
    "Graviton_m2000_13TeV",
    "Graviton_m2500_13TeV"
  };



  //ControlPlotsSignal.root                                        hh4bTree_RadionTohhTohbbhbb_narrow_M-1800_13TeV-madgraph.root  Plots
  //hh4bTree_JetHT_Run2015D-05Oct2015-v1.root                      hh4bTree_RadionTohhTohbbhbb_narrow_M-2000_13TeV-madgraph.root  QCD_HT1000to1500.root
  //hh4bTree_JetHT_Run2015D-PromptReco-v4.root                     hh4bTree_RadionTohhTohbbhbb_narrow_M-2500_13TeV-madgraph.root  QCD_HT1500to2000.root
  //hh4bTree_RadionTohhTohbbhbb_narrow_M-1000_13TeV-madgraph.root  hh4bTree_RadionTohhTohbbhbb_narrow_M-3500_13TeV-madgraph.root  QCD_HT2000toInf.root
  //hh4bTree_RadionTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root  hh4bTree_RadionTohhTohbbhbb_narrow_M-4000_13TeV-madgraph.root  QCD_HT300to500.root
  //hh4bTree_RadionTohhTohbbhbb_narrow_M-1400_13TeV-madgraph.root  hh4bTree_RadionTohhTohbbhbb_narrow_M-4500_13TeV-madgraph.root  QCD_HT500to700.root
  //hh4bTree_RadionTohhTohbbhbb_narrow_M-1600_13TeV-madgraph.root  MassPlotFineBins.root                                          QCD_HT700to1000.root








  for (int i = 0; i < ntrees; i++){

    if (sampleName[i].find("Data") != string::npos) generalCut =  "(HJets_MassPruned[0] > 105) * (HJets_MassPruned[1] > 105) * (HJets_MassPruned[0] < 135) * (HJets_MassPruned[1] < 135) * (SelectedEventminv_leading2hjets > 1000)*(TMath::Abs(SelectedEvent_deta_leading2hjets) < 1.3)";
//    else  generalCut =  "SelectedEvent_btagsf*(HJets_MassPruned[0] > 105) * (HJets_MassPruned[1] > 105) * (HJets_MassPruned[0] < 135) * (HJets_MassPruned[1] < 135) * (SelectedEventminv_leading2hjets > 1000)";
    else generalCut =  "SelectedEvent_btagsf*(HJets_MassPruned[0] > 105) * (HJets_MassPruned[1] > 105) * (HJets_MassPruned[0] < 135) * (HJets_MassPruned[1] < 135) * (SelectedEventminv_leading2hjets > 1000)*(TMath::Abs(SelectedEvent_deta_leading2hjets) < 1.3)";



    string s1 = directory + "" + s[i];

 


    f1  = TFile::Open(s1.data());
    TDirectory* hh4b = (TDirectory*) f1->Get("hh4b;1");

    R2S = (TTree*) hh4b->Get("tree;1");

    TDirectory* allEvents = (TDirectory*) f1->Get("allEvents;1");

    TH1D* counter = (TH1D*) allEvents->Get("hEventCount;1");

    cout << s1.c_str() << endl;
    
    
    counter = (TH1D*) allEvents->Get("hEventCount;1");
    if (counter) cout << "TOTAL NUMBER OF EVENTS  ======================================= " << counter->Integral() << endl;
    else{
      counter = (TH1D*) allEvents->Get("hEventCount_wt;1");
      cout << "TOTAL NUMBER OF EVENTS  ======================================= " << counter->Integral() << endl;
    }

      
    
  


    // R2S->Print();
 
    nbins = 75; 
    minBin = 600., width = 40.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 40 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 75; 
    minBin = 1000., width = 40.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_0to2btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 40 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<2.99)";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "(HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99) * ((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01)";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_HPHP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99) * ((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01)*(HJets_tau2[0]/HJets_tau1[0] < 0.6)*(HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_HPLP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99) * ((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01)*(HJets_tau2[0]/HJets_tau1[0] < 0.6)*(HJets_tau2[1]/HJets_tau1[1] > 0.6)";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_LPHP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99) * ((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01)*(HJets_tau2[0]/HJets_tau1[0] > 0.6)*(HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_4btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "(HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>3.99";
    cut = cut0*generalCut;
 
    PlottiPlotta();

 


    nbins = 15; 
    minBin = 0., width = 0.1; 
    maxBin = minBin + nbins*width;
    plotName  = "DeltaEta_" + sampleName[i];
    histo_title = "";
    xaxis_title = "#Delta #eta";
    yaxis_title = "Events / 0.1";
    variable = "TMath::Abs(SelectedEvent_deta_leading2hjets)";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();

    nbins = 42; 
    minBin = 200., width = 50; 
    maxBin = minBin + nbins*width;
    plotName  = "HT12_" + sampleName[i];
    histo_title = "";
    xaxis_title = "p_{T, j0} + p_{T, j1} (GeV)";
    yaxis_title = "Events / 25 GeV";
    variable = "HJets_Pt[0] + HJets_Pt[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 42; 
    minBin = 200., width = 25; 
    maxBin = minBin + nbins*width;
    plotName  = "PT0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "p_{T, j0} (GeV)";
    yaxis_title = "Events / 25 GeV";
    variable = "HJets_Pt[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 42; 
    minBin = 200., width = 25; 
    maxBin = minBin + nbins*width;
    plotName  = "PT1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "p_{T, j1} (GeV)";
    yaxis_title = "Events / 25 GeV";
    variable = "HJets_Pt[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 30; 
    minBin = -3., width = 0.2; 
    maxBin = minBin + nbins*width;
    plotName  = "ETA_" + sampleName[i];
    histo_title = "";
    xaxis_title = "#eta ";
    yaxis_title = "Events / 0.1";
    variable = "HJets_Eta";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 30; 
    minBin =90., width = 2; 
    maxBin = minBin + nbins*width;
    plotName  = "M0Pruned_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{j0} (GeV)";
    yaxis_title = "Events / 5 GeV";
    variable = "HJets_MassPruned[0]";
    cut0 = "(SelectedEventminv_leading2hjets > 1000)";
    cut = cut0; // no general cut applied
 
    PlottiPlotta();



    nbins = 30; 
    minBin =90., width = 2; 
    maxBin = minBin + nbins*width;
    plotName  = "M1Pruned_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{j1} (GeV)";
    yaxis_title = "Events / 5 GeV";
    variable = "HJets_MassPruned[1]";
    cut0 = "(SelectedEventminv_leading2hjets > 1000)";
    cut = cut0;  // no general cut applied
 
    PlottiPlotta();
    
 
    nbins = 30; 
    minBin =90., width = 2; 
    maxBin = minBin + nbins*width;
    plotName  = "M0Pruned_WMJcut_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{j0} (GeV)";
    yaxis_title = "Events / 5 GeV";
    variable = "HJets_MassPruned[0]";
    cut0 = "";
    cut = cut0*generalCut; // no general cut applied
 
    PlottiPlotta();



    nbins = 30; 
    minBin =90., width = 2; 
    maxBin = minBin + nbins*width;
    plotName  = "M1Pruned_WMJcut_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{j1} (GeV)";
    yaxis_title = "Events / 5 GeV";
    variable = "HJets_MassPruned[1]";
    cut0 = "";
    cut = cut0*generalCut;  // no general cut applied
 
    PlottiPlotta();



    nbins = 10; 
    minBin =0., width = 0.1; 
    maxBin = minBin + nbins*width;
    plotName  = "nCSV_J0_SJ0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J0 SJ0";
    yaxis_title = "Events / 0.1";
    variable = "HJets_csvSubjet0[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 10; 
    minBin =0., width = 0.11; 
    maxBin = minBin + nbins*width;
    plotName  = "nCSV_J1_SJ0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J1 SJ0";
    yaxis_title = "Events";
    variable = "HJets_csvSubjet0[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 10; 
    minBin =0., width = 0.1; 
    maxBin = minBin + nbins*width;
    plotName  = "nCSV_J0_SJ1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J0 SJ1";
    yaxis_title = "Events / 0.1";
    variable = "HJets_csvSubjet1[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 10; 
    minBin =0., width = 0.11; 
    maxBin = minBin + nbins*width;
    plotName  = "nCSV_J1_SJ1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J1 SJ1";
    yaxis_title = "Events / 0.1";
    variable = "HJets_csvSubjet1[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 6; 
    minBin =-0.5, width = 1; 
    maxBin = minBin + nbins*width;
    plotName  = "nCSV_" + sampleName[i];
    histo_title = "";
    xaxis_title = "N(CSV0)+N(CSV1)";
    yaxis_title = "Events";
    variable = "HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    // R2S->Print();
 
    nbins = 150; 
    minBin = 1000., width = 20.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass3btag_" + sampleName[i];
    histo_title = "3 btags";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 20 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "(HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99";
    cut = cut0*generalCut;
 
    PlottiPlotta();

    nbins = 150; 
    minBin = 1000., width = 20.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass4btag_" + sampleName[i];
    histo_title = "4 btags";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 20 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "(HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>3.99";
    cut = cut0*generalCut;
 
    PlottiPlotta();

    nbins = 10; 
    minBin =0., width = 0.1; 
    maxBin = minBin + nbins*width;
    plotName  = "TAU21_J0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "#tau_{21} J0";
    yaxis_title = "Events / 0.1";
    variable = "HJets_tau2[0]/HJets_tau1[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();

    nbins = 10; 
    minBin =0., width = 0.1; 
    maxBin = minBin + nbins*width;
    plotName  = "TAU21_J1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "#tau_{21} J1";
    yaxis_title = "Events / 0.1";
    variable = "HJets_tau2[1]/HJets_tau1[1]";
    cut0 = "";
    cut = cut0*generalCut;

    PlottiPlotta();




  }


  fWrite->Close();



}

void PlottiPlotta(){

  Canvas->Clear();
  Canvas->cd();

  f1->cd();
  numRecVertex1 = new TH1F("numRecVertex1", histo_title.data(), nbins, minBin, maxBin);
  numRecVertex1->Sumw2();
  string plot = variable + ">> numRecVertex1";
  //     R2S->Draw(plot.data(), cut, opt.data(), 100000000, 10000);
  R2S->Draw(plot.data(), cut, "");
  setParams(numRecVertex1, xaxis_title, yaxis_title, 1, 1, 2); 
  Canvas->Update(); 


  fWrite->cd();
  numRecVertex1->Write(plotName.data());

}


void setParams(TH1F* f, string xtitle, string ytitle, int Color, int Style, int Width){


  f->SetStats(0);
  //  f->Sumw2();

  f->SetXTitle(xtitle.c_str());
  f->SetYTitle(ytitle.c_str());

  f->SetTitleSize(0.07, "Y");
  f->SetTitleOffset(0.7, "Y");

  f->SetTitleSize(0.07, "X");
  f->SetTitleOffset(0.7, "X");

  f->SetLineColor(Color);
  f->SetLineStyle(Style);
  f->SetLineWidth(Width);



}

/*
******************************************************************************
*Tree    :tree      : HH4b                                                   *
*Entries :      306 : Total =          165114 bytes  File  Size =      80417 *
*        :          : Tree compression factor =   1.93                       *
******************************************************************************
*Br    0 :SelectedEvent_deta_leading2hjets :                                 *
*         | SelectedEventdeta_leading2hjets/D                                *
*Entries :      306 : Total  Size=       3530 bytes  File Size  =       2209 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.33     *
*............................................................................*
*Br    1 :SelectedEvent_minv_leading2hjets :                                 *
*         | SelectedEventminv_leading2hjets/D                                *
*Entries :      306 : Total  Size=       3530 bytes  File Size  =       2943 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    2 :SelectedEvent_pt_leading2hjets : SelectedEventpt_leading2hjets/D   *
*Entries :      306 : Total  Size=       3512 bytes  File Size  =       2933 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    3 :SelectedEvent_eta_leading2hjets : SelectedEventeta_leading2hjets/D *
*Entries :      306 : Total  Size=       3521 bytes  File Size  =       2938 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    4 :SelectedEvent_y_leading2hjets : SelectedEventy_leading2hjets/D     *
*Entries :      306 : Total  Size=       3503 bytes  File Size  =       2928 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    5 :SelectedEvent_phi_leading2hjets : SelectedEventphi_leading2hjets/D *
*Entries :      306 : Total  Size=       3521 bytes  File Size  =       2938 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    6 :HJets_njets : HJets_njets/I                                        *
*Entries :      306 : Total  Size=       2112 bytes  File Size  =        498 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   3.24     *
*............................................................................*
*Br    7 :HJets_Index : HJets.Index[HJets_njets]/I                           *
*Entries :      306 : Total  Size=       4708 bytes  File Size  =       1097 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   3.74     *
*............................................................................*
*Br    8 :HJets_Pt  : HJets.Pt[HJets_njets]/D                                *
*Entries :      306 : Total  Size=       7144 bytes  File Size  =       4010 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.63     *
*............................................................................*
*Br    9 :HJets_Eta : HJets.Eta[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       4279 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.53     *
*............................................................................*
*Br   10 :HJets_Phi : HJets.Phi[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       4352 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.50     *
*............................................................................*
*Br   11 :HJets_Mass : HJets.Mass[HJets_njets]/D                             *
*Entries :      306 : Total  Size=       7162 bytes  File Size  =       3963 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.65     *
*............................................................................*
*Br   12 :HJets_MassPruned : HJets.MassPruned[HJets_njets]/D                 *
*Entries :      306 : Total  Size=       7216 bytes  File Size  =       3999 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.64     *
*............................................................................*
*Br   13 :HJets_MassSoftDrop : HJets.MassSoftDrop[HJets_njets]/D             *
*Entries :      306 : Total  Size=       7234 bytes  File Size  =       4031 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.63     *
*............................................................................*
*Br   14 :HJets_tau1 : HJets.tau1[HJets_njets]/D                             *
*Entries :      306 : Total  Size=       7162 bytes  File Size  =       4097 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.60     *
*............................................................................*
*Br   15 :HJets_tau2 : HJets.tau2[HJets_njets]/D                             *
*Entries :      306 : Total  Size=       7162 bytes  File Size  =       4106 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.59     *
*............................................................................*
*Br   16 :HJets_tau3 : HJets.tau3[HJets_njets]/D                             *
*Entries :      306 : Total  Size=       7162 bytes  File Size  =       4105 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.59     *
*............................................................................*
*Br   17 :HJets_CSVIVFv2 : HJets.CSVIVFv2[HJets_njets]/D                     *
*Entries :      306 : Total  Size=       7198 bytes  File Size  =       4178 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.57     *
*............................................................................*
*Br   18 :HJets_nhf : HJets.nhf[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       1080 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   6.06     *
*............................................................................*
*Br   19 :HJets_chf : HJets.chf[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       1080 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   6.06     *
*............................................................................*
*Br   20 :HJets_emf : HJets.emf[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       1080 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   6.06     *
*............................................................................*
*Br   21 :HJets_phf : HJets.phf[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       1080 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   6.06     *
*............................................................................*
*Br   22 :HJets_muf : HJets.muf[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       1080 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   6.06     *
*............................................................................*
*Br   23 :HJets_muf : HJets.muf[HJets_njets]/D                               *
*Entries :      306 : Total  Size=       7153 bytes  File Size  =       1080 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   6.06     *
*............................................................................*
*Br   24 :HJets_nconsts : HJets.nconsts[HJets_njets]/I                       *
*Entries :      306 : Total  Size=       4726 bytes  File Size  =       1891 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   2.17     *
*............................................................................*
*Br   25 :HJets_nsubjets : HJets.nsubjets[HJets_njets]/I                     *
*Entries :      306 : Total  Size=       4735 bytes  File Size  =       1050 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   3.92     *
*............................................................................*
*Br   26 :HJets_csvSubjet0 : HJets.csvSubjet0[HJets_njets]/D                 *
*Entries :      306 : Total  Size=       7216 bytes  File Size  =       4194 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.57     *
*............................................................................*
*Br   27 :HJets_csvSubjet1 : HJets.csvSubjet1[HJets_njets]/D                 *
*Entries :      306 : Total  Size=       7216 bytes  File Size  =       4196 *
*Baskets :        5 : Basket Size=      32000 bytes  Compression=   1.57     *
*............................................................................*
*/
