/** \macro H2GGFitter.cc
 *
 * $Id: R2JJFitter.cc,v 1.14 2013/06/27 10:18:27 hinzmann Exp $
 *
 * Software developed for the CMS Detector at LHC
 *
 *
 *  \author Serguei Ganjour - CEA/IRFU/SPP, Saclay
 *  \modified by Maxime Gouzevitch for the Dijet Bump Search - IPNL, Lyon 
 *
 * Macro is implementing the unbinned maximum-likelihood model for 
 * the Higgs to gamma gamma analysis. PDF model and RooDataSets 
 * are stored in the workspace which is feeded to  HiggsAnalysis/CombinedLimit tools:
 * 
 * http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/HiggsAnalysis/CombinedLimit
 * http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/HiggsAnalysis/CombinedLimit/data/lhc-hcg/cms-jj-1fb/
 * 
 * The analysis root trees produced in a simple format 
 *
 *     TFile file(filename,"RECREATE", "X->jj input tree for unbinned maximum-likelihood fit");
 *     TTree* outTree  = new TTree("XTojj","X->jj input tree for unbinned maximum-likelihood fit");
 *     Float_t mass;
 *     Int_t CAT3;
 *     Float_t weight;
 *
 *     outTree->Branch("mass",&mass,"mass/F");
 *     outTree->Branch("weight",&weight,"weight/F");
 *     outTree->Branch("CAT4",&CAT4,"CAT4/I");
 *     {
 *       .............
 *       outTree->Fill();
 *     }
 *
 *     file.Write();
 *     file.Close();
 *     delete outTree;
 *
 * are used as input files. They have to be produced for 
 * data and Monte Carlo signal and background data sets 
 * after all analysis selections to be applied. It is recommended to put   
 * loose kinematical cuts on pt1 and pt2 (20 GeV) since further selections 
 * are possible based on RooDataSets. 
 * It is recommended to use Root 5.28/00 (CMSSW_4_1_3).
 *
 *
 */
// Loading:  .L H2GGFitter.cc
// Running:  runfits("jj120-shapes-combined-Unbinned.root")  
//                

/*
#include <cstring>
#include <cerrno>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <unistd.h>
#include <errno.h>
#include <iomanip>
// ROOT headers
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TIterator.h"

#include "TLatex.h"
#include "TString.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"

// RooFit headers
#include "RooAbsPdf.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooHistPdf.h"
#include "RooMsgService.h"
#include "RooNLLVar.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TStyle.h"

// RooStats headers
#include "RooStats/HLFactory.h"

#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAbsData.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooProduct.h"
#include "RooExtendPdf.h"
#include "RooBernstein.h"
#include "RooFitResult.h"
#include "RooMinimizer.h"
#include "RooCmdArg.h"
#include "RooConstVar.h"
#include "RooRealVar.h"
*/
//#include "HiggsCSandWidth.h"
//#include "HiggsCSandWidth.cc"
//#include "RooPower.h"

using namespace RooFit;
using namespace RooStats ;

static const Int_t NCAT = 3;
Double_t MMIN = 1000.;
Double_t MMAX = 3000;
std::string filePOSTfix="";
double analysisLumi = 2.1977; // Luminosity you use in your analysis
double nEventsInSignalMC = 0.; //number of events in Signal MC sample
int iGraviton = 0;

double signalScaler=0;//analysisLumi/nEventsInSignalMC; // assume signal cross section on 1/fb
double scaleFactorHP=1;// already done on 1 GeV Histo level
double scaleFactorLP=1;// already done on 1 GeV Histo level

void AddSigData(RooWorkspace*, Float_t, int, std::vector<string>);
void AddBkgData(RooWorkspace*, std::vector<string>);
void SigModelFit(RooWorkspace*, Float_t, TString signalname, std::vector<string>);
void BkgModelFit(RooWorkspace*, Bool_t, std::vector<string>, RooFitResult** fitresults);
void MakePlots(RooWorkspace*, Float_t, RooFitResult** , TString signalname, std::vector<string>);
void MakeSigWS(RooWorkspace* w, const char* filename, TString signalname, std::vector<string>);
void MakeBkgWS(RooWorkspace* w, const char* filename, std::vector<string>);
void SetConstantParams(const RooArgSet* params);
void MakeDataCard_1Channel(RooWorkspace* w, const char* fileBaseName, const char* fileBkgName, int iChan, TString signalname, int signalsample, std::vector<string> cat_names, double mass);
Double_t effSigma(TH1 *hist);

TString mainCut("1");

RooArgSet* defineVariables()
{
  // define variables of the input ntuple
  RooRealVar* mgg  = new RooRealVar("mgg","M(jet-jet)",MMIN,MMAX,"GeV");
  RooRealVar* evWeight   = new RooRealVar("evWeight","Reweightings",0.,10000.,"");
  RooRealVar* normWeight  = new RooRealVar("normWeight","Additionnal Weight",0.,10000000.,"");
  RooCategory* categories = new RooCategory("categories","event category 0") ;
  categories->defineType("4btag_cat0",0);
  categories->defineType("3btag_HPHP_cat1",1);
  categories->defineType("3btag_HPLP_cat2",2);
  RooArgSet* ntplVars = new RooArgSet(*mgg, *categories, *evWeight, *normWeight);
 
  return ntplVars;
}


void runfits(const Float_t mass=1600, int signalsample = 0, Bool_t dobands = false)
{

//******************************************************************//
//  Running mode  corresponds to the following cases
//         - full run set:
//         - create signal and background data sets 
//         - make and fit signal and background  models 
//         - write signal and background workspaces in root files
//         - write data card

//*******************************************************************//


  TString signalname;
  if (signalsample==0)
  { signalname="HH";
  }

  TString fileBaseName("CMS_jj_"+signalname+TString::Format("_%.0f_13TeV", mass));

  vector<string> cat_names;
  cat_names.push_back("CMS_jj_4btag_cat0");
  cat_names.push_back("CMS_jj_3btag_HPHP_cat1");
  cat_names.push_back("CMS_jj_3btag_HPLP_cat2");


  TString fileBkgName("CMS_jj_bkg_HH_13TeV");
  TString card_name("Xvv_reduced_models_Bkg_HH_13TeV.rs");
  HLFactory hlf("HLFactory", card_name, false);
  RooWorkspace* w = hlf.GetWs();
  RooFitResult* fitresults[NCAT];

  w->var("mgg")->setMin(MMIN);
  w->var("mgg")->setMax(MMAX);

// Add data to the workspace

  cout << "CREATE SIGNAL" << endl;
  
  AddSigData(w, mass, signalsample,cat_names);

  cout << "CREATE BACKGROUND" << endl;

  AddBkgData(w,cat_names);
  
// Add the signal and background models to the workspace.
// Inside this function you will find a discription our model.
// Fit data with models

  cout << "FIT SIGNAL" << endl;

  SigModelFit(w, mass, signalname, cat_names);
    
  cout << "FIT BACKGROUND" << endl;

  BkgModelFit(w, dobands,cat_names, fitresults);
      
// Make statistical treatment
// Setup the limit on Higgs production

  cout << "CREATE SIGNAL WS" << endl;
  
  MakeSigWS(w, fileBaseName, signalname,cat_names);

  cout << "CREATE BACKGROUND WS" << endl;
  
  MakeBkgWS(w, fileBkgName,cat_names);

  cout << "CREATE DATACARD" << endl;
  MakeDataCard_1Channel(w, fileBaseName, fileBkgName, 0, signalname, signalsample, cat_names, mass);
  MakeDataCard_1Channel(w, fileBaseName, fileBkgName, 1, signalname, signalsample, cat_names, mass);
  MakeDataCard_1Channel(w, fileBaseName, fileBkgName, 2, signalname, signalsample, cat_names, mass);

  cout << "MAKE PLOTS" << endl;
  
// Make plots for data and fit results
  MakePlots(w, mass, fitresults, signalname,cat_names);



    return;



}



