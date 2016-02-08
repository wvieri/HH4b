
import os

masses =[1200]


for mass in masses:
  outputname = "submit_HH_Graviton_"+str(mass)+".src"
  logname = "submit_HH_Graviton_"+str(mass)+".log"
  outputfile = open(outputname,'w')
  outputfile.write('#!/bin/bash\n')
  outputfile.write("cd ${CMSSW_BASE}/src/HH4b/BumpSearchLimitCode; eval `scramv1 run -sh`\n")

  outputfile.write("root -b -q 'R2JJFitterHH_13TeV.cc("+str(mass)+","+'"Graviton"'+",true,1,50000.)'\n")


  outputfile.close()
  
  command="rm "+logname
  print command
  os.system(command)
  #command="bsub -q 1nh -o "+logname+" source "+outputname
  command="chmod 755 ./"+outputname+";./"+outputname
  print command
  os.system(command)


for mass in masses:
  outputname = "submit_HH_Graviton_"+str(mass)+".src"
  logname = "submit_HH_Graviton_"+str(mass)+".log"
  outputfile = open(outputname,'w')
  outputfile.write('#!/bin/bash\n')
  outputfile.write("cd ${CMSSW_BASE}/src/HH4b/BumpSearchLimitCode; eval `scramv1 run -sh`\n")
  outputfile.write("root -b -q 'R2JJFitterHH_13TeV.cc("+str(mass)+","+'"Graviton_subtr"'+",true,1,50000.)'\n")
  outputfile.close()
  
  command="rm "+logname
  print command
  os.system(command)
  #command="bsub -q 1nh -o "+logname+" source "+outputname
  command="chmod 755 ./"+outputname+";./"+outputname
  print command
  os.system(command)
