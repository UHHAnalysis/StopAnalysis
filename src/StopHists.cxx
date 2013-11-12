#include "include/StopHists.h"
#include "SFrameTools/include/EventCalc.h"
#include <iostream>

using namespace std;

StopHists::StopHists(const char* name) : BaseHists(name)
{
  // named default constructor
   
}

StopHists::~StopHists(){
}

void StopHists::Init()
{
   // book all histograms here

   // missing ET and HT
   // double* logMET_bins = MakeLogBinning(40, 50, 1200);
   Book( TH1F( "MET_ly", "missing E_{T} [GeV]", 200, 0, 2000 ) );
   // double* logHT_bins = MakeLogBinning(40, 150, 3000);
   Book( TH1F( "HT_ly", "H_{T} [GeV]", 500, 0, 5000 ) );
   //double* logHTlep_bins = MakeLogBinning(40, 150, 1200);
   Book( TH1F( "HTlep_ly", "H_{T}^{lep} [GeV]", 500, 0, 5000 ) );
   Book( TH1F( "HThad_ly", "H_{T}^{had} [GeV]", 500, 0, 5000 ) );
 
   // jets
   Book( TH1F( "N_jets_ly", "N^{jets}", 30, 0, 30 ) );
   //double* logPtjet1_bins = MakeLogBinning(40, 150, 1500);
   //double* logPtjet2_bins = MakeLogBinning(40, 50, 1000);
   //double* logPtjet3_bins = MakeLogBinning(40, 50, 500);
   //double* logPtjet4_bins = MakeLogBinning(40, 50, 250);
   //  Book( TH1F( "pt_jet1_lx", "p_{T}^{jet 1} [GeV/c]", 40, logPtjet1_bins ) );
   //Book( TH1F( "pt_jet2_lx", "p_{T}^{jet 2} [GeV/c]", 40, logPtjet2_bins ) ); 
   //Book( TH1F( "pt_jet3_lx", "p_{T}^{jet 3} [GeV/c]", 40, logPtjet3_bins ) );
   //Book( TH1F( "pt_jet4_lx", "p_{T}^{jet 4} [GeV/c]", 40, logPtjet4_bins ) );
   Book( TH1F( "pt_jet1_ly", "p_{T}^{jet 1} [GeV/c]", 150, 0, 1500 ) );
   Book( TH1F( "pt_jet2_ly", "p_{T}^{jet 2} [GeV/c]", 100, 0, 1000 ) ); 
   Book( TH1F( "pt_jet3_ly", "p_{T}^{jet 3} [GeV/c]", 50, 0, 500 ) );
   Book( TH1F( "pt_jet4_ly", "p_{T}^{jet 4} [GeV/c]", 25, 0, 250 ) );
   Book( TH1F( "pt_jet5_ly", "p_{T}^{jet 5} [GeV/c]", 25, 0, 250 ) );
   Book( TH1F( "pt_jet6_ly", "p_{T}^{jet 6} [GeV/c]", 25, 0, 250 ) );
   Book( TH1F( "eta_jet1_ly", "#eta^{jet 1}", 100, -5.0, 5.0) );
   Book( TH1F( "eta_jet2_ly", "#eta^{jet 2}", 100, -5.0, 5.0) );
   Book( TH1F( "eta_jet3_ly", "#eta^{jet 3}", 100, -5.0, 5.0) );
   Book( TH1F( "eta_jet4_ly", "#eta^{jet 4}", 100, -5.0, 5.0) );
   Book( TH1F( "eta_jet5_ly", "#eta^{jet 5}", 100, -5.0, 5.0) );
   Book( TH1F( "eta_jet6_ly", "#eta^{jet 6}", 100, -5.0, 5.0) );

   // jet response
   Book( TH2F( "JetResponse", "Response", 500, 0, 2000, 100, 0, 2) );

   double* logPtlep_bins = MakeLogBinning(40, 45, 500);
   // muons
   Book( TH1F( "N_mu", "N^{#mu}", 10, 0, 10 ) );
   Book( TH1F( "pt_mu_lx", "p_{T}^{#mu} [GeV/c]", 40, logPtlep_bins ) );
   Book( TH1F( "eta_mu", "#eta^{#mu}", 100, -5.0, 5.0) );
   Book( TH1F( "reliso_mu", "#mu rel. Iso", 40, 0, 0.5) );

   // electrons
   Book( TH1F( "N_ele", "N^{el}", 10, 0, 10 ) );
   Book( TH1F( "pt_ele_lx", "p_{T}^{el} [GeV/c]", 40, logPtlep_bins ) );
   Book( TH1F( "eta_ele", "#eta^{el}", 100, -5.0, 5.0) );
   Book( TH1F( "relisorho_ele", "el rel. Iso rho", 40, 0, 0.5) );

   // taus
   Book( TH1F( "N_taus", "N^{#tau}", 10, 0, 10 ) );
   Book( TH1F( "pt_tau_lx", "p_{T}^{#tau} [GeV/c]", 40, logPtlep_bins ) );
   Book( TH1F( "eta_tau", "#eta^{#tau}", 100, -5.0, 5.0) );
 
   // primary vertices
   Book( TH1F( "N_pv_ly", "N^{PV}", 50, 0, 50 ) );
   Book( TH1F( "N_events_perLumiBin", "N^{evt}", 24, 0, 24 ) );
   Book( TH1F( "N_pv_perLumiBin", "N^{PV}", 24, 0, 24 ) );

   // rho
   Book( TH1F( "rho", "#rho [GeV]", 1000, 0, 100) );

   // weight
   Book( TH1F( "Weight","weight", 10000,0,1000) );
   Book( TH1F( "Weight_ly","weight", 10000,0,1000) );
  
   // generator distributions
   Book( TH1F( "M_ttbar_gen_ly", "m_{t#bar{t}}_{gen} [GeV/c^{2}]", 1000, 0, 1000) ); 
   Book( TH1F( "t_ptgen_ly", "t p_{T}_{gen} [GeV/c]", 1500, 0, 1500) ); 
   Book( TH1F( "tbar_ptgen_ly", "#bar{t} p_{T}_{gen} [GeV/c]", 1500, 0, 1500) ); 
   Book( TH1F( "q_scale_ly", "q scale", 2000, 0, 2000) );

   // counter for cut flow
   Book( TH1F( "EventCounter", "", 1, 0, 1) );
}

