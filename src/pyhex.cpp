// pybind11_wrapper.cpp
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "./hex.c"

#ifndef BOARD_DIM
    #define PYHEX_NAME Hex
#endif

PYBIND11_MODULE(PYHEX_NAME, m) {
    m.doc() = "PyHex, A lightweight hex simulator"; // Optional module docstring

    pybind11::class_<hex_game>(m, "HexGame")
        .def(pybind11::init<>())
        .def_readonly("board", &hex_game::board)
        .def_readonly("moves", &hex_game::moves)
        .def_readonly("connected", &hex_game::connected)
        .def_readonly("open_positions", &hex_game::open_positions)
        .def_readwrite("number_of_open_positions", &hex_game::number_of_open_positions);

    //m.def("neighbors", pybind11::array_t<int>(neighbors));
    m.def("init", &hg_init, "...");
    m.def("connect", &hg_connect, "...");
    m.def("print", &hg_print, "...");
    m.def("winner", &hg_winner, "...");
    m.def("full_board", &hg_full_board, "...");
    m.def("place_piece_randomly", &hg_place_piece_randomly, "...");

}