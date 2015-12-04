# HH4b
Follow this recipe:
https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideHiggsAnalysisCombinedLimit#ROOT6_SLC6_release_CMSSW_7_4_X

then checkout this directory
cd HH4b/BumpSearchLimitCode
cmsenv
python ProduceWorkspacesHH_13TeV.py

creates bunch of datacards in datacards
and workspaces quite a few workspaces

normally you can then simply run

combine datacards/CMS_jj_HH_2000_13TeV_CMS_jj_4btag_cat0.txt -M Asymptotic

And obtain a limit in units of 10 fb. So if you have a limit of 5 it means 50 fb.
The datacard for the moment is simply based on 4btag category. A bit of work would be required to add both categories.
One need to write properly th function MakeDataCard_1Channel in
R2JJFitterHH_13TeV.cc

The Signal trees are located in MiniTrees/Signal_HH and background (QCD MC) in MiniTrees/Background_HH_13TeV.

