from ROOT import *
import ROOT
import array, math
import os

masses =[m*100 for m in range(6,40+1)]

print "8 TeV"
xsec_x_WW=[1000,1500,1800,2000,2500,3000]
xsec_y_WW=[log(4.254E-01),log(3.298E-02),log(9.056E-03),log(4.083E-03),log(6.191E-04),log(1.010E-04)]
xsec_x_ZZ=[1000,1500,1800,2000,3000]
xsec_y_ZZ=[log(2.137E-01),log(1.662E-02),log(4.559E-03),log(2.027E-03),log(5.099E-05)]
xsec_x_array_WW=array.array('d')
xsec_y_array_WW=array.array('d')
xsec_x_array_ZZ=array.array('d')
xsec_y_array_ZZ=array.array('d')
for p in xsec_x_WW: xsec_x_array_WW.append(p)
for p in xsec_y_WW: xsec_y_array_WW.append(p)
for p in xsec_x_ZZ: xsec_x_array_ZZ.append(p)
for p in xsec_y_ZZ: xsec_y_array_ZZ.append(p)
g_WW=TGraph(len(xsec_x_array_WW),xsec_x_array_WW,xsec_y_array_WW)
g_ZZ=TGraph(len(xsec_x_array_ZZ),xsec_x_array_ZZ,xsec_y_array_ZZ)
f_out_WW=open("theory_RS1_WW_8TeV.txt","w")
f_out_ZZ=open("theory_RS1_ZZ_8TeV.txt","w")
for mass in masses:
        theoryWW=exp(g_WW.Eval(mass))
        theoryZZ=exp(g_ZZ.Eval(mass))
	f_out_WW.write(str(mass)+" "+str(theoryWW)+"\n")
	f_out_ZZ.write(str(mass)+" "+str(theoryZZ)+"\n")
        print "mass = ",mass,"theoryWW = ",theoryWW,"theoryZZ = ",theoryZZ

print "13 TeV"
xsec_x_WW=[1000,1500,2000,2500,3000,4000]
xsec_y_WW=[log(2.37e-3*1e3),log(2.35e-4*1e3),log(4.797e-5*1e3),log(9.4e-6*1e3),log(2.92e-6*1e3),log(2.739e-7*1e3)]
xsec_x_array_WW=array.array('d')
xsec_y_array_WW=array.array('d')
xsec_x_array_ZZ=array.array('d')
xsec_y_array_ZZ=array.array('d')
for p in xsec_x_WW: xsec_x_array_WW.append(p)
for p in xsec_y_WW: xsec_y_array_WW.append(p)
for p in xsec_x_ZZ: xsec_x_array_ZZ.append(p)
for p in xsec_y_ZZ: xsec_y_array_ZZ.append(p)
g_WW=TGraph(len(xsec_x_array_WW),xsec_x_array_WW,xsec_y_array_WW)
g_ZZ=TGraph(len(xsec_x_array_ZZ),xsec_x_array_ZZ,xsec_y_array_ZZ)
f_out_WW=open("theory_RS1_WW_13TeV.txt","w")
f_out_ZZ=open("theory_RS1_ZZ_13TeV.txt","w")
for mass in masses:
        theoryWW=exp(g_WW.Eval(mass))
        theoryZZ=theoryWW/2.
	f_out_WW.write(str(mass)+" "+str(theoryWW)+"\n")
	f_out_ZZ.write(str(mass)+" "+str(theoryZZ)+"\n")
        print "mass = ",mass,"theoryWW = ",theoryWW,"theoryZZ = ",theoryZZ
