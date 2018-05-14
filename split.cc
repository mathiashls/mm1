#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Split : public cSimpleModule {
private:
    cStdDev delayStats;
    cOutVector delayVector;
public:
    Split();
    virtual ~Split();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Split);
Split::Split() {}

Split::~Split() {}


void Split::finish() {
	//TODO
}

void Split::handleMessage(cMessage *msg) {
    cMessage *pkt;
    if (uniform(0, 1) < par("sendToMainQueue")) {
        // send to queue2
    }
    else {
        // send to queue3
    }
}


