#include<systemc.h>
#define add 1
#define mul 2
#define sub 3
#define or1  4
#define and1 5

SC_MODULE(alu_unit)
{
	sc_in<sc_uint<4>> a,b;
	sc_in<sc_uint<4>> opcode;
	sc_out<sc_uint<4>> out;
	
	void behaviour()
	{
		//add-sub-mul-or-and
		
		switch(opcode.read())
		{
			case add:
			out.write(a.read() + b.read());
			break;
			
			case mul:
			out.write(a.read() * b.read());
			break;
			
			case sub:
			out.write(a.read() - b.read());
			break;
			
			case or1:
			out.write(a.read() | b.read());
			break;
			
			case and1:
			out.write(a.read() &  b.read());
			break;
			
			default :
			cout<<"invalid";
            out.write(0);
			
		}
	}
	SC_CTOR(alu_unit)
	{
		SC_METHOD(behaviour);
		sensitive<<a<<b<<opcode;
	}
};

int sc_main(int argc,char* argv[])
{
	sc_signal<sc_uint<4>> asignal,bsignal,opcodesignal,outsignal;
	
	alu_unit alu("alu");
	alu.a(asignal);
	alu.b(bsignal);
	alu.opcode(opcodesignal);
	alu.out(outsignal);
	
	asignal=5;bsignal=5;opcodesignal=1;
	sc_start(10,SC_NS);
    cout<<outsignal.read()<<endl;
	return 0;
}