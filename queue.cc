#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Queue : public cSimpleModule {
private:
    // local variable
    cQueue buffer;
    cMessage *endServiceEvent;
    simtime_t service_time;
public:
    // constructor
    Queue(); // constructor
    virtual ~Queue(); // destructor
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Queue);
    Queue::Queue() {
    endServiceEvent=NULL;
}

Queue::~Queue() {
    cancelAndDelete(endServiceEvent);
}

void Queue::initialize() {
    endServiceEvent=new cMessage("endService");
}

void Queue::finish() {}

void Queue::handleMessage(cMessage *msg) {
    cMessage *pkt;
    // if msg is endServiceEvent, then
    //dequeue and send the pkt to the output
    //if another pkt is available in the buffer, then
    //start a new service
    // if msg is a packet, then
    //enqueue the pkt
    //if server idling, then
    //start a new service
    if (msg==endServiceEvent) {
        // dequeue
        pkt=(cMessage*)buffer.pop();
        // send
        send(pkt,"out");
        if (!buffer.isEmpty()) { // if another pkt is available
            // start the service
            service_time=par("serviceTime");
            scheduleAt(simTime()+service_time,endServiceEvent);
        }
    } else { // msg is a packet
        // enqueue
        buffer.insert(msg);
        // if the server is idling
        if (!endServiceEvent->isScheduled()) {
            // start the service
            service_time=par("serviceTime");
            scheduleAt(simTime()+service_time,endServiceEvent);
        }
    }
}

