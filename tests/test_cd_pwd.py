import os
import subprocess
import tempfile
import unittest

class CdPwdTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        subprocess.run(["make"], check=True)

    def run_shell(self, commands: str) -> str:
        proc = subprocess.run(["./minishell"], input=commands.encode(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return proc.stdout.decode()

    def test_cd_updates_pwd_vars(self):
        with tempfile.TemporaryDirectory() as tmp:
            cmds = f"pwd\ncd {tmp}\npwd\necho $PWD\necho $OLDPWD\nexit\n"
            raw = self.run_shell(cmds).splitlines()
            out = [l for l in raw if not l.startswith('\x1b')]
            self.assertGreaterEqual(len(out), 4)
            first_pwd = out[0]
            new_pwd = out[1]
            env_pwd = out[2]
            env_oldpwd = out[3]
            self.assertEqual(new_pwd, env_pwd)
            self.assertEqual(first_pwd, env_oldpwd)

if __name__ == '__main__':
    unittest.main()
