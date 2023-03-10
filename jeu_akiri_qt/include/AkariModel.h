#ifndef AKARIMODEL_H
#define AKARIMODEL_H
#include <QObject>
#include "common.h"
#include "include/Matrix.h"
#include <map>
#include <vector>

class AkariModel : public QObject {

  Q_OBJECT

public:
  explicit AkariModel(QObject * parent = nullptr);
  /*
   * Enum type for difficulty level
   *
   */
  enum Level
  {
    Easy = 0,
    Normal,
    Hard
  };



  /*
   * Enum type for grid size
   *
   */
  enum Size
  {
    dim_7 = 0,
    dim_10,
    dim_14
  };

  /**
   * @brief get_size gets the current value of enum size
   */
  Size get_size();

  /**
   * @brief get_size gets the current value of enum level
   */
  Level get_level();

  /**
   * @brief get_sizeInteger gets the size in an integer format
   */
  int get_sizeInteger();

  /**
   * @brief sizeToString converts the enum type to a string type
   * @param size the enum to be converted
   * @return the corresponding string
   */
  std::string sizeToString(Size size);

  /**
   * @brief sizeToString converts the enum type to a string type
   * @param size the enum to be converted
   * @return the corresponding string
   */
  std::string levelToString(Level level);

  /**
   * @brief containsSubstring verify if a string is a part of another
   * @param mainString the string that will reserach at it
   * @param substring the researshed string
   * @return true if subString is included in mainString, false otherwise
   */
  bool containsSubstring(const std::string& mainString, const std::string& subString);

  /**
   * @brief get_cellsStateMatrix gets the grid matrix
   */
  Matrix<cellState> & get_cellsStateMatrix();




  void create_grid();

public slots :
    /**
     * @brief set_size updates model's size from the sizeCombox of widget
     * @param size_index
     */
    virtual void set_size(int size_index);

    /**
     * @brief set_level updates model's level  from the levelCombox of widget
     * @param level_index
     */
    virtual void set_level(int level_index);

    virtual void onCellClicked(int row, int col);

    virtual void ONDoneClicked();
signals :
  void responseOnMouseClick(Matrix<cellState> &);
  void areWin(bool);

private:
  Size _size;
  Level _level;
 // Matrix<char> & _cellsStateMatrix;
  Matrix<cellState> & _cellsStateMatrix;

  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> _map;

  /**
   * @brief fill_cellsStateMatrix fill the _cellsStateMatrix from a file
   * @param filename file's name
   */
  void fill_cellsStateMatrix(QString filename);

  void fill_neigbours_list(int beg, int end, std::vector<std::pair<int, int>> & neigbours);

  bool verify_four_neigbours(int max_lamps, int row, int col);






};

#endif // AKARIMODEL_H
