int nbins, nbins1; 
double min, max, width;
double min1, max1;
string histo_title;
string xaxis_title;
string yaxis_title;
string plotName, plotNameFake;
string variable, variable1;
TCut cut;
TCut cut0;
// TCut generalCut = "(isNucl || isNuclLoose) ";
//TCut generalCut =  "evweight_w_btagSF";
TCut generalCut =  "";



TH1F* numRecVertex1 = new TH1F();
TH2F* numRecVertex2 = new TH2F();
TFile *f1, *f2, *write;

bool bDATA = false;

TCanvas* Canvas  = new TCanvas("Canvas", "",  500, 500);

TTree* R2S;

void ControlPlotter(){

  string directory("HH4b_subjetBTagged_15ov2015/"); 

  string s_file = directory + "ControlPlotsSignal.root"; 
  //string s_file = "ControlPlotsNoReg_X270.root"; 
  write  = new TFile(s_file.data(), "RECREATE");

  const int ntrees = 8;

  string s[ntrees] = {
    "QCD_HT300to500.root", 
    "QCD_HT500to700.root", 
    "QCD_HT700to1000.root", 
    "QCD_HT1000to1500.root", 
    "QCD_HT1500to2000.root", 
    "QCD_HT2000toInf.root", 
    "Radion_m1200_13TeV.root", 
    "Radion_m1600_13TeV.root"};

  string sampleName[ntrees] = {
    "QCD_HT300to500", 
    "QCD_HT500to700", 
    "QCD_HT700to1000", 
    "QCD_HT1000to1500", 
    "QCD_HT1500to2000", 
    "QCD_HT2000toInf", 
    "Radion_m1200_13TeV",
    "Radion_m1600_13TeV"};



  for (int i = 0; i < ntrees; i++){


    string s1 = directory + "" + s[i];

 


    f1  = TFile::Open(s1.data());
    TDirectory* hh4b = (TDirectory*) f1->Get("hh4b;1");

    R2S = (TTree*) hh4b->Get("tree;1");

    TDirectory* allEvents = (TDirectory*) f1->Get("allEvents;1");

    TH1D* counter = (TH1D*) allEvents->Get("hEventCount;1");

    cout << s1.c_str() << endl;
    cout << "TOTAL NUMBER OF EVENTS  ======================================= " << counter->Integral() << endl;

    // R2S->Print();
 
    nbins = 50; 
    min = 1000, width = 40; 
    max = min + nbins*width;
    plotName  = "TotalMass_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 40 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();

    
    nbins = 15; 
    min = 0, width = 0.1; 
    max = min + nbins*width;
    plotName  = "DeltaEta_" + sampleName[i];
    histo_title = "";
    xaxis_title = "#Delta #eta";
    yaxis_title = "Events / 0.1";
    variable = "TMath::Abs(SelectedEvent_deta_leading2hjets)";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 42; 
    min = 200, width = 25; 
    max = min + nbins*width;
    plotName  = "PT0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "p_{T, j0} (GeV)";
    yaxis_title = "Events / 25 GeV";
    variable = "HJets_Pt[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 42; 
    min = 200, width = 25; 
    max = min + nbins*width;
    plotName  = "PT1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "p_{T, j1} (GeV)";
    yaxis_title = "Events / 25 GeV";
    variable = "HJets_Pt[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 30; 
    min = -3, width = 0.2; 
    max = min + nbins*width;
    plotName  = "ETA_" + sampleName[i];
    histo_title = "";
    xaxis_title = "#eta ";
    yaxis_title = "Events / 0.1";
    variable = "HJets_Eta";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 16; 
    min =90, width = 5; 
    max = min + nbins*width;
    plotName  = "M0Pruned_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{j0} (GeV)";
    yaxis_title = "Events / 5 GeV";
    variable = "HJets_MassPruned[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 16; 
    min =90, width = 5; 
    max = min + nbins*width;
    plotName  = "M1Pruned_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{j1} (GeV)";
    yaxis_title = "Events / 5 GeV";
    variable = "HJets_MassPruned[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();
    
 


    nbins = 10; 
    min =0, width = 0.1; 
    max = min + nbins*width;
    plotName  = "nCSV_J0_SJ0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J0 SJ0";
    yaxis_title = "Events / 0.1";
    variable = "HJets_csvSubjet0[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 10; 
    min =0, width = 0.11; 
    max = min + nbins*width;
    plotName  = "nCSV_J1_SJ0_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J1 SJ0";
    yaxis_title = "Events";
    variable = "HJets_csvSubjet0[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    nbins = 10; 
    min =0, width = 0.1; 
    max = min + nbins*width;
    plotName  = "nCSV_J0_SJ1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J0 SJ1";
    yaxis_title = "Events / 0.1";
    variable = "HJets_csvSubjet1[0]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 10; 
    min =0, width = 0.11; 
    max = min + nbins*width;
    plotName  = "nCSV_J1_SJ1_" + sampleName[i];
    histo_title = "";
    xaxis_title = "CSV J1 SJ1";
    yaxis_title = "Events / 0.1";
    variable = "HJets_csvSubjet1[1]";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();



    nbins = 6; 
    min =-0.5, width = 1; 
    max = min + nbins*width;
    plotName  = "nCSV_" + sampleName[i];
    histo_title = "";
    xaxis_title = "N(CSV0)+N(CSV1)";
    yaxis_title = "Events";
    variable = "(HJets_csvSubjet0[0]>0.605)+(HJets_csvSubjet0[1]>0.605)+(HJets_csvSubjet1[0]>0.605)+(HJets_csvSubjet1[1]>0.605)";
    cut0 = "";
    cut = cut0*generalCut;
 
    PlottiPlotta();


    // R2S->Print();
 
    nbins = 50; 
    min = 1000, width = 40; 
    max = min + nbins*width;
    plotName  = "TotalMass3btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 40 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "((HJets_csvSubjet0[0]>0.605)+(HJets_csvSubjet0[1]>0.605)+(HJets_csvSubjet1[0]>0.605)+(HJets_csvSubjet1[1]>0.605))>2.99";
    cut = cut0*generalCut;
 
    PlottiPlotta();

  }


  write->Close();

}

void PlottiPlotta(){

  Canvas->Clear();
  Canvas->cd();

  f1->cd();
  numRecVertex1 = new TH1F("numRecVertex1", histo_title.data(), nbins, min, max);
  numRecVertex1->Sumw2();
  string plot = variable + ">> numRecVertex1";
  //     R2S->Draw(plot.data(), cut, opt.data(), 100000000, 10000);
  R2S->Draw(plot.data(), cut, "");
  setParams(numRecVertex1, xaxis_title.data(), yaxis_title.data(), 1, 1, 2); 
  Canvas->Update(); 


  write->cd();
  numRecVertex1->Write(plotName.data());

}


void setParams(TH1F* f, char* xtitle, char* ytitle, int Color, int Style, int Width){


  f->SetStats(0);
  //  f->Sumw2();

  f->SetXTitle(xtitle);
  f->SetYTitle(ytitle);

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