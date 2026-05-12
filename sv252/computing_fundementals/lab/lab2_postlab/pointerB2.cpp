bool deleteRow(int**& matrix, int r, int c, int row) {
    // TODO
    if (r <= 0 || c <= 0 || matrix == nullptr || row >= r || row < 0) {return false;}
    if (r == 1 && row == 0) {
        delete[] matrix[0];
        delete[] matrix;
        matrix = nullptr;
        return true;
    }
    
    int** newMatrix = new int*[r-1];
    for (int i = 0; i < r-1; i++) {
        newMatrix[i] = new int[c];
    }
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < c; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    for (int i = row; i < r-1; i++) {
        for (int j = 0; j < c; j++) {
            newMatrix[i][j] = matrix[i+1][j];
        }
    }
    
    matrix = newMatrix;
    return true;
}