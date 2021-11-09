#define BUFSIZE 256

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

void *downtime(){

    sleep(1);
//TODO: 1st downtime: Do balanceTree here
// Using wrlock due to modifications
// Freeing root at the end to ensure no memory leaks occur
    pthread_rwlock_wrlock(&lock);
    Node *balanced = balanceTree(root);
    freeSubtree(root);
    root = balanced;
    balanced = NULL;
    pthread_rwlock_unlock(&lock);

    sleep(1);
//TODO: 2nd downtime: Do balanceTree here
    pthread_rwlock_wrlock(&lock);
    balanced = balanceTree(root);
    freeSubtree(root);
    root = balanced;
    balanced = NULL;
    pthread_rwlock_unlock(&lock);

    sleep(1);
//TODO: 3rd downtime: Do balanceTree here
    pthread_rwlock_wrlock(&lock);
    balanced = balanceTree(root);
    freeSubtree(root);
    root = balanced;
    balanced = NULL;
    pthread_rwlock_unlock(&lock);

    return NULL;
}


void* ServeClient(char *client){
// TODO: Open the file and read commands line by line
    FILE *fp = fopen(client, "r");
    if (fp){
        char line[BUFSIZE];
        while(fgets(line, BUFSIZE, fp)){
            // TODO: match and execute commands
            char *string = line;
            char *command, *value;
            string = strsep(&string, "\n");
            command = strsep(&string, " ");
            value = strsep(&string, " ");
            // TODO: Handle command: "insertNode <some unsigned int value>"
            // print: "[ClientName]insertNode <SomeNumber>\n"
            // e.g. "[client1_commands]insertNode 1\n"
            //Using wrlock since modifications are made
            if (strcmp(command, "insertNode") == 0){
                pthread_rwlock_wrlock(&lock);
                root = insertNode(root, atoi(value));
                printf("[%s]insertNode<%s>\n", client, value);
                pthread_rwlock_unlock(&lock);
            }
                // TODO: Handle command: "deleteNode <some unsigned int value>"
                // print: "[ClientName]deleteNode <SomeNumber>\n"
                // e.g. "[client1_commands]deleteNode 1\n"
                //Using wrlock since modifications are made
            else if(strcmp(command, "deleteNode") == 0){
                pthread_rwlock_wrlock(&lock);
                root = deleteNode(root, atoi(value));
                printf("[%s]deleteNode<%s>\n", client, value);
                pthread_rwlock_unlock(&lock);
            }
                // TODO: Handle command: "countNodes"
                // print: "[ClientName]countNodes = <SomeNumber>\n"
                // e.g. "[client1_commands]countNodes 1\n"
                // Does not modify the tree so using rdlock instead
                //The thread can acquire the lock if a writer does not hold it
            else if (strcmp(command, "countNodes") == 0){
                pthread_rwlock_rdlock(&lock);
                int count = countNodes(root);
                printf("[%s]countNodes<%d>\n", client, count);
                pthread_rwlock_unlock(&lock);
            }
                // TODO: Handle command: "sumSubtree"
                // print: "[ClientName]sumSubtree = <SomeNumber>\n"
                // e.g. "[client1_commands]sumSubtree 1\n"
                // Does not modify the tree so using rdlock instead
                //The thread can acquire the lock if a writer does not hold it
            else if(strcmp(command, "sumSubtree") == 0){
                pthread_rwlock_rdlock(&lock);
                int sum = sumSubtree(root);
                printf("[%s]sumSubtree<%d>\n", client, sum);
                pthread_rwlock_unlock(&lock);
            }
        }
    }
    fclose(fp);
    return NULL;
}
