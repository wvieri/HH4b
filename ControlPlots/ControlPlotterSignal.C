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

TCut generalCut =  "(HJets_MassPruned[0] > 105) * (HJets_MassPruned[1] > 105) * (HJets_MassPruned[0] < 135) * (HJets_MassPruned[1] < 135) * (SelectedEventminv_leading2hjets > 1000) * (HJets_tau2[0]/HJets_tau1[0] < 0.6 || HJets_tau2[1]/HJets_tau1[1] < 0.6)";

TH1F* numRecVertex1 = new TH1F();
TH2F* numRecVertex2 = new TH2F();
TFile *f1, *f2, *fWrite;

bool bDATA = false;

TCanvas* Canvas  = new TCanvas("Canvas", "",  500, 500);

TTree* R2S;

void PlottiPlotta();
void setParams(TH1F* f, string xtitle, string ytitle, int Color, int Style, int Width);

void ControlPlotterSignal(){

  string directory("HH4b_subjetBTagged_15ov2015/"); 

  string s_file = directory + "ControlPlots_1GeV.root"; 
  //string s_file = "ControlPlotsNoReg_X270.root"; 
  fWrite  = new TFile(s_file.data(), "RECREATE");

  const int ntrees = 24;

  string s[ntrees] = {
    "Data_RunD.root",
    "QCD_HT300to500.root", 
    "QCD_HT500to700.root", 
    "QCD_HT700to1000.root", 
    "QCD_HT1000to1500.root", 
    "QCD_HT1500to2000.root", 
    "QCD_HT2000toInf.root",
    "hh4bTree_TT_TuneCUETP8M1_13TeV-powheg-pythia8.root", // 8 samples

    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1000_13TeV-madgraph_btagsf.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1200_13TeV-madgraph_btagsf.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1400_13TeV-madgraph_btagsf.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1600_13TeV-madgraph_btagsf.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-1800_13TeV-madgraph_btagsf.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-2000_13TeV-madgraph_btagsf.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-2500_13TeV-madgraph_btagsf.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-3500_13TeV-madgraph_btagsf.root", 
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-4000_13TeV-madgraph_btagsf.root",
    "hh4bTree_RadionTohhTohbbhbb_narrow_M-4500_13TeV-madgraph_btagsf.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1200_13TeV-madgraph_btagsf.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1400_13TeV-madgraph_btagsf.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1600_13TeV-madgraph_btagsf.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-1800_13TeV-madgraph_btagsf.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-2000_13TeV-madgraph_btagsf.root",
    "hh4bTree_GravitonTohhTohbbhbb_narrow_M-2500_13TeV-madgraph_btagsf.root"
  };

  string sampleName[ntrees] = {
    "Data",
    "QCD_HT300to500", 
    "QCD_HT500to700", 
    "QCD_HT700to1000", 
    "QCD_HT1000to1500", 
    "QCD_HT1500to2000", 
    "QCD_HT2000toInf",
     "TTbar", 
    
    "Radion_m1000_13TeV",
    "Radion_m1200_13TeV",
    "Radion_m1400_13TeV",
    "Radion_m1600_13TeV",
    "Radion_m1800_13TeV",
    "Radion_m2000_13TeV",
    "Radion_m2500_13TeV",
    "Radion_m3500_13TeV",
    "Radion_m4000_13TeV",
    "Radion_m4500_13TeV",
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

    
    TCut  btagsf = "SelectedEvent_btagsf";
    if (i < 8) btagsf = ""; //if signal is used where we have btagsf

      
    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_4btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    else  cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    else cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_HPHP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    else  cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();





    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_HPLP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] > 0.6)";
    else  cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] > 0.6)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();






    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_3btagExactly_LPHP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01) * (HJets_tau2[0]/HJets_tau1[0] > 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    else cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01) * (HJets_tau2[0]/HJets_tau1[0] > 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();















    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_subtr_4btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets_subtr";
    if (i > 7) variable = "SelectedEventminv_leading2hjets_subtr";
    else variable = "SelectedEventminv_leading2hjets_subtractedd";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    else  cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_subtr_3btagExactly_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    if (i > 7) variable = "SelectedEventminv_leading2hjets_subtr";
    else variable = "SelectedEventminv_leading2hjets_subtractedd";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    else cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_subtr_3btagExactly_HPHP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    if (i > 7) variable = "SelectedEventminv_leading2hjets_subtr";
    else variable = "SelectedEventminv_leading2hjets_subtractedd";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    else  cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();





    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_subtr_3btagExactly_HPLP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    if (i > 7) variable = "SelectedEventminv_leading2hjets_subtr";
    else variable = "SelectedEventminv_leading2hjets_subtractedd";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] > 0.6)";
    else  cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01) * (HJets_tau2[0]/HJets_tau1[0] < 0.6) * (HJets_tau2[1]/HJets_tau1[1] > 0.6)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();






    nbins = 4000; 
    minBin = 1000., width = 1.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass1GeV_subtr_3btagExactly_LPHP_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    if (i > 7) variable = "SelectedEventminv_leading2hjets_subtr";
    else variable = "SelectedEventminv_leading2hjets_subtractedd";
    if (i > 7) cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01) * (HJets_tau2[0]/HJets_tau1[0] > 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    else cut0 = "((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])>2.99)*((HJets_nsubjetsBTaggedCSVL[0]+HJets_nsubjetsBTaggedCSVL[1])<3.01) * (HJets_tau2[0]/HJets_tau1[0] > 0.6) * (HJets_tau2[1]/HJets_tau1[1] < 0.6)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();

























    if (i < 8) continue;










    //================================= SYSTEMATICS BTAGSF ==============================//



    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_4btag_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_3btagExactly_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();









    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_4btag_bcUp_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_bcUp*(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();

    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_4btag_bcDown_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_bcDown*(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();

    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_3btagExactly_bcUp_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_bcUp*(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();

    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_3btagExactly_bcDown_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_bcDown*(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();

    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_4btag_lUp_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_lUp*(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_4btag_lDown_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_lDown*(SelectedEvent_nsubjetsBTaggedCSVL > 3.99)";
    cut = btagsf*cut0*generalCut;
 
    PlottiPlotta();


    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_3btagExactly_lUp_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_lUp*(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    cut = btagsf*cut0*generalCut;
 


    nbins = 80; 
    minBin = 1000., width = 50.; 
    maxBin = minBin + nbins*width;
    plotName  = "TotalMass_3btagExactly_lDown_" + sampleName[i];
    histo_title = "";
    xaxis_title = "m_{4b} (GeV)";
    yaxis_title = "Events / 1 GeV";
    variable = "SelectedEventminv_leading2hjets";
    cut0 = "SelectedEvent_btagsf_lDown*(SelectedEvent_nsubjetsBTaggedCSVL > 2.99)*(SelectedEvent_nsubjetsBTaggedCSVL < 3.01)";
    cut = btagsf*cut0*generalCut;
 
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
