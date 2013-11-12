// $Id: StopCycle.cxx,v 1.10 2012/12/07 14:21:51 peiffer Exp $

#include <iostream>

using namespace std;

// SFrame include(s):
#include "include/StopCycle.h"
#include "include/StopHists.h"
#include "SFrameTools/include/EventCalc.h"
#include "SFrameAnalysis/include/Cleaner.h"
#include "SFrameAnalysis/include/SelectionModules.h"
#include "SFrameAnalysis/include/TopJetHists.h"

ClassImp( StopCycle );

StopCycle::StopCycle()
   : AnalysisCycle() {

   // constructor, declare additional variables that should be 
   // obtained from the steering-xml file
  
   // set the integrated luminosity per bin for the lumi-yield control plots
   SetIntLumiPerBin(500.);

}

StopCycle::~StopCycle() 
{
   // destructor
}

void StopCycle::BeginCycle() throw( SError ) 
{
   // Start of the job, general set-up and definition of 
   // objects are done here

   // Important: first call BeginCycle of base class
   AnalysisCycle::BeginCycle();

   return;

}

void StopCycle::EndCycle() throw( SError ) 
{
   // clean-up, info messages and final calculations after the analysis

  
   // call the base cycle class for all standard methods
   AnalysisCycle::EndCycle();

   return;

}

void StopCycle::BeginInputData( const SInputData& id ) throw( SError ) 
{
   // declaration of histograms and selections.
   // AnalysisCyle expects Selections and HistCollections to be registered here.
   // Their memory will be released in AnalysisCycle::EndInputData.

   // Important: first call BeginInputData of base class
   AnalysisCycle::BeginInputData( id );

   // -------------------- set up the selections ---------------------------
   HadronicEventSel = new Selection("HadronicEventSelection");
   HadronicEventSel->addSelectionModule(new HadronicEventSelection());

   NJetSel = new Selection("NJetSelection");
   NJetSel->addSelectionModule(new NJetSelection(3, 999, 50., 2.5));

   HTCutSel = new Selection("HThadCut");
   HTCutSel->addSelectionModule(new HThadCut(50., 2.5, 350.));

   METCutSel = new Selection("METCut");
   METCutSel->addSelectionModule(new METCut(100.));

   BSel = new Selection( "BSelection");
   BSel->addSelectionModule(new NBTagSelection(1)); //at least one b tag

   TopTagSel = new Selection( "TopTagSelection");
   TopTagSel->addSelectionModule(new NTopTagSelection(1)); //at least one top tag

   // HEPTopTagSel = new Selection( "HEPTopTagSelection");
   // HEPTopTagSel->addSelectionModule(new NHEPTopTagSelection(1)); //at least one HEP top tag

   // HEPTopTagAndSubBTagSel = new Selection( "HEPTopTagAndSubBTagSelection");
   // HEPTopTagAndSubBTagSel->addSelectionModule(new NHEPTopTagAndSubBTagSelection(1)); 
   //HEP top tag + sub BTag

   RegisterSelection(HadronicEventSel);
   RegisterSelection(NJetSel);
   RegisterSelection(HTCutSel);
   RegisterSelection(METCutSel);
   RegisterSelection(BSel);
   RegisterSelection(TopTagSel);
   // RegisterSelection(HEPTopTagSel);
   // RegisterSelection(HEPTopTagAndSubBTagSel);

   // ---------------- set up the histogram collections --------------------

   // histograms without any cuts
   RegisterHistCollection( new StopHists("StopHists_NoCuts") );
   RegisterHistCollection( new TopJetHists("TopJetHists_NoCuts") );

   // histograms after (object cleaning +) JEC
   RegisterHistCollection( new StopHists("StopHists_ObjectCleaning") );
   RegisterHistCollection( new TopJetHists("TopJetHists_ObjectCleaning") );
  
   // histograms after lepton veto
   RegisterHistCollection( new StopHists("StopHists_LeptonVeto") );
   RegisterHistCollection( new TopJetHists("TopJetHists_LeptonVeto") );

   // histograms after NJet selection
   RegisterHistCollection( new StopHists("StopHists_NJetSelection") );
   RegisterHistCollection( new TopJetHists("TopJetHists_NJetSelection") );

   // histograms after HT selection
   RegisterHistCollection( new StopHists("StopHists_HTSelection") );
   RegisterHistCollection( new TopJetHists("TopJetHists_HTSelection") );

   // histograms after MET selection
   RegisterHistCollection( new StopHists("StopHists_METSelection") );
   RegisterHistCollection( new TopJetHists("TopJetHists_METSelection") );

   // histograms with B-Tag
   RegisterHistCollection( new StopHists("StopHists_BTag") );
   RegisterHistCollection( new TopJetHists("TopJetHists_BTag") );
 
   // histograms with Top-Tag (CMS tagger)
   RegisterHistCollection( new StopHists("StopHists_TopTag") );
   RegisterHistCollection( new TopJetHists("TopJetHists_TopTag") );
  
   // histograms with HEP Top-Tag 
   //RegisterHistCollection( new StopHists("StopHists_HEPTopTag") );
   //RegisterHistCollection( new TopJetHists("TopJetHists_HEPTopTag") );

   // histograms with HEP Top-Tag + subjet bTag
   //RegisterHistCollection( new StopHists("StopHists_HEPTopTagAndSubB") );
   //RegisterHistCollection( new TopJetHists("TopJetHists_HEPTopTagAndSubB") );

   // important: initialise histogram collections after their definition
   InitHistos();

}

