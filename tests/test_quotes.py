import subprocess
import unittest

class QuoteErrorTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        subprocess.run(["make"], check=True)

    def run_shell(self, commands: str):
        proc = subprocess.run(["./minishell"], input=commands.encode(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return proc.stdout.decode(), proc.stderr.decode(), proc.returncode

    def test_unmatched_double_quote(self):
        out, err, code = self.run_shell('echo "foo\nexit\n')
        self.assertIn("unexpected EOF while looking for matching", err)
        self.assertEqual(2, code)

    def test_unmatched_single_quote(self):
        out, err, code = self.run_shell("echo 'bar\nexit\n")
        self.assertIn("unexpected EOF while looking for matching", err)
        self.assertEqual(2, code)

if __name__ == '__main__':
    unittest.main()
