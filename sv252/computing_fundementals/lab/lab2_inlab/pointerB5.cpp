int** transposeMatrix(int** matrix, int r, int c) {
    // TODO
    if (matrix == nullptr || r <= 0 || c <= 0) {return nullptr;}
    
    int** newMatrix = new int*[c];
    for (int i = 0; i < c; i++) {
        newMatrix[i] = new int[r];
    }
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            newMatrix[j][i] = matrix[i][j];
        }
    }
    
    return newMatrix;
}