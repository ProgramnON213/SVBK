int** insertCol(int**& matrix, int r, int c, int* colArr, int col) {
    // TODO
    if (r < 0 || c < 0) {return nullptr;}
    if (colArr == nullptr || col > c || col < 0) {return matrix;}
    
    int** newMatrix = new int*[r];
    for (int i = 0; i < r; i++) {
        newMatrix[i] = new int[c + 1];
    }
    
    if (matrix == nullptr || r == 0 || c == 0) {
        for (int i = 0 ; i < r; i++) {
            newMatrix[i][0] = colArr[i];
        }
    }
    else {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < col; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
        newMatrix[i][col] = colArr[i];
        for (int j = col; j < c; j++) {
            newMatrix[i][j+1] = matrix[i][j];
        }
    }
    }
    
    for (int i = 0; i < r; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    matrix = newMatrix;
    return newMatrix;
}