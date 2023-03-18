#include <iostream>
#include <cstring>
#include <QDir>
#include <QRandomGenerator>
#include "include/AkariModel.h"
#include "include/Matrix.h"


using namespace std;

AkariModel::AkariModel(QObject *parent)
    : QObject{parent},  _cellsStateMatrix(*(new Matrix<cellState>(7)))
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

Matrix<cellState> & AkariModel::get_cellsStateMatrix() {
    return _cellsStateMatrix;
}


void AkariModel::fill_cellsStateMatrix(QString filename) {

   int lineIndex;
   QFile file(":/grids/Akiri_Grids/"+filename);
   QString line;
   char currChar;

   if (file.open(QIODevice::ReadOnly)) {
       line = file.readLine();
       QRandomGenerator generator = QRandomGenerator::securelySeeded();
       lineIndex = generator.bounded(2,line.toInt());
       printf("%d \n",  line.toInt());
       printf("ligne index %d\n", lineIndex);
       for (int i = 1; i < lineIndex; i++) {
           if (!file.canReadLine()) {
               cout << "Impossible de trouver la ligne " << lineIndex << " dans le fichier " << filename.toStdString() << endl;
               exit(EXIT_FAILURE);
           }
           line = file.readLine();
       }

       _cellsStateMatrix = * new Matrix<cellState>(get_sizeInteger());

       for (int row = 0; row < get_sizeInteger(); row++) {
           for(int col = 0; col < get_sizeInteger(); col++) {
               currChar = line.toStdWString()[(get_sizeInteger() * row) + col];
               switch (currChar) {
               case '.':
                   _cellsStateMatrix(row, col) = UNENLIGHTENED;
                   break;
               case 'X':
                   _cellsStateMatrix(row, col) = BLACK;
                   break;
               case '0':
                   _cellsStateMatrix(row, col) = BLACK_0;
                   break;
               case '1':
                   _cellsStateMatrix(row, col) = BLACK_1;
                   break;
               case '2':
                   _cellsStateMatrix(row, col) = BLACK_2;
                   break;
               case '3':
                   _cellsStateMatrix(row, col) = BLACK_3;
                   break;
               case '4':
                   _cellsStateMatrix(row, col) = BLACK_4;
                   break;
               default:
                   break;
               }


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
                fill_cellsStateMatrix(filename);
            }
    }
 }

void AkariModel::fill_neigbours_list(int row, int col,  std::vector<std::pair<int, int>> & neigbours) {
    int i = row + 1;
    while(i < get_sizeInteger() && (_cellsStateMatrix(i, col) == UNENLIGHTENED || _cellsStateMatrix(i, col) == ENLIGHTENED || _cellsStateMatrix(i, col) == YELLOW_LAMP  || _cellsStateMatrix(i, col) == RED_LAMP)) {
        neigbours.push_back(std::make_pair(i, col));
        i++;
    }

    i = row - 1;
    while(i >= 0 &&  (_cellsStateMatrix(i, col) == UNENLIGHTENED || _cellsStateMatrix(i, col) == ENLIGHTENED || _cellsStateMatrix(i, col) == YELLOW_LAMP  || _cellsStateMatrix(i, col) == RED_LAMP)) {
        neigbours.push_back(std::make_pair(i, col));
        i--;
    }

    i = col + 1;
    while(i < get_sizeInteger() &&  (_cellsStateMatrix(row, i) == UNENLIGHTENED || _cellsStateMatrix(row, i) == ENLIGHTENED || _cellsStateMatrix(row, i) == YELLOW_LAMP  || _cellsStateMatrix(row, i) == RED_LAMP)) {
        neigbours.push_back(std::make_pair(row, i));
        i++;
    }

    i = col - 1;
    while(i >= 0 &&  (_cellsStateMatrix(row, i) == UNENLIGHTENED || _cellsStateMatrix(row, i) == ENLIGHTENED || _cellsStateMatrix(row, i) == YELLOW_LAMP  || _cellsStateMatrix(row, i) == RED_LAMP)) {
        neigbours.push_back(std::make_pair(row, i));
        i--;
    }
}

void AkariModel::onCellClicked(int row, int col) {
    std::vector<std::pair<int, int>>  neigbours;

    if(row < 0 || col < 0) return;

    switch (_cellsStateMatrix(row, col)) {
        case UNENLIGHTENED:
           // _clickedCells.push_back(std::make_pair(row, col));
            fill_neigbours_list(row, col, neigbours);
            for (const auto& pair : neigbours) {
                _cellsStateMatrix(pair.first, pair.second) = ENLIGHTENED;
            }
             _cellsStateMatrix(row, col) = YELLOW_LAMP;
              _vector.push_back(std::make_pair(std::make_pair(row, col), neigbours));
            emit responseOnMouseClick(_cellsStateMatrix);
            break;

        case ENLIGHTENED:
           // _clickedCells.push_back(std::make_pair(row, col));
            fill_neigbours_list(row, col, neigbours);
            for (const auto& pair : neigbours) {
                if(_cellsStateMatrix(pair.first, pair.second) == YELLOW_LAMP) {
                    _cellsStateMatrix(pair.first, pair.second) = RED_LAMP;
                }
                if( _cellsStateMatrix(pair.first, pair.second) == UNENLIGHTENED) {
                    _cellsStateMatrix(pair.first, pair.second) = ENLIGHTENED;
                }
            }
            _cellsStateMatrix(row, col) = RED_LAMP;
            _vector.push_back(std::make_pair(std::make_pair(row, col), neigbours));
            emit responseOnMouseClick(_cellsStateMatrix);

            break;
        case RED_LAMP :
           // _clickedCells.push_back(std::make_pair(row, col));
            for (const auto& pair : value_of({row, col})) {
                bool isStayingRed = false;
                if(_cellsStateMatrix(pair.first, pair.second) == RED_LAMP) {                 
                    for(const auto& p : value_of({pair.first, pair.second})) {
                        if(_cellsStateMatrix(p.first, p.second) == RED_LAMP && p !=  std::make_pair(row, col)) {
                            isStayingRed = true;
                            break;
                        }
                    }
                    if(!isStayingRed) {
                        _cellsStateMatrix(pair.first, pair.second) = YELLOW_LAMP;
                    }
                }
                bool found = false;
                for (const auto& key_value : _vector) {
                    if (key_value.first == std::make_pair(row, col)) {
                        continue;
                    }
                    if (key_value.first == pair || std::find(key_value.second.begin(), key_value.second.end(), pair) != key_value.second.end()) {
                        found = true;
                        break;
                    }

                }
                if (!found) {
                      _cellsStateMatrix(pair.first, pair.second) = UNENLIGHTENED;
                }
            }
             _cellsStateMatrix(row, col) = ENLIGHTENED;
            //_vector.erase({row, col}); // Remove the cell's neigbours from the map
             remove({row, col});
             emit responseOnMouseClick(_cellsStateMatrix);

            break;
        case YELLOW_LAMP :
           // _clickedCells.push_back(std::make_pair(row, col));
            for (const auto& pair : value_of({row, col})) {
                bool found = false;
                for (const auto& key_value : _vector) {
                    if (key_value.first == std::make_pair(row, col)) {
                        continue;
                    }
                    if (key_value.first == pair || std::find(key_value.second.begin(), key_value.second.end(), pair) != key_value.second.end()) {
                        found = true;
                        break;
                    }

                }
                if (!found) {
                      _cellsStateMatrix(pair.first, pair.second) = UNENLIGHTENED;
                }
            }
             _cellsStateMatrix(row, col) = UNENLIGHTENED;         
             remove({row, col});
            emit responseOnMouseClick(_cellsStateMatrix);
            break;
        default:
            break;
    }
}

bool AkariModel:: verify_four_neigbours(int right_lamps_nb, int row, int col) {
    int lamps_nb = 0;
    for(int i = row - 1; i <= row + 1; i += 2) {
        if(i >= 0 && i < get_sizeInteger() && _cellsStateMatrix(i, col) == YELLOW_LAMP) {
            lamps_nb++;
        }
    }
    for(int j = col - 1; j <= col + 1; j += 2) {
        if(j >= 0 && j < get_sizeInteger() && _cellsStateMatrix(row, j) == YELLOW_LAMP) {
            lamps_nb++;
        }
    }
    if(lamps_nb == right_lamps_nb) return true;
    return false;
}

void AkariModel::ONDoneClicked() {
    for(int row = 0; row < get_sizeInteger(); row++) {
       for(int col = 0; col < get_sizeInteger(); col++) {
           switch (_cellsStateMatrix(row, col)) {
               case UNENLIGHTENED :
                   emit isDone(false);
                   return;
               case RED_LAMP :
                   emit isDone(false);
                   return;
               case BLACK_0 :
                  if(!verify_four_neigbours(0, row, col)) {
                      emit isDone(false);
                      return;
                  }
                  break;
               case BLACK_1 :
                  if(!verify_four_neigbours(1, row, col)) {
                      emit isDone(false);
                      return;
                  }
                  break;
               case BLACK_2 :
                  if(!verify_four_neigbours(2, row, col)) {
                      emit isDone(false);
                      return;
                  }
                  break;
               case BLACK_3 :
                  if(!verify_four_neigbours(3, row, col)) {
                      emit isDone(false);
                      return;
                  }
                  break;
               case BLACK_4 :
                  if(!verify_four_neigbours(4, row, col)) {
                      emit isDone(false);
                      return;
                  }
                  break;

               default:
                   break;
           }
       }
    }

    emit isDone(true);


}


void AkariModel::clearGrid() {
    for (int row = 0; row < get_sizeInteger(); row++) {
        for(int col = 0; col < get_sizeInteger(); col++) {
            if(_cellsStateMatrix(row, col) == ENLIGHTENED || _cellsStateMatrix(row, col) == YELLOW_LAMP || _cellsStateMatrix(row, col) == RED_LAMP) {
                _cellsStateMatrix(row, col) = UNENLIGHTENED;
            }
        }

    }
}


void AkariModel::unDo() {

    if(!_vector.empty()) {
        std::pair<int, int> lastCellClicked = _vector.rbegin()->first;
        onCellClicked( lastCellClicked.first, lastCellClicked.second);
    }

}

void AkariModel::remove(std::pair<int, int> pairToRemove) {
    auto it = std::find_if(_vector.begin(), _vector.end(), [ pairToRemove](std::pair<std::pair<int, int>,  std::vector<std::pair<int, int>>>  pair) {
        return pair.first ==  pairToRemove;
    });

    _vector.erase(it);


}

std::vector<std::pair<int, int>> AkariModel::value_of(std::pair<int, int> key) {
    std::vector<std::pair<int, int>> value;
    for (const auto& myPair : _vector) {
        if (key ==  myPair.first ) {
            value = myPair.second;
            return  value;
        }
    }
    return value;
}
