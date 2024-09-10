#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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

    string backgroundOptions = data[2];
    if (!backgroundOptions.empty()) {
        if (backgroundOptions.find("RY_TAK")!=string::npos)
                    cssFile << "    background-repeat: repeat-y;\n";
        if (backgroundOptions.find("RX_TAK")!=string::npos)
                    cssFile << "    background-repeat: repeat-x;\n";
        if (backgroundOptions.find("ROZ_TAK")!=string::npos)
                    cssFile << "    background-size: cover;\n";
        if (backgroundOptions.find("FIX_TAK")!=string::npos)
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
    vector<string> borderRadius = split(data[13], ';');

    for (int i = 0; i < stoi(data[6]); ++i) {
        cssFile << ".column-" << i + 1 << " {\n";
        cssFile << "    background-color: " << columnBgColors[i] << ";\n";
        cssFile << "    font-size: " << columnFontSizes[i] << "px;\n";
        cssFile << "    color: " << columnFontColors[i] << ";\n";
        cssFile << "    padding: 20px;\n"; // Dodanie paddingu dla lepszego wyglądu
        cssFile << "    flex: 1;\n"; // Każda kolumna zajmuje równą przestrzeń
        cssFile << "    margin: 10px;\n"; // Odstęp między kolumnami
        if( i<columnBgImages.size()){
        if(columnBgImages[i] != "NIE") {
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
        }
        if(i<borderRadius.size()) cssFile << "    border-radius: " << borderRadius[i] << "px;\n";
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

void dataUserInput(vector<string> &data) {
    string input;

    // 1. Kolor tla strony
    cout << "Podaj kolor tla (np. #000000 dla czarnego lub nazwe koloru): ";
    cin >> input;
    data.push_back(input);

    // 2. Obraz tla strony
    cout << "Podaj sciezke do obrazu tla (lub wpisz 'NIE' jesli brak): ";
    cin >> input;
    data.push_back(input);

    // 3. Opcje tla strony (np. RY_TAK, ROZ_TAK, RX_TAK, FIX_TAK)
    cout << "Podaj opcje tla strony (np. RY_TAK;ROZ_TAK lub 'NIE' jesli brak): ";
    cin >> input;
    data.push_back(input);

    // 4. Tytul strony
    cout << "Podaj tytul strony: ";
    cin.ignore();  // Oczyszczenie bufora po wczesniejszym cin
    getline(cin, input);
    data.push_back(input);

    // 5. Rozmiar czcionki tytulu
    cout << "Podaj rozmiar czcionki tytulu (w px): ";
    cin >> input;
    data.push_back(input);

    // 6. Kolor czcionki tytulu
    cout << "Podaj kolor czcionki tytulu: ";
    cin >> input;
    data.push_back(input);

    // 7. Liczba kolumn
    cout << "Podaj liczbe kolumn: ";
    cin >> input;
    data.push_back(input);

    // 8. Teksty kolumn (oddzielone srednikami)
    cout << "Podaj teksty kolumn oddzielone srednikami (np. 'Tekst1;Tekst2;Tekst3'): ";
    cin.ignore();  // Oczyszczenie bufora
    getline(cin, input);
    data.push_back(input);

    // 9. Rozmiary czcionek kolumn (oddzielone srednikami)
    cout << "Podaj rozmiary czcionek kolumn oddzielone srednikami (np. '12;14;16'): ";
    getline(cin, input);
    data.push_back(input);

    // 10. Kolory czcionek kolumn (oddzielone srednikami)
    cout << "Podaj kolory czcionek kolumn oddzielone srednikami (np. 'red;blue;green'): ";
    getline(cin, input);
    data.push_back(input);

    // 11. Kolory tla kolumn (oddzielone srednikami)
    cout << "Podaj kolory tla kolumn oddzielone srednikami (np. '#ffffff;#000000;#ff0000'): ";
    getline(cin, input);
    data.push_back(input);

    // 12. Obrazy tla kolumn (oddzielone srednikami, wpisz 'NIE' jesli nie ma)
    cout << "Podaj obrazy tla kolumn oddzielone srednikami (wpisz 'NIE', jesli brak): ";
    getline(cin, input);
    data.push_back(input);

    // 13. Opcje tla kolumn (oddzielone srednikami, np. 'RY_TAK;RX_TAK')
    cout << "Podaj opcje tla kolumn oddzielone srednikami (np. 'RY_TAK;RX_TAK'): ";
    getline(cin, input);
    data.push_back(input);

    // 14. Zaokraglenie rogow kolumn (w px)
    cout << "Podaj wartosc zaokraglenia rogow kolumn (w px): ";
    cin >> input;
    data.push_back(input);

    // 15. Kolor tla stopki
    cout << "Podaj kolor tla stopki: ";
    cin >> input;
    data.push_back(input);

    // 16. Obraz tla stopki
    cout << "Podaj sciezke do obrazu tla stopki (lub wpisz 'NIE' jesli brak): ";
    cin >> input;
    data.push_back(input);

    // 17. Opcje tla stopki (np. 'RY_TAK;ROZ_TAK')
    cout << "Podaj opcje tla stopki (np. 'RY_TAK;ROZ_TAK'): ";
    cin >> input;
    data.push_back(input);

    // 18. Kolor czcionki stopki
    cout << "Podaj kolor czcionki stopki: ";
    cin >> input;
    data.push_back(input);

    // 19. Rozmiar czcionki stopki (w px)
    cout << "Podaj rozmiar czcionki stopki (w px): ";
    cin >> input;
    data.push_back(input);

    // 20. Tekst stopki
    cout << "Podaj tekst stopki: ";
    cin.ignore();
    getline(cin, input);
    data.push_back(input);
}



int main() {
   
    vector<string> data;  //vector w którym będą umieszczane wszystkie dane

    cout << "Czy chcesz wczytac dane z pliku dane.txt? wpisz 't' w przeciwnym razie wpisz 'n' : ";
    char odp;
    cin>>odp;

    if(odp=='t'){

    ifstream inputFile("dane.txt");
    string line;
    // Otwieranie pliku wejściowego
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            data.push_back(line);
        }
        inputFile.close();
    } else {
        cout << "Nie można otworzyć pliku dane.txt" << endl;
        return 1;
    }

    }else{
        dataUserInput(data);
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
        cout << "Nie mozna utworzyc plikow wyjsciowych" << endl;
        return 1;
    }

    cout << "Pliki index.html i style.css zostaly wygenerowane." << endl;
    return 0;
}
