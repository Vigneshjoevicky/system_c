#include <systemc.h>  // Include SystemC library

SC_MODULE(xor_gate)
{
    sc_in<bool> a, b;
    sc_out<bool> out;

    void xor_op()
    {
        if (a.read() != b.read())
        {
            out.write(true);
        }
        else
        {
            out.write(false);
        }
    }

    SC_CTOR(xor_gate)
    {
        SC_METHOD(xor_op);
        sensitive << a << b;
    }
};

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> asignal, bsignal, outsignal;

    xor_gate gate("xor");
    gate.a(asignal);
    gate.b(bsignal);
    gate.out(outsignal);

    asignal = 0; bsignal = 0;
    sc_start(1, SC_NS);
    cout << "0 0 : " << outsignal.read() << endl;

    asignal = 0; bsignal = 1;
    sc_start(1, SC_NS);
    cout << "0 1 : " << outsignal.read() << endl;

    asignal = 1; bsignal = 0;
    sc_start(1, SC_NS);
    cout << "1 0 : " << outsignal.read() << endl;

    asignal = 1; bsignal = 1;
    sc_start(1, SC_NS);
    cout << "1 1 : " << outsignal.read() << endl;

    return 0;
}
