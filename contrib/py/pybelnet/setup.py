from setuptools import setup, find_packages



setup(
  name="pybelnet",
  version="0.0.1",
  license="ZLIB",
  author="jeff",
  author_email="jeff@i2p.rocks",
  description="belnet python bindings",
  url="https://github.com/beldex-coin/beldex-network",
  install_requires=["pysodium", "requests", "python-dateutil"],
  packages=find_packages())