void AddSigData(RooWorkspace* w, Float_t mass, int signalsample, std::vector<string> cat_names) {

  Int_t ncat = NCAT;
  TString inDir   = "./MiniTrees/Signal_HH_13TeV/";


//****************************//
// Signal Data Set
//****************************//

  // Variables
  RooArgSet* ntplVars = defineVariables();


//signal300_tree_radcut.root
  int iMass = abs(mass);       
  string signal(inDir.Data());
  signal = signal +"dijetHH_" + filePOSTfix + "" + string(Form("HHOUT%d_miniTree.root", iMass));
  
  cout << " ================================================================================= signal_c_str() = " << signal.c_str() << endl;

  TFile sigFile1(signal.c_str());

  TTree* sigTree1 = (TTree*) sigFile1.Get("TCVARS");

// common preselection cut

  sigTree1->Print();

//****************************//
// Signal  Data Set
//****************************//
// Create non scaled signal dataset composed with  different productions 
// according to their cross sections

  RooDataSet sigScaled("sigScaled","Signal",sigTree1,*ntplVars,mainCut, "normWeight");

  cout << "Print Signal Scaled" << endl;
  //  sigScaled.Print("v");

  RooDataSet* sigToFit[NCAT];
  for (int c = 0; c < ncat; ++c) {
    TString cut(TString::Format("categories==%d",c));
    TString name = TString::Format("Sig_%s",cat_names.at(c).c_str());

    sigToFit[c] =  (RooDataSet*) sigScaled.reduce(*w->var("mgg"),mainCut+TString::Format(" && categories==%d",c));
    w->import(*sigToFit[c],Rename(TString::Format("Sig_%s",cat_names.at(c).c_str())));
    cout << "Sum Entries = " << sigToFit[c]->sumEntries() << " isWeighted ? = " << sigToFit[c]->isWeighted() << endl;
    
  }

  cout << "End Making Sig Data" << endl;
          
}


void AddBkgData(RooWorkspace* w, std::vector<string> cat_names) {

  Int_t ncat = NCAT;
  TString inDir   = "./MiniTrees/Background_HH_13TeV/";

// common preselection cut


  Float_t minMassFit(MMIN),maxMassFit(MMAX); 


//****************************//
// CMS Data Set
//****************************//
// retrieve the data tree;
// no common preselection cut applied yet; 



  TString infile = inDir + "dijetHH_miniTree.root"; 
  if (filePOSTfix.find("subtr") != string::npos) 
    infile = inDir + "dijetHH_subtr_miniTree.root"; 

  TFile dataFile(infile.Data());

  TTree* dataTree     = (TTree*) dataFile.Get("TCVARS");

  // Variables
  RooArgSet* ntplVars = defineVariables();

  RooDataSet Data("Data","dataset",dataTree,*ntplVars,"","normWeight");

  
  RooDataSet* dataToFit[NCAT];
  for (int c = 0; c < ncat; ++c) {

    dataToFit[c] = (RooDataSet*) Data.reduce(*w->var("mgg"),mainCut+TString::Format(" && categories==%d",c));
    w->import(*dataToFit[c],Rename(TString::Format("Data_%s",cat_names.at(c).c_str())));

    cout << "Sum Entries data = " << dataToFit[c]->sumEntries() << " isWeighted ? = " << dataToFit[c]->isWeighted() << endl;
  }

// Create full data set without categorization
  RooDataSet* data    = (RooDataSet*) Data.reduce(*w->var("mgg"),mainCut);
  w->import(*data, Rename("Data"));
  data->Print("v");

}



void SigModelFit(RooWorkspace* w, Float_t mass, TString signalname, std::vector<string> cat_names) {

  Int_t ncat = NCAT;
  Float_t MASS(mass);

//******************************************//
// Fit signal with model pdfs
//******************************************//
// retrieve pdfs and datasets from workspace to fit with pdf models

  cout << "Fit signal" << endl;

  RooDataSet* sigToFit[NCAT];
  RooAbsPdf* jjSig[NCAT];

  Float_t minMassFit(MMIN),maxMassFit(MMAX); 


// Fit Signal 

  for (int c = 0; c < ncat; ++c) {
    cout << "---------- category = " << c << endl;
    sigToFit[c]   = (RooDataSet*) w->data(TString::Format("Sig_%s",cat_names.at(c).c_str()));
    jjSig[c]     = (RooAbsPdf*)  w->pdf(signalname+"_jj"+TString::Format("_%s",cat_names.at(c).c_str()));

    cerr << ("jj_"+signalname+TString::Format("_sig_m0_%s",cat_names.at(c).c_str())) << endl;
    ((RooRealVar*) w->var("jj_"+signalname+TString::Format("_sig_m0_%s",cat_names.at(c).c_str())))->setVal(MASS);
  
    cout << " Mass = " << MASS << endl;
      
    jjSig[c]     ->fitTo(*sigToFit[c],Range(mass*0.8,mass*1.3),SumW2Error(kTRUE),RooFit::PrintEvalErrors(-1));

    cout << " fitted " << endl;

// IMPORTANT: fix all pdf parameters to constant
    w->defineSet(TString::Format("SigPdfParam_%s",cat_names.at(c).c_str()), RooArgSet(*w->var("jj_"+signalname+TString::Format("_sig_m0_%s",cat_names.at(c).c_str())),
								   *w->var("jj_"+signalname+TString::Format("_sig_sigma_%s",cat_names.at(c).c_str())),
								   *w->var("jj_"+signalname+TString::Format("_sig_alpha_%s",cat_names.at(c).c_str())),
								   *w->var("jj_"+signalname+TString::Format("_sig_n_%s",cat_names.at(c).c_str())) 
										      //								   *w->var("jj_"+signalname+TString::Format("_sig_gsigma_%s",cat_names.at(c).c_str())),
										      //								   *w->var("jj_"+signalname+TString::Format("_sig_frac_%s",cat_names.at(c).c_str()))) 
										      ));

    cout << " defined " << endl;

    SetConstantParams(w->set(TString::Format("SigPdfParam_%s",cat_names.at(c).c_str())));
  }


}



