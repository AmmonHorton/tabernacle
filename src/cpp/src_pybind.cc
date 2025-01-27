// src_pybind.cc
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "view.h"
#include "tab.h"
#include "plan.h"
#include "chapter_pointer.h"

namespace py = pybind11;

PYBIND11_MODULE(bible_bindings, m) {
    py::class_<ChapterPointer>(m, "ChapterPointer")
        .def(py::init<const std::string&, size_t, size_t, const std::string*>())
        .def_readonly("chapter_name", &ChapterPointer::chapter_name_)
        .def_readonly("start_index", &ChapterPointer::start_index_)
        .def_readonly("stop_index", &ChapterPointer::stop_index_)
        .def_readonly("text_memory", &ChapterPointer::text_memory_);

    py::class_<View, std::shared_ptr<View>>(m, "View")
        .def(py::init<const ChapterPointer&>())
        .def("set_chapter_before", &View::set_chapter_before)
        .def("set_chapter_after", &View::set_chapter_after)
        .def("add_to_history", &View::add_to_history)
        .def("get_chapter_before", &View::get_chapter_before)
        .def("get_chapter_after", &View::get_chapter_after)
        .def("get_previous_from_history", &View::get_previous_from_history)
        .def("get_chapter_pointer", &View::get_chapter_pointer);

    py::class_<Plan, std::shared_ptr<Plan>>(m, "Plan")
        .def(py::init<const std::string&, const std::string&>())
        .def("add_chapter_pointer", &Plan::add_chapter_pointer)
        .def("get_chapter_pointers", &Plan::get_chapter_pointers)
        .def("get_name", &Plan::get_name)
        .def("get_description", &Plan::get_description);

    py::class_<Tab, std::shared_ptr<Tab>>(m, "Tab")
        .def(py::init<const std::string&>())
        .def("set_plan", &Tab::set_plan)
        .def("get_plan", &Tab::get_plan)
        .def("set_current_view", &Tab::set_current_view)
        .def("get_current_view", &Tab::get_current_view);
}
