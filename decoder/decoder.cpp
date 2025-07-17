#include<systemc.h>
SC_MODULE(decoder)
{
	sc_in<sc_uint<2>> input;
	sc_out<bool> d0,d1,d2,d3;
	
	void process()
	{
	    d0.write(0);
		d1.write(0);
		d2.write(0);
		d3.write(0);
	    
		switch(input.read())
		{
			case 0:
			d0.write(1);
			break;
			
			
			case 1:
			d1.write(1);
			break;
			
			
			case 2:
			d2.write(1);
			break;
			
			
			case 3:
			d3.write(1);
			break;
		}
	}
	
	SC_CTOR(decoder)
	{
		SC_METHOD(process);
		sensitive<<input;
	}
};
int sc_main(int argc,char* argv[])
{
	sc_signal<sc_uint<2>> inputsignal;
	sc_signal<bool> d0s,d1s,d2s,d3s;
	
	decoder d("d");
	
	d.input(inputsignal);
	d.d0(d0s);
	d.d1(d1s);
	d.d2(d2s);
	d.d3(d3s);
	
	inputsignal.write(3);
	sc_start(1,SC_NS);
	cout<<d0s.read()<<d1s.read()<<d2s.read()<<d3s.read()<<endl;
	return 0;
}
