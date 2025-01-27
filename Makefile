.PHONY: TaskManager

tm:
	
	gcc src/main.c -o TM.exe  -lgdi32 -mwindows -lcomctl32
	./TM
