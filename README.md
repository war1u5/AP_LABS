# Lab1

### 1. make compile (make clean pentru a sterge executabilul)
### 2. nproc --all
### 3. pasez lui ex3 argumentul 2
### 4. nr de core-uri este limitat de nr de core-uri fizice de pe masina, in 
timp ce thread-urile sunt niste abstractizari
### 5. da, sysconf(_SC_NPROCESSORS_ONLN); va intoarce nr de core-uri al 
respectivului device => mai multe thread-uri
### 6. functia printf() este buffered. codul se executa asa repede deci 
nu-si consuma cuanta de timp
### 8. cat /proc/sys/kernel/threads-max
