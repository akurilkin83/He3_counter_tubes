#include "iostream"
#include "fstream"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"




using namespace std; 



int test(){
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Thu Feb 15 09:41:46 2018 by ROOT version6.06/06)
//   from TTree TreeEventsHe3/Events He3 Detector
//   found on file: ./He3_counter.root
//////////////////////////////////////////////////////////


ofstream myfile1, myfile2, myfile3, myfile4,myfile5;
myfile1.open("dep_energy.txt");
myfile2.open("MeanSLP.txt");
myfile3.open("MeamSLT.txt");
myfile4.open("MeanSL_sum.txt");
myfile5.open("Efficiency.txt");

//Reset ROOT and connect tree file
//   gROOT->Reset();
   TFile *f = new TFile("./He3_counter_output.root");
//   TFile *f = new TFile("./test.root");
   if (!f) {
      cout<<"no input file"<<endl;
      return -1;
   }
  TTree * ttree = (TTree*)f->Get("Ntuple1");

//Declaration of leaves types
   Int_t           EventNr;
   Double_t        Energy;
   Double_t        xpos;
   Double_t        ypos;
   Double_t        zpos;
   Double_t        TotalSLP;
   Double_t        MeanSLP;
   Double_t        TotalSLT;
   Double_t        MeanSLT;
   Double_t        vertex_x;
   Double_t        vertex_y;
   Double_t        vertex_z;
   Double_t        energy_n;

   // Set branch addresses.
   ttree->SetBranchAddress("EventNr",&EventNr);
   ttree->SetBranchAddress("Energy",&Energy);
   ttree->SetBranchAddress("xpos",&xpos);
   ttree->SetBranchAddress("ypos",&ypos);
   ttree->SetBranchAddress("zpos",&zpos);
   ttree->SetBranchAddress("TotalSLP",&TotalSLP);
   ttree->SetBranchAddress("MeanSLP",&MeanSLP);
   ttree->SetBranchAddress("TotalSLT",&TotalSLT);
   ttree->SetBranchAddress("MeanSLT",&MeanSLT);
   ttree->SetBranchAddress("vertex_x",&vertex_x);
   ttree->SetBranchAddress("vertex_y",&vertex_y);
   ttree->SetBranchAddress("vertex_z",&vertex_z);
   ttree->SetBranchAddress("energy_n",&energy_n);

//   ttree->SetBranchAddress("pr_neutron",&pr_neutron);




//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// TreeEventsHe3->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname


// histograms



TH1D *dep_energy = new TH1D("dep_energy","deposited energy",2000,0,1000);
TH1D *meanSLP    = new TH1D("meanSLP","mean step length of proton",2000,0,20);
TH1D *meanSLT    = new TH1D("meanSLT","mean step length of triton",2000,0,20);
TH1D *meanSL    = new TH1D("meanSL","mean step length of proton + triton",4000,0,40);

//TH1D *meanSLT    = new TH1D("meanSLT","mean step length of triton",180,0,18);
TH1D *Tk_neutron = new TH1D("Tk_neutron","kinetic energy of neutron",1000,0,0.04);


TH2D * reaction_yx = new TH2D("reaction_yx","reaction : y-x correlation",200,-20,20,200,-20,20);
TH2D * reaction_xz = new TH2D("reaction_xz","reaction : x-z correlation",200,-20,20,200,-20,20);
TH2D * reaction_yz = new TH2D("reaction_yz","reaction : y-z correlation",400,-10,30,400,-20,20);
//TH2D * vertex_yx = new TH2D("vertex_yx","vertex : y-x correlation",400,-100,100,420,-10,60);
//TH2D * efficiency = new TH2D("efficiency","efficiency : y-x",400,-100,100,420,-10,60);

TH2D * vertex_yx = new TH2D("vertex_yx","vertex : y-x correlation",200,-20,20,200,-20,20);
TH2D * efficiency = new TH2D("efficiency","reaction : y-x correlation",200,-20,20,200,-20,20);

//TH2D * cover_yx = new TH2D("cover_yx","cover absorbtion : y-x correlation for cover",400,-100,100,420,-10,60);



   Long64_t nentries = ttree->GetEntries();
   float_t ver_y_new =0; //  for beam under 45deg
    Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
//   for (Long64_t i=0; i<100000;i++) {
      nbytes += ttree->GetEntry(i);
    vertex_yx->Fill(vertex_x,vertex_y);   // for beam with one line with detector

//ver_y_new = vertex_y - 25.0;
//    vertex_yx->Fill(vertex_x,vertex_y);

	if (zpos!=-1000){
//	if (zpos>-1&&Energy>300){
	
	dep_energy->Fill(Energy);
	meanSLP->Fill(MeanSLP);
	meanSLT->Fill(MeanSLT);
	meanSL->Fill(MeanSLT+MeanSLP);
	Tk_neutron->Fill(energy_n);
	
	reaction_yx->Fill(xpos,ypos);
	reaction_xz->Fill(zpos,xpos);
	reaction_yz->Fill(zpos,ypos);
	efficiency->Fill(xpos,ypos);
	}
