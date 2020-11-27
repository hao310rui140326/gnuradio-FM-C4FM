


default:
	ps -axjf |grep python*

clean:
	killall python2  python3  ac4fm_tx.sh

start:
	python2 ./c_start.py

stop:
	python2 ./c_stop.py


