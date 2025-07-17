#include<systemc.h>

SC_MODULE(testclk)
{
	sc_in<bool> ck;
	
	void process()
	{
		while(true)
		{
		    wait();
			cout<<"print @ "<<sc_time_stamp()<<"	triggerd"<<endl;
		}
	}		
		
		SC_CTOR(testclk)
		{
		    	SC_THREAD(process);
				sensitive<<ck.pos();
		}
	
	
};

int sc_main(int argc,char* argv[])
{
	sc_clock clock("clk",10,SC_NS);
	
	testclk tclk("tclk");
	
	tclk.ck(clock);
	
	sc_start(100,SC_NS);
	return 0;
}