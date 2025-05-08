# AutoPR

## What is this?
A tool that automates GitHub pull requests. For GitHub repo owners who are tired of manually setting up pull requests.

If you have any questions you can contact me over Discord, my username is valky5.

With the default config values, this is what this tool is automating for you.
```
git checkout -b __new_feature
git push --set-upstream origin __new_feature

gh pr create --base main --head __new_feature --title \"title\" --body \"desc\"
gh pr merge --merge_type

git checkout main
git branch -d __new_feature
git push origin --delete __new_feature

git fetch origin
git reset --hard origin/main
```

## Requirements
- Windows 64 Bit (currently not supported for Mac or Linux)
- https://git-scm.com/
- https://cli.github.com/

## How to Use
1. Compile and build the executable
2. Place the exe in root of a git project folder
3. Run the exe
4. Manually create some commits (but do not push)
5. Use the exe to create and merge a pull request for those commits

## Options
- [x] Set merge type
- [x] Disable PR description prompt
- [ ] Set PR title to latest commit message (will disable title prompt)
- [ ] Do not delete feature branch
- [ ] Do not merge pull request

## Todo
- Change "(3) Go Back" navigation prompts to "(x) Go Back" (so user knows it will always be 'x' to go back)
- Change "Merge Type (squash)" option to be like the "PR Description Prompt (yes)" so it will cycle between the 3 choices (merge, rebase, squash)
- Optimize and review `options.c` code (it works but it is a mess)
