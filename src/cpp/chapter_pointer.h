// chapter_pointer.h
#ifndef CHAPTER_POINTER_H
#define CHAPTER_POINTER_H

#include <string>

struct ChapterPointer {
    std::string chapter_name_;
    size_t start_index_;
    size_t stop_index_;
    const std::string* text_memory_;

    ChapterPointer(const std::string& chapter_name, size_t start, size_t stop, const std::string* memory)
        : chapter_name_(chapter_name), start_index_(start), stop_index_(stop), text_memory_(memory) {}
};

#endif // CHAPTER_POINTER_H
