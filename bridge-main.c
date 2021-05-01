/****************************************************************
 * Name(s)  Patrick Charlton                                    *
 * Box(s):  E189                                                *
 * Assignment name Test: Wagons Lab                             *
 *      (25% off if name/number does not match assignment)      *
 * Assignment for Tuesday April 16, 2019;                       *
 ***************************************************************/

/* **************************************************************
 * Academic honesty certification:                              *
 *   Written/online sources used:                               *
 *   Silberschatz, Abraham. Operating Systems Concepts. 9th     *
 *   edition                                                    *
 *                                                              *
 *   http://www.cs.grinnell.edu/~walker/courses/451.sp19-       *
 *   willamette/labs/lab-semaphores.php                         *
 *   Help obtained                                              *
 *     Professor Henry Walker                                   *
 *   My/our signature(s) below confirms that the above list of  *
 *  sources is complete AND that I/we have not talked to        *
 *       anyone else                                            *
 *   (e.g., CSC 161 students) about the solution to this        *
 *  problem                                                     *
 *                                                              *
 *   Signature:                                                 *
 *                                                              *
 ***************************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>


/* Fix loop
 shared mem
 print arrival time
 print duration to cross */

#define BUF_SIZE 5            /* logical size of buffer */
#define SHARED_MEM_SIZE (BUF_SIZE+2)*sizeof(int) /* size of shared memory */

//Serves as Semaphore and shm key
key_t semkey = 0xFA2B;

//the mutex,  North to South semaphores, and vice versa
//Same declaration as psudocode
#define mutex    0
#define semtoSouth   1
#define semtoNorth   2
#define semnum    3
//The Wagons going to South and Wagons going to A

#define wagontoSouth    1
#define wagontoNorth    0

//Stalltime between crossing for empty loop iterations
#define stalltime    5000
#define crosstime    10

#define debug 1//Detailed Crossing info

void wagonfork(int direction);//New Wagon process

//Wagon going toward North and South respectively
void goNorth();
void goSouth();

//Semaphores used
void semWait(int semid, int semno);
void semSignal(int semid, int semno);
int createSem(int value);

//Stall function for waiting for blank loop iterations
void stall(int iterations);

int get_semid(key_t semkey);
int get_shmid(key_t shmkey);

struct varshare {//Memory struct to store all crossing, North and South variable
    int XingCnt;
    int XedCnt;
    int toaWaitCnt;
    int tobWaitCnt;
    
    enum {None, aBnd, bBnd} XingDir;
};

void debugprint(struct varshare * shared); //It doesn't work for some reason without this

int main(void) {
    
    caddr_t currTime;   /* shared memory base address */
    
    /* set up shared memory segment */
    currTime=mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE,
                  MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (currTime == (caddr_t) -1)
    { perror ("error in mmap while allocating shared memory\n");
        exit (1);
    }
    
    printf("Current PID: %d \n", getpid());//Starting PID
    fflush(stdout);
    
    union semun semval;
    //union semval;
    
    unsigned short semInitVal[semnum];
    semInitVal[mutex] = 1;
    semInitVal[semtoSouth] = 0;
    semInitVal[semtoNorth] = 0;
    semval.array = semInitVal;
    //semun.array = semInitVal;
    
    int semid = get_semid((key_t)semkey);
    if (semctl(semid, mutex, SETALL, semval) == -1) {
        perror("semctl failed");
        exit(EXIT_FAILURE);
    }
    int shmid = get_shmid((key_t)semkey);
    struct varshare * varshared = shmat(shmid,0,0);
    
    //Initialize to null
    varshared->XingCnt = 0;
    varshared->XedCnt = 0;
    varshared->toaWaitCnt = 0;
    varshared->tobWaitCnt = 0;
    varshared->XingDir = None;
    
    int numberofWagons;
    srand(time(NULL));
    while (numberofWagons < 30) {
        
        // Generate direction - North or South
        int * direction= rand() % 2;
        //printf("Wagon %d waiting going to the %d side of the bridge, starting at %d\n", wagonid, direction, *currTime);
        
        // Generate wagon trip duration - 3 to 6 minutes
        int * duration = rand() % 4;
        
        //Generate wagon start time - arrive every 1 to 4 minutes
        int * arrival = rand() % 4;
        
        pid_t child;
        child = fork();
        if (child == -1){
            perror ("Fork Failure");
            exit(EXIT_FAILURE);
        }
        
        else if (child == 0){
            if (direction == wagontoNorth) {
                goNorth();
            }
            else if (direction == wagontoSouth) {
                goSouth();
            }
            else{
                printf ("Invalid wagon \n");
                fflush(stdout);
                exit(EXIT_FAILURE);
            }
            wait(NULL);
        }
        else
            return 0;
    }
    
    /*
     for (int j = 0; j < i; j++) {
     wait(NULL);
     } */
    
    printf("That's all folks!\n");
    fflush(stdout);
    if (shmdt(varshared) == -1) {
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }
    
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        perror("shmctrl failed");
        exit(EXIT_FAILURE);
    }
    
    if (semctl(semid, mutex, IPC_RMID, semval) == -1) {
        perror("semctl failed");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}


