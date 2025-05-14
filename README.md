# AutoPR

## What is this?
A tool that automates GitHub pull requests. For GitHub repo owners who are tired of manually setting up pull requests.

With the default config values, this is what this tool is automating for you.
```
git checkout -b __new_feature
git push --set-upstream origin __new_feature

gh pr create --base main --head __new_feature --title \"TITLE\" --body \"DESCRIPTION\"
gh pr merge --MERGE_TYPE

git checkout main
git branch -d __new_feature
git push origin --delete __new_feature

git fetch origin
git reset --hard origin/main
```

I realize after making this that this handles a very specific scenario but you know what hey I had fun doing it because I got more experience learning C.

## Requirements
- Windows 64 Bit (currently not supported for Mac or Linux)
- https://git-scm.com/
- https://cli.github.com/

## How to Use
1. Download the [latest release](https://github.com/valkyrienyanko/AutoPR/releases/latest)
2. Run the exe from anywhere on your pc
3. Navigate to options and set your repository path
4. Manually create some commits (but do not push)
5. Use the exe to create and merge a pull request for those commits (make sure you are up-to-date with main branch before you do this)

## Options
- [x] Set merge type
- [x] Disable title prompt
- [x] Disable description prompt
- [x] Disable delete feature branch
- [x] Disable merge pull request

## Known Issues
- If PR title (or commit message if this is being used as PR title) contains any special characters like '&', the branch will fail to be created and the program will end
- If the user puts in a malformed repository path, the program may crash
