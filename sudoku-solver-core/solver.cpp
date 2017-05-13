#include "solver.h"
#include <vector>
#include <stdint.h>
#include <memory>
#include <iostream>


Sudoku backtrack(std::vector<Sudoku>& stack) {
    while (!stack.empty()) {
          auto element = stack.back();
          stack.pop_back();

          Index free_field = element.next();
          if (free_field.finished()) {
              return element;
        }
        auto posibilities = element.possibilities(free_field);

        for (auto& val : posibilities) {
            Sudoku tmp = element;
            tmp.field(free_field, val);
            stack.push_back(tmp);
        }
    }
    throw "no solution availible";
}


Sudoku solve(const Sudoku &sudoku) {
    std::vector<Sudoku> stack;
    stack.push_back(sudoku);
    return backtrack(stack);
}
