
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/**********************************************
 *                                            *
 * Configuration settings                     *
 *                                            *
 **********************************************/
#define NPROC (1)     /** number of children processes */
#define MAXLOCKS (10) /** Total available resources (size of the lock table) */
#define MAXCHILDLOCKS                                                                            \
    (4) /** max resource a child can hold before requesting 'release locks' from the LockManager \
         */

pid_t pids[NPROC]; /** Process ids */

enum LockStatus {
    NOTMARKED = 0, /** lock available (no child process owns this lock) */
    MARKED = 1     /** lock reserved (lock is taken by a child) */
};

/*
 * Structure the LockManager holds (this is a single lock)
 */
struct Lock {
    int marked;   /** lock status (MARKED, NOTMARKED) */
    int by_child; /** PID of the process that's holding the lock */
};

/**
 * Array of locks owned by the manager. The manager will parcel out locks
 * to child processes when they request them (if the request is valid).
 */
struct Lock locks[MAXLOCKS]; /** MAXLOCKS locks for the manager */

/**
 * Whether or not there was a deadlock. Returned by CheckForDeadLock() and used by
 * LockManager().
 */
enum deadlock_status {
    NO_DEADLOCK = 0,      /** there is no deadlock */
    DEADLOCK_DETECTED = 1 /** Deadlock detected    */
};

/**
 * Children send this request to the lock manager.
 */
enum LockAction {
    LOCK = 100,   /** Child requests to lock a resource */
    RELEASE = 200 /** Child requests to release all its resources */
};

/**
 * Children send this message to request a lock.
 */
struct msg_requestLock {
    int lockID; /** this a number from 0 up to (MAXLOCKS-1) */
    int Action; /** LockAction (LOCK, RELEASE) */
};

/**
 * Lock manager sends back this response depending on what happened to the request
 */
enum LockRequestStatus {
    GRANTED = 0,     /** The lock has been granted to you. */
    NOT_GRANTED = 1, /** Lock has not been granted. Some else already owns it so wait. */
    YOU_OWN_IT = 2,  /** You already own the lock! */
    PREVENT = 3      /** Deadlock detected! Request is rejected */
};

/**
 * LockManager sends status of request to children.
 */
struct msg_requestStatus {
    int status;   /** LockRequestStatus (GRANTED, NOT_GRANTED, YOU_OWN_IT, PREVENT) */
    int by_child; /** if not granted, who owns it */
};

/**
 * Terminate all child processes. Called at the end to cleanup.
 */
void finish() {
    for (int cid = 0; cid < NPROC; cid++) kill(pids[cid], SIGKILL);
    exit(0);
}

/**
 * Code for the child processes
 */
void child(int child_id, int req, int ack) {
    int count = 0; /* It is used for num of locks and check if we exceed MAXCHILDLOCKS */

    struct msg_requestLock MSG;    /* message from child (me) to parent */
    struct msg_requestStatus STAT; /* message from parent to child (me) */

    /* Set up random number generator using the time as the starting point */
    struct timeval tt;
    (void)gettimeofday(&tt, NULL);
    srand(tt.tv_sec * 1000000 + tt.tv_usec);

    /* Loop until forever, */
    for (;;) {
        MSG.lockID = rand() % MAXLOCKS;
        MSG.Action = LOCK;

        printf("\tChild %d: Requesting lock %d . . .\n", child_id, MSG.lockID);
        fflush(stdout);

        /*
         * Both calls are blocked if there is nothing to do.
         */

        write(req, (char *)&MSG, sizeof(MSG));
        read(ack, (char *)&STAT, sizeof(STAT));

        if (STAT.status == GRANTED) { /* Success got lock */
            count++;
            printf("\tChild %d: Got lock %d (%d).\n", child_id, MSG.lockID, count);
            fflush(stdout);
        }

#ifdef TRACE
        if (STAT.status == GRANTED)
            printf("\tChild %d: Got lock.\n", child_id);
        else if (STAT.status == NOT_GRANTED)
            printf("\tChild %d: Child %d owns this lock.\n", child_id, STAT.by_child);
        else if (STAT.status == YOU_OWN_IT)
            printf("\tChild %d: I own this lock.\n", child_id);

        printf("\tChild %d: Owns %d locks now.\n", child_id, count);
        fflush(stdout);
#endif

        if (STAT.status == NOT_GRANTED) {
            printf("Child %d waiting for lock %d\n", child_id, MSG.lockID);
            fflush(stdout);

            /*
             * I will get it shortly or the LockManager
             * will NOT give it to me to prevent a deadlock.
             */
            read(ack, (char *)&STAT, sizeof(STAT));
            if (STAT.status == GRANTED) {
                count++;
                printf("\tChild %d: Got lock %d (%d).\n", child_id, MSG.lockID, count);
            } else if (STAT.status == PREVENT) {
                printf("CHILD: %d Will try again, (preventing)\n", child_id);
                fflush(stdout);
            } else {
                printf("CHILD: %d    FATAL ERROR\n", child_id);
                fflush(stdout);
                exit(-1);
            }
        }

        if (count >= MAXCHILDLOCKS) {
            /*
             * Child sends request to release all its locks
             */
            printf("\tChild %d: Requesting RELEASE locks.\n", child_id);
            fflush(stdout);

            MSG.Action = RELEASE;
            write(req, (char *)&MSG, sizeof(struct msg_requestLock));

            count = 0;

            sleep(1);
        }

    } /* for(;;) */
} /* child */

