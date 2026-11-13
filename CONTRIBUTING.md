# Contributing

This follows the quality-management process in our Initial Project Plan:
every change is reviewed before it reaches `main`.

## Workflow

1. Update `main`: `git switch main && git pull`
2. Create a branch for your change: `git switch -c <branch-name>`

   Name it in the format `<area>/<short-description>`, where area is
   `firmware`, `hardware`, `enclosure` or `docs`, e.g. `firmware/lcd-driver`.
3. Commit in small important changes, and briefly explain what you've done in each commit
   message. i.e. `git commit -m "fix: fixed a bug on line X"` (remember to do `"git add ."` beforehand.)
4. Push the branch: `git push -u origin <branch-name>`
5. Open a pull request into `main` on GitHub and fill in the template I made.
6. Get at least one approving review, then merge. `main` has branch protection so it has to have a reviewer.

## Reviews

| Area       | Reviewer                                        |
| ---------- | ----------------------------------------------- |
| Firmware   | Bradley (Embedded Programming Leader); Bradley's own code is reviewed by another member |
| Hardware   | Juncheng (Hardware Leader)                      |
| Enclosure  | Raisa (Mechanical Design Leader)                |

Reviewers should check that the change builds, and is readable and commented.
Leave comments on GitHub; the author resolves them.

## Line endings

`.gitattributes` normalises line endings, so Windows and Linux can work
on the same files.
