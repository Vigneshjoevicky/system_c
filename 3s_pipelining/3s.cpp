#include<systemc.h>

using namespace std;
struct instructions
{
	string opcode;
	int operand_1;
	int operand_2;
	int result;
	
};
// ostream &operator<<(ostream &os, const instructions &instr)
// {
//     return os;
// }
ostream &operator<<(ostream &os, const instructions &instr)
{
    os << "[Opcode: " << instr.opcode
          << ", Operand 1: " << instr.operand_1
       << ", Operand 2: " << instr.operand_2
         << ", Result: " << instr.result << "]";
    return os;
}


instructions array_in[5]={ {"add",1,2},
                        {"sub",3,2},
	                    {"mul",5,2},
						{"mod",10,2},
						{"and",1,2}
                       };
					   
SC_MODULE(fetch_stage)
{
	sc_fifo_out<instructions> instruct;
	sc_in<bool> clk;
	
	SC_CTOR(fetch_stage)
	{
		SC_THREAD(fetch_process);
	}
	
	void fetch_process()
	{
	    
		for(int i=0;i<5;i++)
		{
			wait(clk.posedge_event());
			instruct.write(array_in[i]);
			//cout<<sc_time_stamp()<<" fetching...."<<" "<<array_in[i].opcode<<" "<<array_in[i].operand_1<<" "<<array_in[i].operand_2<<" "<<endl;
			cout << sc_time_stamp() << " fetching.... " << array_in[i] << endl;

		}
	}
	
};

SC_MODULE(decode_stage)
{
	sc_fifo_in<instructions> fin;
	sc_fifo_out<instructions> fout;
	sc_in<bool> clk;

	
	SC_CTOR(decode_stage)
	{
		SC_THREAD(decode_process);
		
	}
	void decode_process()
	{
	  while(1)
	  {
	  	wait(clk.posedge_event());
		instructions instr=fin.read();
		 fout.write(instr);
		 cout<<sc_time_stamp()<<" decoding ...."<<instr.opcode<<" "<<instr.operand_1<<" "<<instr.operand_2<<" "<<endl;
	  }
		
	}
};

SC_MODULE(execute_stage)
{

    sc_fifo_in<instructions> ex_in;
	sc_in<bool> clk; 
	SC_CTOR(execute_stage)
	{
		SC_THREAD(execute_process);
	}
	void execute_process()
	{
	while(1)
	{
		wait(clk.posedge_event());
		instructions instr=ex_in.read();
		
		if(instr.opcode == "add")
		{
			instr.result=instr.operand_1 + instr.operand_2;
			cout<<sc_time_stamp()<<" "<<" result for add "<<instr.result<<endl;
		}
		if(instr.opcode == "sub")
		{
			instr.result=instr.operand_1 - instr.operand_2;
			cout<<sc_time_stamp()<<" "<<" result for sub "<<instr.result<<endl;
		}
		
		if(instr.opcode == "mul")
		{
			instr.result=instr.operand_1 * instr.operand_2;
			cout<<sc_time_stamp()<<" "<<" result for mul "<<instr.result<<endl;
		}
		
		if(instr.opcode == "mod")
		{
			instr.result=instr.operand_1 % instr.operand_2;
			cout<<sc_time_stamp()<<" "<<" result for modulus "<<instr.result<<endl;
		}
		if(instr.opcode == "and")
		{
			instr.result=instr.operand_1 & instr.operand_2;
			cout<<sc_time_stamp()<<" "<<" result for and "<<instr.result<<endl;
		}
	}
		
    }
	
};

int sc_main(int,char*[])
{
	fetch_stage fetch("fetch");
	decode_stage decode("decode");
	execute_stage execute("execute");
	

	sc_clock clock("clk",1,SC_NS);
	
	fetch.clk(clock);
	decode.clk(clock);
	execute.clk(clock);
	
	sc_fifo<instructions> fetch_to_decode_fifo(5);
    sc_fifo<instructions> decode_to_execute_fifo(5);
	
	fetch.instruct(fetch_to_decode_fifo);
	decode.fin(fetch_to_decode_fifo);
	decode.fout( decode_to_execute_fifo);
	execute.ex_in( decode_to_execute_fifo);
	
	sc_start(20,SC_NS);
	return 0;
	
}