
import os

masses =[1600]
ievts =[0,2,5,10,20]

start = -1
itoys = 250


for mass in masses:
 for ievt in ievts:  
   start=start+1
   outputname = "bias_HH_Graviton_"+str(mass)+"_"+str(ievt)+".src"
   logname = "bias_HH_Graviton_"+str(mass)+"_"+str(ievt)+".log"
   outputfile = open(outputname,'w')
   outputfile.write('#!/bin/bash\n')
   outputfile.write("cd ${CMSSW_BASE}/src/HH4b/BumpSearchLimitCode; eval `scramv1 run -sh`\n")

   if start == 0:
     outputfile.write("root -b -q 'WSMakerForToys.C'\n")

   outputfile.write("combine datacards/toys_"+str(mass)+".txt -M GenerateOnly --setPhysicsModelParameters pdf_index=0 --freezeNuisances pdf_index --toysFrequentist -t "+str(itoys)+" --expectSignal " + str(ievt) + " --saveToys -m "+str(mass)+" \n")
   outputfile.write("mv higgsCombineTest.GenerateOnly.mH"+str(mass)+".123456.root toys/higgsCombineTest.GenerateOnly.mH"+str(mass)+"_mu"+str(ievt)+".123456.root\n")
   outputfile.write("combine datacards/toys_"+str(mass)+".txt -M MaxLikelihoodFit --toysFile toys/higgsCombineTest.GenerateOnly.mH"+str(mass)+"_mu"+str(ievt)+".123456.root -t "+str(itoys)+" --rMin -80 --rMax 80 --setPhysicsModelParameters pdf_index=0 --freezeNuisances pdf_index\n");
   
   outputfile.write("mv mlfit.root toys/mlfit_"+str(mass)+"_mu"+str(ievt)+".root\n")
   outputfile.write("root -b -q 'BiasStudies.C("+str(mass)+", "+str(ievt)+")'\n")  
   outputfile.close()
   
   command="rm "+logname
   print command
   os.system(command)
  #command="bsub -q 1nh -o "+logname+" source "+outputname
   command="chmod 755 ./"+outputname+";./"+outputname
   print command
   os.system(command)
   
