from distutils.core import setup
setup(name='tstspendfrom',
      version='1.0',
      description='Command-line utility for Testcoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@Testcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
