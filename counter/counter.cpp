#include<systemc.h>

SC_MODULE(counter)
{
	sc_in<bool> in;
	sc_out<sc_uint<4>> out;
	sc_in<bool> clk,reset;
	
	void behaviour()
	{
	    sc_uint<4> count=0;


		while(true)
		{
			
			if(reset.read())
			{
				count=0;
			}
			else if(in.read())
			{
				count=count+1;
				
			}
		    out.write(count);
			wait();
		}
	}
	
	SC_CTOR(counter)
	{
		SC_CTHREAD(behaviour);
		sensitive<<clk.pos();
	}
};
int sc_main(int argc,char* argv[])
{
	sc_signal<sc_uint<4>> outsignal;
	sc_signal<bool> resetsignal,insignal;
	sc_clock clksignal("clock",10,SC_NS);
	counter incrementer("incrementer");
	incrementer.in(insignal);
	incrementer.out(outsignal);
	incrementer.reset(resetsignal);
	incrementer.clk(clksignal);
	
	resetsignal=1;insignal=0;
	 sc_start(50,SC_NS);
	 cout<<outsignal.read()<<endl;
	
	
	resetsignal=0;insignal=1;
	sc_start(100,SC_NS);
	cout<<outsignal.read()<<endl;
    
	cout << "SystemC Version: " << sc_version() <<endl;
	return 0;
	
	
}