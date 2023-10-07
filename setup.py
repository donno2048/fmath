from setuptools import setup, Extension
from sysconfig import get_config_var

setup(
    name='fmath',
    version='1.0.2',
    license='MIT',
    author='Elisha Hollander',
    author_email='just4now666666@gmail.com',
    description='A library for Python for fast math on floats',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    url='https://github.com/donno2048/fmath',
    project_urls={
        'Documentation': 'https://github.com/donno2048/fmath#readme',
        'Bug Reports': 'https://github.com/donno2048/fmath/issues',
        'Source Code': 'https://github.com/donno2048/fmath',
    },
    python_requires='>=3.0',
    classifiers=['Programming Language :: Python :: 3'],
    ext_modules=[Extension('fmath', ['pyfmath.c'], extra_compile_args=((get_config_var('CFLAGS') or '') + " -O0 -ffast-math -march=native").split())],
    zip_safe=False,
)
