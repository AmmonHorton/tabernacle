# Coding Standard for Tabernacle

## General Guidelines
- Code should be clean, maintainable, and consistent.
- Use meaningful names for variables, functions, and classes.

## Naming Conventions
- **Classes**: UpperCamelCase (e.g., `View`, `Tab`).
- **Functions and Variables**: snake_case (e.g., `set_chapter_before`, `chapter_name_`).
- **Member Variables**: Use trailing underscores (e.g., `chapter_name_`).

## Formatting Rules
- Follow Google C++ style for C++ files.
- Python files should be formatted using Black with a line length of 88.
- Include header guards in all header files.

## Best Practices
- Write modular, reusable code.
- Avoid large functions; break them into smaller, focused functions.
- Use `const` wherever possible.
- Prefer smart pointers (`std::shared_ptr`, `std::unique_ptr`) over raw pointers.
- Use STL containers (e.g., `std::vector`, `std::map`) for data storage.

## Documentation
- Use Doxygen-style comments for all classes and functions.
- Add comments for complex or non-obvious logic.

## Testing
- Write unit tests for each class and major function.
- Use `pytest` for Python tests and `Google Test` for C++ tests.