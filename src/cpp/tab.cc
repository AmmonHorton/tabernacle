
// tab.cc
#include "tab.h"

Tab::Tab(const std::string& name) : name_(name), plan_(nullptr), current_view_(nullptr) {}

void Tab::set_plan(std::shared_ptr<Plan> plan) {
    plan_ = plan;
}

std::shared_ptr<Plan> Tab::get_plan() const {
    return plan_;
}

void Tab::set_current_view(std::shared_ptr<View> view) {
    current_view_ = view;
}

std::shared_ptr<View> Tab::get_current_view() const {
    return current_view_;
}
