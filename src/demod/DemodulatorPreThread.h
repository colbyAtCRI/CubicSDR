#pragma once

#include <queue>
#include <vector>

#include "CubicSDRDefs.h"
#include "DemodDefs.h"
#include "DemodulatorWorkerThread.h"

class DemodulatorInstance;

class DemodulatorPreThread : public IOThread {
public:

    DemodulatorPreThread(DemodulatorInstance *parent);
    ~DemodulatorPreThread();

    void run();

    DemodulatorThreadParameters &getParams();
    void setParams(DemodulatorThreadParameters &params_in);
    
    void setDemodType(std::string demodType);
    std::string getDemodType();

    void initialize();
    void terminate();

    Modem *getModem();
    ModemKit *getModemKit();
    
protected:
    DemodulatorInstance *parent;
    msresamp_crcf iqResampler;
    double iqResampleRatio;
    std::vector<liquid_float_complex> resampledData;

    Modem *cModem;
    ModemKit *cModemKit;

    DemodulatorThreadParameters params;
    DemodulatorThreadParameters lastParams;

    nco_crcf freqShifter;
    int shiftFrequency;

    std::atomic_bool initialized;
    std::atomic_bool demodTypeChanged;
    std::string demodType;
    std::string newDemodType;

    DemodulatorWorkerThread *workerThread;
    std::thread *t_Worker;

    DemodulatorThreadWorkerCommandQueue *workerQueue;
    DemodulatorThreadWorkerResultQueue *workerResults;

    DemodulatorThreadInputQueue* iqInputQueue;
    DemodulatorThreadPostInputQueue* iqOutputQueue;
    DemodulatorThreadCommandQueue* threadQueueNotify;
    DemodulatorThreadCommandQueue* commandQueue;
};