void StopHists::Fill()
{
   // fill the histograms

   // fill the histograms
   EventCalc* calc = EventCalc::Instance();
   bool IsRealData = calc->IsRealData();
   LuminosityHandler* lumih = calc->GetLumiHandler();

   BaseCycleContainer* bcc = calc->GetBaseCycleContainer();

   // important: get the event weight
   double weight = calc->GetWeight();

   int run = calc->GetRunNum();
   int lumiblock = calc->GetLumiBlock();
   int Npvs = calc->GetPrimaryVertices()->size();

   Hist("N_pv_ly")->Fill(Npvs, weight);
   if(calc->IsRealData()){  
      Hist( "N_pv_perLumiBin")->Fill( lumih->GetLumiBin(run, lumiblock), Npvs*weight);
      Hist( "N_events_perLumiBin")->Fill( lumih->GetLumiBin(run, lumiblock), weight);
   }

   Hist("rho")->Fill(bcc->rho, weight);

   MET* met = calc->GetMET();
   Hist("MET_ly")->Fill(met->pt(), weight);

   double HT = calc->GetHT();
   Hist("HT_ly")->Fill(HT, weight);

   double HTlep = calc->GetHTlep();
   Hist("HTlep_ly")->Fill(HTlep, weight);

   double HThad = calc->GetHThad(50., 2.5);
   Hist("HThad_ly")->Fill(HThad, weight);

   std::vector<Jet>* jets = calc->GetJets();
   int Njets = 0;
   for(unsigned int i=0; i<jets->size(); ++i){
      if( jets->at(i).pt() > 50. && fabs(jets->at(i).eta()) < 2.5 ) Njets++;
   }
   Hist("N_jets_ly")->Fill(Njets, weight);

   if(Njets>=1){
      Hist("pt_jet1_ly")->Fill(jets->at(0).pt(), weight);
      Hist("eta_jet1_ly")->Fill(jets->at(0).eta(), weight);
   }

   if(Njets>=2){
      Hist("pt_jet2_ly")->Fill(jets->at(1).pt(), weight);
      Hist("eta_jet2_ly")->Fill(jets->at(1).eta(), weight);
   }

   if(Njets>=3){
      Hist("pt_jet3_ly")->Fill(jets->at(2).pt(), weight);
      Hist("eta_jet3_ly")->Fill(jets->at(2).eta(), weight);
   }

   if(Njets>=4){
      Hist("pt_jet4_ly")->Fill(jets->at(3).pt(), weight);
      Hist("eta_jet4_ly")->Fill(jets->at(3).eta(), weight);
   }

   if(Njets>=5){
      Hist("pt_jet5_ly")->Fill(jets->at(4).pt(), weight);
      Hist("eta_jet5_ly")->Fill(jets->at(4).eta(), weight);
   }

   if(Njets>=6){
      Hist("pt_jet6_ly")->Fill(jets->at(5).pt(), weight);
      Hist("eta_jet6_ly")->Fill(jets->at(5).eta(), weight);
   }

   TH2F* h = (TH2F*) Hist("JetResponse");
   for(int i=0; i<Njets; i++) {
      if(jets->at(i).has_genjet()) h->Fill(jets->at(i).genjet_pt(), (jets->at(i).pt())/(jets->at(i).genjet_pt()), weight);
   }

   std::vector<Muon>* muons = calc->GetMuons();
   int Nmuons = muons->size();
   Hist("N_mu")->Fill(Nmuons, weight);
   for (int i=0; i<Nmuons; ++i){
      Muon thismu = muons->at(i);
      Hist("pt_mu_lx")->Fill(thismu.pt(), weight);
      Hist("eta_mu")->Fill(thismu.eta(), weight);

      Hist("reliso_mu")->Fill(thismu.relIso(), weight);
   }

   std::vector<Electron>* electrons = calc->GetElectrons();
   int Nelectrons = electrons->size();
   Hist("N_ele")->Fill(Nelectrons, weight);
   for (int i=0; i<Nelectrons; ++i){
      Electron thisele = electrons->at(i);
      Hist("pt_ele_lx")->Fill(thisele.pt(), weight);
      Hist("eta_ele")->Fill(thisele.eta(), weight);

      Hist("relisorho_ele")->Fill(thisele.relIsorho(bcc->rho), weight);
   }

  //  std::vector<Tau>* taus = calc->GetTaus();
//    int Ntaus = taus->size();
//    Hist("N_taus")->Fill(Ntaus, weight);
//    for (int i=0; i<Ntaus; ++i){
//       Tau thistau = taus->at(i);
//       Hist("pt_tau_lx")->Fill(thistau.pt(), weight);
//       Hist("eta_tau")->Fill(thistau.eta(), weight);
//    }

   Hist("Weight")-> Fill(weight);
   Hist("Weight_ly")-> Fill(weight); 
  
   double mttbar_gen = 0.;
   double t_genpt = 0.;
   double tbar_genpt = 0.;
   if(calc->GetGenParticles() ) {
      mttbar_gen = ( calc->GetTTbarGen()->Top().v4() + calc->GetTTbarGen()->Antitop().v4()).M();
      t_genpt = calc->GetTTbarGen()->Top().v4().Pt();
      tbar_genpt = calc->GetTTbarGen()->Antitop().v4().Pt();

      Hist("M_ttbar_gen_ly")->Fill(mttbar_gen, weight);
      Hist("t_ptgen_ly")->Fill(t_genpt, weight);
      Hist("tbar_ptgen_ly")->Fill(tbar_genpt, weight);
   }

   if(calc->GetGenInfo() ) {
      Hist("q_scale_ly")->Fill(calc->GetGenInfo()->pdf_scalePDF(), weight);
   }

   Hist("EventCounter")->Fill(0.5, weight);

}

void StopHists::Finish()
{
  // final calculations, like division and addition of certain histograms
  EventCalc* calc = EventCalc::Instance();
  bool IsRealData = calc->IsRealData();
  if (IsRealData){
    Hist("N_pv_perLumiBin")->Divide( Hist("N_pv_perLumiBin"), Hist("N_events_perLumiBin"));
    Hist( "N_pv_perLumiBin")->GetYaxis()->SetTitle("Events/Lumi");
  }

}

