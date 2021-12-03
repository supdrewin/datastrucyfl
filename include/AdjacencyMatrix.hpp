/**
 * Copyright(C) 2021 Supdrewin <https://github.com/supdrewin>
 * AdjacencyMatrix.hpp is part of Adjacency Matrix Example.
 * The Adjacency Matrix Example is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * The Adjacency Matrix Example is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License along
 * with this program.If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __adjacency_matrix_hpp
#define __adjacency_matrix_hpp 1

#include <iomanip>

#include "CompressedMatrix.hpp"

template <int max_vertex_number>
class adjacency_matrix
    : public compressed_matrix<int, max_vertex_number, max_vertex_number> {
protected:
  std::string vertices;
  int vertices_number;

public:
  adjacency_matrix() : vertices(), vertices_number(0) {}
  adjacency_matrix(std::string vertices) {
    this->vertices = vertices;
    this->set_vertices_number();
  }
  virtual ~adjacency_matrix() {}

  //----------------- vertices number ----------------------------//
  void set_vertices_number() { this->vertices_number = this->vertices.size(); }
  int get_vertices_number() { return this->vertices_number; }

  void print_vertices_number() {
    std::cout << _control_character("32;1m") "The number of vertices: "
              << _control_character("0;35m") << this->vertices_number
              << std::endl;
  }
  //----------------- vertices number ----------------------------//

  //-------------------- edges number ----------------------------//
  int edges_number() { return this->get_size(); }

  void print_edges_number() {
    std::cout << _control_character("32;1m") "The number of edges: "
              << _control_character("0;35m") << this->edges_number()
              << std::endl;
  }
  //-------------------- edges number ----------------------------//

  //-------------------------- vertex ----------------------------//
  bool add_vertex(char vertex) {
    for (auto v : this->vertices)
      if (v == vertex) {
        std::cout << _control_character("31;1m") << __PRETTY_FUNCTION__
                  << ": Warning for existing vertex!" << std::endl;
        return false;
      }
    this->vertices += vertex;
    this->set_vertices_number();
    return true;
  }

  void delete_vertex(int index) {
    this->vertices.erase(index, 1);
    this->set_vertices_number();
    this->trim_edges_of_vertex(index);
  }
  void delete_vertex(char vertex) {
    this->delete_vertex(this->vertices.find_first_of(vertex));
  }
  //-------------------------- vertex ----------------------------//

  //-------------------------- edge ------------------------------//
  bool add_edge(int head, int end, int weight) {
    return this->add(head, end, weight);
  }

  bool delete_edge(int index) { return this->erase(index); }
  bool delete_edge(int head, int end) { return this->pos_erase(head, end); }

  void trim_edges_of_vertex(int vertex) {
    for (int i = 0; i < this->get_size(); ++i)
      if (this->list[i].line == vertex or //
          this->list[i].culomn == vertex)
        this->erase(i--);
      else {
        if (this->list[i].line > vertex)
          this->list[i].line--;
        if (this->list[i].culomn > vertex)
          this->list[i].culomn--;
      }
  }
  //-------------------------- edge ------------------------------//

  void print_matrix() {
    std::cout << _control_character("32;1m") "Now print this adjacency matrix:"
              << _control_character("0;35m") << std::endl;
    for (int i = 0, k = 0; i < this->get_vertices_number(); ++i) {
      std::cout << vertices[i];
      for (int j = 0; j < this->get_vertices_number(); ++j)
        std::cout << std::setw(6)
                  << ((this->list[k].line == i and //
                       this->list[k].culomn == j)
                          ? this->list[k++].data
                          : (i == j ? 0 : -1));
      std::cout << std::endl;
    }
  }
  void print() {
    this->print_vertices_number();
    this->print_edges_number();
    this->print_matrix();
  }
};

#endif // !__adjacency_matrix_hpp
