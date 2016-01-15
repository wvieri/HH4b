import os

masses =[1200,1400,1600,1800,2000,2500]


for mass in masses:
  outputname = "submit_HH_"+str(mass)+".src"
  logname = "submit_HH_"+str(mass)+".log"
  outputfile = open(outputname,'w')
  outputfile.write('#!/bin/bash\n')
  outputfile.write("cd ${CMSSW_BASE}/src/HH4b/BumpSearchLimitCode; eval `scramv1 run -sh`\n")
  outputfile.write("root -b -q 'R2JJFitterHH_13TeV.cc("+str(mass)+","+'""'+",0)'\n")
  outputfile.write("combineCards.py datacards/CMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_3btag_cat1.txt datacards/CMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_4btag_cat0.txt &>datacards/CMS_jj_HH_"+str(mass)+"_13TeV_CMS_jj_2cat.txt")

  outputfile.close()
  
  command="rm "+logname
  print command
  os.system(command)
  #command="bsub -q 1nh -o "+logname+" source "+outputname
  command="chmod 755 ./"+outputname+";./"+outputname
  print command
  os.system(command)
