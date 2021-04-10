#include <iostream>
#include <TGraph.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>


void test(std::string file)
{
	TFile* f = new TFile(file.c_str());
	TGraph* g = new TGraph(); 

	TTree* t = (TTree*) f->Get("eventsReWeightsTree");
	t->SetBranchAddress("CA5Graph", &g);//"FSI_PI_PRODGraph", &g);
	int evtid;
	t->SetBranchAddress("evt", &evtid);
	TCanvas* c1 = new TCanvas("c1", "c1");
	c1->cd();
	/*
	t->GetEntry(40846);
	std::cout<<evtid<<" "<<g->Eval(1.002)<<std::endl;
	g->Draw();
	c1->SaveAs("test.pdf");
	*/

	for(int i=0; i<t->GetEntries(); i++)
	{
		t->GetEntry(i);
		if(evtid==700075)//3801644)//5504076)//3102668)
		{
			std::cout<<i<<" "<<g->Eval(1.01)<<std::endl;
			g->Draw();
			c1->SaveAs("test.pdf");
			break;	
		}
	}
	
	return ;
}
