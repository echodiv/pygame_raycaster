from distutils.core import setup, Extension


def main():
    setup(name="raycaster",
          version="0.0.1",
          description="LIbrary for fake 3d games with pygame",
          author="Sergey Batalov",
          author_email="echodiv@outlook.com",
          ext_modules=[Extension("raycaster", ["raycaster.cpp"])])


if __name__ == "__main__":
    main()
