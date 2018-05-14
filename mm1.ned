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

simple Split
{
    parameters:
        @display();
    gates:
        input in;
        output out1;
        output out2;
}

network MM1
{
    @display("bgb=566,229");
    submodules:
        gen: Generator {
            @display("p=46,113");
        }
        queue1: Queue {
            @display("p=172,113");
        }
        sink2: Sink {
            @display("p=513,58");
        }
        queue2: Queue {
            @display("p=368,58");
        }
        queue3: Queue {
            @display("p=368,167");
        }
        sink3: Sink {
            @display("p=505,167");
        }
        split: Split {
            @display();
        }
    connections:
        gen.out --> queue1.in;
        queue1.out --> split.in;
        split.out1 --> queue2.in;
        split.out2 --> queue3.in;
        queue2.out --> sink2.in;
        queue3.out --> sink3.in;
}

