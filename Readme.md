# CS 210 – Corner Grocer Item Tracker
**Portfolio Project | C++ | Visual Studio**

---

**Summarize the project and what problem it was solving.**

The Corner Grocer Item Tracker is a C++ console application that analyzes a grocery store's daily purchase log. The store collected a plain-text record of every item sold but had no way to query or summarize that data. This program reads the input file, builds a frequency map of every item purchased, and gives the user an interactive menu to search for a specific item, view a sorted frequency list, generate a text histogram, and review summary statistics. It also writes an automatic backup of the frequency data at startup.

**What did you do particularly well?**

I'm most proud of the separation of concerns across the three source files. `FileManager` handles all file I/O — reading, sanitizing, writing, and validating — while `GroceryTracker` owns all data logic including frequency lookups, sorting, and formatted output. The `main` file acts only as a thin controller. I also put real effort into input validation: the `getValidatedInt()` helper rejects non-numeric and out-of-range input, clears the stream properly, and loops until it gets a valid response.

**Where could you enhance your code?**

A few improvements would make this more robust. Accepting the input filename as a command-line argument instead of hardcoding it would make the program more flexible without touching the source. The histogram also scales linearly with raw counts, which would become unreadable for very high-frequency items — a normalized scale would be a better long-term solution. Adding unit tests for `GroceryTracker` would also help catch regressions quickly.

**Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?**

The trickiest part was the `FileManager::sanitizeLine()` method. I worked through several bugs: a misspelled method name, `std::transform` written as a constructor call instead of a function call, and invalid character access syntax (`trimmed{0}` instead of `trimmed[0]`). I leaned heavily on cppreference.com and traced the logic manually with test strings before it behaved correctly. That habit of reading official documentation and stepping through execution mentally is something I plan to carry into every project going forward.

**What skills from this project will be particularly transferable to other projects or course work?**

The class design pattern here — separating I/O from business logic — applies to nearly any project regardless of language. Using `std::map` for frequency counting, writing comparator lambdas for `std::sort`, and handling stream errors gracefully are foundational C++ skills that will appear again in systems programming and backend development. The input validation loop is also a pattern I'll reuse anywhere a program needs to accept user input safely.

**How did you make this program maintainable, readable, and adaptable?**

Every function has a single clear purpose and a plain-language comment describing it. Meaningful names throughout — `sanitizeLine`, `getFrequency`, `printHistogram`, `chooseSortMode` — make the code read almost like a description of what it's doing. The `SortMode` enum makes sorting options explicit rather than relying on magic integers. The clean split between `FileManager` and `GroceryTracker` means either class can be extended or replaced without affecting the other, and file name constants are declared in one place so they're easy to update.
