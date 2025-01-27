// plan.h
#ifndef PLAN_H
#define PLAN_H

#include <string>
#include <vector>
#include <memory>
#include "chapter_pointer.h"

class Plan {
public:
    Plan(const std::string& name, const std::string& description);

    void add_chapter_pointer(const ChapterPointer& chapter_pointer);
    const std::vector<ChapterPointer>& get_chapter_pointers() const;
    const std::string& get_name() const;
    const std::string& get_description() const;

private:
    std::string name_;
    std::string description_;
    std::vector<ChapterPointer> chapter_pointers_;
};

#endif // PLAN_H
