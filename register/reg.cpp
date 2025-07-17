#include<systemc.h>

SC_MODULE(reg_4)
{
	sc_in<sc_uint<4>> in;
	sc_out<sc_uint<4>> outreg;
	sc_in<bool> reset;
	sc_in<bool> enable;
	sc_in<bool> clk;
	
	void process()
	{
	   while(true){
	   wait();
		if(reset.read())
		{
			outreg.write(0);
		}
		else if(enable.read())
		{
			outreg.write(in.read());
		}
		}
	}
	
	SC_CTOR(reg_4)
	{
		SC_CTHREAD(process,clk.pos());
	}
	
};
int sc_main(int argc,char* argv[])
{
    sc_clock clksig("clk",20,SC_NS);
    sc_signal<bool> resetsignal,enablesignal;
    sc_signal<sc_uint<4>> regsignal,outregsignal;
    reg_4 reg("reg");
    
    reg.clk(clksig);
    reg.reset(resetsignal);
    reg.enable(enablesignal);
    reg.in(regsignal);
    reg.outreg(outregsignal);

    //  Apply Reset
    resetsignal = 1;
    enablesignal = 1;
    regsignal = 0b1010;
    sc_start(20, SC_NS);
    cout << "TC1"<< outregsignal.read() << endl;

    // Load value when enabled
    resetsignal = 0;
    regsignal = 0b0110;
    sc_start(20, SC_NS);
    cout << "TC2 " << outregsignal.read() << endl;

    // Change input but disable enable 
    enablesignal = 0;
    regsignal = 0b1111;
    sc_start(20, SC_NS);
    cout << "TC3 " << outregsignal.read() << endl;

    //Re-enable and change value
    enablesignal = 1;
    regsignal = 0b1001;
    sc_start(20, SC_NS);
    cout << "TC4  " << outregsignal.read() << endl;

    // reset again ----
    resetsignal = 1;
    sc_start(20, SC_NS);
    cout << "TC5 " << outregsignal.read() << endl;

    return 0;
}