//	if (zpos>-1&&pr_neutron==1){
//	cover_yx->Fill(xpos,ypos);
//	}



   }
    efficiency->Divide(vertex_yx);








    TCanvas *c1 = new TCanvas("c1","Results",600,800);
    c1->Divide(2,2);
    c1->cd(1);
    meanSLT->Draw();
    meanSLT->GetXaxis()->SetTitle("step length, mm");

//    Tk_neutron->Draw();
    c1->cd(2);
    meanSLP->Draw();
    meanSLP->GetXaxis()->SetTitle("step length, mm");

    c1->cd(3);
    meanSL->Draw();
    meanSL->GetXaxis()->SetTitle("step length, mm");


    c1->cd(4);
    dep_energy->Draw();
    dep_energy->GetXaxis()->SetTitle("depositet energy, keV");

//    TCanvas *c2 = new TCanvas("c2","Result for 8atm_3He_4th_detectors",600,800);
//    c2->Divide(2,2);
//    c2->cd(1);
//    vertex_yx->Draw("colz");
//    c2->cd(2);
//    reaction_yx->Draw("colz");
//    c2->cd(3);
//    reaction_xz->Draw("colz");
//    c2->cd(4);
//    reaction_yz->Draw("colz");


    TCanvas *c3 = new TCanvas("c3","Results",600,800);
    c3->Divide(2,2);

    c3->cd(1);
    reaction_yz->Draw("colz");

    c3->cd(2);
    vertex_yx->Draw("colz");

    c3->cd(3);
    efficiency->Draw("colz");
//    efficiency->GetXaxis()->SetTitle("efficiency");

    c3->cd(4);

    TH1D *hh = efficiency->ProjectionY("_py",56,145);
//    TH1D *hh = efficiency->ProjectionY("_py",50,50);
    hh->Scale(1./90.);
    hh->SetMaximum(1);
    hh->SetTitle("Efficiency");
    hh->GetXaxis()->SetTitle("efficiency");
    hh->Draw("hist");

//    TCanvas *c4 = new TCanvas("c4","Result for 8atm_3He_4th_detectors",600,800);
//    cover_yx->Draw("colz");




c1->Print("histo.pdf[");
c1->Print("histo.pdf");
c3->Print("histo.pdf");
c3->Print("histo.pdf]");
//c4->Print("h1.pdf");
//c4->Print("h1.pdf]");



Int_t Nbins_dep_energy = dep_energy->GetNbinsX();
Int_t Nbins_MeanSLP = meanSLP->GetNbinsX();
Int_t Nbins_MeanSLT = meanSLT->GetNbinsX();
Int_t Nbins_MeanSL = meanSL->GetNbinsX();


myfile1 << "Energy(eV)     Counts"<<"\n";
for (Int_t i=0;i<Nbins_dep_energy;i++){
if (dep_energy->GetBinContent(i)!=0){
    myfile1<<"   "<<dep_energy->GetBinCenter(i)<<"      "<< dep_energy->GetBinContent(i)<<"\n";
    }
}
myfile1.close();


myfile2 << "MeanSLP(mm)     Counts"<<"\n";
for (Int_t i=0;i<Nbins_MeanSLP;i++){
if (meanSLP->GetBinContent(i)!=0){
    myfile2<<"   "<<meanSLP->GetBinCenter(i)<<"      "<< meanSLP->GetBinContent(i)<<"\n";
    }
}
myfile2.close();

myfile3 << "MeanSLT(mm)     Counts"<<"\n";
for (Int_t i=0;i<Nbins_MeanSLT;i++){
if (meanSLT->GetBinContent(i)!=0){
    myfile3<<"   "<<meanSLT->GetBinCenter(i)<<"      "<< meanSLT->GetBinContent(i)<<"\n";
    }
}
myfile3.close();




myfile4 << "MeanSL(mm)     Counts"<<"\n";
for (Int_t i=0;i<Nbins_MeanSL;i++){
if (meanSL->GetBinContent(i)!=0){
    myfile4<<"   "<<meanSL->GetBinCenter(i)<<"      "<< meanSL->GetBinContent(i)<<"\n";
    }
}
myfile4.close();



myfile5 << "Efficiency, %"<<"\n";
myfile5<< reaction_yx->GetEntries()/vertex_yx->GetEntries()*100.<<"\n";




//    ttree->Draw("ypos:xpos>>h55(200,-100,100,200,-10,50)","zpos>-1","colz");    
//    h55->Divide(h44);
//h55->Draw("colz");
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += TreeEventsHe3->GetEntry(i);
//   }

return 0;
}