void StopCycle::EndInputData( const SInputData& id ) throw( SError ) 
{
   AnalysisCycle::EndInputData( id );
}

void StopCycle::BeginInputFile( const SInputData& id ) throw( SError ) 
{
   // Connect all variables from the Ntuple file with the ones needed for the analysis
   // The variables are commonly stored in the BaseCycleContaincer

   // important: call to base function to connect all variables to Ntuples from the input tree
   AnalysisCycle::BeginInputFile( id );
}

void StopCycle::ExecuteEvent( const SInputData& id, Double_t weight) throw( SError ) 
{
   // this is the most important part: here the full analysis happens
   // user should implement selections, filling of histograms and results

   // first step: call Execute event of base class to perform basic consistency checks
   // also, the good-run selection is performed there and the calculator is reset
   AnalysisCycle::ExecuteEvent( id, weight );

   // get Event calc object
   EventCalc* calc = EventCalc::Instance();

   // init cleaner + basecyclecontainer
   Cleaner cleaner;
   BaseCycleContainer* bcc = calc->GetBaseCycleContainer();

   // ------------------------------------------------------------------------ //
   // start the analysis
   FillControlHistos("_NoCuts");

   // apply JEC
   if (bcc->jets)      cleaner.JetRecorrector(m_corrector,true);
   // if (bcc->jets)      cleaner.JetCleaner(30, 5.0, true); // clean jets (apply jet ID)

   FillControlHistos("_ObjectCleaning");

   // veto events with isolated electrons and muons
   if(!HadronicEventSel->passSelection(bcc)) throw SError( SError::SkipEvent );
   FillControlHistos("_LeptonVeto");

   // require at least 3 jets with jet-pt > 50 GeV && abs(eta) < 2.5
   if(!NJetSel->passSelection(bcc)) throw SError( SError::SkipEvent );
   FillControlHistos("_NJetSelection");

   // cut on HT of the event with jet-pt > 50 GeV && abs(eta) < 2.5 (> 350 GeV)
   if(!HTCutSel->passSelection(bcc)) throw SError( SError::SkipEvent );
   FillControlHistos("_HTSelection");

   // cut on MET of the event (> 100 GeV)
   if(!METCutSel->passSelection(bcc)) throw SError( SError::SkipEvent );
   FillControlHistos("_METSelection");

   // require at least one b-tag
   if(BSel->passSelection()) {
      FillControlHistos("_BTag");
   }
  
   // require at least one top-tag (CMS tagger)
   if(TopTagSel->passSelection()) {
      FillControlHistos("_TopTag");
   }

   return;
  
}

void StopCycle::FillControlHistos(TString postfix)
{
   // fill some control histograms, need to be defined in BeginInputData
   
   BaseHists* stophists = GetHistCollection((std::string)("StopHists"+postfix));
   BaseHists* topjethists = GetHistCollection((std::string)("TopJetHists"+postfix));
    
   stophists->Fill();
   topjethists->Fill();
}

