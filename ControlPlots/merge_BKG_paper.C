{

  // control plots we want

  const int nplots = 13;
  const int ntrees = 8;
  double sherpa = 1.;//1./2.54;
  double Lumi = 3.0;
  double NewNtot = 150.;
  double scale_radion = 1./20000.;
  double scale_mssmhiggs = NewNtot/300000.;
  double scale_ttgj_eff = 0.102;

  double ReajustScale = 5.;

  bool entryUpdate = 0;

  string directory = "HH4b_subjetBTagged_15ov2015/";

  /*
../SAMPLES_20151106/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
TOTAL NUMBER OF EVENTS  ======================================= 232442
../SAMPLES_20151106/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
TOTAL NUMBER OF EVENTS  ======================================= 911943
../SAMPLES_20151106/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
TOTAL NUMBER OF EVENTS  ======================================= 97008
../SAMPLES_20151106/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
TOTAL NUMBER OF EVENTS  ======================================= 198141
../SAMPLES_20151106/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root
TOTAL NUMBER OF EVENTS  ======================================= 708121
../SAMPLES_20151106/RadionTohhTohbbhbb_narrow_M-1200_13TeV-madgraph.root
TOTAL NUMBER OF EVENTS  ======================================= 50000
../SAMPLES_20151106/RadionTohhTohbbhbb_narrow_M-1600_13TeV-madgraph.root
TOTAL NUMBER OF EVENTS  ======================================= 50000
------------------------------------
In pb
/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM 351300
/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM 31630
/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM 6802
/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM 1206
/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM 120.4
/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM 25.25
  */

 //5, 1.1, 1.1, 0.37, 16.5};

  double scaleXsec[ntrees] = {351300000*Lumi/19826197, 31630000*Lumi/19664159, 6802000*Lumi/15356448, 1206000*Lumi/4884057, 
			      120400*Lumi/3863167, 25.25*Lumi/1912529,
				1, 1};

  double Uncertainty[ntrees] = {1, 1, 1, 1, 1, 1,
				1, 1};


  string sTitle[ntrees] =   {"QCD_HT300to1000", "QCD_HT300to1000",  "QCD_HT300to1000",  "QCD_HT1000to1500", "QCD_HT1500to2000", "QCD_HT2000toInf", 
			     "M_{R} = 1.2 TeV", "M_{R} = 1.6 TeV"};

  bool AddToStack[ntrees] = {true, true, true,  true, true, true,
			     false, false};
  
  bool UsefulColor[ntrees] = {false, false, true, true, true, true,
			      true, true};

  int Color[ntrees] = {kYellow, kYellow, kYellow, 42, 43, 44,
		       kBlack, kBlue};

  string treeNames[ntrees] = { "QCD_HT300to500", "QCD_HT500to700",  "QCD_HT700to1000", "QCD_HT1000to1500",  "QCD_HT1500to2000", "QCD_HT2000toInf", 
			       "Radion_m1200_13TeV", "Radion_m1600_13TeV"};


  string plotNames[nplots] = {"TotalMass", "PT0",  "PT1", "M0Pruned", "M1Pruned",  "ETA", "DeltaEta",  "nCSV_J0_SJ0", "nCSV_J0_SJ1", "nCSV_J1_SJ0", "nCSV_J1_SJ1", "nCSV", "TotalMass3btag"};


  TH1D* plots[ntrees][nplots];

  TCanvas* PT_HAT = new TCanvas();
  PT_HAT->SetBottomMargin(0.12);


  TH1D* PF_FF[nplots];

  TH1D* totalPlot[nplots];
  THStack* stacks[nplots]; 


  TLegend *leg = new TLegend(0.55,0.57,0.89,0.87);
  leg->SetTextSize(0.03546853);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  TLegend *leg2 = new TLegend(0.25,0.75,0.53,0.89);
  leg2->SetTextSize(0.03146853);
  leg2->SetLineColor(1);
  leg2->SetLineStyle(1);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetHeader("Signal");// for #Lambda = 1 TeV");

  TLegend *leg2Digamma = new TLegend(0.25,0.67,0.53,0.89);
  leg2Digamma->SetTextSize(0.03146853);
  leg2Digamma->SetLineColor(1);
  leg2Digamma->SetLineStyle(1);
  leg2Digamma->SetLineWidth(1);
  leg2Digamma->SetFillColor(0);
  leg2Digamma->SetHeader("Signal");

  TLegend *leg3 = new TLegend(0.60,0.58,0.89,0.87);
  leg3->SetTextSize(0.03546853);
  leg3->SetLineColor(1);
  leg3->SetLineStyle(1);
  leg3->SetLineWidth(1);
  leg3->SetFillColor(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("Signal shapes");



  TLegend *leg7 = new TLegend(0.60,0.65,0.89,0.89);
  leg7->SetTextSize(0.03146853);
  leg7->SetLineColor(1);
  leg7->SetLineStyle(1);
  leg7->SetLineWidth(1);
  leg7->SetFillColor(0);
  leg7->SetHeader("Smoothing");


  TPaveText *channel = new TPaveText(0.15,0.82,0.4,0.89, "brNDC");
  channel->SetBorderSize(0);
  channel->SetFillColor(0);
   //   pt->SetShadowColor(kWhite);
  channel->AddText("X #rightarrow HH #rightarrow #gamma#gammab#bar{b}");
  channel->SetTextSize(0.05);
  //  channel->SetTextColor(kBlue);

  TPaveText *channelData = new TPaveText(0.55,0.54,0.8,0.59, "brNDC");
  channelData->SetBorderSize(0);
  channelData->SetFillColor(0);
   //   pt->SetShadowColor(kWhite);
  channelData->AddText("X #rightarrow HH #rightarrow #gamma#gammab#bar{b}");
  channelData->SetTextSize(0.05);
  channelData->SetTextColor(kBlue);

  TPaveText *pt = new TPaveText(0.10,0.92,0.90,0.97, "brNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  pt->SetTextFont(42);
  pt->AddText("19.7 fb^{-1} (8 TeV)");
  pt->SetTextSize(0.04);
  pt->SetTextAlign(32);

  TPaveText *ptSim = new TPaveText(0.10,0.92,0.90,0.97, "brNDC");
  ptSim->SetBorderSize(0);
  ptSim->SetFillColor(0);
  ptSim->SetTextFont(42);
  ptSim->AddText("8 TeV");
  ptSim->SetTextSize(0.05);
  ptSim->SetTextAlign(32);

  TPaveText *ptCMS = new TPaveText(0.19,0.82,0.25,0.87, "brNDC");
  ptCMS->SetBorderSize(0);
  ptCMS->SetFillColor(0);
  ptCMS->AddText("CMS");
  ptCMS->SetTextFont(62);
  ptCMS->SetTextSize(0.05);
  ptCMS->SetTextAlign(32);

  TPaveText *ptCMS_SIM = new TPaveText(0.23,0.76,0.30,0.81, "brNDC");
  ptCMS_SIM->SetBorderSize(0);
  ptCMS_SIM->SetFillColor(0);
  ptCMS_SIM->AddText("Simulation");
  ptCMS_SIM->SetTextFont(62);
  ptCMS_SIM->SetTextSize(0.05);
  ptCMS_SIM->SetTextAlign(32);


  string fileName = directory +  "ControlPlotsSignal.root";
  TFile *file = new TFile(fileName.c_str(), "READ");
  //TFile *file = new TFile("ControlPlotsNoReg_X270.root", "READ");
  int iterator=0;

  for (int iTreeNames = 0; iTreeNames < ntrees; iTreeNames++){
    for (int iPlotNames = 0; iPlotNames < nplots; iPlotNames++){
      string sNames = plotNames[iPlotNames] + "_" + treeNames[iTreeNames] + ";1";
  
      //      cout << sNames.c_str() << endl;

      TH1D* plots[iTreeNames][iPlotNames] = (TH1D* ) file->Get(sNames.c_str());
  
      if (iTreeNames == 0)    {
	string stitle=plots[0][iPlotNames]->GetTitle();
	string xtitle = plots[0][iPlotNames]->GetXaxis()->GetTitle();
	string ytitle = plots[0][iPlotNames]->GetYaxis()->GetTitle();
	stitle = stitle + "; " + xtitle + "; " + ytitle;

	THStack* stacks[iPlotNames] = new THStack(plotNames[iPlotNames].c_str(), stitle.c_str());
	//	THStack* stacksNorm[iPlotNames] = new THStack(plotNames[iPlotNames].c_str(), stitle.c_str());

	TH1D* totalPlot[iPlotNames] = new TH1D();
	
	plots[iTreeNames][iPlotNames]->Copy(*totalPlot[iPlotNames]);

	totalPlot[iPlotNames]->Scale(0); 

	totalPlot[iPlotNames]->SetFillStyle(3004); totalPlot[iPlotNames]->SetFillColor(1);
      }
      
      plots[iTreeNames][iPlotNames]->SetFillColor(Color[iTreeNames]);
      if (plotNames[iPlotNames].find("TotalMass") != string::npos && iPlotNames < 10) {
	double nrec = plots[iTreeNames][iPlotNames]->Integral();
	cout << "name of sample is  " << treeNames[iTreeNames].c_str() << " norm = " << nrec << endl;
	//	cout << "error = " << sqrt(nrec*fabs(20000.-nrec))/sqrt(20000.) << endl;
	//	cout << "relative error = " << sqrt(nrec*fabs(20000.-nrec))/sqrt(20000.)/(nrec+1e-10) << endl;
	//	cout << "Total Number of entries = " << plots[iTreeNames][iPlotNames]->GetEntries() << endl;
      }

      plots[iTreeNames][iPlotNames]->Scale(scaleXsec[iTreeNames]);

      if (iTreeNames > -1) plots[iTreeNames][iPlotNames]->SetLineColor(Color[iTreeNames]);
      //     plots[iTreeNames][iPlotNames]->Sumw2();

      if (AddToStack[iTreeNames]) {
	stacks[iPlotNames]->Add(plots[iTreeNames][iPlotNames],"Hist");

	TH1D* scalePlot = new TH1D();
	plots[iTreeNames][iPlotNames]->Copy(*scalePlot);
	//	cout <<plotNames[iPlotNames] << " " << treeNames[iTreeNames] << endl; 
	for (int ibin = 1; ibin <= scalePlot->GetNbinsX(); ibin++){
	  	double error = scalePlot->GetBinError(ibin);
		error = sqrt(error*error + (Uncertainty[iTreeNames]-1)*scalePlot->GetBinContent(ibin)*(Uncertainty[iTreeNames]-1)*scalePlot->GetBinContent(ibin));
		scalePlot->SetBinError(ibin, 0);
	}

	totalPlot[iPlotNames]->Add(scalePlot);	
	
      }
      //      if (iTreeNames == 0) plots[iTreeNames][iPlotNames]->SetMarkerStyle(20);
      if (!AddToStack[iTreeNames]){// && iTreeNames > 0 ) {
	plots[iTreeNames][iPlotNames]->SetFillStyle(0);
	//	plots[iTreeNames][iPlotNames]->SetLineStyle(iTreeNames%4+2);
	plots[iTreeNames][iPlotNames]->SetLineWidth(3);
	if (iPlotNames == 0 &&  UsefulColor[iTreeNames]) {
	  string s_out(sTitle[iTreeNames].c_str());
	  //	  s_out = string("#sigma(") + s_out + ") x " + Form("%.0f", scaleXsec[iTreeNames]);
	  leg2->AddEntry(plots[iTreeNames][iPlotNames], s_out.c_str(),"l");
	  //	  string s_out(sTitle[iTreeNames].c_str());
	  //	  s_out = string("#sigma(") + s_out + ") x " + Form("%.0f", scaleXsec[iTreeNames]/ReajustScale);
	  //	  leg2Digamma->AddEntry(plots[iTreeNames][iPlotNames], s_out.c_str(),"l");
	}
	
      }


      //      if (iPlotNames == 0 && iTreeNames == 0) leg->AddEntry(plots[iTreeNames][iPlotNames], treeNames[iTreeNames].c_str(),"pl");
      //      else if (iPlotNames == 0 && iTreeNames > 0 && UsefulColor[iTreeNames] && AddToStack[iTreeNames]) leg->AddEntry(plots[iTreeNames][iPlotNames], sTitle[iTreeNames].c_str(),"f");
      if (iPlotNames == 0 && iTreeNames > 0 && UsefulColor[iTreeNames] && AddToStack[iTreeNames]) leg->AddEntry(plots[iTreeNames][iPlotNames], sTitle[iTreeNames].c_str(),"f");
       
   }
    
  }


  cout << "Initialization done" << endl;

  

  for (int iPlotNames = 0; iPlotNames < nplots; iPlotNames++){



    cout << "iPLotNames = " << iPlotNames << endl;
 
    




    


   cout << " ============= Signal only ============ " << endl;

   leg3->Clear();

   double max = totalPlot[iPlotNames]->GetMaximum();

   totalPlot[iPlotNames]->Draw();
   stacks[iPlotNames]->Draw("SAMEHIST");

   for (int iTreeNames = 1; iTreeNames < ntrees; iTreeNames++){
	
     if (!AddToStack[iTreeNames]) {
       if (max < plots[iTreeNames][iPlotNames]->GetMaximum()){
	 max = plots[iTreeNames][iPlotNames]->GetMaximum();
       }
       plots[iTreeNames][iPlotNames]->Draw("SAMEHIST");

     }

   }

    leg->Draw();
    leg2->Draw();
      
   totalPlot[iPlotNames]->SetMaximum(max*1.6);
   totalPlot[iPlotNames]->SetMinimum(0.7);
   PT_HAT->Update();
   
   string nameOut =  directory + "Plots/" + plotNames[iPlotNames] + ".png";
   PT_HAT->SaveAs(nameOut.c_str());
   
   string nameOut =  directory + "Plots/" + plotNames[iPlotNames] + ".pdf";
   PT_HAT->SaveAs(nameOut.c_str());


   PT_HAT->SetLogy(1);
   totalPlot[iPlotNames]->SetMaximum(totalPlot[iPlotNames]->GetMaximum()*3);
   PT_HAT->Update();

   string nameOut =  directory + "Plots/" + plotNames[iPlotNames] + "_log.png";
   PT_HAT->SaveAs(nameOut.c_str());
   
   string nameOut =  directory + "Plots/" + plotNames[iPlotNames] + "_log.pdf";
   PT_HAT->SaveAs(nameOut.c_str());

    
   PT_HAT->SetLogy(0);

    




  }

 

}