void debugprint(struct varshare *shared){
    if(debugprint > 0){
        int XingCnt;
        int XedCnt;
        int toaWaitCnt;
        int tobWaitCnt;
        enum {None, aBnd, bBnd} XingDir;
        
        XingCnt = shared->XingCnt;
        XedCnt = shared->XedCnt;
        toaWaitCnt = shared->toaWaitCnt;
        tobWaitCnt = shared->tobWaitCnt;
        XingDir = shared->XingDir;
        
        /* printf("PID: %d | XingCnt = %d, XedCnt = %d, toaWaitCnt = %d, tobWaitCnt = %d, Dir = %d\n",
         getpid(), XingCnt, XedCnt, toaWaitCnt, tobWaitCnt, XingDir); */
        fflush(stdout);
    }
}

void goNorth(void){
    printf("PID: %d \n Wagon Crossing to North\n", getpid());
    fflush(stdout);
    
    int semid = get_semid((key_t)semkey);
    int shmid = get_shmid((key_t)semkey);
    struct varshare * varshared = shmat(shmid, 0, 0);
    
    printf("Waiting on Mutex for pass to North\n");
    fflush(stdout);
    semWait(semid, mutex);
    printf("Mutex Passed \n");
    fflush(stdout);
    
    if ((varshared->XingDir == aBnd || varshared->XingDir == None) &&
        varshared->XingCnt < 5 &&
        (varshared->XingCnt + varshared->XingCnt < 10 || varshared->tobWaitCnt == 0) &&
        varshared->toaWaitCnt == 0){
        printf ("Crossing to North about to start\n");
        fflush(stdout);
        varshared->XingDir = aBnd;
        varshared->XingCnt++;
        
        debugprint(varshared);
        printf("North signaling mutex \n");
        fflush(stdout);
        semSignal(semid, mutex);
    }
    
    else{
        printf("North is now supposed to wait\n");
        fflush(stdout);
        varshared->toaWaitCnt++;
        debugprint(varshared);
        
        printf("Signalling mutex (NS)\n");
        fflush(stdout);
        printf("ONE");
        semSignal(semid, mutex);
        printf("TwoE");
        semWait(semid, semtoNorth);
        
        printf("North was waiting until signal call. Signal has been called \n");
        fflush(stdout);
        varshared->toaWaitCnt--;
        varshared->XingCnt++;
        varshared->XingDir = aBnd;
        
        debugprint(varshared);
        
        if (varshared->toaWaitCnt > 0 &&
            varshared->XingCnt < 5 &&
            (varshared->XedCnt+ varshared->XingCnt < 10 ||
             varshared->tobWaitCnt == 0)){
                printf("Signaling wagon behind current wagon \n");
                printf("Wagon about to cross\n");
                fflush(stdout);
                semSignal(semid, semtoNorth);
            }
        
        else{
            printf("Wagon about to cross \n");
            fflush(stdout);
            debugprint(varshared);
            printf("Signaling Mutex\n");
            fflush(stdout);
            semSignal(semid, mutex);
        }
    }
    
    printf ("Bridge Crossing\n");
    fflush(stdout);
    stall(crosstime);
    
    printf("Bridge Crossed. Waiting for mutex \n");
    fflush(stdout);
    semWait(semid, mutex);
    printf("Mutex Passed\n");
    fflush(stdout);
    varshared->XedCnt++;
    varshared->XingCnt--;
    
    if (varshared->toaWaitCnt!= 0 &&
        (varshared->XingCnt + varshared->XedCnt < 10 ||
         varshared->tobWaitCnt == 0)){
            debugprint(varshared);
            printf("Signaling Wagon Crossing to North\n");
            semSignal(semid, semtoNorth);
        }
    
    else if(varshared->XingCnt == 0 &&
            varshared->tobWaitCnt !=0 &&
            (varshared->toaWaitCnt == 0 ||
             varshared->XedCnt + varshared->tobWaitCnt >= 10)){
                printf("Changing Direction to turn toward South\n");
                printf("Signaling Wagon waiting to cross to South\n");
                fflush(stdout);
                
                varshared->XingDir = bBnd;
                varshared->XedCnt = 0;
                debugprint(varshared);
                semSignal(semid, semtoSouth);
            }
    
    else if(varshared->XingCnt == 0 &&
            varshared->toaWaitCnt == 0 &&
            varshared -> tobWaitCnt == 0){
        printf("Crossing Direction set to none. No more Wagons waiting \n");
        fflush(stdout);
        varshared->XingDir = None;
        varshared->XedCnt = 0;
        
        debugprint(varshared);
        printf("Signaling Mutex\n");
        fflush(stdout);
        semSignal(semid, mutex);
    }
    
    else
    {
        debugprint(varshared);
        printf("Signaling Mutex\n");
        fflush(stdout);
        semSignal(semid, mutex);
    }
    
    if(shmdt(varshared)==-1){
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }
    
    //exit(EXIT_SUCCESS);
}