void BkgModelFit(RooWorkspace* w, Bool_t dobands, std::vector<string> cat_names, RooFitResult** fitresult) {

  Int_t ncat = NCAT;

//******************************************//
// Fit background with model pdfs
//******************************************//

// retrieve pdfs and datasets from workspace to fit with pdf models

  cout << "Start background model fit" << endl;
  RooDataSet* data[NCAT];
  RooPlot* plotbkg_fit[NCAT];

// dobands and dosignal
  RooDataSet* signal[NCAT];
  RooAbsPdf*  jjSig[NCAT];


  Float_t minMassFit(MMIN),maxMassFit(MMAX); 

// Fit data with background pdf for data limit

  RooRealVar* mgg     = w->var("mgg");  
  mgg->setUnit("GeV");
  
  TLatex *text = new TLatex();
  text->SetNDC();
  text->SetTextSize(0.04);


  for (int c = 0; c < ncat; ++c) {
    data[c]   = (RooDataSet*) w->data(TString::Format("Data_%s",cat_names.at(c).c_str()));
                    
    RooFormulaVar *p1mod = new RooFormulaVar(TString::Format("p1mod_%s",cat_names.at(c).c_str()),"","@0",*w->var(TString::Format("bkg_fit_slope1_%s",cat_names.at(c).c_str())));
    RooFormulaVar *p1mod_clone = new RooFormulaVar(TString::Format("p1mod_%s",cat_names.at(c).c_str()),"","@0",*w->var(TString::Format("bkg_fit_slope1_clone_%s",cat_names.at(c).c_str())));
    RooFormulaVar *p2mod = new RooFormulaVar(TString::Format("p2mod_%s",cat_names.at(c).c_str()),"","@0",*w->var(TString::Format("bkg_fit_slope2_%s",cat_names.at(c).c_str())));
     


    RooFormulaVar *sqrtS = new RooFormulaVar(TString::Format("sqrtS_%s",cat_names.at(c).c_str()),"","@0",*w->var("sqrtS"));
    RooFormulaVar *x = new RooFormulaVar(TString::Format("x_%s",cat_names.at(c).c_str()),"","@0/@1",RooArgList(*mgg, *sqrtS));


    // EXO-12-053 1-parameter function
    RooAbsPdf* bkg_fitTmp_2par = new RooGenericPdf(TString::Format("bkg_fit_%s",cat_names.at(c).c_str()), "exp(@1*@0)", RooArgList(*x, *p1mod_clone));
    fitresult[c] = bkg_fitTmp_2par->fitTo(*data[c], Strategy(1),Minos(kFALSE), Range(minMassFit,maxMassFit),SumW2Error(kTRUE), Save(kTRUE),RooFit::PrintEvalErrors(-1));

    RooAbsPdf* bkg_fitTmp = new RooGenericPdf(TString::Format("bkg_fit_%s",cat_names.at(c).c_str()), "exp(@1*@0/(1+@1*@2*@0))", RooArgList(*x, *p1mod, *p2mod));

    bkg_fitTmp->fitTo(*data[c], Strategy(1),Minos(kFALSE), Range(minMassFit,maxMassFit),SumW2Error(kTRUE), Save(kTRUE),RooFit::PrintEvalErrors(-1));
 


    RooAbsReal* bkg_fitTmp2  = new RooRealVar(TString::Format("bkg_fit_%s_norm",cat_names.at(c).c_str()),"",4000.0,0.0,10000000);
    w->import(*bkg_fitTmp);
    w->import(*bkg_fitTmp2);


//************************************************//
// Plot jj background fit results per categories 
//************************************************//
// Plot Background Categories 
//****************************//

    TCanvas* ctmp = new TCanvas("ctmp","jj Background Categories",0,0,500,500);
    Int_t nBinsMass(40);
    plotbkg_fit[c] = mgg->frame(nBinsMass);
    plotbkg_fit[c]->SetTitle("");

    data[c]->plotOn(plotbkg_fit[c],LineColor(kWhite),MarkerColor(kWhite));    

    bkg_fitTmp_2par->plotOn(plotbkg_fit[c],LineColor(kBlue),Range("fitrange"),NormRange("fitrange"),RooFit::PrintEvalErrors(-1)); 
    bkg_fitTmp->plotOn(plotbkg_fit[c],LineColor(kRed),Range("fitrange"),NormRange("fitrange"),RooFit::PrintEvalErrors(-1)); 
    data[c]->plotOn(plotbkg_fit[c]);    

    plotbkg_fit[c]->Draw();  



    RooArgSet* set = new RooArgSet(*mgg);
    /*
    cout << " ================================ PRINTING ===================================" << endl;

  

      // ================================================================== data_obs_CMS
      //        cat_names.push_back("CMS_jj_4btag_cat0");

    data[c]->plotOn(plotbkg_fit[c],LineColor(kWhite),MarkerColor(kWhite));    

    bkg_fitTmp_2par->plotOn(plotbkg_fit[c],LineColor(kBlue),Range("fitrange"),NormRange("fitrange"),RooFit::PrintEvalErrors(-1)); 
    */

    double normalisation =  data[c]->sumEntries();
    const double alpha = 1 - 0.6827;

    double chi2 = 0, chi2_3par = 0;
    double rss0=0, rss_3par=0;
    for (int i = 0; i < (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->GetN() ; i++)
      {
	Double_t x0,y0;
	(plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->GetPoint(i, x0, y0);
	int N = y0;
	double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
	double U =  ROOT::Math::gamma_quantile_c(alpha/2,N+1,1);

	double xc, yc;
	double xlowErr = (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->GetErrorXlow(i);
	double xhighErr = (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->GetErrorXhigh(i);
	(plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->GetPoint(i, xc, yc);


	(plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->SetPointError(i, 0, 0, N-L, U-N);
	if (N==0)
	  {
	    (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->SetPoint(i, x0, 1.01e-1);
	    (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->SetPointError(i, 0, 0, N-L, U-N);
	  } else {
	  //            (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->SetPoint(i, x, 0.);
	}

	
	cout << "total integral = "  <<  data[c]->sumEntries();


	double xmin = xc-fabs(xlowErr), xmax = xc+fabs(xhighErr);
	
	mgg->setRange("A",xmin,xmax);

	RooAbsReal* intBin0 = bkg_fitTmp_2par->createIntegral(*set,*set,"A") ;

	RooAbsReal* intBin_3par = bkg_fitTmp->createIntegral(*set,*set,"A") ;
    
	double dintBin0 = intBin0->getVal();
	double dintBin_3par = intBin_3par->getVal();
	cout << "=================== Bin = " << i << " xmin = " << xmin << " xmax = " << xmax << " xlowErr = " << xlowErr << " xhighErr = " << xhighErr << " N-L = " << N-L << " U-N = " << U-N << " bin content = " << y0 << " intBin = " << dintBin0 << " unnormalised integral = " << dintBin0*normalisation << " yc = " << yc << endl;

	if (dintBin0*normalisation >= yc) chi2 += TMath::Power((dintBin0*normalisation - yc)/(U-N),2);
	else  chi2 += TMath::Power((dintBin0*normalisation - yc)/(N-L),2);

	if (dintBin_3par*normalisation >= yc) chi2_3par += TMath::Power((dintBin_3par*normalisation - yc)/(U-N),2);
	else  chi2_3par += TMath::Power((dintBin_3par*normalisation - yc)/(N-L),2);

	rss0 += TMath::Power((dintBin0*normalisation - yc),2);
	rss_3par += TMath::Power((dintBin_3par*normalisation - yc),2);

      }

    double p1_10 = 1;
    double p2_10 = (plotbkg_fit[c]->getHist(TString::Format("h_Data_%s",cat_names.at(c).c_str())))->GetN() - 3;
    double Ftest_10 = (rss0-rss_3par)/p1_10 / (rss_3par/p2_10);
    double good_CL23 =  1.-TMath::FDistI(Ftest_10,p1_10,p2_10);
    
    cout <<  " p1_10 = " << p1_10 << " p2_10 = " << p2_10 << " Ftest_23 = " << Ftest_10 << endl;

    cout << "chi2 = " << chi2 << endl;
    cout << "chi2_3par = " << chi2_3par << endl;
    cout << "F Test CL = " << good_CL23 << endl;


//********************************************************************************//

    if (dobands) {

      RooAbsPdf *cpdf; cpdf = bkg_fitTmp_2par;
      TGraphAsymmErrors *onesigma = new TGraphAsymmErrors();
      TGraphAsymmErrors *twosigma = new TGraphAsymmErrors();
      
      RooRealVar *nlim = new RooRealVar(TString::Format("nlim%d",c),"",0.0,0.0,10.0);
      nlim->removeRange();
      
      RooCurve *nomcurve = dynamic_cast<RooCurve*>(plotbkg_fit[c]->getObject(1));
      
      for (int i=1; i<(plotbkg_fit[c]->GetXaxis()->GetNbins()+1); ++i) {
	double lowedge = plotbkg_fit[c]->GetXaxis()->GetBinLowEdge(i);
	double upedge  = plotbkg_fit[c]->GetXaxis()->GetBinUpEdge(i);
	double center  = plotbkg_fit[c]->GetXaxis()->GetBinCenter(i);
	
	double nombkg = nomcurve->interpolate(center);
	nlim->setVal(nombkg);
	mgg->setRange("errRange",lowedge,upedge);
	RooAbsPdf *epdf = 0;
	epdf = new RooExtendPdf("epdf","",*cpdf,*nlim,"errRange");
	
	RooAbsReal *nll = epdf->createNLL(*(data[c]),Extended());
	RooMinimizer minim(*nll);
	minim.setStrategy(0);
	double clone = 1.0 - 2.0*RooStats::SignificanceToPValue(1.0);
	double cltwo = 1.0 - 2.0*RooStats::SignificanceToPValue(2.0);
	
	minim.migrad();
	minim.minos(*nlim);
	// printf("errlo = %5f, errhi = %5f\n",nlim->getErrorLo(),nlim->getErrorHi());
	
	onesigma->SetPoint(i-1,center,nombkg);
	if (fabs(nlim->getErrorLo())>1e-5) onesigma->SetPointError(i-1,0.,0.,-nlim->getErrorLo(),nlim->getErrorHi());
	else onesigma->SetPointError(i-1,0.,0.,nlim->getErrorHi(),nlim->getErrorHi());

	minim.setErrorLevel(0.5*pow(ROOT::Math::normal_quantile(1-0.5*(1-cltwo),1.0), 2)); // the 0.5 is because qmu is -2*NLL
	// eventually if cl = 0.95 this is the usual 1.92!      
	
	
	minim.migrad();
	minim.minos(*nlim);
	
	twosigma->SetPoint(i-1,center,nombkg);
	if (fabs(nlim->getErrorLo())>1e-5) twosigma->SetPointError(i-1,0.,0.,-nlim->getErrorLo(),nlim->getErrorHi());
	else twosigma->SetPointError(i-1,0.,0.,nlim->getErrorHi(),nlim->getErrorHi());
	
	
	delete nll;
	delete epdf;
	
      }
      mgg->setRange("errRange",minMassFit,maxMassFit);
      
      twosigma->SetLineColor(kYellow);
      twosigma->SetFillColor(kYellow);
      twosigma->SetMarkerColor(kYellow);
      twosigma->Draw("L3 SAME");
      
      onesigma->SetLineColor(kGreen);
      onesigma->SetFillColor(kGreen);
      onesigma->SetMarkerColor(kGreen);
      onesigma->Draw("L3 SAME");
      

      TLatex *lat  = new TLatex(MMIN+1000,10.,Form("#scale[1.0]{Exp. #chi^{2} = %.1f}",chi2));
      lat->SetTextSize(0.04);
      lat->Draw();
      TLatex *lat_3par  = new TLatex(MMIN+1000,6.,Form("#scale[1.0]{Lev. Exp. #chi^{2} = %.1f}",chi2_3par));
      lat_3par->SetTextSize(0.04);
      lat_3par->Draw();

      TLatex *lat_ftest  = new TLatex(MMIN+1000,20.,Form("#scale[1.0]{F Test 1 vs 2 par. CL = %.2f}",good_CL23));
      lat_ftest->SetTextSize(0.03);
      lat_ftest->Draw();

      plotbkg_fit[c]->SetTitle("");
      plotbkg_fit[c]->Draw("SAME"); 
      plotbkg_fit[c]->SetTitle("");      

      string out("plots/backgrounds");
      out = out + "" + filePOSTfix.c_str() + Form("_channel%d", c) + "_withband.pdf";
      ctmp->SaveAs(out.c_str());

      plotbkg_fit[c]->GetYaxis()->SetRangeUser(1.001e-1,500);

      ctmp->SetLogy();

      out = string("plots/backgrounds");
      out = out + "" + filePOSTfix.c_str() + Form("_channel%d", c) + "_withband_log.pdf";
      ctmp->SaveAs(out.c_str());

      out = string("plots/backgrounds");
      out = out + "" + filePOSTfix.c_str() + Form("_channel%d", c) + "_withband_parameters.root";


      TFile * output = new TFile(out.c_str(), "RECREATE");
      onesigma->Write("onesigma");
      twosigma->Write("twosigma");
      p1mod->Write();
      output->Close();
    }


  }


}


void SetConstantParams(const RooArgSet* params) {

  TIterator* iter(params->createIterator());
  for (TObject *a = iter->Next(); a != 0; a = iter->Next()) {
    RooRealVar *rrv = dynamic_cast<RooRealVar *>(a);
    if (rrv) { rrv->setConstant(true); std::cout << " " << rrv->GetName(); }
  }  

}

void MakePlots(RooWorkspace* w, Float_t mass, RooFitResult** fitresults, TString signalname, std::vector<string> cat_names) {

  cout << "Start plotting" << endl; 

  Int_t ncat = NCAT;

// retrieve data sets from the workspace
  RooDataSet* dataAll         = (RooDataSet*) w->data("Data");
  RooDataSet* signalAll       = (RooDataSet*) w->data("Sig");

  RooDataSet* data[9];  
  RooDataSet* signal[9];
  //  RooAbsPdf*  jjGaussSig[9];
  //  RooAbsPdf*  jjCBSig[9];
  RooAbsPdf*  jjSig[9];
  RooAbsPdf*  bkg_fit[9];  
//  RooAbsPdf*  bkg_fit2[9];  

  for (int c = 0; c < ncat; ++c) {
    data[c]         = (RooDataSet*) w->data(TString::Format("Data_%s",cat_names.at(c).c_str()));
//    signal[c]       = (RooDataSet*) w->data(TString::Format("Sig_%s",cat_names.at(c).c_str()));
    signal[c]       = (RooDataSet*) w->data(TString::Format("Sig_%s",cat_names.at(c).c_str()));
    //    jjGaussSig[c]  = (RooAbsPdf*)  w->pdf(TString::Format("jjGaussSig_%s",cat_names.at(c).c_str()));
    //    jjCBSig[c]     = (RooAbsPdf*)  w->pdf(TString::Format("jjCBSig_%s",cat_names.at(c).c_str()));
    jjSig[c]       = (RooAbsPdf*)  w->pdf(signalname+"_jj"+TString::Format("_%s",cat_names.at(c).c_str()));
    bkg_fit[c]       = (RooAbsPdf*)  w->pdf(TString::Format("bkg_fit_%s",cat_names.at(c).c_str()));
//    bkg_fit2[c]      = (RooAbsPdf*)  w->pdf(TString::Format("bkg_fit2_%s",cat_names.at(c).c_str()));
  }

// retrieve mass observable from the workspace
  RooRealVar* mgg     = w->var("mgg");  
  mgg->setUnit("GeV");

// retrieve pdfs after the fits
// Signal Model

//  RooAbsPdf* jjGaussSigAll  = w->pdf("jjGaussSig"+signalname);
//  RooAbsPdf* jjCBSigAll     = w->pdf("jjCBSig"+signalname);
  RooAbsPdf* jjSigAll       = w->pdf(signalname+"_jj");

//  RooAbsPdf* bkg_fitAll       = w->pdf("bkg_fit");
  RooAbsPdf* bkg_fitAll       = w->pdf("bkg_fitAll");
  
  cout << "Progress plotting 1" << endl;
 
//****************************//
// Plot jj Fit results
//****************************//


  Float_t minMassFit(MMIN),maxMassFit(MMAX); 
  Float_t MASS(mass);

  Int_t nBinsMass(100);



  cout << "Progress plotting 2" << endl;

//********************************************//
// Plot jj signal fit results per categories 
//********************************************//
// Plot Signal Categories 
//****************************//

  TLatex *text = new TLatex();
  text->SetNDC();
  text->SetTextSize(0.04);

//  TCanvas* c2 = new TCanvas("c2","jj Categories",0,0,1000,1000);

//  c2->Divide(3,3);
  RooPlot* plotjj[9];
  for (int c = 0; c < ncat; ++c) {
    plotjj[c] = mgg->frame(Range(minMassFit,maxMassFit),Bins(nBinsMass));
    signal[c]->plotOn(plotjj[c],LineColor(kWhite),MarkerColor(kWhite));    

    jjSig[c]  ->plotOn(plotjj[c]);
    //    jjSig[c]  ->plotOn(plotjj[c],Components("jjGaussSig"+signalname+TString::Format("_%s",cat_names.at(c).c_str())),LineStyle(kDashed),LineColor(kGreen),RooFit::PrintEvalErrors(-1));
    //   jjSig[c]  ->plotOn(plotjj[c],Components("jjCBSig"+signalname+TString::Format("_%s",cat_names.at(c).c_str())),LineStyle(kDashed),LineColor(kRed),RooFit::PrintEvalErrors(-1));
    

    //    jjSig[c]  ->paramOn(plotjj[c]);
    signal[c]  ->plotOn(plotjj[c]);

        
    TCanvas* dummy = new TCanvas(Form("dummy_%d",c), "dummy",0, 0, 400, 400);
    TH1F *hist = new TH1F(Form("hist_%d",c), "hist", 400, minMassFit, maxMassFit);
 
    plotjj[c]->SetTitle("");      
    plotjj[c]->SetMinimum(0.0);
    plotjj[c]->SetMaximum(1.40*plotjj[c]->GetMaximum());
    plotjj[c]->GetXaxis()->SetTitle("m_{jj} (GeV)");

    TCanvas* ctmp_sig = new TCanvas(Form("ctmp_sig_%d",c),"jj Background Categories",0,0,500,500);
    plotjj[c]->Draw();  
//    hist->Draw("same");
    plotjj[c]->Print();

    plotjj[c]->Draw("SAME");  
    TLegend *legmc = new TLegend(0.62,0.75,0.92,0.9);
    legmc->AddEntry(plotjj[c]->getObject(2),"Simulation","LPE");
    legmc->AddEntry(plotjj[c]->getObject(1),"Parametric Model","L");
    //    legmc->AddEntry(plotjj[c]->getObject(3),"Crystal Ball component","L");
    //    legmc->AddEntry(plotjj[c]->getObject(2),"Gaussian Outliers","L");
    
    legmc->SetBorderSize(0);
    legmc->SetFillStyle(0);
    legmc->Draw();    
    
    //    float effS = effSigma(hist);
//    text->DrawLatex(0.65,0.4, TString::Format("#sigma_{eff} = %.2f GeV",effS));
//    cout<<"effective sigma [" << c << "] = " << effS <<endl;

    TLatex *lat  = new TLatex(minMassFit+1.5,0.85*plotjj[c]->GetMaximum(),"#scale[1.0]{CMS Preliminary}");
    lat->Draw();
    //    TLatex *lat2 = new TLatex(minMassFit+1.5,0.75*plotjj[c]->GetMaximum(),cat_names.at(c).c_str());
    // lat2->Draw();
    //    TLatex *lat3 = new TLatex(minMassFit+1.5,0.55*plotjj[c]->GetMaximum(),TString::Format("#scale[0.8]{#sigma_{eff} = %.2f GeV}",effS));
    //    lat3->Draw();

    int iMass = abs(mass);

    //ctmp_sig->SaveAs("plots/sigmodel_"+signalname+TString::Format("%d_%s.png", iMass, cat_names.at(c).c_str()));
    string pdfout("plots/sigmodel_");
    cout << pdfout.c_str() << endl;
    pdfout = pdfout + "" + filePOSTfix.c_str() + "" + signalname.Data() + "" + Form("%d_%s.pdf", iMass, cat_names.at(c).c_str());
    cout << pdfout.c_str() << endl;

    string pngout("plots/sigmodel_");
    pngout = pngout + "" + filePOSTfix.c_str() + "" + signalname.Data() + "" + Form("%d_%s.pdf", iMass, cat_names.at(c).c_str());
    cout << pngout.c_str() << endl;

    ctmp_sig->SaveAs(pngout.c_str());
    ctmp_sig->SaveAs(pdfout.c_str());


  }


//************************************************//
// Plot jj background fit results per categories 
//************************************************//
// Plot Background Categories 
//****************************//

  TCanvas* c4 = new TCanvas("c4","jj Background Categories",0,0,1000,1000);
  c4->Divide(2,2);

  RooPlot* plotbkg_fit[9];
  for (int c = 0; c < ncat; ++c) {
    plotbkg_fit[c] = mgg->frame(Range(minMassFit,maxMassFit),Bins(nBinsMass));
    data[c]->plotOn(plotbkg_fit[c],LineColor(kWhite),MarkerColor(kWhite));    
    bkg_fit[c]->plotOn(plotbkg_fit[c],LineColor(kBlue),Range("fitrange"),NormRange("fitrange")); 
    data[c]->plotOn(plotbkg_fit[c]);    
    bkg_fit[c]->paramOn(plotbkg_fit[c], ShowConstants(true), Layout(0.4,0.9,0.9), Format("NEU",AutoPrecision(4)));
    plotbkg_fit[c]->getAttText()->SetTextSize(0.03);
    c4->cd(c+1);
    plotbkg_fit[c]->Draw();  
    gPad->SetLogy(1);
    plotbkg_fit[c]->SetAxisRange(0.1,plotbkg_fit[c]->GetMaximum()*1.5,"Y");
  }


 
  string out("plots/backgrounds");
  out = out + "" + filePOSTfix.c_str() + "_log.pdf";
  c4->SaveAs(out.c_str());

  out = string("plots/backgrounds");
  out = out + "" + filePOSTfix.c_str() + "_log.png";
  c4->SaveAs(out.c_str());



  TCanvas* c5 = new TCanvas("c5","jj Background Categories",0,0,1000,1000);
  c5->Divide(2,2);

  for (int c = 0; c < ncat; ++c) {
    plotbkg_fit[c] = mgg->frame(nBinsMass);
    data[c]->plotOn(plotbkg_fit[c],LineColor(kWhite),MarkerColor(kWhite));    
    bkg_fit[c]->plotOn(plotbkg_fit[c],LineColor(kBlue),Range("fitrange"),NormRange("fitrange")); 
    data[c]->plotOn(plotbkg_fit[c]);    
    bkg_fit[c]->paramOn(plotbkg_fit[c], ShowConstants(true), Layout(0.4,0.9,0.9), Format("NEU",AutoPrecision(4)));
    plotbkg_fit[c]->getAttText()->SetTextSize(0.03);
    c5->cd(c+1);
    plotbkg_fit[c]->Draw();  
  }

  out = string("plots/backgrounds");
  out = out + "" + filePOSTfix.c_str() + ".pdf";
  c5->SaveAs(out.c_str());

  out = string("plots/backgrounds");
  out = out + "" + filePOSTfix.c_str() + ".png";
  c5->SaveAs(out.c_str());
  



}


void MakeSigWS(RooWorkspace* w, const char* fileBaseName, TString signalname, std::vector<string> cat_names) {

  TString wsDir   = "workspaces/"+filePOSTfix;
  Int_t ncat = NCAT;


//********************************//
// Retrieve P.D.F.s
//********************************//

  RooAbsPdf* jjSigPdf[6];

// (1) import signal P.D.F.s

  RooWorkspace *wAll = new RooWorkspace("w_all","w_all");


  for (int c = 0; c < ncat; ++c) {
    jjSigPdf[c] = (RooAbsPdf*)  w->pdf(signalname+"_jj"+TString::Format("_%s",cat_names.at(c).c_str()));
    wAll->import(*w->pdf(signalname+"_jj"+TString::Format("_%s",cat_names.at(c).c_str())));
  }

// (2) Systematics on energy scale and resolution

  wAll->factory("CMS_sig_p1_jes[0.0,-5.0,5.0]");
  wAll->factory("CMS_jj_sig_p1_jes[0.012,0.012,0.012]");
  wAll->factory("sum::CMS_sig_p1_jes_sum(1.0,prod::CMS_sig_p1_jes_prod(CMS_sig_p1_jes, CMS_jj_sig_p1_jes))");
    for (int c = 0; c < ncat; ++c) {
      wAll->factory("prod::CMS_jj_"+signalname+"_sig_m0_"+TString::Format("%s",cat_names.at(c).c_str())+"(jj_"+signalname+"_sig_m0_"+TString::Format("%s",cat_names.at(c).c_str())+", CMS_sig_p1_jes_sum)");
    }

// (3) Systematics on resolution: create new sigmas

    // apply JER resolution smearing from 
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution#JER_Scaling_factors_and_Uncertai
    // Assume ~7% smearing +- 3% for each jet. Divide by sqrt(2) for both

  wAll->factory("CMS_sig_p2_jer[0.0,-5.0,5.0]");
  wAll->factory("CMS_jj_sig_p2_jer[0.02,0.02,0.02]");
  wAll->factory("sum::CMS_sig_p2_jer_sum(1.00,prod::CMS_sig_p2_jer_prod(CMS_sig_p2_jer, CMS_jj_sig_p2_jer))");

    for (int c = 0; c < ncat; ++c) {
      wAll->factory("prod::CMS_jj_"+signalname+"_sig_sigma_"+TString::Format("%s",cat_names.at(c).c_str())+"(jj_"+signalname+"_sig_sigma_"+TString::Format("%s",cat_names.at(c).c_str())+", CMS_sig_p2_jer_sum)");
    }

    //    for (int c = 0; c < ncat; ++c) {
    //wAll->factory("prod::CMS_jj_"+signalname+"_sig_gsigma_"+TString::Format("%s",cat_names.at(c).c_str())+"(jj_"+signalname+"_sig_gsigma_"+TString::Format("%s",cat_names.at(c).c_str())+", CMS_sig_p2_jer_sum)");
    //    }

// (4) do reparametrization of signal
  for (int c = 0; c < ncat; ++c) {
    wAll->factory(
		  "EDIT::"+signalname+"_jj"+TString::Format("_sig_%s(",cat_names.at(c).c_str())+signalname+"_jj"+TString::Format("_%s,",cat_names.at(c).c_str()) +
		  " jj_"+signalname+TString::Format("_sig_m0_%s=CMS_jj_",cat_names.at(c).c_str())+signalname+TString::Format("_sig_m0_%s, ", cat_names.at(c).c_str()) +
		  " jj_"+signalname+TString::Format("_sig_sigma_%s=CMS_jj_",cat_names.at(c).c_str())+signalname+TString::Format("_sig_sigma_%s)", cat_names.at(c).c_str()));
  }

  TString filename(wsDir+TString(fileBaseName)+".root");
  wAll->writeToFile(filename);
  cout << "Write signal workspace in: " << filename << " file" << endl;

  return;
}


void MakeBkgWS(RooWorkspace* w, const char* fileBaseName, std::vector<string> cat_names) {

  TString wsDir   = "workspaces/"+filePOSTfix;
  Int_t ncat = NCAT;  


//********************************//
// Retrieve the datasets and PDFs
//********************************//

  RooDataSet* data[NCAT];
  RooExtendPdf* bkg_fitPdf[NCAT];

// (1) import everything

  cout << "Start importing everything" << endl;

  RooWorkspace *wAll = new RooWorkspace("w_all","w_all");

  for (int c = 0; c < ncat; ++c) {
 
    cout << "For category " << c << endl;
    data[c]      = (RooDataSet*) w->data(TString::Format("Data_%s",cat_names.at(c).c_str()));
    ((RooRealVar*) data[c]->get()->find("mgg"))->setBins(MMAX-MMIN) ;
    RooDataHist* dataBinned = data[c]->binnedClone();
    bkg_fitPdf[c] = (RooExtendPdf*)  w->pdf(TString::Format("bkg_fit_%s",cat_names.at(c).c_str()));
    //   wAll->import(*data[c], Rename(TString::Format("data_obs_%s",cat_names.at(c).c_str())));
    wAll->import(*dataBinned, Rename(TString::Format("data_obs_%s",cat_names.at(c).c_str())));
   wAll->import(*w->pdf(TString::Format("bkg_fit_%s",cat_names.at(c).c_str())));
   wAll->import(*w->function(TString::Format("bkg_fit_%s_norm",cat_names.at(c).c_str())));

   double mean = (wAll->var(TString::Format("bkg_fit_%s_norm",cat_names.at(c).c_str())))->getVal();
   double min = (wAll->var(TString::Format("bkg_fit_%s_norm",cat_names.at(c).c_str())))->getMin();
   double max = (wAll->var(TString::Format("bkg_fit_%s_norm",cat_names.at(c).c_str())))->getMax();
   wAll->factory(TString::Format("CMS_bkg_fit_%s_norm[%g,%g,%g]", cat_names.at(c).c_str(), mean, min, max));

    mean = (wAll->var(TString::Format("bkg_fit_slope1_%s",cat_names.at(c).c_str())))->getVal();
    min = (wAll->var(TString::Format("bkg_fit_slope1_%s",cat_names.at(c).c_str())))->getMin();
    max = (wAll->var(TString::Format("bkg_fit_slope1_%s",cat_names.at(c).c_str())))->getMax();

   wAll->factory(TString::Format("CMS_bkg_fit_slope1_%s[%g,%g,%g]", cat_names.at(c).c_str(), mean, min, max));


    mean = (wAll->var(TString::Format("bkg_fit_slope2_%s",cat_names.at(c).c_str())))->getVal();
    min = (wAll->var(TString::Format("bkg_fit_slope2_%s",cat_names.at(c).c_str())))->getMin();
    max = (wAll->var(TString::Format("bkg_fit_slope2_%s",cat_names.at(c).c_str())))->getMax();

   wAll->factory(TString::Format("CMS_bkg_fit_slope2_%s[%g,%g,%g]", cat_names.at(c).c_str(), mean, min, max));
 
    cout << "Done For category " << c << endl;    
  }
  
  
  cout << "Imported" << endl;

// (2) do reparametrization of background

  for (int c = 0; c < ncat; ++c) {
    TString sFormat = 	    TString::Format("EDIT::CMS_bkg_fit_%s(bkg_fit_%s,",cat_names.at(c).c_str(),cat_names.at(c).c_str()) +
      TString::Format(" bkg_fit_%s_norm=CMS_bkg_fit_%s_norm,", cat_names.at(c).c_str(),cat_names.at(c).c_str())+
      TString::Format(" bkg_fit_slope1_%s=CMS_bkg_fit_slope1_%s,", cat_names.at(c).c_str(),cat_names.at(c).c_str())+
      TString::Format(" bkg_fit_slope2_%s=CMS_bkg_fit_slope2_%s)", cat_names.at(c).c_str(),cat_names.at(c).c_str());

    cout << sFormat.Data() << endl;

    wAll->factory(sFormat.Data());
  } 


  TString filename(wsDir+TString(fileBaseName)+".root");
  wAll->writeToFile(filename);
  cout << "Write background workspace in: " << filename << " file" << endl;

  std::cout << "observation ";
  for (int c = 0; c < ncat; ++c) {
    std::cout << "  " << (wAll->data(TString::Format("data_obs_%s",cat_names.at(c).c_str())))->sumEntries();
    (wAll->data(TString::Format("data_obs_%s",cat_names.at(c).c_str())))->Print();
  }
  std::cout << std::endl;
  
  for (int c = 0; c < ncat; ++c) {
    printf("CMS_bkg_fit_slope1_%s  param  %.4f  %.3f   # Mean and absolute uncertainty on background slope\n",
	   cat_names.at(c).c_str(), (wAll->var(TString::Format("CMS_bkg_fit_slope1_%s",cat_names.at(c).c_str())))->getVal(), 10.);
    printf("CMS_bkg_fit_slope2_%s  param  %.4f  %.3f   # Mean and absolute uncertainty on background slope\n",
	   cat_names.at(c).c_str(), (wAll->var(TString::Format("CMS_bkg_fit_slope2_%s",cat_names.at(c).c_str())))->getVal(), 10.);
  }

  cout << "BKG WS DONE" << endl;

  return;
}
























Double_t effSigma(TH1 *hist) {

  TAxis *xaxis = hist->GetXaxis();
  Int_t nb = xaxis->GetNbins();
  if(nb < 10) {
    std::cout << "effsigma: Not a valid histo. nbins = " << nb << std::endl;
    return 0.;
  }

  Double_t bwid = xaxis->GetBinWidth(1);
  if(bwid == 0) {
    std::cout << "effsigma: Not a valid histo. bwid = " << bwid << std::endl;
    return 0.;
  }
  Double_t xmax = xaxis->GetXmax();
  Double_t xmin = xaxis->GetXmin();
  Double_t ave = hist->GetMean();
  Double_t rms = hist->GetRMS();

  Double_t total=0.;
  for(Int_t i=0; i<nb+2; i++) {
    total+=hist->GetBinContent(i);
  }
  if(total < 100.) {
    std::cout << "effsigma: Too few entries " << total << std::endl;
    return 0.;
  }
  Int_t ierr=0;
  Int_t ismin=999;

  Double_t rlim=0.683*total;
  Int_t nrms=rms/(bwid);    // Set scan size to +/- rms
  if(nrms > nb/10) nrms=nb/10; // Could be tuned...

  Double_t widmin=9999999.;
  for(Int_t iscan=-nrms;iscan<nrms+1;iscan++) { // Scan window centre
    Int_t ibm=(ave-xmin)/bwid+1+iscan;
    Double_t x=(ibm-0.5)*bwid+xmin;
    Double_t xj=x;
    Double_t xk=x;
    Int_t jbm=ibm;
    Int_t kbm=ibm;
    Double_t bin=hist->GetBinContent(ibm);
    total=bin;
    for(Int_t j=1;j<nb;j++){
      if(jbm < nb) {
        jbm++;
        xj+=bwid;
        bin=hist->GetBinContent(jbm);
        total+=bin;
        if(total > rlim) break;
      }
      else ierr=1;
      if(kbm > 0) {
        kbm--;
        xk-=bwid;
        bin=hist->GetBinContent(kbm);
        total+=bin;
        if(total > rlim) break;
      }
      else ierr=1;
    }
    Double_t dxf=(total-rlim)*bwid/bin;
    Double_t wid=(xj-xk+bwid-dxf)*0.5;
    if(wid < widmin) {
      widmin=wid;
      ismin=iscan;
    }
  }
  if(ismin == nrms || ismin == -nrms) ierr=3;
  if(ierr != 0) std::cout << "effsigma: Error of type " << ierr << std::endl;

  return widmin;
}



void MakeDataCard_1Channel(RooWorkspace* w, const char* fileBaseName, const char* fileBkgName, int iChan, TString signalname, int signalsample, std::vector<string> cat_names, double mass) {

  TString cardDir = "datacards/"+filePOSTfix;
  Int_t ncat = NCAT;
  TString wsDir   = "../workspaces/"+filePOSTfix;
//**********************//
// Retrieve the datasets
//**********************//

  cout << "Start retrieving dataset" << endl;

  RooDataSet* data[NCAT];
  RooDataSet* signal[NCAT];
  for (int c = 0; c < NCAT; ++c) {
    data[c]        = (RooDataSet*) w->data(TString::Format("Data_%s",cat_names.at(c).c_str()));
    signal[c]      = (RooDataSet*) w->data(TString::Format("Sig_%s",cat_names.at(c).c_str()));
  }

//*****************************//
// Print Expected event yields
//*****************************//

  cout << "======== Expected Events Number =====================" << endl;  
  cout << "#Events data:        " <<  w->data("Data")->sumEntries()  << endl;
  for (int c = 0; c < ncat; ++c) {
    cout << TString::Format("#Events data %s:   ",cat_names.at(c).c_str()) << data[c]->sumEntries()  << endl;
  }
  cout << ".........Expected Signal ............................" << endl;  
  Float_t siglikeErr[NCAT];
  for (int c = 0; c < ncat; ++c) {
    cout << TString::Format("#Events Signal %s: ",cat_names.at(c).c_str()) << signal[c]->sumEntries() << endl;
    siglikeErr[c]=0.6*signal[c]->sumEntries();
  }
  cout << "====================================================" << endl;  

//*************************//
// Print Data Crd int file
//*************************//


  TString filename(cardDir+TString(fileBaseName)+Form("_%s.txt",cat_names[iChan].c_str()));
  ofstream outFile(filename);

  cout << "================================================================ signalScaler = " << signalScaler << endl;

  double scaleFactor=signalScaler;
  // Pythia HP+HP
  //if(((signalsample==0))&&(iChan==0))
  //    scaleFactor*=(scaleFactorHP*scaleFactorHP);
  // Pythia HP+LP
  //if(((signalsample==0))&&(iChan==1))
  //    scaleFactor*=(scaleFactorHP*scaleFactorLP);

  outFile << "# Fully Hadronic HH analysis" << endl;
  outFile << "imax 1" << endl;
  outFile << "kmax *" << endl;
  outFile << "---------------" << endl;

  outFile << Form("shapes data_obs %s ", cat_names[iChan].c_str()) << wsDir+TString(fileBkgName)+".root" << Form(" w_all:data_obs_%s", cat_names[iChan].c_str()) << endl;
  outFile << Form("shapes bkg_fit_jj %s ", cat_names[iChan].c_str()) <<  wsDir+TString(fileBkgName)+".root" << Form(" w_all:CMS_bkg_fit_%s", cat_names[iChan].c_str()) << endl;
  outFile << Form("shapes HH_jj %s ", cat_names[iChan].c_str()) << wsDir+TString::Format("CMS_jj_HH_%.0f_13TeV.root", mass) << Form(" w_all:HH_jj_sig_%s", cat_names[iChan].c_str()) << endl;
  outFile << "---------------" << endl;
  outFile << Form("bin          %s", cat_names[iChan].c_str()) << endl;
  outFile <<  "observation   "  <<  Form("%.10lg",data[iChan]->sumEntries()) << endl;
  outFile << "------------------------------" << endl;

  outFile << "bin                      "<< Form("%s       %s      ", cat_names[iChan].c_str(), cat_names[iChan].c_str()) << endl;
  outFile << "process                 HH_jj     bkg_fit_jj     " << endl;
  outFile << "process                 0        1          " << endl;
  if(signalname=="HH")
      outFile <<  "rate                      " 
	  << " " << signal[iChan]->sumEntries()*scaleFactor << " " << 1 << endl;
  outFile << "--------------------------------" << endl;
  outFile << "# signal scaled by " << signalScaler << " to a cross section of 10/fb and also scale factor of " << scaleFactor/signalScaler << " are applied." << endl;
  
  outFile << "CMS_lumi_8TeV       lnN  1.046      - " << endl;
  outFile << "CMS_pu              lnN  1.020      - # pileup impact of W mass tag" << endl;
  outFile << "CMS_eff_Htag_unc    lnN  1.02       - # JEs and JER uncertainty on H mass tag" << endl;
  outFile << "CMS_eff_Htag_sf     lnN  1.10       - # differenec between H tag and W tag efficiencies" << endl;
  outFile << "CMS_PDF_Scales      lnN  1.02       - # selection efficiency" << endl;
  if(iChan==0)
    outFile << "CMS_eff_btagsf    lnN  1.17       - # btag efficiency" << endl;
  else if (iChan == 1 || iChan == 2)
    outFile << "CMS_eff_btagsf    lnN  0.95       - # btag efficiency" << endl;
    
  if (iChan < 2)
    outFile << "CMS_eff_tau21     lnN  1.27/0.76       - # tau21 efficiency" << endl;
  else if(iChan == 2)
    outFile << "CMS_eff_tau21     lnN  0.38/1.75       - # tau21 efficiency" << endl;

  // HPHP 3btag: ((1.03+0.13)^2 - (1.03)^2) / 1.03^2 :  1.27/0.76
  // HPLP 3btag: ((1.03+0.13)(0.88+0.49) - (1.03)*0.88) / 1.03*0.88 :  1.75/0.38


  /*  
  if((iChan==0)||(iChan==3)){
  outFile << "CMS_eff_vtag_tau21_sf         lnN  1.15       - # tau21 efficiency" << endl;
  } else {
  // anti-correlated the high purity (1.076*1.076) and low purity (0.54*1.076) categories
  outFile << "CMS_eff_vtag_tau21_sf         lnN  0.58      - # tau21 efficiency" << endl;
  }
  */
  //  outFile << "CMS_scale_j         lnN  1.120 	   - # jet energy scale" << endl;
  //  outFile << "CMS_res_j         lnN  1.040	- # jet energy resolution" << endl;


  outFile << "# Parametric shape uncertainties, entered by hand." << endl;
  outFile << Form("CMS_sig_p1_jes    param   0.0   1.0   # dijet mass shift due to JES uncertainty") << endl;
  outFile << Form("CMS_sig_p2_jer     param   0.0   1.0   # dijet mass resolution shift due to JER uncertainty") << endl;
 
  outFile << Form("CMS_bkg_fit_%s_norm           flatParam  # Normalization uncertainty on background slope",cat_names[iChan].c_str()) << endl;

  outFile << Form("CMS_bkg_fit_slope1_%s         flatParam  # Mean and absolute uncertainty on background slope",cat_names[iChan].c_str()) << endl;

  outFile << Form("CMS_bkg_fit_slope2_%s         flatParam  # Mean and absolute uncertainty on background levelled parameter",cat_names[iChan].c_str()) << endl;

  outFile.close();

  cout << "Write data card in: " << filename << " file" << endl;

  return;
}

void style(){
  TStyle *defaultStyle = new TStyle("defaultStyle","Default Style");
  defaultStyle->SetOptStat(0000);
  defaultStyle->SetOptFit(000); 
  defaultStyle->SetPalette(1);
  /////// pad ////////////
  defaultStyle->SetPadBorderMode(1);
  defaultStyle->SetPadBorderSize(1);
  defaultStyle->SetPadColor(0);
  defaultStyle->SetPadTopMargin(0.05);
  defaultStyle->SetPadBottomMargin(0.13);
  defaultStyle->SetPadLeftMargin(0.15);
  defaultStyle->SetPadRightMargin(0.04);
  /////// canvas /////////
  defaultStyle->SetCanvasBorderMode(0);
  defaultStyle->SetCanvasColor(0);
  defaultStyle->SetCanvasDefH(600);
  defaultStyle->SetCanvasDefW(600);
  /////// frame //////////
  defaultStyle->SetFrameBorderMode(0);
  defaultStyle->SetFrameBorderSize(1);
  defaultStyle->SetFrameFillColor(0); 
  defaultStyle->SetFrameLineColor(1);
  /////// label //////////
  defaultStyle->SetLabelOffset(0.005,"XY");
  defaultStyle->SetLabelSize(0.05,"XY");
  defaultStyle->SetLabelFont(42,"XY");
  /////// title //////////
  defaultStyle->SetTitleOffset(1.1,"X");
  defaultStyle->SetTitleSize(0.01,"X");
  defaultStyle->SetTitleOffset(1.10,"Y");
  defaultStyle->SetTitleSize(0.05,"Y");
  defaultStyle->SetTitleFont(42, "XYZ");
  /////// various ////////
  // defaultStyle->SetNdivisions(505,"Y");
  defaultStyle->SetLegendBorderSize(0); // For the axis titles:

  defaultStyle->SetTitleColor(1, "XYZ");
  defaultStyle->SetTitleFont(42, "XYZ");
  defaultStyle->SetTitleSize(0.06, "XYZ");
  defaultStyle->SetTitleXOffset(0.9);
  defaultStyle->SetTitleYOffset(1.05);
  
  // For the axis labels:
  defaultStyle->SetLabelColor(1, "XYZ");
  defaultStyle->SetLabelFont(42, "XYZ");
  defaultStyle->SetLabelOffset(0.007, "XYZ");
  defaultStyle->SetLabelSize(0.04, "XYZ");

  // For the axis:
    defaultStyle->SetAxisColor(1, "XYZ");
    defaultStyle->SetStripDecimals(kTRUE);
    defaultStyle->SetTickLength(0.03, "XYZ");
    defaultStyle->SetNdivisions(310, "XYZ");
    defaultStyle->SetPadTickX(1);
    defaultStyle->SetPadTickY(1);
    defaultStyle->cd();
  return;
}


void R2JJFitterHH_13TeV(double mass, std::string postfix="", bool dobands=false, int graviton = 0, double nEvents = 50000.)
{
    filePOSTfix=postfix;
    iGraviton = graviton;
    nEventsInSignalMC = nEvents;
    signalScaler=analysisLumi/nEventsInSignalMC;
    style();
    runfits(mass, 0, dobands);

}
