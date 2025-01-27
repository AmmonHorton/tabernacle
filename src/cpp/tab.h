// tab.h
#ifndef TAB_H
#define TAB_H

#include <memory>
#include <string>
#include "plan.h"
#include "view.h"

class Tab {
public:
    Tab(const std::string& name);

    void set_plan(std::shared_ptr<Plan> plan);
    std::shared_ptr<Plan> get_plan() const;

    void set_current_view(std::shared_ptr<View> view);
    std::shared_ptr<View> get_current_view() const;

private:
    std::string name_;
    std::shared_ptr<Plan> plan_;
    std::shared_ptr<View> current_view_;
};

#endif // TAB_H
