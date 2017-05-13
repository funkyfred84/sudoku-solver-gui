#ifndef SUDOKU_H
#define SUDOKU_H
#include <array>
#include <stdint.h>
#include <vector>
#include <iostream>

class Index {
public:
    Index(const size_t row, const size_t column);
    Index(const bool finished);
    size_t row(void) const;
    size_t column(void) const;
    bool finished(void) const;
private:
    size_t _row;
    size_t _column;
    bool _finished;
};

class Sudoku {
public:
    Sudoku(void);
    Sudoku(const std::array<uint8_t, 81>& fields);

    void field(const Index& index, const uint8_t value);
    Index next();
    std::vector<uint8_t> possibilities(const Index& index) const;

    uint8_t field(const Index& index) const;
    bool operator==(const Sudoku& val) const;
    bool operator !=(const Sudoku& val) const;
private:
    std::array<uint8_t, 81> _fields;
};


#endif // SUDOKU_H
