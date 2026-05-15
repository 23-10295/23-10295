#include <vector>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>

using namespace std;

int main(){
  return 0;
}

double mean(vector<double> v){
    if (v.empty()) return 0.0;
    double sum = 0.0;
    for (double x : v) sum += x;
    return sum / v.size();
}

double variance(vector<double> v){
    if (v.size() < 2) return 0.0;
    double m = mean(v);
    double sum_sq_diff = 0.0;
    for (double x : v) sum_sq_diff += pow(x - m, 2);
    return sum_sq_diff / (v.size() - 1);
}

double pearson_r(vector<double> A, vector<double> B){
    if (A.size() != B.size() || A.empty()) return 0;
    int n = A.size();
    double mean_A = accumulate(A.begin(), A.end(), 0.0) / n;
    double mean_B = accumulate(B.begin(), B.end(), 0.0) / n;
    double numerator = 0.0, sum_sq_A = 0.0, sum_sq_B = 0.0;
    for (int i = 0; i < n; ++i) {
        double dA = A[i] - mean_A;
        double dB = B[i] - mean_B;
        numerator += dA * dB;
        sum_sq_A  += dA * dA;
        sum_sq_B  += dB * dB;
    }
    double denom = sqrt(sum_sq_A) * sqrt(sum_sq_B);
    return (denom == 0) ? 0 : numerator / denom;
}

char valToChar(int i) {
    return i <= 9 ? (char)(i + '0') : (char)(i - 10 + 'A');
}
int charToVal(char c) {
    return c <= '9' ? (int)(c - '0') : (int)(c - 'A' + 10);
}
vector<char> fromDec(int n, int base) {
    if (n == 0) return {'0'};
    vector<char> result;
    while (n > 0) { result.push_back(valToChar(n % base)); n /= base; }
    reverse(result.begin(), result.end());
    return result;
}
int toDec(vector<char> s, int base) {
    int res = 0, power = 1;
    for (int i = s.size() - 1; i >= 0; i--) { res += charToVal(s[i]) * power; power *= base; }
    return res;
}
vector<char> intToVec(int n) {
    if (n == 0) return {'0'};
    string s = to_string(n);
    return vector<char>(s.begin(), s.end());
}

vector<char> dec_to_septapus(int n){return fromDec(n, 7);}
vector<char> dec_to_octopus(int n){return fromDec(n, 8);}
vector<char> dec_to_hexakaidecapus(int n){return fromDec(n, 16);}
vector<char> septapus_to_dec(vector<char> s){return intToVec(toDec(s, 7));}
vector<char> octopus_to_dec(vector<char> s){return intToVec(toDec(s, 8));}
vector<char> hexakaidecapus_to_dec(vector<char> s){return intToVec(toDec(s, 16));}
vector<char> septapus_to_octopus(vector<char> s){return fromDec(toDec(s, 7), 8);}
vector<char> septapus_to_hexakaidecapus(vector<char> s){return fromDec(toDec(s, 7), 16);}
vector<char> octapus_to_septapus(vector<char> s){return fromDec(toDec(s, 8), 7);}
vector<char> octopus_to_hexakaidecapus(vector<char> s){return fromDec(toDec(s, 8), 16);}
vector<char> hexakaidecapus_to_septapus(vector<char> s){return fromDec(toDec(s, 16), 7);}
vector<char> hexakaidecapus_to_octopus(vector<char> s){return fromDec(toDec(s, 16), 8);}
