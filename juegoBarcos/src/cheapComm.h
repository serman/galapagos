//
//  cheamComm.h
//  panel1_tracking
//
//  Created by Sergio Galan on 5/7/14.
//
//

#ifndef __panel1_tracking__cheapComm__
#define __panel1_tracking__cheapComm__

#include <iostream>
#include "ofxOsc.h"

//static ofEvent	<oscData> eventoOSC;



class cheapComm {
	public:
    
	    void setup();

        ofxOscSender myOscData;
            ofxOscSender myOscData2;
    
        static cheapComm *getInstance(){
            if (!m_pInstance)   // Only allow one instance of class to be generated.
                m_pInstance = new cheapComm;
            return m_pInstance;

        }
        void sendMarcador(int nsol, int nnormal);
    void sendStart( );
    void sendEnd();
    
    private:    
            cheapComm();
            cheapComm(cheapComm const&);              // Don't Implement
            void operator=(cheapComm const&); // Don't implement
            static cheapComm* m_pInstance;

};

#endif /* defined(__panel1_tracking__cheapComm__) */
