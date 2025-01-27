// plan.cc
#include "plan.h"

Plan::Plan(const std::string& name, const std::string& description)
    : name_(name), description_(description) {}

void Plan::add_chapter_pointer(const ChapterPointer& chapter_pointer) {
    chapter_pointers_.push_back(chapter_pointer);
}

const std::vector<ChapterPointer>& Plan::get_chapter_pointers() const {
    return chapter_pointers_;
}

const std::string& Plan::get_name() const {
    return name_;
}

const std::string& Plan::get_description() const {
    return description_;
}
