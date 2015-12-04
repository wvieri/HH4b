mgg[890,2500];

jj_HH_sig_m0[2000.0, 900.0, 3100.0];
jj_HH_sig_sigma[100, 50.0, 1000.0];
jj_HH_sig_alpha[0.8, 0.5, 3]; 
jj_HH_sig_n[13.0, 0.5, 10]; 
jj_HH_sig_gsigma[100, 50.0, 1000.0];
jj_HH_sig_frac[0.5, 0.3, 1.0];

jjGaussSigHH = Gaussian(mgg, jj_HH_sig_m0, jj_HH_sig_gsigma);
jjCBSigHH    = CBShape(mgg, jj_HH_sig_m0, jj_HH_sig_sigma, jj_HH_sig_alpha, jj_HH_sig_n);
HH_jj      = AddPdf(jjGaussSigHH, jjCBSigHH, jj_HH_sig_frac);

jj_HH_sig_m0_CMS_jj_4btag_cat0[2000.0, 900.0, 3100.0];
jj_HH_sig_sigma_CMS_jj_4btag_cat0[100, 50.0, 1000.0];
jj_HH_sig_alpha_CMS_jj_4btag_cat0[ 0.8, 0.0, 3.0]; 
jj_HH_sig_n_CMS_jj_4btag_cat0[130, 0.00001, 1000.0]; 
jj_HH_sig_gsigma_CMS_jj_4btag_cat0[100, 50.0, 1000.0];
jj_HH_sig_frac_CMS_jj_4btag_cat0[0.5, 0.3, 1.0];


jjGaussSigHH_CMS_jj_4btag_cat0 = Gaussian(mgg, jj_HH_sig_m0_CMS_jj_4btag_cat0, jj_HH_sig_gsigma_CMS_jj_4btag_cat0);
jjCBSigHH_CMS_jj_4btag_cat0    = CBShape(mgg, jj_HH_sig_m0_CMS_jj_4btag_cat0, jj_HH_sig_sigma_CMS_jj_4btag_cat0, jj_HH_sig_alpha_CMS_jj_4btag_cat0, jj_HH_sig_n_CMS_jj_4btag_cat0);
HH_jj_CMS_jj_4btag_cat0      = AddPdf(jjGaussSigHH_CMS_jj_4btag_cat0, jjCBSigHH_CMS_jj_4btag_cat0, jj_HH_sig_frac_CMS_jj_4btag_cat0);



bkg_fit_slope_CMS_jj_4btag_cat0[1000.0,0, 10000000];
bkg_fit_slope1_CMS_jj_4btag_cat0[10., -100.0, 500.0];




jj_HH_sig_m0_CMS_jj_3btag_cat1[2000.0, 900.0, 3100.0];
jj_HH_sig_sigma_CMS_jj_3btag_cat1[100, 50.0, 1000.0];
jj_HH_sig_alpha_CMS_jj_3btag_cat1[ 0.8, 0.0, 3.0]; 
jj_HH_sig_n_CMS_jj_3btag_cat1[130, 0.00001, 1000.0]; 
jj_HH_sig_gsigma_CMS_jj_3btag_cat1[100, 50.0, 1000.0];
jj_HH_sig_frac_CMS_jj_3btag_cat1[0.5, 0.3, 1.0];


jjGaussSigHH_CMS_jj_3btag_cat1 = Gaussian(mgg, jj_HH_sig_m0_CMS_jj_3btag_cat1, jj_HH_sig_gsigma_CMS_jj_3btag_cat1);
jjCBSigHH_CMS_jj_3btag_cat1    = CBShape(mgg, jj_HH_sig_m0_CMS_jj_3btag_cat1, jj_HH_sig_sigma_CMS_jj_3btag_cat1, jj_HH_sig_alpha_CMS_jj_3btag_cat1, jj_HH_sig_n_CMS_jj_3btag_cat1);
HH_jj_CMS_jj_3btag_cat1      = AddPdf(jjGaussSigHH_CMS_jj_3btag_cat1, jjCBSigHH_CMS_jj_3btag_cat1, jj_HH_sig_frac_CMS_jj_3btag_cat1);



bkg_fit_slope_CMS_jj_3btag_cat1[1000.0,0, 10000000];
bkg_fit_slope1_CMS_jj_3btag_cat1[10., -100.0, 500.0];




wei[1,0,10];

sqrtS[8000., 8000., 8000.]
