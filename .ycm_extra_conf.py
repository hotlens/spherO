import subprocess

p = subprocess.Popen("pkg-config --cflags gtkmm-2.4 libunicapgtk", stdout=subprocess.PIPE,
                     shell=True)
cflags, err = p.communicate()

flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-std=c++11',
    '-Iinclude',
]
flags += cflags.split(" ")

def FlagsForFile(filename):
    return {
        'flags': flags,
        'do_cache': True
    }
