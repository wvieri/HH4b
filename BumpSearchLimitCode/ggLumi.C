{

  TCanvas* c1 = new TCanvas("c1","Parton Lumi Ration 13/8 TeV and expo fit",200,10,700,500);

  TF1* luminosity = new TF1("luminosity", "[1]*TMath::Exp(x*[0])+[2]");
  luminosity->SetParameter(0, 0.1);
  luminosity->SetParameter(1, 1);
  luminosity->SetParameter(2, 2);

  /*

https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBSMAt8TeV
https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBSMAt13TeV

250.00 	2,6943005181 	0,3480090158
300.00 	2,8522067364 	0,3383104126
400.00 	3,1604118233 	0,3011
500.00 	3,4880860876 	0,2642160845
800.00 	4,5598537923 	0,1539387309
1000.00 	5,3960612691 	0,1364179104
1500.00 	8,1397260274 	0,0972468917
2000.00 	12,4812895797 	0,0659453303
2500.00 	19,897045658 	0,0423507109
3000.00 	33,4160305344 	0,0254863813
  */

  Double_t x[10], y[10],  x_err[10],  y_err[10];
  x[0] = 250/13000.;  x[1] = 300/13000.;   x[2] = 400/13000.; x[3] = 500/13000.;   
  x[4] = 800/13000.;  x[5] = 1000/13000.;   x[6] = 1500/13000.; x[7] = 2000/13000.;   
  x[8] = 2500/13000.;  x[9] = 3000/13000.;

  x_err[0] = 100/13000.;  x_err[1] = 100/13000.;   x_err[2] = 100/13000.; x_err[3] = 100/13000.;   
  x_err[4] = 100/13000.;  x_err[5] = 100/13000.;   x_err[6] = 100/13000.; x_err[7] = 100/13000.;   
  x_err[8] = 100/13000.;  x_err[9] = 100/13000.; 

  y[0] = 2.69;  y[1] = 2.82;   y[2] = 3.16; y[3] = 3.49;   
  y[4] = 4.56;  y[5] = 5.40;   y[6] = 8.14; y[7] = 12.48;   
  y[8] = 19.90;  y[9] = 33.42; 

  y_err[0] = 0.6;  y_err[1] = 0.6;   y_err[2] = 0.6; y_err[3] = 0.6;     
  y_err[4] = 1.0;  y_err[5] = 1.0;   y_err[6] = 2.0; y_err[7] = 1.0;     
  y_err[8] = 1.0;  y_err[9] = 1.0; 

  TGraphErrors* gLumi = new TGraphErrors(10, x, y,  x_err,  y_err);
  TH1D* PLOTTER = new TH1D("PLOTTER", "Parton Lumi Ration 13/8 TeV and expo fit; M_{X}/13 TeV;  Ratio;", 1, 0, 0.30);
  PLOTTER->SetMinimum(0);
  PLOTTER->SetMaximum(50);

  PLOTTER->SetStats(0);

  PLOTTER->Draw();
  gLumi->Draw("P");
  gLumi->Fit("luminosity");

  TPaveText *pt = new TPaveText(.15,.3,.4,.6, "BRNDC");
   pt->AddText(Form("Slope = %.1f", luminosity->GetParameter(0)));
   pt->AddText(Form("Norm = %.2f", luminosity->GetParameter(1)));
   pt->AddText(Form("Constant = %.1f", luminosity->GetParameter(2)));

   cout << "at 0.25 TeV = " << luminosity->Eval(250./13000) << endl;
   cout << "at 0.5 TeV = " << luminosity->Eval(500./13000) << endl;
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

  FILE *fp = fopen("radion.txt","r");
  FILE *fp_bfhh = fopen("radion_to_hh.txt","r");
  ntuple = new TNtuple("ntuple","NTUPLE","x:y"); 
  float x0,y0,z0;
  char line[127], line_bfhh[127];

  ofstream myfile;
  myfile.open("Radion_13TeV_HH_finalstate.txt");
  myfile << "Mass (GeV)\tgg -> Radion -> HH at 13 TeV and LambdaR = 3 TeV\n";
  myfile << "Obtained from YR4 using gg->H cross section. PDF4LHC 15 PDF\n";
  myfile << "https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBSMAt8TeV\n";
  myfile << "https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBSMAt13TeV\n";
  myfile << "https://github.com/acarvalh/Cross_sections_CMS/blob/master/WED/radion_inclusive.txt\n";

  ofstream myfile_noHH;
  myfile_noHH.open("Radion_13TeV_finalstate.txt");
  myfile_noHH << "Mass (GeV)\tgg -> Radion at 13 TeV and LambdaR = 3 TeV\n";
  myfile_noHH << "Obtained from YR4 using gg->H cross section. PDF4LHC 15 PDF";
  myfile_noHH << "https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBSMAt8TeV\n";
  myfile_noHH << "https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageBSMAt13TeV\n";
  myfile_noHH << "https://github.com/acarvalh/Cross_sections_CMS/blob/master/WED/radion_inclusive.txt\n";
  int counter = 0;
  while (fgets(&line,127,fp) && fgets(&line_bfhh,127,fp_bfhh)) {
    counter++;
    cout << "counter " << counter << endl; 

    sscanf(&line[0],"%f %f",&x0,&y0);
    sscanf(&line_bfhh[0],"%f %f",&x0,&z0);

    double lumiRatio =  luminosity->Eval(x0/13000.);

    cout << "luminosity->Eval(x0/13000.) " << lumiRatio << endl; 

    printf("x0=%f, y0=%f, z0=%f lumi=%f\n",x0,y0,z0,lumiRatio);
    ntuple->Fill(x0,y0*z0*lumiRatio);
    myfile << x0 << "\t" << y0*z0*lumiRatio << "\n";
    myfile_noHH << x0 << "\t" << y0*lumiRatio << "\n";

  }
  cout<<ntuple.GetNvar()<<" "<<ntuple.GetVar1()<<ntuple.GetVar2()<<endl;


  myfile.close();
  myfile_noHH.close();


}
