/*** generator.cc ***/
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Generator: public cSimpleModule {
private:
    cMessage *sendMsgEvent;
public:
    Generator(); // constructor
    virtual ~Generator(); // destructor
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Generator);

Generator::Generator() {
    sendMsgEvent=NULL;
}

Generator::~Generator() {
    cancelAndDelete(sendMsgEvent);
}

void Generator::initialize() {
    // create the "send" packet
    sendMsgEvent=new cMessage("sendEvent");
    // schedule the first event at random time
    scheduleAt(par("interArrivalTime"), sendMsgEvent);
}

void Generator::finish() {
}

void Generator::handleMessage(cMessage *msg) {
    cMessage *pkt;
    simtime_t departure_time;
    // create new packet
    pkt = new cMessage("packet");
    // sent to the output
    send(pkt,"out");
    // compute the new departure time
    departure_time=simTime()+par("interArrivalTime");
    // schedule the new packet generation
    scheduleAt(departure_time, sendMsgEvent);
}

