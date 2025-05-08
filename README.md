# AutoPR

## What is this?
A tool that automates GitHub pull requests. If you have any questions you can contact me over Discord, my username is valky5.

## Requirements
- https://git-scm.com/
- https://cli.github.com/

## How to Use
1. Compile and build the executable
2. Place the exe in root of a git project folder
3. Run the exe
4. Manually create some commits (but do not push)
5. Use the exe to create and merge a pull request for those commits

## Known Issues
- `load_option` cannot find key if it does not exist in config. Key does not exist in config because default config is only generated if config file does not exist. The solution is to write a default key to the config if `load_option` fails to find the key. See the TODO comment in `load_option` for where this should be implemented.

## Todo
- Create default option if `load_option` cannot find the option in the config. This will require creating a new Dictionary type so we can easily store and look up the default_options.
- Add option to auto create PR title based on the message in the latest commit
- Change "(3) Go Back" navigation prompts to "(x) Go Back" (so user knows it will always be 'x' to go back)
- Change "Merge Type (squash)" option to be like the "PR Description Prompt (yes)" so it will cycle between the 3 choices (merge, rebase, squash)
- Optimize and review `options.c` code (it works but it is a mess)
- Add option to prevent deletion of branches (and if this is the case prompt the user to name their branches)