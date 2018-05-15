/*** sink.cc ***/
#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Splitter : public cSimpleModule {
private:
    // online stats
    cStdDev delayStats;
    cOutVector delayVector;
public:
   Splitter(); // constructor
    virtual ~Splitter(); // destructor
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Splitter);
Splitter::Splitter() {}

Splitter::~Splitter() {}

void Splitter::initialize() {
    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");
}

void Splitter::finish() {
    recordScalar("Ave delay",delayStats.getMean());
    recordScalar("min delay", delayStats.getMin());
    recordScalar("max delay", delayStats.getMax());
    recordScalar("Number of packets",delayStats.getCount());
}

void Splitter::handleMessage(cMessage *msg) {
    // compute queueing delay
    simtime_t delay=simTime() - msg->getCreationTime();
    // update stats
    delayStats.collect(delay);
    delayVector.record(delay);
    // delete msg
    double teste= par("prob");
    if( uniform(0,1)< teste){
        send(msg,"out1");

    }else{
        send(msg,"out2");
    }


}

