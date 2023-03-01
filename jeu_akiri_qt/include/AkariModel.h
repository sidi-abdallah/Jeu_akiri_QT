#ifndef AKARIMODEL_H
#define AKARIMODEL_H
#include <QObject>

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
   * @brief get_matrix gets the grid matrix
   */
  char ** get_matrix();



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



private:
  Size _size;
  Level _level;
  char ** _matrix;

  /**
   * @brief fill_matrix fill the _matrix from a file
   * @param filename file's name
   */
  void fill_matrix(QString filename);






};

#endif // AKARIMODEL_H
