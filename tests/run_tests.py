"""Test driver for the grade book program.

Runs the program once per file in tests/inputs (in name order), feeding the file as keyboard input. All runs share one working folder, so the Grades.dat saved by one run is loaded by the next, like running the program several times by hand. After each run, Grades.dat, Grades.out, Grades.trn and the screen output are copied to test_runs/<run name>/, since the program rewrites them every run.

Each run's Grades files are then compared with the known-good copies in tests/expected/<run name>/, and the run passes if they match.
After checking a deliberate change by hand, run with --update to save the new output as the expected output.

usage: python tests/run_tests.py [--update] [path/to/Program4]
"""
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
INPUTS = ROOT / "tests" / "inputs"
EXPECTED = ROOT / "tests" / "expected"
OUT = ROOT / "test_runs"
WORK = OUT / "work"
TIME_LIMIT = 10  # seconds per run
SAVED_FILES = ["Grades.dat", "Grades.out", "Grades.trn", "screen.txt"]
CHECKED_FILES = ["Grades.dat", "Grades.out", "Grades.trn"]  # screen.txt is not compared
EXE_CANDIDATES = ["build/Debug/Program4.exe", "build/Program4.exe", "build/Program4"]


def find_program(args):
    if args:
        exe = Path(args[0]).resolve()
        return exe if exe.is_file() else None
    for candidate in EXE_CANDIDATES:
        exe = ROOT / candidate
        if exe.is_file():
            return exe
    return None


def read_lines(path):
    # text mode, so Windows and Unix line endings compare equal
    return path.read_text().splitlines() if path.exists() else None


def compare_run(name):
    """Return a list of problems, empty if this run matches the expected output."""
    problems = []
    for file_name in CHECKED_FILES:
        expected = read_lines(EXPECTED / name / file_name)
        actual = read_lines(OUT / name / file_name)
        if expected == actual:
            continue
        if expected is None or actual is None:
            problems.append(f"{file_name}: {'no expected copy' if expected is None else 'not written'}")
            continue
        # report the first line that differs
        for i in range(max(len(expected), len(actual))):
            want = expected[i] if i < len(expected) else "(end of file)"
            got = actual[i] if i < len(actual) else "(end of file)"
            if want != got:
                problems.append(f"{file_name} line {i + 1}:\n    expected: {want}\n    got:      {got}")
                break
    return problems


def main():
    args = sys.argv[1:]
    update = "--update" in args
    args = [arg for arg in args if arg != "--update"]

    exe = find_program(args)
    if exe is None:
        print("Program not found. Build it first with: cmake --build build")
        return 1

    shutil.rmtree(OUT, ignore_errors=True)
    if any(path.is_file() and path.name != "desktop.ini" for path in OUT.rglob("*")):
        print(f"Could not clear {OUT}. Close anything using it and try again.")
        return 1
    WORK.mkdir(parents=True, exist_ok=True)

    all_passed = True
    for input_file in sorted(INPUTS.glob("*.txt")):
        name = input_file.stem
        with open(input_file) as stdin, open(WORK / "screen.txt", "w") as stdout:
            try:
                subprocess.run([str(exe)], stdin=stdin, stdout=stdout, cwd=WORK,
                               timeout=TIME_LIMIT)
            except subprocess.TimeoutExpired:
                print(f"{name:<28} FAIL\n  did not finish in {TIME_LIMIT}s (does the input end with Q?)")
                all_passed = False

        # keep a copy of this run's files before the next run rewrites them
        run_dir = OUT / name
        run_dir.mkdir(exist_ok=True)
        for file_name in SAVED_FILES:
            if (WORK / file_name).exists():
                shutil.copy(WORK / file_name, run_dir)

        if update:
            (EXPECTED / name).mkdir(parents=True, exist_ok=True)
            for file_name in CHECKED_FILES:
                if (run_dir / file_name).exists():
                    shutil.copy(run_dir / file_name, EXPECTED / name)
            print(f"{name:<28} expected output updated")
            continue

        problems = compare_run(name)
        print(f"{name:<28} {'PASS' if not problems else 'FAIL'}")
        for problem in problems:
            print("  " + problem)
        if problems:
            all_passed = False

    (WORK / "screen.txt").unlink(missing_ok=True)
    print("Output files for each run are in test_runs/.")
    return 0 if all_passed else 1


if __name__ == "__main__":
    sys.exit(main())
