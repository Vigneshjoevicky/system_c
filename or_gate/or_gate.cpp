#include <systemc.h>
#include <iostream>
 
SC_MODULE(or_gate)
{
    sc_in<bool> a;
    sc_in<bool> b;
    sc_out<bool> out;
 
    void operation()
    {
        out.write(a.read() | b.read());
    }
 
    SC_CTOR(or_gate)
    {
        SC_METHOD(operation);
        sensitive << a << b;
    }
};
 
int sc_main(int argc, char* argv[])
{
    sc_signal<bool> signal_a, signal_b, signal_out;
 
    or_gate or1("or_gate");  // renamed from 'or' to 'or1'
    or1.a(signal_a);
    or1.b(signal_b);
    or1.out(signal_out);
 
    std::cout << "Simulation starts" << std::endl;
 
    signal_a = 0;
    signal_b = 0;
    sc_start(1, SC_NS);
    std::cout << "0 OR 0 = " << signal_out.read() << std::endl;
 
    signal_a = 0;
    signal_b = 1;
    sc_start(1, SC_NS);
    std::cout << "0 OR 1 = " << signal_out.read() << std::endl;
 
    signal_a = 1;
    signal_b = 0;
    sc_start(1, SC_NS);
    std::cout << "1 OR 0 = " << signal_out.read() << std::endl;
 
    signal_a = 1;
    signal_b = 1;
    sc_start(1, SC_NS);
    std::cout << "1 OR 1 = " << signal_out.read() << std::endl;
 
    return 0;
}
