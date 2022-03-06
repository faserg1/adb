# Awesome Discord Bot

Or just simply — ADB. It's a library to build a bot on C++.
And yes, currently in development.

# What can this library do?

Hm...

[] Messages - receiving and sending... but not editing and removing =( SAD
[] Inegrations - some of them.
[] Reactions - well, you can create them!
[] Voice - in dev. Soon will be added Opus & libsodium decoding/encoding.

And much more things in plans, with logging and error handling (yup, there is no error handling yet)

# Wanna test?

Good! You need cmake and vcpkg.
How to build? Well...

    cmake . -DCMAKE_TOOLCHAIN_FILE:STRING=path/to/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=your-target-triplet
    cmake --build .

Now library will be in build folder. And don't forget libadb/include folder!

# Secrets

You can create cfg/secrets folder with secrets and id's localy. Folder ignored by git.
Or, you can use env vars.
For more info, check cmake/secrets.cmake.

And, if you want to change secrets programaticly, use `adb::cfg::Secrets`