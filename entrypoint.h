//==========================================================================================
// + + +   This Software is released under the "Simplified BSD License"  + + +
// Copyright 2014 F4GKR Sylvain AZARIAN . All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are
//permitted provided that the following conditions are met:
//
//   1. Redistributions of source code must retain the above copyright notice, this list of
//	  conditions and the following disclaimer.
//
//   2. Redistributions in binary form must reproduce the above copyright notice, this list
//	  of conditions and the following disclaimer in the documentation and/or other materials
//	  provided with the distribution.
//
//THIS SOFTWARE IS PROVIDED BY Sylvain AZARIAN F4GKR ``AS IS'' AND ANY EXPRESS OR IMPLIED
//WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Sylvain AZARIAN OR
//CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//The views and conclusions contained in the software and documentation are those of the
//authors and should not be interpreted as representing official policies, either expressed
//or implied, of Sylvain AZARIAN F4GKR.
//==========================================================================================
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stdint.h>
#include <sys/types.h>

#ifdef _WIN64
#include <windows.h>
#endif

#define LIBRARY_API __stdcall __declspec(dllexport)
#define RC_OK (1)
#define RC_NOK (0)

// call is log( UUID, severity, msg)
typedef int   (__stdcall _tlogFun)(char *, int, char *);

// call is pushSamples( UUID, ptr to float array of samples, sample count, channel count )
typedef int   (_stdcall  _pushSamplesFun)( char *, float *, int, int);

extern "C" {

    #ifdef _WIN64
    BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID *lpvReserved );
    #endif

    LIBRARY_API int initLibrary(char *json_init_params, _tlogFun* ptr, _pushSamplesFun *acqCb );
    LIBRARY_API int getBoardCount();

    LIBRARY_API int setBoardUUID( int device_id, char *uuid );

    LIBRARY_API char *getHardwareName();


    // manage sample rates
    LIBRARY_API int getPossibleSampleRateCount() ;
    LIBRARY_API unsigned int getPossibleSampleRateValue(int index);
    LIBRARY_API unsigned int getPrefferedSampleRateValue();

    //manage min/max freqs
    LIBRARY_API int64_t getMin_HWRx_CenterFreq();
    LIBRARY_API int64_t getMax_HWRx_CenterFreq();

    // discover gain stages and settings
    LIBRARY_API int getRxGainStageCount() ;
    LIBRARY_API char* getRxGainStageName( int stage);
    LIBRARY_API char* getRxGainStageUnitName( int stage);
    LIBRARY_API int getRxGainStageType( int stage);
    LIBRARY_API float getMinGainValue(int stage);
    LIBRARY_API float getMaxGainValue(int stage);
    LIBRARY_API int getGainDiscreteValuesCount( int stage );
    LIBRARY_API float getGainDiscreteValue( int stage, int index ) ;

    // driver instance specific functions
    // will be called with device index in the range [0..getBoardCount()[
    LIBRARY_API char* getSerialNumber( int device_id );

    LIBRARY_API int prepareRXEngine( int device_id );
    LIBRARY_API int finalizeRXEngine( int device_id );

    LIBRARY_API int setRxSampleRate( int device_id , int sample_rate);
    LIBRARY_API int getActualRxSampleRate( int device_id );

    LIBRARY_API int setRxCenterFreq( int device_id , int64_t freq_hz );
    LIBRARY_API int64_t getRxCenterFreq( int device_id );

    LIBRARY_API int setRxGain( int device_id, int stage_id, float gain_value );
    LIBRARY_API float getRxGainValue( int device_id , int stage_id );
    LIBRARY_API bool setAutoGainMode( int device_id );
}

#endif // ENTRYPOINT_H
