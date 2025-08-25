
#include<systemc.h>
#include<iostream>
SC_MODULE(full_adder)
{
	sc_in<bool> a,b,cin;
	sc_out<bool> sum,carry;
	
	void operation()
	{
		int ans,cout;
		ans= a.read()^ b.read()^ cin.read();
		cout=(a.read() & b.read()) | (cin.read()&(a.read()^b.read()));
		
		sum.write(ans);
		carry.write(cout);
	}
	
	SC_CTOR(full_adder)
	{
		SC_METHOD(operation);
		sensitive<<a<<b<<cin;
	}
};

int sc_main(int argc,char* argv[])
{
	sc_signal<bool> a_signal,b_signal,cin_signal,sum_signal,carry_signal;
	
	full_adder fadd("full_adder");
	fadd.a(a_signal);
	fadd.b(b_signal);
	fadd.cin(cin_signal);
	fadd.sum(sum_signal);
	fadd.carry(carry_signal);
	
	a_signal=0,b_signal=0,cin_signal=0;
	sc_start(10,SC_NS);
	cout<<"0 0 0	: "<<sum_signal.read()<<"	"<<carry_signal.read()<<endl;
	
	a_signal=0,b_signal=0,cin_signal=1;
	sc_start(10,SC_NS);
	cout<<"0 0 1	: "<<sum_signal.read()<<"	"<<carry_signal.read()<<endl;
	
	a_signal=0,b_signal=1,cin_signal=0;
	sc_start(10,SC_NS);
	cout<<"0 1 0	: "<<sum_signal.read()<<"	"<<carry_signal.read()<<endl;
	
	return 0;
	
}