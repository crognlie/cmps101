typedef struct PriorityQueue* PriorityQueueRef;

/* Creation & Destruction */
PriorityQueueRef newPriorityQueue(int, double *);
void freePriorityQueue(PriorityQueueRef *);

/* Access Methods */
int getNumElements(PriorityQueueRef);
int getMin(PriorityQueueRef);
int inQueue(PriorityQueueRef, int);

/* Manipulation Methods */
void deleteMin(PriorityQueueRef);
void decreaseKey(PriorityQueueRef, int, double);

/* Other Methods */
void printPriorityQueue(PriorityQueueRef, FILE*);
