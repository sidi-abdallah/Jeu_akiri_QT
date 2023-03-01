#include <iostream>
#include <cstring>
#include <QDir>
#include <QRandomGenerator>
#include "include/AkariModel.h"

using namespace std;

AkariModel::AkariModel(QObject *parent)
    : QObject{parent}
{



}

void AkariModel::set_size(int size_index) {
    _size = static_cast<AkariModel::Size>(size_index);
}

AkariModel::Size AkariModel::get_size(){
    return _size;
}

void AkariModel::set_level(int level_index) {
    _level = static_cast<AkariModel::Level>(level_index);
}

AkariModel::Level AkariModel::get_level() {
    return _level;
}

int AkariModel::get_sizeInteger() {
    switch (_size) {
    case dim_7:
        return 7;
    case dim_10:
        return 10;
    case dim_14:
        return 14;
    default:
        break;
    }
}


string AkariModel::sizeToString(Size size) {
    static const char* names[] = {"7", "10", "14"};
    return names[static_cast<int>(size)];
}

string AkariModel::levelToString(Level level) {
    static const char* names[] = {"easy", "normal", "hard"};
    return names[static_cast<int>(level)];
}

bool AkariModel::containsSubstring(const string& s, const string& substring) {
    return s.find(substring) != string::npos;
}

char ** AkariModel::get_matrix() {
    return _matrix;
}

void AkariModel::fill_matrix(QString filename) {

   int lineIndex;
   QFile file(":/grids/Akiri_Grids/"+filename);
   QString line;

   if (file.open(QIODevice::ReadOnly)) {
       line = file.readLine();
       QRandomGenerator generator = QRandomGenerator::securelySeeded();
       lineIndex = generator.bounded(1,line.toInt());
       printf("%d \n",  line.toInt());
       printf("ligne index %d\n", lineIndex);
       for (int i = 1; i < lineIndex; i++) {
           if (!file.canReadLine()) {
               cout << "Impossible de trouver la ligne " << lineIndex << " dans le fichier " << filename.toStdString() << endl;
               exit(EXIT_FAILURE);
           }
           line = file.readLine();
       }
       _matrix = (char ** ) malloc(get_sizeInteger() * sizeof(char *));
       for(int i = 0; i < 7; i++) {
           _matrix[i] = (char *) malloc(get_sizeInteger() * sizeof(char));
       }

       for (int row = 0; row < get_sizeInteger(); row++) {
           for(int col = 0; col < get_sizeInteger(); col++) {
               _matrix[row][col] = line.toStdWString()[(get_sizeInteger() * row) + col];
               printf("%c ",_matrix[row][col]);
           }
       }

       file.close();
   } else {
       cout << "Impossible d'ouvrir le fichier " << filename.toStdString() << endl;
       exit(EXIT_FAILURE);
   }

}

void AkariModel::create_grid() {
    string levelString = levelToString(_level);
    string sizeString = sizeToString(_size);
    QDir dossierDansRessources(":/grids/Akiri_Grids");
    QStringList filesList = dossierDansRessources.entryList();

    for (const QString& filename : filesList) {
            if(containsSubstring(filename.toStdString(), levelString) && containsSubstring(filename.toStdString(), sizeString)) {
                cout << "file found" << endl;
                fill_matrix(filename);
            }
    }
 }









