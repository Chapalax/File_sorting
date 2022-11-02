#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int asciiFun(char firstElem){
    int intFirstElem = int(firstElem);
    if(intFirstElem > 96 && intFirstElem < 123){
        return intFirstElem - 32;
    }else if(intFirstElem > 64 && intFirstElem < 91) {
        return intFirstElem;
    }
}

int main(){
    string nw;
    string slovo;
    cout << "Enter your word" << endl;
    cin >> slovo;
    string line;
    vector<string> words;
    ifstream file("alp.txt");

    while(getline(file, line)) {
        if(!line.empty()) {
            if (line[line.size() - 1] != ' ') {
                words.push_back(line.substr(line.rfind(' ') + 1, line.size()));
            }
            while (line.find(' ') != string::npos) {
                if (line[0] != ' ') {
                    int occurrence = line.find(' ');
                    words.push_back(line.substr(0, occurrence));
                    line = line.substr(occurrence + 1, line.length());
                } else {
                    line = line.substr(1, line.size());
                }
            }
        }
    }
    words.push_back(slovo);
    sort(words.begin(), words.end());

    for (int j = 0; j < words.size()-1; j++){
        for (int i = 0; i < words.size()-1; i++) {
            int minLen = min(words[i].size(), words[i+1].size());

            for (int k = 0; k < minLen; k++) {
                if (asciiFun(words[i][k]) > asciiFun(words[i + 1][k])) {
                    string bufer = words[i];
                    words[i] = words[i + 1];
                    words[i + 1] = bufer;
                    break;
                }
                else if (asciiFun(words[i][k]) < asciiFun(words[i + 1][k]))
                    break;
            }
        }
    }


    ofstream tofile("alp.txt");
    for(auto & word : words){
        nw += word + '\n';
    }

    tofile << nw;
    cout << "Your word has been added! Please check the file";
    return 0;
}