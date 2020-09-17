from setuptools import setup, Extension

setup(
    name='hanming',
    ext_modules=[
        Extension('hanming', ['hanming.c']),
    ]
)
