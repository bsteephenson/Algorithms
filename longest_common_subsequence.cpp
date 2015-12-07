#include "iostream"

using namespace std;

enum Direction {DEC_A, DEC_B, DEC_BOTH};

struct LCS_box {
    int length; // length of LCS up to this point
    Direction direction; // represents the direction I need to go to continue the LCS
};

// returns length of LCS, puts contents into buffer
string lcs(string A, string B);

int main() {
    string word1 = "0s0o0m0e0t0h0i0n0g";
    string word2 = "s1o1m1e1t1h1i1n1g1";

    cout << "Enter two words" << endl;
    cin >> word1 >> word2;

    cout << lcs(word1, word2) << endl;
}

string lcs(string A, string B)
{
    
    // figure out length of LCS of each A[1..a] B[1..b] subarrays

    LCS_box matrix[A.length()][B.length()];
    for (int a = 0; a < A.length(); a++) {
        for (int b = 0; b < B.length(); b++) {
            matrix[a][b].length = 0;
            if (A[a] == B[b]) {
                matrix[a][b].direction = DEC_BOTH;
                if (a == 0 || b == 0) {
                    matrix[a][b].length = 1;
                }
                else {
                    matrix[a][b].length = matrix[a - 1][b - 1].length + 1;
                }
                continue;
            }
            if (a != 0) {
                if (matrix[a-1][b].length >= matrix[a][b].length) {
                    matrix[a][b].length = matrix[a-1][b].length;
                    matrix[a][b].direction = DEC_A;
                }
            }
            if (b != 0) {
                if (matrix[a][b-1].length >= matrix[a][b].length) {
                    matrix[a][b].length = matrix[a][b-1].length;
                    matrix[a][b].direction = DEC_B;
                }
            }
        }
    }

    // now reconstruct LCS

    int a = A.length() - 1;
    int b = B.length() - 1;
    string answer = "";

    while (a >= 0 && b >= 0) {

        if (matrix[a][b].direction == DEC_BOTH) {
            answer = A[a] + answer;
            a--;
            b--;
        }
        else if (matrix[a][b].direction == DEC_A) {
            a--;
        }
        else if (matrix[a][b].direction == DEC_B) {
            b--;
        }
    }

    return answer;

}