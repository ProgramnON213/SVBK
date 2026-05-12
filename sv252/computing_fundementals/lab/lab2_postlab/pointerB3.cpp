bool deleteCol(int**& matrix, int r, int c, int col) {
    // TODO
    if (r <= 0 || c <= 0 || matrix == nullptr || col >= c || col < 0) {return false;}
    if (c == 1 && col == 0) {
        delete[] matrix[0];
        delete[] matrix;
        matrix = nullptr;
        return true;
    }
    
    int** newMatrix = new int*[r];
    for (int i = 0; i < r; i++) {
        newMatrix[i] = new int[c-1];
    }
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
        for (int j = col; j < c-1; j++) {
            newMatrix[i][j] = matrix[i][j+1];
        }
    }
    
    matrix = newMatrix;
    return true;
}