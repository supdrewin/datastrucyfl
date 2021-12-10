/**
 * Copyright(C) 2021 Supdrewin <https://github.com/supdrewin>
 * sort.hh is part of Sort Algorithm Example.
 * The Sort Algorithm Example is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * The Sort Algorithm Example is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABI-
 * LITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __sort_hh
#define __sort_hh 1

namespace sort { //! DON'T declare using this namespace!

template <typename type> struct base_data {
  type key{}; //* a minimal member to be sorted

  inline void operator=(type right) { this->key = right; }

  inline bool operator>(base_data right) { return (this->key > right.key); }
  inline bool operator<(base_data right) { return (this->key < right.key); }
  inline bool operator>=(base_data right) { return (this->key >= right.key); }
  inline bool operator<=(base_data right) { return (this->key <= right.key); }
  inline bool operator==(base_data right) { return (this->key == right.key); }
  inline bool operator!=(base_data right) { return (this->key != right.key); }
};

template <typename type, unsigned size> struct array {
  base_data<type> elems[size];

  //! begin with it's head, and end after the last one
  inline base_data<type> *begin() { return &(this->elems[0]); }
  inline base_data<type> *end() { return &(this->elems[size]); }

  void insert_sort() {
    for (int i{1}, j; i < int(size); ++i) {
      base_data<type> tmp = this->elems[i];

      for (j = i - 1; j >= 0 and tmp < this->elems[j]; --j)
        this->elems[j + 1] = this->elems[j];
      this->elems[j + 1] = tmp;
    }
  }

  void shell_sort() {
    unsigned tmp_size{size}, loop{};

    while (tmp_size /= 2)
      ++loop;

    auto span{new int[loop]};
    *span = size / 2;

    for (unsigned i{1}; i < loop; ++i)
      span[i] = span[i - 1] / 2;

    for (unsigned time{}; time < loop; ++time)
      for (int group{}; group < span[time]; ++group)
        for (int member{group}, i; member + span[time] < int(size);
             member += span[time]) {
          base_data<type> tmp = this->elems[member + span[time]];

          for (i = member; i >= 0 and tmp < this->elems[i]; i -= span[time])
            this->elems[i + span[time]] = this->elems[i];
          this->elems[i + span[time]] = tmp;
        }

    delete[] span;
  }
};

} // namespace sort

#endif // !__sort_hh
