// LabVIEW-pcm.cpp : Defines the exported functions for the DLL.
//

#include "framework.h"
#include "LabVIEW-pcm.h"
#include "../src/utils.h"
#include "../src/cpucounters.h"
#include "../src/topology.h"
using namespace pcm;


// This is an example of an exported variable
LABVIEWPCM_API int nLabVIEWpcm=0;

static SystemCounterState before_sstateGLB;
static SystemCounterState after_sstateGLB;
static PCM* mGLB;

LABVIEWPCM_API int fnLabVIEWinit(void)
{
    mGLB = PCM::getInstance(); // doesn't work in DLL?

    // program counters, and on a failure just exit

    if (mGLB->program() != PCM::Success) return -1; //-1 here

    return 0;
}

LABVIEWPCM_API int fnLabVIEWstart(void)
{
	before_sstateGLB = getSystemCounterState();
	return 0;
}

LABVIEWPCM_API int fnLabVIEWstop(void)
{
	after_sstateGLB = getSystemCounterState();
	return 0;
}
LABVIEWPCM_API int fnLabVIEWgetIPC(double *ipcLV, double *l2hitLV, uint64 *lv2missLV, double *l3hitLV, uint64 *l3missLV, uint64 *bytesReadLV)
{
    *ipcLV = getIPC(before_sstateGLB, after_sstateGLB);
	*l2hitLV = getL2CacheHitRatio(before_sstateGLB, after_sstateGLB);
	*lv2missLV = getL2CacheMisses(before_sstateGLB, after_sstateGLB);
    *l3hitLV = getL3CacheHitRatio(before_sstateGLB, after_sstateGLB);
	*l3missLV = getL3CacheMisses(before_sstateGLB, after_sstateGLB);
    *bytesReadLV = getBytesReadFromMC(before_sstateGLB, after_sstateGLB);
    
    return 0;
}
// This is an example of an exported function.
LABVIEWPCM_API int fnLabVIEWpcm(void)
{
    PCM* m = PCM::getInstance();

    // program counters, and on a failure just exit

    if (m->program() != PCM::Success) return -1;

    SystemCounterState before_sstate = getSystemCounterState();

    //[run your code here]

        SystemCounterState after_sstate = getSystemCounterState();
        double ipc = getIPC(before_sstate, after_sstate);
        double l3hit = getL3CacheHitRatio(before_sstate, after_sstate);
		uint64 bytesRead = getBytesReadFromMC(before_sstate, after_sstate);


           
        /*
    cout << "Instructions per clock:" << getIPC(before_sstate, after_sstate)

        << "L3 cache hit ratio:" << getL3CacheHitRatio(before_sstate, after_sstate)

        << "Bytes read:" << getBytesReadFromMC(before_sstate, after_sstate)

        << [and so on]...
        */
    return 0;
}

// This is the constructor of a class that has been exported.
CLabVIEWpcm::CLabVIEWpcm()
{
    return;
}
