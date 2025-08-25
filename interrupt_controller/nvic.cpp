#include <systemc.h>

SC_MODULE(button_module)
{
    sc_out<bool> irq;
    int delay;
    SC_HAS_PROCESS(button_module);
    button_module(sc_module_name name,int d):sc_module(name),delay(d)
    {
        SC_THREAD(process);
    }
    void process()
    {
        irq.write(false);
        wait(delay, SC_NS);
        irq.write(true);
        wait(10, SC_NS);
        irq.write(false);
    }
};

SC_MODULE(interrupt_controller)
{
    sc_in<bool> irq_in1,irq_in2,irq_in3;
    sc_out<bool> int_out;
    sc_out<int> vector_out;

    SC_CTOR(interrupt_controller)
    {
        SC_THREAD(watch);
    }

    void watch()
    {
        while (true)
        {
            wait(irq_in1.posedge_event()|irq_in2.posedge_event()|irq_in3.posedge_event());  
            if(irq_in1.read())
            {
                cout << sc_time_stamp() << " ns: interrupt detected" << endl;
               int_out.write(true);
               vector_out.write(1);
               wait(10, SC_NS);
               int_out.write(false);
                vector_out.write(0);
            }


            else if(irq_in2.read())
            {
                cout << sc_time_stamp() << " ns: interrupt detected" << endl;
               int_out.write(true);
               vector_out.write(2);
               wait(10, SC_NS);
               int_out.write(false);
                vector_out.write(0);
            }

            else if(irq_in3.read())
            {
                cout << sc_time_stamp() << " ns: interrupt detected" << endl;
               int_out.write(true);
               vector_out.write(3);
               wait(10, SC_NS);
               int_out.write(false);
                vector_out.write(0);
            }
            
        }
    }
};

SC_MODULE(cpu_module)
{
    sc_in<bool> in_signal;
    sc_in<int> vector_in;

    SC_CTOR(cpu_module)
    {
        SC_THREAD(execution);
        SC_METHOD(i_monitor);
        sensitive << in_signal;
        dont_initialize();
    }

    void ISR1()
    {
        cout << sc_time_stamp() << " ns: CPU executing ISR...111111" << endl;
    }

     void ISR2()
    {
        cout << sc_time_stamp() << " ns: CPU executing ISR...222222" << endl;
    }

     void ISR3()
    {
        cout << sc_time_stamp() << " ns: CPU executing ISR...333333" << endl;
    }

    void execution()
    {
        while (true)
        {
            cout << sc_time_stamp() << " ns: CPU running the main loop" << endl;
            wait(5, SC_NS);
        }
    }

    void i_monitor()
    {
        if (in_signal.read())
        {
            int selector =vector_in.read();
            switch(selector)
            {
                case 1:
                {
                   ISR1();
                   break;
                }
                 case 2:
                {
                    ISR2(); 
                    break;
                }
                 case 3:
                {
                     ISR3();
                     break;
                }
            }
        }
    }
};

int sc_main(int, char *[])
{
    button_module button1("button",10);
     button_module button2("button",20);
      button_module button3("button",30);
    
    cpu_module cpu("cpu");
    interrupt_controller ic("ic");

    sc_signal<bool> irq_signal1,irq_signal2,irq_signal3;
    sc_signal<bool> int_signal;
    sc_signal<int> vector_signal;
    button1.irq(irq_signal1);
    button2.irq(irq_signal2);
    button3.irq(irq_signal3);

    ic.irq_in1(irq_signal1);
    ic.irq_in2(irq_signal2);
    ic.irq_in3(irq_signal3);

    ic.int_out(int_signal);
    ic.vector_out(vector_signal);

    cpu.in_signal(int_signal);
    cpu.vector_in(vector_signal);
    
    sc_start(100, SC_NS);

    return 0;
}

/*The buttons trigger interrupts at different times using delays. 
The interrupt controller handles priority and generates the vector. 
The CPU detects the interrupt through in_signal and executes the corresponding ISR by checking vector_in. 
It's a simple interrupt simulation where SC_METHOD is used for responsiveness and SC_THREAD for continuous main loop execution.*/