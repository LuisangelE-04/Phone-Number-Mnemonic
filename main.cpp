#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

const vector<string> letterDigits = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

string getUserNumber() {
    string userPhoneNumber, phoneNumber;
    cin >> userPhoneNumber;

    for(int i = 0; i < userPhoneNumber.length(); i++) {
        if(userPhoneNumber[i] != '-') {
            phoneNumber.push_back(userPhoneNumber[i]);
        }
        else {
            phoneNumber.push_back(' ');
        }
    }
    
    return phoneNumber;
}

bool checkIfValid(string segment1, string segment2) {
    char invalidNums[2] = {'0', '1'};
    int j, i;
    bool isValid = true;

    if(segment1.length() != 3 || segment2.length() != 4) {
        isValid = false;
        return isValid;
    }

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 2; j++) {
            if(segment1[i] == invalidNums[j]) {
                isValid = false;
                return isValid;
            }
        }
    }

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 2; j++) {
            if(segment2[i] == invalidNums[j]) {
                isValid = false;
                return isValid;
            }
        }
    }

    return isValid;
}

void readValidNames(vector<string>& words3, vector<string>& words4, vector<string>& words7, string file) {
    ifstream fin(file);
    while(getline(fin, file)) {
        if(file.length() == 3) {
            words3.push_back(file);
        }
        else if(file.length() == 4) {
            words4.push_back(file);
        }
        else if(file.length() == 7) {
            words7.push_back(file);
        }
    }
    fin.close();
}

// get digits and pass by refernce
void convertToDigits(int digits[], string seg1, string seg2) {
    int i;
    string newNum;
    
    for(i = 0; i < 3; i++) {
        newNum += seg1[i];
        newNum += " ";
    }
    for(i = 0; i < 4; i++) {
        newNum += seg2[i];
        newNum += " ";
    }

    istringstream inSS(newNum);
    for(i = 0; i < 7; i++) {
        inSS >> digits[i];
    }
}

void outputMatches(int digits[], vector<string> words3, vector<string> words4, vector<string> words7) {
    ofstream fout("output.txt");

    bool validWord = false;
    bool validWord2 = false;
    int counter = 0;
    int counter2 = 0;
    int totWords = 0;
    int words, i, chars;

    for(words = 0; words < words3.size(); words++) {
        for(i = 0; i < 3; i++) {
            for(chars = 0; chars < letterDigits.at(digits[i]-2).length(); chars++) {
                if(letterDigits.at(digits[i]-2)[chars] == words3.at(words)[i]) {
                    counter ++;
                    break;
                }
            }
        }
        if(counter == 3) {
            validWord = true;
        }
        if(validWord) {
            for(int w2 = 0; w2 < words4.size(); w2++) {
                for(int j = 0; j < 4; j++) {
                    for(int char2 = 0; char2 < letterDigits.at(digits[j+3]-2).length(); char2++) {
                        if(letterDigits.at(digits[j+3]-2)[char2] == words4.at(w2)[j]) {
                            counter2 ++;
                            break;
                        }
                    }
                }
                if(counter2 == 4) {
                    validWord2 = true;
                }
                if(validWord2) {
                    fout << words3.at(words) << " " << words4.at(w2) << endl;
                    totWords++;
                }
                validWord2 = false;
                counter2 = 0;
            }
        }
        counter = 0;
        validWord = false;
    }

    bool validLong = false;
    int counterLong = 0;

    for(int words = 0; words < words7.size(); words++) {
        for(int i = 0; i < 7; i++) {
            for(int chars = 0; chars < letterDigits.at(digits[i]-2).length(); chars++) {
                if(letterDigits.at(digits[i]-2)[chars] == words7.at(words)[i]) {
                    counterLong++;
                    break;
                }
            }
        }
        if(counterLong == 7) {
            validLong = true;
        }
        if(validLong) {
            fout << words7.at(words) << endl;
            totWords++;
        }
        validLong = false;
        counterLong = 0;
    }

    if(totWords == 0) {
        fout << "No results!" << endl;
    }

    fout.close();
}

int main() {
    istringstream inSS(getUserNumber());
    string segment1, segment2;
    inSS >> segment1 >> segment2;

    if(checkIfValid(segment1, segment2) == false) {
        cout << "Invalid phone number" << endl;
        exit(1);
    }

    string fileName = "ShortList.txt";
    vector<string> words3;
    vector<string> words4;
    vector<string> words7;
    readValidNames(words3, words4, words7, fileName);

    int digits[7];
    convertToDigits(digits, segment1, segment2);
    
    outputMatches(digits, words3, words4, words7);

    return 0;
}