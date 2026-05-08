void addElement(int*& arr, int n, int val, int index) {
    // TODO
    int* res = new int[n+1];
    for (int i = 0; i < index; i++) {
        res[i] = arr[i];
    }
    res[index] = val;
    for (int j = index; j < n; j++) {
        res[j+1] = arr[j];
    }
    arr = res;
}
