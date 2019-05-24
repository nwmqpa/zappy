#!/usr/bin/env python3
"""Entrypoint for the integration tester application."""
import sys
import os
import json
import subprocess
import typing


def get_test_output(test, to_get) -> typing.Optional[str]:
    """Get the test output to_get, whether is a file or not."""
    if to_get not in test:
        return None
    if test[to_get]["is_file"]:
        with open(test[to_get]["value"], "r") as rF:
            return rF.read()
    else:
        return test[to_get]["value"]


def print_diff(stdout, stderr, code, test) -> bool:
    """Print the diff between tests, or if the test passed."""
    has_pass = True
    for to_get, output in zip(["stdout", "stderr"], [stdout, stderr]):
        test_output = get_test_output(test, to_get)
        if test_output is not None and test_output != output:
            print("\033[1;97mExpected on \033[1;94m{}\033[1;97m:\n\033[1;92m{}\033[0m".format(
                to_get.upper(),
                test_output
            ))
            print("\033[1;97mGot on \033[1;94m{}\033[1;97m:\n\033[1;91m{}\033[0m".format(
                to_get.upper(),
                output
            ))
            has_pass = False
    if "error_code" in test:
        if code != test["error_code"]:
            print("\033[1;97mExpected code: \033[1;92m{}\033[1;97m but got \033[1;91m{}\033[0m".format(
                test["error_code"],
                code
            ))
            has_pass = False
    if has_pass:
        print("\033[1;92mPASSED\033[0m")
    else:
        print("\033[1;91mERROR\033[0m")
    return has_pass

def execute_test(test) -> bool:
    """Execute test."""
    print("\033[1;97mExecuting \033[1;96m{}\033[0m".format(test["name"]))
    proc = subprocess.Popen(test["run"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = proc.communicate()
    code = proc.returncode
    return print_diff(stdout.decode(), stderr.decode(), code, test)


class Application(object):
    """Main object for the integration tester application."""

    def __init__(self) -> None:
        """
        Initialize the object.

        :rtype: None
        """
        pass

    def print_usage(self):
        """
        Display usage and exit the program.

        :rtype: None
        """
        print("USAGE")
        print("\t./integration_tester directory|file")
        print("")
        print("DESCRIPTION")
        print("\tdirectory|file file(s) used to test the integration.")
        sys.exit(0)

    def exit_on_error(self, message: str, exit_code: int) -> None:
        """
        Display error and exit the program.

        :param message: Message displayed before exiting.
        :type message: str
        :param exit_code: Exit code used to exit.
        :type exit_code: int
        :rtype: None
        """
        sys.stderr.write("{0}: {1} ({2})\n".format("integration_tester", message, exit_code))
        sys.exit(exit_code)

    def parse_args(self) -> None:
        """
        Parse the arguments given.

        :rtype: None
        """
        if (len(sys.argv) == 2 and sys.argv[1] in ["-h", "--help"]):
            self.print_usage()
        try:
            if not os.path.exists(sys.argv[1]):
                self.exit_on_error("Path does not exists.")
            self.tests = []
            if os.path.isfile(sys.argv[1]):
                with open(sys.argv[1], 'r') as file:
                    tests = json.loads(file.read())
                    for test in tests:
                        self.tests.append(test)
            elif os.path.isdir(sys.argv[1]):
                for file_path in os.scandir(sys.argv[1]):
                    if ".json" not in file_path.path:
                        continue
                    with open(file_path.path, "r") as file:
                        tests = json.loads(file.read())
                        for test in tests:
                            self.tests.append(test)
        except IndexError:
            raise Exception("No second argument.")

    def execute_tests(self) -> bool:
        """
        Execute all tests.

        :rtype: None
        """
        tests = [execute_test(test) for test in self.tests]
        passed = len(list(filter(lambda x: x, tests)))
        if passed / len(tests) <= 0.25:
            sys.stdout.write("\033[1;91m")
        elif passed / len(tests) <= 0.50:
            sys.stdout.write("\033[1;93m")
        elif passed / len(tests) <= 0.75:
            sys.stdout.write("\033[1;94m")
        elif passed / len(tests) < 1:
            sys.stdout.write("\033[1;96m")
        if passed / len(tests) == 1:
            sys.stdout.write("\033[1;92m")
        sys.stdout.write("PASSED [{}/{}]".format(passed, len(tests)))
        print("\033[0m")
        return passed / len(tests) == 1


    def run(self) -> None:
        """
        Run the application.

        :rtype: None
        """
        try:
            self.parse_args()
        except Exception as e:
            self.exit_on_error(str(e), 1)
        return 0 if self.execute_tests() == 1 else 1


if __name__ == "__main__":
    app = Application()
    sys.exit(app.run())

