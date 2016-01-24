{

  TCanvas* c1 = new TCanvas("c1","Parton Lumi Ration 13/8 TeV and expo fit",200,10,700,500);

  TF1* luminosity = new TF1("luminosity", "[1]*TMath::Exp(x*[0])+[2]");
  luminosity->SetParameter(0, 0.1);
  luminosity->SetParameter(1, 1);
  luminosity->SetParameter(2, 2);



  Double_t x[4], y[4],  x_err[4],  y_err[4];
  x[0] = 1000/13000.;  x[1] = 2000/13000.;   x[2] = 3000/13000.; x[3] = 4000/13000.;   
  x_err[0] = 100/13000.;  x_err[1] = 100/13000.;   x_err[2] = 100/13000.; x_err[3] = 100/13000.;   
  y[0] = 6;  y[1] = 15;   y[2] = 46; y[3] = 203.4;   
  y_err[0] = 0.6;  y_err[1] = 1.5;   y_err[2] = 4.6; y_err[3] = 20.3;     

  TGraphErrors* gLumi = new TGraphErrors(4, x, y,  x_err,  y_err);
  TH1D* PLOTTER = new TH1D("PLOTTER", "Parton Lumi Ration 13/8 TeV and expo fit; M_{X}/13 TeV;  Ratio;", 1, 0, 0.5);
  PLOTTER->SetMinimum(0);
  PLOTTER->SetMaximum(300);

  PLOTTER->SetStats(0);

  PLOTTER->Draw();
  gLumi->Draw("P");
  gLumi->Fit("luminosity");

  TPaveText *pt = new TPaveText(.15,.3,.4,.6, "BRNDC");
   pt->AddText(Form("Slope = %.1f", luminosity->GetParameter(0)));
   pt->AddText(Form("Norm = %.2f", luminosity->GetParameter(1)));
   pt->AddText(Form("Constant = %.1f", luminosity->GetParameter(2)));

   cout << "at 1.2 TeV = " << luminosity->Eval(1200./13000) << endl;
   cout << "at 1.4 TeV = " << luminosity->Eval(1400./13000) << endl;
   cout << "at 1.6 TeV = " << luminosity->Eval(1600./13000) << endl;
   cout << "at 1.8 TeV = " << luminosity->Eval(1800./13000) << endl;
   cout << "at 2.0 TeV = " << luminosity->Eval(2000./13000) << endl;
   cout << "at 2.5 TeV = " << luminosity->Eval(2500./13000) << endl;

   cout << "1200 " << luminosity->Eval(1200./13000)*1.87*9 << endl;
   cout << "1400 " << luminosity->Eval(1400./13000)*0.938*9 << endl;
   cout << "1600 " << luminosity->Eval(1600./13000)*0.484*9 << endl;
   cout << "1800 " << luminosity->Eval(1800./13000)*0.254*9 << endl;
   cout << "2000 " << luminosity->Eval(2000./13000)*0.135*9 << endl;
   cout << "2500 " << luminosity->Eval(2500./13000)*0.0286*9 << endl;


   pt->Draw();

  c1->SaveAs("ggLumiRatio_8_13TeV.png");
  c1->SaveAs("ggLumiRatio_8_13TeV.pdf");

}
