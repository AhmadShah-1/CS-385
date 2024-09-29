

int seq_search(int array[], const int n, int key) {
    for(int i = 0; i < n; i++) {
        if(array[i] == key) {
            return i;
        }
    }
    return -1;
}
