int SETUP(){
 if( gSystem->Load( "libTree" ) == -1 ) return -1;                                                                                                                                                                                                                           
 if( gSystem->Load( "libHist" ) == -1 ) return -1;                                                                                                                                                                                                                           
 if( gSystem->Load( "libXMLParser" ) == -1 ) return -1;                                                                                                                                                                                                                      
 if( gSystem->Load( "libProof" ) == -1 ) return -1;                                                                                                                                                                                                                          
 if( gSystem->Load( "libProofPlayer" ) == -1 ) return -1;                                                                                                                                                                                                                    
 if( gSystem->Load( "libSFrameCore" ) == -1 ) return -1; 
 
 if( gSystem->Load( "libfastjet" ) == -1 ) return -1;
 if( gSystem->Load( "libfastjettools" ) == -1 ) return -1;
 if( gSystem->Load( "libJetMETObjects" ) == -1 ) return -1;
 if( gSystem->Load( "libGraf" ) == -1 ) return -1;
 if( gSystem->Load( "libSFrameTools" ) == -1 ) return -1;
 if( gSystem->Load( "libNtuple" ) == -1 ) return -1;
 if( gSystem->Load( "libAnalysis" ) == -1 ) return -1;
 
 if( gSystem->Load( "libStopAnalysis" ) == -1 ) return -1;
 
 return 0;
}
