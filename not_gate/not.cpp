

#include <systemc.h>


SC_MODULE(NotGate) {
    sc_in<bool> a;     // Input
    sc_out<bool> y;    // Output

    void do_not() {
        y.write(!a.read());
    }

    SC_CTOR(NotGate) {
        SC_METHOD(do_not);
        sensitive << a;
    }
};
int sc_main(int argc, char* argv[]) {
    sc_signal<bool> a_sig;
    sc_signal<bool> y_sig;

    NotGate not1("NOT1");
    not1.a(a_sig);
    not1.y(y_sig);

    
    cout << "A Y" << endl;

    
    a_sig = 0;
    sc_start(1, SC_NS);
    cout << a_sig.read() << " " << y_sig.read() << endl;

    a_sig = 1;
    sc_start(1, SC_NS);
    cout << a_sig.read() << " " << y_sig.read() << endl;

    return 0;
}
