// *** mm1.ned ***
simple Generator
{
    parameters:
        volatile double interArrivalTime; // sec
        @display("i=block/source");
    gates:
        output out;
}

simple Queue
{
    parameters:
        volatile double serviceTime; // sec
        @display("i=block/queue");
    gates:
        input in;
        output out;
}

simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}

simple Splitter
{
    parameters:
        @display("i=block/fork");
        double prob= default(0.5);
    gates:
        input in;
        output out1;
        output out2;
}

network MM1
{
    submodules:
        gen: Generator {
            @display("p=30,40");
        }
        queue: Queue {
            @display("p=104,40");
        }
        queue2: Queue {
            @display("p=269,22");
        }

        queue3: Queue {
            @display("p=269,92");
        }
        sink2: Sink {
            @display("p=361,22");
        }
        sink3: Sink {
            @display("p=361,92");
        }

        splitter: Splitter {
            @display("p=185,40");
        }
    connections:
        gen.out --> queue.in;
        queue.out --> splitter.in;
        splitter.out1 --> queue2.in;
        splitter.out2 --> queue3.in;
        queue2.out --> sink2.in;
        queue3.out --> sink3.in;
}
