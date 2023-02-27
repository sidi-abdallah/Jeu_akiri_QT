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
    EASY = 0,
    Midium,
    Hard
  };

private:
  int grid_size;







};

#endif // AKARIMODEL_H
