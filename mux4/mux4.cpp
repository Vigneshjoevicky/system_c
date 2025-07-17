#include<systemc.h>

SC_MODULE(mux)
{
	sc_in<bool> in0,in1,in2,in3;
	sc_in<sc_uint<2>> selector;
	sc_out<bool> out;
	
	void process()
	{
		switch(selector.read())
		{
			case 0:
			out.write(in0.read());
			break;
			
			case 1:
			out.write(in1.read());
			break;
			
			case 2:
			out.write(in2.read());
			break;
			
			case 3:
			out.write(in3.read());
			break;
			
		
		}
	
	}
		
		SC_CTOR(mux)
		{
			SC_METHOD(process);
			sensitive<<in0<<in1<<in2<<in3<<selector;
		}
};
int sc_main(int argc, char* argv[])
{
	sc_signal<bool> in0s,in1s,in2s,in3s,outs;
	sc_signal<sc_uint<2>> selectsig;
	
	mux mul("mul");
	mul.in0(in0s);
    mul.in1(in1s);
	mul.in2(in2s);
	mul.in3(in3s);
	mul.selector(selectsig);
	mul.out(outs);
	
	in0s=1;in1s=0;in2s=1;in3s=0;
	selectsig=3;
	sc_start(10,SC_NS);
	cout<<outs.read()<<endl;
	return 0;
}