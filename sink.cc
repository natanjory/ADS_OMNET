/*** sink.cc ***/
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule {
private:
    // online stats
    cStdDev delayStats;
    cOutVector delayVector;

    cStdDev delayTotal;
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
    delayTotal.setName("TotalDelay2");
}

void Sink::finish() {
    recordScalar("Ave delay",delayStats.getMean());
    recordScalar("Ave Delay total",delayTotal.getMean());
    recordScalar("min delay", delayStats.getMin());
    recordScalar("max delay", delayStats.getMax());
    recordScalar("Number of packets",delayStats.getCount());


}

void Sink::handleMessage(cMessage *msg) {
    // compute queueing delay
    simtime_t delay=simTime() - msg->getTimestamp();
    simtime_t delay2=simTime() - msg->getCreationTime();
    // update stats
    delayTotal.collect(delay2);
    delayStats.collect(delay);
    delayVector.record(delay);
    // delete msg
    delete(msg);
}

