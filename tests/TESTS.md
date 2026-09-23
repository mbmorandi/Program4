# Test Plan
(requires a built .exe with cmake, then run_tests.py)
Each file in `tests/inputs/` is fed to the program as keyboard input, in order, and each run loads the `Grades.dat` the previous run saved.
A run passes when its `Grades.dat`, `.out` and `.trn` match `tests/expected/<run>/` (copies to print go to `test_runs/<run>/`). After checking a deliberate change by hand, `--update` saves the new output as expected.

| Run | Checks (spec iterations) |
| 1 | Commands before setup; S rejects bad counts, weights not adding to 100, and a second S; A rejects duplicate/invalid IDs; O alphabetical (whole name, any case) and by number; Q saves (1, 2, 4) |
| 2 | Load on startup; P/T/F prompt alphabetically, skip grades over 100, reject a repeat or bad number (2, 3) |
| 3 | Recorded flags survive a restart; C changes a grade, rejects unknown ID/bad type/bad number with one message; G rounds averages; O shows them (3, 4) |
| 4 | S replaces loaded data; P rejected with no programs; G averages tests when there are no programs (4) |
