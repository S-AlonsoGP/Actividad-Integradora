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

// helper function
int expand_around_center(string *s, int left, int right) {
    while (left >= 0 && right < s->length() && (*s)[left] == (*s)[right]) {
	left--;
	right++;
    }
    return right - left - 1;
}

// this function returns the starting and ending indices of the longest palindromic substring in the given string s
// using *s for large strings to avoid copying
pair<int, int> longest_palindrome (string *s) {
	
    int n = s->length();
    if (n == 0) {
	return {-1, -1};
    }
    int start = 0;
    int end = 0;
    for (int i = 0; i < n; i++) {
	int len1 = expand_around_center(s, i, i);
	int len2 = expand_around_center(s, i, i + 1);
	int len = max(len1, len2);
	if (len > end - start) {
	    start = i - (len - 1) / 2;
	    end = i + len / 2;
	}
    }
    return {start, end};
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

/**
 * Assuming that malicious code always has "mirrored" code (chars palindromes), it would be a good idea to look for this type of code in a transmission. The program should then look for "mirrored" code within the transmission files (only at chars level, do not look for it at bits level). The program displays in a single line (two integers separated by a space) the position (starting at 1) where the longest "mirrored" code (palindrome) for each stream file starts and ends. It can be assumed that this type of code will always be found.
 */

    pair<int, int> longest1 = longest_palindrome(&transmission1);
    pair<int, int> longest2 = longest_palindrome(&transmission2);

    if (longest1.first != -1 && longest1.second != -1) {
	cout << "Longest palindrome in transmission1: " << longest1.first + 1 << " " << longest1.second + 1 << endl;
    } else {
	cout << "No palindrome found in transmission1" << endl;
    }

    if (longest2.first != -1 && longest2.second != -1) {
	cout << "Longest palindrome in transmission2: " << longest2.first + 1 << " " << longest2.second + 1 << endl;
    } else {
	cout << "No palindrome found in transmission2" << endl;
    }

    return 0;
}

