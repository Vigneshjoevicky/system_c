#include<systemc.h>
#include<iostream>

SC_MODULE(half_adder)
{
     sc_in<bool> a,b;
     sc_out<bool> sum,carry;

     void adder_operation()
     {
       bool tsum=a.read() ^ b.read();
       bool tcarry=a.read() & b.read();
        sum.write(tsum);
        carry.write(tcarry);
     }

     SC_CTOR(half_adder)
     {
        SC_METHOD(adder_operation);
        sensitive <<a<<b;

     }
};

int sc_main(int argc,char* argv[])
{
    half_adder adder("adder");
    sc_signal<bool> signal1,signal2,sig_sum,sig_carry;

    adder.a(signal1);
    adder.b(signal2);
    adder.sum(sig_sum);
    adder.carry(sig_carry);

    signal1=0;signal2=0;
    sc_start(2,SC_NS);
    cout<<sig_sum.read()<<sig_carry.read()<<endl;

    
    signal1=0;signal2=1;
    sc_start(2,SC_NS);
    cout<<sig_sum.read()<<sig_carry.read()<<endl;

    
    signal1=1;signal2=0;
    sc_start(2,SC_NS);
    cout<<sig_sum.read()<<sig_carry.read()<<endl;

    
    signal1=1;signal2=1;
    sc_start(2,SC_NS);
    cout<<sig_sum.read()<<sig_carry.read()<<endl;
    return 0;
}