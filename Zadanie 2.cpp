#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
/*
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}*/

vector<string> split(const string &s, char delimiter){
    vector<string> results;
    int i=0,j=0;
    string tmp;
    while(i<=s.size()){
        if(s[i]==delimiter || i==s.size()){
            tmp=s.substr(j,i-j);
            results.push_back(tmp);
            j=i+1;
        }
        i++;
    }
    return results;
}

void generateCSS(ofstream &cssFile, const vector<string> &data) {
    // Tło strony
    cssFile << "body {\n";
    cssFile << "    background-color:" << data[0] << ";\n";

    if (!data[1].empty()) {
        cssFile << "    background-image: url('" << data[1] << "');\n";
    }

    vector<string> backgroundOptions = split(data[2], ';');
    if (!backgroundOptions.empty()) {
        if (backgroundOptions[0] == "RY_TAK")
            cssFile << "    background-repeat: repeat-y;\n";
        else if (backgroundOptions[0] == "RX_TAK")
            cssFile << "    background-repeat: repeat-x;\n";
        else if (backgroundOptions[0] == "ROZ_TAK")
            cssFile << "    background-size: cover;\n";
        else if (backgroundOptions[0] == "FIX_TAK")
            cssFile << "    background-attachment: fixed;\n";
    }

    cssFile << "}\n\n";

    // Ustawienia kontenera kolumn
    cssFile << ".columns {\n";
    cssFile << "    display: flex;\n"; // Flexbox layout
    cssFile << "    justify-content: space-around;\n"; // Równe odstępy między kolumnami
    cssFile << "}\n\n";

    // Stylizacja tytułu
    cssFile << "h1 {\n";
    cssFile << "    font-size: " << data[4] << "px;\n";
    cssFile << "    color: " << data[5] << ";\n";
    cssFile << "}\n\n";

    // Stylizacja kolumn
    vector<string> columnTexts = split(data[7], ';');
    vector<string> columnFontSizes = split(data[8], ';');
    vector<string> columnFontColors = split(data[9], ';');
    vector<string> columnBgColors = split(data[10], ';');
    vector<string> columnBgImages = split(data[11], ';');
    vector<string> columnBgOptions = split(data[12], ';');
    string borderRadius = data[13];

    for (int i = 0; i < stoi(data[6]); ++i) {
        cssFile << ".column-" << i + 1 << " {\n";
        cssFile << "    background-color: " << columnBgColors[i] << ";\n";
        cssFile << "    font-size: " << columnFontSizes[i] << "px;\n";
        cssFile << "    color: " << columnFontColors[i] << ";\n";
        cssFile << "    padding: 20px;\n"; // Dodanie paddingu dla lepszego wyglądu
        cssFile << "    flex: 1;\n"; // Każda kolumna zajmuje równą przestrzeń
        cssFile << "    margin: 10px;\n"; // Odstęp między kolumnami
       if (columnBgImages[i] != "NIE") {
            cssFile << "    background-image: url('" << columnBgImages[i] << "');\n";
            if (!columnBgOptions[i].empty()) {
                if (columnBgOptions[i].find("RY_TAK")!=string::npos)
                    cssFile << "    background-repeat: repeat-y;\n";
                if (columnBgOptions[i].find("RX_TAK")!=string::npos)
                    cssFile << "    background-repeat: repeat-x;\n";
                if (columnBgOptions[i].find("ROZ_TAK")!=string::npos)
                    cssFile << "    background-size: cover;\n";
                if (columnBgOptions[i].find("FIX_TAK")!=string::npos)
                    cssFile << "    background-attachment: fixed;\n";
            }
        }
        cssFile << "    border-radius: " << borderRadius << "px;\n";
        cssFile << "}\n\n";
    }

    // Stylizacja stopki
    cssFile << "footer {\n";
    cssFile << "    background-color: " << data[14] << ";\n";
    cssFile << "    font-size: " << data[18] << "px;\n"; // Rozmiar czcionki
    cssFile << "    color: " << data[17] << ";\n"; // Kolor czcionki
    if (!data[15].empty()) {
        cssFile << "    background-image: url('" << data[15] << "');\n";
        string footerBgOptions = data[16];
        if (!footerBgOptions.empty()) {
            if (footerBgOptions.find("RY_TAK")!=string::npos)
                    cssFile << "    background-repeat: repeat-y;\n";
            if (footerBgOptions.find("RX_TAK")!=string::npos)
                    cssFile << "    background-repeat: repeat-x;\n";
            if (footerBgOptions.find("ROZ_TAK")!=string::npos)
                    cssFile << "    background-size: cover;\n";
            if (footerBgOptions.find("FIX_TAK")!=string::npos)
                    cssFile << "    background-attachment: fixed;\n";
        }
    }
    cssFile << "    padding: 20px;\n"; // Dodaj padding dla lepszego wyglądu
    cssFile << "    text-align: center;\n"; // Wyśrodkowanie tekstu
    cssFile << "}\n";
}

void generateHTML(ofstream &htmlFile, const vector<string> &data) {
    // Nagłówek HTML
    htmlFile << "<!DOCTYPE html>\n<html lang=\"pl\">\n<head>\n";
    htmlFile << "    <meta charset=\"UTF-8\">\n";
    htmlFile << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    htmlFile << "    <title>" << data[3] << "</title>\n";
    htmlFile << "    <link rel=\"stylesheet\" href=\"style.css\">\n";
    htmlFile << "</head>\n<body>\n";

    // Tytuł strony
    htmlFile << "    <h1>" << data[3] << "</h1>\n";

    // Kolumny
    htmlFile << "    <div class=\"columns\">\n";
    vector<string> columnTexts = split(data[7], ';');
    for (int i = 0; i < stoi(data[6]); ++i) {
        htmlFile << "        <div class=\"column-" << i + 1 << "\">\n";
        htmlFile << "            <p>" << columnTexts[i] << "</p>\n";
        htmlFile << "        </div>\n";
    }
    htmlFile << "    </div>\n";

    // Stopka
    htmlFile << "    <footer>\n";
    htmlFile << "        <p>" << data[19] << "</p>\n";
    htmlFile << "    </footer>\n";

    // Zamknięcie HTML
    htmlFile << "</body>\n</html>\n";
}

int main() {
    // Otwieranie pliku wejściowego
    ifstream inputFile("dane.txt");
    vector<string> data;
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            data.push_back(line);
        }
        inputFile.close();
    } else {
        cerr << "Nie można otworzyć pliku dane.txt" << endl;
        return 1;
    }

    // Otwieranie plików wyjściowych
    ofstream htmlFile("index.html");
    ofstream cssFile("style.css");

    if (htmlFile.is_open() && cssFile.is_open()) {
        generateCSS(cssFile, data);
        generateHTML(htmlFile, data);
        
        htmlFile.close();
        cssFile.close();
    } else {
        cerr << "Nie można utworzyć plików wyjściowych" << endl;
        return 1;
    }

    cout << "Pliki index.html i style.css zostały wygenerowane." << endl;
    return 0;
}
