import os
import subprocess
import unittest

class MinishellTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        subprocess.run(["make"], check=True)

    def run_shell(self, commands: str) -> str:
        proc = subprocess.run(["./minishell"], input=commands.encode(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return proc.stdout.decode()

    def test_echo_home(self):
        output = self.run_shell('echo "$HOME"\nexit\n')
        self.assertIn(os.environ.get("HOME", ""), output)

    def test_pipeline_quotes(self):
        output = self.run_shell('echo "$HOME" | cat\nexit\n')
        self.assertIn(os.environ.get("HOME", ""), output)

    def test_backslash_literal(self):
        output = self.run_shell('echo \\hello\nexit\n')
        self.assertIn('\\hello', output)

if __name__ == '__main__':
    unittest.main()