/**
 *      ***TODO*** (3)
 * Print the lock table so that YOU see what your program is doing
 */
void PrintLocks() {

for (int i = 0; i < MAXLOCKS; i++){

if(locks[i].marked == MARKED){

printf("FREE,");

}
else{

printf("%d",locks[i].by_child);

}



}





}

/*******************************************************
 *                                                     *
 * LockManager():                                      *
 *               Task to determine deadlock            *
 *               Also to release and give locks        *
 * Terminates when LiveLock is detected  *
 *******************************************************/

int LockManager(int cid, struct msg_requestLock ChildRequest, int respond[NPROC]) {
    struct msg_requestStatus STAT;
    int deadlock = NO_DEADLOCK;

    if (ChildRequest.Action == RELEASE) {
        /*
         *      ***TODO*** (1)
         * Release child's resources.
         */
         locks[ChildRequest.lockID].marked == NOTMARKED;
         locks[ChildRequest.lockID].by_child = NULL;

    } else if (ChildRequest.Action == LOCK) {
        int t_lock;
        t_lock = ChildRequest.lockID;
        if (locks[t_lock].marked == NOTMARKED) {
            /*
             *      ***TODO*** (2)
             * Give requested lock to child
             */
            locks[t_lock].marked == MARKED;
            locks[t_lock].by_child = cid;
   STAT.status = GRANTED;
   
   write(respond[cid], (char *)&STAT, sizeof(STAT));
            PrintLocks();
        } else { /* lock is not free */
            if (locks[t_lock].by_child == cid) {
                /*
                 * Tell child that this lock is already owned
                 * by this (the requestor) child
                 */
                STAT.status = YOU_OWN_IT;
                write(respond[cid], (char *)&STAT, sizeof(STAT));
            } else { /* lock taken by another child */
                /* This should not be possible in this level */
                finish();
            }
        }
    }

    //
    // if ChildRequest.Action is neither RELEASE nor LOCK, you got a protocol error.
    //

    return (deadlock);
}

/******************************************************************
 *
 ******************************************************************/
int main(int argc, char **argv) {
    int listen[NPROC];
    int respond[NPROC];

    struct msg_requestLock ChildRequest;

    /*
     * Arrange for termination to call the cleanup procedure
     */
    signal(SIGTERM, finish);

    /*
     * initialize, don't carre about child
     */
    for (int li = 0; li < MAXLOCKS; li++) {
        locks[li].marked = NOTMARKED;
    }

    /*
     * Initialize pipes and fork the children processes
     */
    for (int cid = 0; cid < NPROC; cid++) {
        int parent_to_child[2];
        int child_to_parent[2];

        /*
         * Create the child -> parent pipe.
         */
        pipe(child_to_parent);
        listen[cid] = child_to_parent[0];
        fcntl(listen[cid], F_SETFL, O_NONBLOCK);

        /*
         * Create the parent -> child pipe.
         */
        pipe(parent_to_child);
        respond[cid] = parent_to_child[1];
        fcntl(respond[cid], F_SETFL, O_NONBLOCK);

        /*
         * Create child process.
         */

        if ((pids[cid] = fork()) == 0) {
            /*
             * *********** Child process code. ***********
             */
            signal(SIGTERM, SIG_DFL);
            close(parent_to_child[1]);
            close(child_to_parent[0]);

            child(cid, child_to_parent[1], parent_to_child[0]);

            _exit(0);
        }

        close(child_to_parent[1]);
        close(parent_to_child[0]);
    }

    int deadlock = NO_DEADLOCK; /* When deadlock occurs, exit     */
    /*
     * For this assignment there will never be a deadlock because our
     * LockManager prevents deadlocks
     */
    while (deadlock != DEADLOCK_DETECTED) {
        for (int cid = 0; cid < NPROC; cid++) {
            int nb = read(listen[cid], (char *)&ChildRequest, sizeof(ChildRequest));
            if (nb == sizeof(ChildRequest)) {
                deadlock = LockManager(cid, ChildRequest, respond);
            }
        }
    }
    }
