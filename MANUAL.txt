First, extend this window to fullscreen.


0.download
  If you see this text in manual file, maybe you also downloaded all package. If not, you can download source files from github.
	https://github.com/SeungChan92/simulation_platform.git


1.compile
  Note : If you want to just run already compiled program, skip this section.
	- compiler : g++
	- command in terminal
		(1) cd [directory you downloaded my source files in]
server		(2) g++ -g -std=c++11 -pthread server.cpp source/*Server.cpp source/JobManager.cpp source/TP*.cpp -o server.out -ldl
sim_submit	(3) g++ -g -std=c++11 sim_submit.cpp source/*Client.cpp -o sim_submit.out
sim_status	(4) g++ -g -std=c++11 sim_status.cpp source/*Client.cpp -o sim_status.out
testbench	(5) g++ -g -std=c++11 testbench.cpp source/*Client.cpp source/JobManager.cpp -o testbench.out


2.install
  If you compiled or have .out files, all program installed.


3.run
  common :
	(1) Move to the directory you compiled or downloaded server program on.
		$ cd [directory you downloaded my source files in]

	(2) Server collaborate with all client program. So first run the server.
		$ ./server.out [port_no] [numberOf_threads]

			+ replace [port_no]		to the number you want to open. (maybe 40000)
			+ replace [numberOf_threads] 	to the number you want to keep in thread pool. (maybe 10) 
	
	(3) Open a new terminal for client program. Maybe on another computer or same one.

	(4) Move to the directory you compiled or downloaded client programs on.
		$ cd [directory you downloaded my source files in]

  Then you have two choice.

  #1 submit and check result one simulator by one :
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
	(1) execute it.
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
