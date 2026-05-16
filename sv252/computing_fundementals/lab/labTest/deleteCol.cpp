#include <iostream>
#include <iomanip>
using namespace std;

bool deleteCol(int** matrix, int r, int c, int col) {
    if (matrix == nullptr || r <= 0 || c <= 0 || col < 0 || col > c) {return false;}
    if (c == 1 && col == 0) {
        delete[] matrix[0];
        delete[] matrix;
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

    return true;
}

int main() {
    int r = 3, c = 4;
    
    // 1. Cấp phát và khởi tạo mảng động 2 chiều
    int** matrix = new int*[r];
    for (int i = 0; i < r; ++i) {
        matrix[i] = new int[c];
        for (int j = 0; j < c; ++j) {
            matrix[i][j] = i * c + j + 1; // Khởi tạo dữ liệu mẫu: 1, 2, 3...
        }
    }

    // In ma trận ban đầu
    cout << "Ma tran ban dau (" << r << "x" << c << "):\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    // 2. Kiểm thử: Thực hiện xoá cột có index 1 (cột thứ 2)
    int colToDelete = 1;
    cout << "\n-> Tien hanh xoa cot index " << colToDelete << "...\n";
    
    bool result = deleteCol(matrix, r, c, colToDelete);

    if (result) {
        // BẮT BUỘC: Tự giảm c ở main vì hàm xoá không nhận tham chiếu (int& c)
        c--; 
        cout << "Xoa thanh cong! Ma tran hien tai (" << r << "x" << c << "):\n";
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cout << setw(3) << matrix[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        // Trả về false do vị trí lỗi hoặc do đã xoá cột duy nhất cuối cùng
        cout << "Da xoa di cot cuoi cung. Mang hai chieu tro thanh nullptr.\n";
        
        // BẮT BUỘC: Tự gán nullptr do hàm không nhận tham chiếu (int**& matrix)
        matrix = nullptr; 
        c = 0;
    }

    // 3. Quét dọn - Giải phóng bộ nhớ trước khi thoát
    if (matrix != nullptr) {
        for (int i = 0; i < r; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }

    return 0;
}