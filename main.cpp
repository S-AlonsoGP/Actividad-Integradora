#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string leerArchivo(string nombre){
    ifstream archivo(nombre);
    if(!archivo.is_open()){
        cout << "Error, no se pudo abrir el archivo" << endl;
    }
    string contenido;
    string linea;
    while(getline(archivo, linea)){
        contenido += linea;
    }
    archivo.close();
    return contenido;
}

bool esHexadecimal(string texto){
    for(char c : texto){
        if(!((c >= '0' && c <= '9') ||
             (c >= 'A' && c <= 'F') ||
             (c >= 'a' && c <= 'f'))){
            return false;
        }
    }

    return true;
}

vector<int> lps(string mcode){
    vector<int> lps(mcode.length(), 0);
    int i = 1;
    int len = 0;
    while(i < mcode.length()){
        if(mcode[i] == mcode[len]){
            len++;
            lps[i] = len;
            i++;
        }else{
            if(len != 0){
                len = lps[len - 1];
            }else{
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int kmp(string transmission, string mcode){
    int n = transmission.length();
    int m = mcode.length();
    int i = 0;
    int j = 0;
    vector<int> tabla = lps(mcode);
    while (i < n){
        if(mcode[j] == transmission[i]){
            i++;
            j++;
        }else{
            if(j != 0){
                j = tabla[j-1];
            }else{
                i += 1;
            }
        }
        if(j == m){
            return i -j;
        }
    }
    return -1;
}

int longest_palindrome(string s) {
    int n = s.length();
    if (n == 0) return 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLength = 1;

    for (int i = 0; i < n; i++) {
	dp[i][i] = true;
    }

    for (int length = 2; length <= n; length++) {
	for (int i = 0; i < n - length + 1; i++) {
	    int j = i + length - 1;
	    if (s[i] == s[j]) {
		if (length == 2) {
		    dp[i][j] = true;
		} else {
		    dp[i][j] = dp[i + 1][j - 1];
		}
		if (dp[i][j]) {
		    maxLength = max(maxLength, length);
		}
	    }
	}
    }
    return maxLength;
}

int main(){
    string transmission1 = leerArchivo("transmission1.txt");
    string transmission2 = leerArchivo("transmission2.txt");

    string mcode1 = leerArchivo("mcode1.txt");
    string mcode2 = leerArchivo("mcode2.txt");
    string mcode3 = leerArchivo("mcode3.txt");
    if(!esHexadecimal(mcode1)){
        cout << "mcode1 no contiene hexadecimal valido" << endl;
    }

    int resultado = kmp(transmission1, mcode1);
    if (resultado != -1) {
        cout << "Posicion: " << resultado + 1 << endl;
    }
    else {
        cout << "false" << endl;
    }

    string prueba1 = "aabbaa";
    string prueba2 = "abcde";
    cout << "Longest Palindrome in '" << prueba1 << "' is of length: " << longest_palindrome(prueba1) << endl;
    cout << "Longest Palindrome in '" << prueba2 << "' is of length: " << longest_palindrome(prueba2) << endl;

    return 0;
}
