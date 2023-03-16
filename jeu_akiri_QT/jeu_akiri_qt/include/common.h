#ifndef COMMON_H
#define COMMON_H

enum cellState
{
    BLACK = 0,
    BLACK_0,
    BLACK_1,
    BLACK_2,
    BLACK_3,
    BLACK_4,
    ENLIGHTENED,
    UNENLIGHTENED,
    RED_LAMP,
    YELLOW_LAMP
};

enum RoundDuration{
    unlimited,
    ten_minutes,
    five_minutes,
    three_minutes,
    one_minute
};
#endif // COMMON_H
