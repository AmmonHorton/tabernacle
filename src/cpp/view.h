// view.h
#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include <stack>
#include "chapter_pointer.h"

class View {
public:
    View(const ChapterPointer& chapter_pointer);

    void set_chapter_before(std::shared_ptr<View> before);
    void set_chapter_after(std::shared_ptr<View> after);
    void add_to_history(std::shared_ptr<View> previous);

    std::shared_ptr<View> get_chapter_before() const;
    std::shared_ptr<View> get_chapter_after() const;
    std::shared_ptr<View> get_previous_from_history();
    const ChapterPointer& get_chapter_pointer() const;

private:
    ChapterPointer chapter_pointer_;
    std::shared_ptr<View> chapter_before_;
    std::shared_ptr<View> chapter_after_;
    std::stack<std::shared_ptr<View>> history_;
};

#endif // VIEW_H
