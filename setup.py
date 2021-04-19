from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

__version__ = "1.0.0"

ext_modules = [
    Pybind11Extension(f"PyHex.Hex{i}", ["src/pyhex.cpp"], define_macros=[
        ('BOARD_DIM', i),
        ('PYHEX_NAME', f"Hex{i}")
    ])
    for i in range(1, 51, 2)
]

setup(
    name="PyHex",
    version=__version__,
    author="Ole-Christoffer Granmo, Per-Arne Andersen",
    author_email="per.andersen@uia.no",
    url="https://github.com/cair/hex-ai",
    description="A hex simulator written in C with python bindings.",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
