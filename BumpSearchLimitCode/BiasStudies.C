
void BiasStudies(int mass, int ievt)
{
  TFile *_file0 = TFile::Open(Form("toys/mlfit_%d_mu%d.root", mass, ievt));
 
  TCanvas* c1 = new TCanvas("c1", "");
  TTree* tree_fit_sb = (TTree*) _file0->Get("tree_fit_sb;1");

  tree_fit_sb->Draw(Form("(mu-%d)/(muLoErr+muHiErr)*2>>h(20,-4,4)", ievt));
  
  TH1D* hist = (TH1D*) _file0->Get("h");
  hist->Fit("gaus");
  c1->SaveAs(Form("toys/Bias_Graviton%d_mu%d.png",mass, ievt));
  c1->SaveAs(Form("toys/Bias_Graviton%d_mu%d.pdf",mass, ievt));
  tree_fit_sb->Draw("mu>>hmu(70,-20,50)");
  TH1D* hmu = (TH1D*) _file0->Get("hmu");
  TF1* funG = new TF1("funG", "[0]*TMath::Gaus(x,[1],[2])");

  funG->SetParameter(0, 40.);
  funG->SetParameter(1, 0.);
  funG->SetParameter(2, 1.);
  

  hmu->Fit("gaus");
  c1->SaveAs(Form("toys/Mu_Graviton%d_mu%d.png",mass, ievt));
  c1->SaveAs(Form("toys/Mu_Graviton%d_mu%d.pdf",mass, ievt));
}
