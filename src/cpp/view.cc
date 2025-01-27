// view.cc
#include "view.h"

View::View(const ChapterPointer& chapter_pointer) : chapter_pointer_(chapter_pointer), chapter_before_(nullptr), chapter_after_(nullptr) {}

void View::set_chapter_before(std::shared_ptr<View> before) {
    chapter_before_ = before;
}

void View::set_chapter_after(std::shared_ptr<View> after) {
    chapter_after_ = after;
}

void View::add_to_history(std::shared_ptr<View> previous) {
    history_.push(previous);
}

std::shared_ptr<View> View::get_chapter_before() const {
    return chapter_before_;
}

std::shared_ptr<View> View::get_chapter_after() const {
    return chapter_after_;
}

std::shared_ptr<View> View::get_previous_from_history() {
    if (!history_.empty()) {
        auto previous = history_.top();
        history_.pop();
        return previous;
    }
    return nullptr;
}
