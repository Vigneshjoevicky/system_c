#include<systemc.h>

SC_MODULE(demux)
{
	sc_in<bool> input;
	sc_in<sc_uint<2>> selector;
	sc_out<bool> out1,out2,out3,out4;
	
	void process()
	{
	
	    out1.write(0);
        out2.write(0);
        out3.write(0);
        out4.write(0);

		switch(selector.read())
		{
			case 0 :
			out1.write(input.read());
			break;
			
			case 1 :
			out2.write(input.read());
			break;
			
			case 2 :
			out3.write(input.read());
			break;
			
			case 3 :
			out4.write(input.read());
			break;
		}
	}
	SC_CTOR(demux)
	{
		SC_METHOD(process);
		sensitive<<input<<selector;
	}
	
};
int sc_main(int argc,char* argv[])
{
	sc_signal<bool> inputsignal,out1sig,out2sig,out3sig,out4sig;
	sc_signal<sc_uint<2>> selectorsig;
	demux dm("dm");
	dm.input(inputsignal);
	dm.out1(out1sig);
	dm.out2(out2sig);
	dm.out3(out3sig);
	dm.out4(out4sig);
	dm.selector(selectorsig);
	
	inputsignal=1;
	selectorsig=3;
	
	sc_start(10,SC_NS);
	cout<<out1sig.read()<<out2sig.read()<<out3sig.read()<<out4sig.read()<<endl;
	
	return 0;
}