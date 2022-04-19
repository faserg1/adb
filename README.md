# Awesome Discord Bot

Or just simply — ADB. It's a library to build a bot on C++.
And yes, currently in development.

What can this library do? Take a look at the wiki =)

# Wanna test?

Good! You need cmake and vcpkg.
How to build? Well...

    cmake . -DCMAKE_TOOLCHAIN_FILE:STRING=path/to/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=your-target-triplet
    cmake --build .
    cmake --install .

Now library will be in build folder. And don't forget libadb/include folder!

# Looking for examples?

Check out tests folder =)
Sometimes it updates while I am testing out new features implementations.

# Secrets

**Warning! Secrets API will be modified!**

You can create cfg/secrets folder with secrets and id's localy. Folder ignored by git.
Or, you can use env vars.
For more info, check cmake/secrets.cmake.

And, if you want to change secrets programaticly, use `adb::cfg::Secrets`