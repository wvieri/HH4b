import os

masses =[1200,1400,1600,1800,2000,2500]


for mass in masses:
  outputname = "submit_HH_Radion_"+str(mass)+".src"
  logname = "submit_HH_Radion_"+str(mass)+".log"
  outputfile = open(outputname,'w')
  outputfile.write('#!/bin/bash\n')
  outputfile.write("cd ${CMSSW_BASE}/src/HH4b/BumpSearchLimitCode; eval `scramv1 run -sh`\n")
  outputfile.write("root -b -q 'R2JJFitterHH_13TeV.cc("+str(mass)+","+'"Radion"'+",0,0,50000.)'\n")
  outputfile.write("combineCards.py datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_HPHP_cat1.txt datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_4btag_cat0.txt &>datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_2cat.txt\n")
  outputfile.write("combine datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_2cat.txt -M Asymptotic  -n Radion -m "+str(mass)+"\n")
#  outputfile.write("combine datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_HPLP_cat2.txt -M Asymptotic -n Radion_3btag_HPLP_cat2 -m "+str(mass)+"\n")
  outputfile.write("combine datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_HPHP_cat1.txt -M Asymptotic -n Radion_3btag_HPHP_cat1  -m "+str(mass)+"\n")
  outputfile.write("combine datacards/RadionCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_4btag_cat0.txt -M Asymptotic -n Radion_4btag_cat0 -m "+str(mass)+"\n")

  outputfile.write("mv higgsCombineRadion.Asymptotic.mH"+str(mass)+".root LimitOutput\n")
#  outputfile.write("mv higgsCombineRadion_3btag_HPLP_cat2.Asymptotic.mH"+str(mass)+".root LimitOutput\n") 
  outputfile.write("mv higgsCombineRadion_3btag_HPHP_cat1.Asymptotic.mH"+str(mass)+".root LimitOutput\n") 
  outputfile.write("mv higgsCombineRadion_4btag_cat0.Asymptotic.mH"+str(mass)+".root LimitOutput\n")

  outputfile.close()
  
  command="rm "+logname
  print command
  os.system(command)
  #command="bsub -q 1nh -o "+logname+" source "+outputname
  command="chmod 755 ./"+outputname+";./"+outputname
  print command
  os.system(command)


#masses =[1200,1400,1600,1800,2000,2500]


for mass in masses:
  outputname = "submit_HH_Graviton_"+str(mass)+".src"
  logname = "submit_HH_Graviton_"+str(mass)+".log"
  outputfile = open(outputname,'w')
  outputfile.write('#!/bin/bash\n')
  outputfile.write("cd ${CMSSW_BASE}/src/HH4b/BumpSearchLimitCode; eval `scramv1 run -sh`\n")
  if mass == 1800:
    outputfile.write("root -b -q 'R2JJFitterHH_13TeV.cc("+str(mass)+","+'"Graviton"'+",0,1,48400.)'\n")
  else:
    outputfile.write("root -b -q 'R2JJFitterHH_13TeV.cc("+str(mass)+","+'"Graviton"'+",0,1,50000.)'\n")
  outputfile.write("combineCards.py datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_HPHP_cat1.txt datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_4btag_cat0.txt &>datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_2cat.txt\n")

  outputfile.write("combine datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_2cat.txt -M Asymptotic  -n Graviton -m "+str(mass)+"\n")
#  outputfile.write("combine datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_HPLP_cat2.txt -M Asymptotic -n Graviton_3btag_HPLP_cat2 -m "+str(mass)+"\n")
  outputfile.write("combine datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_HPHP_cat1.txt -M Asymptotic -n Graviton_3btag_HPHP_cat1  -m "+str(mass)+"\n")
  outputfile.write("combine datacards/GravitonCMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_4btag_cat0.txt -M Asymptotic -n Graviton_4btag_cat0 -m "+str(mass)+"\n")


  outputfile.write("mv higgsCombineGraviton.Asymptotic.mH"+str(mass)+".root LimitOutput\n")
#  outputfile.write("mv higgsCombineGraviton_3btag_HPLP_cat2.Asymptotic.mH"+str(mass)+".root LimitOutput\n") 
  outputfile.write("mv higgsCombineGraviton_3btag_HPHP_cat1.Asymptotic.mH"+str(mass)+".root LimitOutput\n") 
  outputfile.write("mv higgsCombineGraviton_4btag_cat0.Asymptotic.mH"+str(mass)+".root LimitOutput\n")

  outputfile.close()
  
  command="rm "+logname
  print command
  os.system(command)
  #command="bsub -q 1nh -o "+logname+" source "+outputname
  command="chmod 755 ./"+outputname+";./"+outputname
  print command
  os.system(command)
