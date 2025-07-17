#include<systemc.h>

SC_MODULE(flip_flop)
{
	sc_in<bool> clk;
	sc_in<bool> din;
	sc_out<bool> qout;
	sc_in<bool> reset;
	
	
	void process()
	{
		if(reset.read())
		{
			qout.write(0);
		}
		else
		{
			qout.write(din.read());
		}
	}
	
	SC_CTOR(flip_flop)
	{
		SC_METHOD(process);
		sensitive<<clk.pos();
	}
};
int sc_main(int argc,char* argv[])
{
      sc_clock clksig("clksig",10,SC_NS);
	  sc_signal<bool> insignal,outsignal,resetsignal;
	  flip_flop ff("ffd");
	  
	  ff.clk(clksig);
	  ff.reset(resetsignal);
	  ff.din(insignal);
	  ff.qout(outsignal);

    

	  
     
    
     insignal = 1;
    sc_start(20, SC_NS); 
    cout <<sc_time_stamp()<< outsignal.read() << endl;
   
	resetsignal = 1; insignal = 0;
    sc_start(20, SC_NS); 
    cout <<sc_time_stamp()<< outsignal.read() << endl;
    
	insignal = 0;
     sc_start(20, SC_NS); 
     cout << sc_time_stamp()<<outsignal.read() << endl;
   resetsignal = 0; insignal = 1;
     sc_start(20, SC_NS); 
     cout <<sc_time_stamp()<< outsignal.read() << endl;
   
	  return 0;
}