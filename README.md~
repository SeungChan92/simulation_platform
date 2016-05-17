# Simulation Platform

By SeungChan An (Inha University)

This program allow user to easily run, and manage simulations. Our server program cooperate with every our client programs. And they communicate using protocol. Client can submit simulators (.out or .so) and check status. If you want to submit lots of simulator at the same time, you'd better use 'testbench'. When client submit a simulator, server save it in server-side repository and run it covered with 'measure thread'. Detail flow is described in UML diagram in our package.

### Citing

If you find Simulation Platform useful in your project, please consider citing:

    Author = SeungChan An
    Title = Simulation Platform
    Year = 2016

### Contents
1. [Development Environment](#development-environment)
2. [Installation](#installation)
3. [Run](#run)
4. [Run: Server](#run-server)
5. [Run: Client](#run-client)
6. [Usage](#usage)

### Development Environment

1. OS : ubuntu 14.04 LTS
2. Language : c++, c
3. compiler : g++ 4.8.4 with option '-g', and '-std=c++11'

### Installation

1. Clone the Simulation Platform repository
  ```Shell
  git clone https://github.com/SeungChan92/simulation_platform
  ```

2. It's done. If you want to compile some source yourself, check the Compile section in MANUAL.txt.

### Run

*After successfully completing [installation](#installation)*, you'll be ready to run it.

You will run server and client program step by step.

### Run: Server
	(1) Move to the directory you compiled or downloaded server program on.
		$ cd [directory you downloaded my source files in]

	(2) Server collaborate with all client program. So first run the server.
		$ ./server.out [port_no] [numberOf_threads]

			+ replace [port_no]		to the number you want to open. (maybe 40000)
			+ replace [numberOf_threads] 	to the number you want to keep in thread pool. (maybe 10) 
	
	(3) Open a new terminal for client program. Maybe on another computer or same one.

### Run: Client

*you have two choice.*

  #1 submit one simulator and check the result :

	(1) submit a simulator.
		     $ ./sim_submit.out [server_ip] [port_no] [simulator_file_name]
		(ex) $ ./sim_submit.out 127.0.0.1 40000 ./simulator/simulator_dynamic.out

			+ replace [server_ip]	to your server ip. (maybe 127.0.0.1)
			+ replace [port_no]	to the number you opened. (maybe 40000)
			+ replace [simulator_file_name] to the name of a runnable file which is in the same directory with client programs.
							(test with : './simulator/simulator_dynamic.out' in this package)

	(2) check the result 
		$ ./sim_status.out [server_ip] [port_no] [job_no]

			+ replace [server_ip]	to the same with above one - (1)
			+ replace [port_no]	to the same with above one - (1)
			+ replace [job_no]	to the number of your job. When you submit a simulator, we receive job_no on the terminal.
						(maybe 1)

  #2 use testbench :

	(1) execute testbench.
		$ ./testbench.out

	(2) type options.
		+ server IP : your server ip. (maybe 127.0.0.1)
		+ server port number : the number you opened. (maybe 40000)
		+ file path : absolute path of a runnable file. (test with 	: ./simulator/simulator_dynamic.out)
								(or		: ./simulator/simulator_dynamic.so)
		+ number of submit : How many times do you want to submit this simulator. (maybe 5 or 20)

	(3) you will see progress.
		+ process status
			+ R : the process run this job is running.
			+ E : the process run this job is over.

### Usage

You can check elapsed time of your simulator on various conditions. You can change condition like:
    
+ number of threads run simultaneously.
+ run on process or thread
