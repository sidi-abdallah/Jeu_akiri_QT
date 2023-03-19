#ifndef AKARIMODEL_H
#define AKARIMODEL_H
#include <QObject>
#include "common.h"
#include "include/Matrix.h"
#include <vector>


class QTimer;
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

  /**
   * @brief create_grid fills cellsStateMatrix from a line of a filename based on the chosen size and level
   */
  void create_grid();

  /**
   * @brief clearGrid resets all cells by removing lamps and lightening from cells
   */
  void clearGrid();

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

  /**
   * @brief onCellClicked handles all possible cases when a cell is clicked
   * @param row the row of the cell
   * @param col the column of the cell
   */
    virtual void onCellClicked(int row, int col);

    /**
     * @brief ONDoneClicked returns the result of the game when done button is clicked
     */
    virtual void ONDoneClicked();
  /**
     * @brief unDo remove the last move
     */
    virtual void unDo();

signals :
  /**
   * @brief responseOnMouseClick sends cellState's matrix when a cell is clicked
   */
  void responseOnMouseClick(Matrix<cellState> &);

  /**
   * @brief isDone
   */
  void isDone(bool);

private:
  /**
   * @brief _size Size of the grid (chosen by the user and recovered by the model)
   */
  Size _size;

  /**
   * @brief _level Level of the grid (chosen by the user and recovered by the model)
   */
  Level _level;

  /**
   * @brief _cellsStateMatrix This matrix describes the state of cells in a grid
   */
  Matrix<cellState> & _cellsStateMatrix;


  /**
   * @brief _vector
   */
  std::vector<std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>> _vector;

  /**
   * @brief _clickedCells
   */
  std::vector<std::pair<int, int>> _clickedCells;

  /**
   * @brief fill_cellsStateMatrix fill the _cellsStateMatrix from a file
   * @param filename file's name
   */
  void fill_cellsStateMatrix(QString filename);

  /**
   * @brief fill_neigbours_list Populates a vector of neighboring cells for a given cell in the Akari puzzle
   * @param beg begin of vector neighbors
   * @param end end of vector neighbors
   * @param neigbours
   */
  void fill_neigbours_list(int beg, int end, std::vector<std::pair<int, int>> & neigbours);

  /**
   * @brief verify_four_neigbours Verifies if a given cell has the correct number of neighboring YELLOW_LAMPs
   * @param max_lamps number of allowed cells neighbrs with lamps
   * @param row
   * @param col
   * @return
   */
  bool verify_four_neigbours(int max_lamps, int row, int col);

  /**
   * @brief remove Removes a pair from a vector of pairs based on a specified key value
   * @param pairToRemove
   */
  void remove(std::pair<int, int> pairToRemove);

  /**
   * @brief value_of Retrieves the value associated with a specified key from a map, represented as a vector of pairs.
   * @param key
   * @return
   */
  std::vector<std::pair<int, int>> value_of(std::pair<int, int> key);






};

#endif // AKARIMODEL_H
