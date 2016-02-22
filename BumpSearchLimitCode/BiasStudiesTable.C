void BiasStudiesTable()
{
  TFile *_file0 = new TFile();
  TCanvas* c1 = new TCanvas("c1", "");

  int vmass[3] = {1200, 1600, 2000};
  int vevt[5] = {0, 2, 5, 10, 20};

  TH1D* hist = new TH1D();

  TTree* tree_fit_sb = new TTree();

  TF1* funG = new TF1("funG", "[0]*TMath::Gaus(x,[1],[2])");

  ofstream myfile;
  myfile.open ("toys/BiasStudies.txt");
  myfile << "Mass (GeV) & Sig (#evt) & \t $\\mu_{g}$ & \t\t Mean & \t Median & \t $\\sigma_{g}$ & \t RMS \\\\ \n \\hline \n";

  
  double mu, muLoErr, muHiErr;

  for (int imass = 0; imass < 3; imass++){
    for (int nevt = 0; nevt < 5; nevt++){
    
      int mass =  vmass[imass];
      int ievt = vevt[nevt];

      _file0 = TFile::Open(Form("toys/mlfit_%d_mu%d.root", mass, ievt));
 
      tree_fit_sb = (TTree*) _file0->Get("tree_fit_sb;1");

      tree_fit_sb->SetBranchAddress("mu", &mu);
      tree_fit_sb->SetBranchAddress("muLoErr", &muLoErr);
      tree_fit_sb->SetBranchAddress("muHiErr", &muHiErr);

      tree_fit_sb->Draw(Form("(mu-%d)/(muLoErr+muHiErr)*2>>h(20,-4,4)", ievt));

      hist = (TH1D*) _file0->Get("h");

      gStyle->SetOptFit(0011);

      funG->SetParName(1, "bias");
      funG->SetParName(2, "sigma");

      funG->SetParameter(0, 40.);
      funG->SetParameter(1, 0.);
      funG->SetParameter(2, 1.);
      
      hist->Fit("funG");


      //calculate the median
       const Long64_t nentries = tree_fit_sb->GetEntries();
      Double_t* vbias = new Double_t[nentries];
      for (Int_t i=0; i<nentries; i++) {
	 tree_fit_sb->GetEntry(i);
	 double bias = (mu-ievt)/(muLoErr+muHiErr)*2;
	 vbias[i] = bias;
      }

      double Median = TMath::Median(nentries, vbias);


      myfile << Form("%d & \t\t %d & \t\t %.2f & \t\t %.2f & \t \{\\bf %.2f} & \t %.2f & \t %.2f \\\\ \n",mass, ievt, funG->GetParameter(1), hist->GetMean(), Median, funG->GetParameter(2), hist->GetRMS());
      
      TLine* lMedian = new TLine(Median, 0, Median, hist->GetMaximum()*0.9);
      lMedian->SetLineStyle(2);
      lMedian->SetLineWidth(2);
      lMedian->SetLineColor(kBlack);

      lMedian->Draw();

      TPaveText *ptstats = new TPaveText(0.15,0.70,0.35,0.85,"blNDC");
      ptstats->SetName("stats");
      ptstats->SetBorderSize(0);
      ptstats->SetFillColor(10);
      ptstats->SetLineColor(0);
      ptstats->SetLineWidth(0);
      ptstats->SetTextAlign(12);
      ptstats->AddText(Form("Median = %.2f", Median));
      ptstats->SetTextSize(0.035);
      ptstats->Draw();

      hist->SetTitle(Form("Signal at m_{x} = %d with %d signal events injected; Pull; Ntoys;", mass, ievt));

      c1->SaveAs(Form("toys/Bias_Graviton%d_mu%d.png",mass, ievt));
      c1->SaveAs(Form("toys/Bias_Graviton%d_mu%d.pdf",mass, ievt));

      tree_fit_sb->Draw(Form("mu>>hmu(20,-10.,10+%d*4.)", ievt));
      TH1D* hmu = (TH1D*) _file0->Get("hmu");
      hmu->Fit("gaus");
      
      hmu->SetStats(0);
      c1->SaveAs(Form("toys/Mu_Graviton%d_mu%d.png",mass, ievt));
      c1->SaveAs(Form("toys/Mu_Graviton%d_mu%d.pdf",mass, ievt));
    }
    myfile << "\\hline \n";
  }

  myfile.close();

}
