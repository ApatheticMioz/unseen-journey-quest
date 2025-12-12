# Contributing to Unseen Journey Quest

Thank you for your interest in contributing to this project!

## How to Contribute

### Reporting Issues

1. Check if the issue already exists in the [Issues](../../issues) section
2. If not, create a new issue with:
   - A clear, descriptive title
   - Steps to reproduce the problem
   - Expected vs actual behavior
   - Your environment (OS, compiler version)

### Submitting Changes

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Make your changes following the code style guidelines below
4. Test your changes thoroughly
5. Commit with clear, descriptive messages
6. Push to your fork and submit a Pull Request

### Code Style Guidelines

- Use 4-space indentation (no tabs)
- Follow existing naming conventions (camelCase for variables/functions, PascalCase for classes)
- Keep lines under 120 characters
- Add comments for complex logic
- Ensure code compiles without warnings

### Building and Testing

```bash
# Linux/Mac
g++ -o unseen_journey_quest main.cpp -lncurses
./unseen_journey_quest

# Windows (with PDCurses)
g++ -o unseen_journey_quest.exe main.cpp -lpdcurses
```

### Pull Request Guidelines

- Reference any related issues in your PR description
- Provide a clear description of what changes you made and why
- Ensure your code builds and runs correctly
- Keep PRs focused on a single change

## Questions?

Feel free to open an issue for any questions about contributing.
