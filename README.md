# LAB3
### 1. 
./raceCondition 10 1 1
40 answer should be 40

./raceCondition 10000 1 1
40000 answer should be 40000

./zRunMultipleTimes.sh ./raceCondition 1 1 1 10000 | grep "2 answer"
Teoretic ar trebui sa obtin 2 answer should be 4 in cazul in care 
ambele thread-uri modifica simultan variabila 'a'

### 2.
./testCorrectnessIntensive.sh ./raceCondition-seq ./raceCondition 1 50
The result of your parallel program is
======================================
4 answer should be 4
======================================
Running intensive correctness test with threads
Test 1/50
----------
Test 46/50
Test 47/50
Test 48/50
Test 49/50
Test 50/50
Output correct on intensive test

-La fel ca in cazul ex1

### 6. 
un thread obtine lock ul pe mutex in timp ce celalalt asteapta pana devine disponibil

### 7. 
cele doua threaduri isi tin resursele ocupate reciproc
thread 1 pune lock pe mutexA si thread 2 pune lock pe mutexB
cand thread 1 incearca sa puna lock pe mutex B n o sa poata pentru ca thread 2 il are deja si vice versa

da, chiar si dupa eliminarea sleep urilor mai putem intalni acest fenomen

### 8. 
thread 1 pune lock si blocheaza stdout prin intermediul printf deci celalalt thread nu se poate executa pana cand thread 1 nu face unlock

### 9 & 10.
warius@warius-virtual-machine:~/Desktop/AP/3_lab/03$ time ./sumVectorValues 100000 1 1

Sum: 5000050000 

real    0m0,015s
user    0m0,004s
sys     0m0,011s
warius@warius-virtual-machine:~/Desktop/AP/3_lab/03$ time ./sumVectorValues 100000 1 2


Sum: 5000050000 

real    0m0,015s
user    0m0,009s
sys     0m0,006s