void goSouth(void){
    printf("PID: %d \n Wagon Crossing to South\n", getpid());
    fflush(stdout);
    
    int semid = get_semid((key_t)semkey);
    int shmid = get_shmid((key_t)semkey);
    struct varshare * varshared = shmat(shmid, 0, 0);
    
    printf("Waiting on Mutex for pass to South\n");
    fflush(stdout);
    semWait(semid, mutex);
    printf("Mutex Passed");
    fflush(stdout);
    debugprint(varshared);
    
    if ((varshared->XingDir == bBnd || varshared->XingDir == None) &&
        varshared->XingCnt < 5 &&
        (varshared->XingCnt + varshared->XingCnt < 10 || varshared->toaWaitCnt == 0) &&
        varshared->tobWaitCnt == 0){
        printf ("Crossing to South about to start\n");
        fflush(stdout);
        varshared->XingDir = bBnd;
        varshared->XingCnt++;
        
        debugprint(varshared);
        printf("South signaling mutex \n");
        fflush(stdout);
        semSignal(semid, mutex);
    }
    
    else{
        printf("South is now supposed to wait\n");
        fflush(stdout);
        varshared->tobWaitCnt++;
        debugprint(varshared);
        
        printf("Signaling mutex \n");
        fflush(stdout);
        semSignal(semid, mutex);
        semWait(semid, semtoSouth);
        
        printf("South was waiting until signal call. Signal has been called \n");
        fflush(stdout);
        varshared->tobWaitCnt--;
        varshared->XingCnt++;
        varshared->XingDir = bBnd;
        
        debugprint(varshared);
        
        if (varshared->tobWaitCnt > 0 &&
            varshared->XingCnt < 5 &&
            (varshared->XedCnt+ varshared->XingCnt < 10 ||
             varshared->toaWaitCnt == 0)){
                printf("Signaling Wagon behind current Wagon \n");
                printf("Wagon about to cross\n");
                fflush(stdout);
                semSignal(semid, semtoSouth);
            }
        
        else{
            printf("Wagon about to cross \n");
            fflush(stdout);
            debugprint(varshared);
            printf("Signaling Mutex\n");
            fflush(stdout);
            semSignal(semid, mutex);
        }
    }
    
    printf (" Bridge Crossing\n");
    fflush(stdout);
    stall(crosstime);
    
    printf("Bridge Crossed. Waiting for mutex \n");
    fflush(stdout);
    semWait(semid, mutex);
    printf("Mutex Passed\n");
    fflush(stdout);
    varshared->XedCnt++;
    varshared->XingCnt--;
    
    if (varshared->tobWaitCnt!= 0 &&
        (varshared->XingCnt + varshared->XedCnt < 10 ||
         varshared->tobWaitCnt == 0)){
            debugprint(varshared);
            printf("Signaling Wagon Crossing to South\n");
            semSignal(semid, semtoSouth);
        }
    
    else if(varshared->XingCnt == 0 &&
            varshared->toaWaitCnt !=0 &&
            (varshared->tobWaitCnt == 0 ||
             varshared->XedCnt + varshared->tobWaitCnt >= 10)){
                printf("Changing Direction to turn toward North\n");
                varshared->XingDir = aBnd;
                varshared->XedCnt = 0;
                debugprint(varshared);
                printf("Signaling Wagon waiting to cross to North\n");
                fflush(stdout);
                semSignal(semid, semtoNorth);
            }
    
    else if(varshared->XingCnt == 0 &&
            varshared->toaWaitCnt != 0 &&
            varshared -> tobWaitCnt == 0){
        printf("Crossing Direction set to none. No more Wagons waiting \n");
        fflush(stdout);
        varshared->XingDir = None;
        varshared->XedCnt = 0;
        
        debugprint(varshared);
        printf("Signaling Mutex\n");
        fflush(stdout);
        semSignal(semid, mutex);
    }
    
    else
    {
        debugprint(varshared);
        printf("Signaling Mutex\n");
        fflush(stdout);
        semSignal(semid, mutex);
    }
    
    if(shmdt(varshared)==-1){
        perror("shmdt failed");
        exit(EXIT_FAILURE);
    }
    
    //exit(EXIT_SUCCESS);
}

