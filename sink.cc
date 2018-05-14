/*** sink.cc ***/
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule {
private:
    // online stats
    cStdDev delayStats;
    cOutVector delayVector;
public:
    Sink(); // constructor
    virtual ~Sink(); // destructor
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Sink);
Sink::Sink() {}

Sink::~Sink() {}

void Sink::initialize() {
    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");
}

void Sink::finish() {
    recordScalar("Ave delay",delayStats.getMean());
    recordScalar("Number of packets",delayStats.getCount());
}

void Sink::handleMessage(cMessage *msg) {
    // compute queueing delay
    simtime_t delay=simTime() - msg->getCreationTime();
    // update stats
    delayStats.collect(delay);
    delayVector.record(delay);
    // delete msg
    delete(msg);
}