void stall(int iterations){
    int i;
    for (i = 0; i< iterations; i++){
        ;
    }
}

void semWait(int semid, int semno){
    struct  sembuf waitbuf;
    
    waitbuf.sem_num = semno;
    
    waitbuf.sem_op = -1;
    waitbuf.sem_flg = 0;
    
    if (semop(semid, &waitbuf, 1) == -1){
        perror("semWait failed");
        exit(EXIT_FAILURE);
    }
}

void semSignal(int semid, int semno){
    struct sembuf sigBuf;
    
    sigBuf.sem_num = semno;
    
    sigBuf.sem_op = 1;
    sigBuf.sem_flg = 0;
    
    if (semop(semid, &sigBuf, 1) == -1) {
        perror("semSignal failed");
        exit(EXIT_FAILURE);
    }
}

int get_semid(key_t semkey){
    int value = semget(semkey, semnum, 0777 | IPC_CREAT);
    
    if (value == -1){
        perror("semget failed");
        exit(EXIT_FAILURE);
    }
    
    return value;
}

int get_shmid(key_t shmkey){
    int value = shmget(shmkey, sizeof(struct varshare), 0777 | IPC_CREAT);
    
    if (value == -1){
        perror("semget failed");
        exit(EXIT_FAILURE);
    }
    
    return value;
}
